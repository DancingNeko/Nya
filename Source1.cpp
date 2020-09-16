#include<iostream>
using namespace std;

struct step
{
    int n;
    step* next;
};
int originalDimension;
void castPuzzle(int a[], int target, int dim);
void moveSliderBR(int a[], int dim, int target, int& sliderLoc);
void moveTargetRight(int a[], int& slider, int targetLoc, int w, int h);
int checkLocation(int a[], int target, int size);
void moveTarget(int a[], int target, int w, int h);
void autoComplete(int a[], int dim);
bool moveSlider(int a[], int& slider, int dir, int w, int h);
void UREdgeProcessing(int a[], int target, int dim);
void moveTargetDown(int a[], int& sliderLoc, int targetLoc, int w, int h);
void twoXtwoSolving(int a[]);
int* convertPuzzle(int a[], int dim);
bool checkComplete(int a[]);
step* recordStep(int dir, step* add);
step* head = new step;
step* add = head;



bool check_repeat(int* a)
{
    if (*a * *(a + 1) == 2 || *a * *(a + 1) == 12)
    {
        *a = -1;
        *(a + 1) = -1;
        return true;
    }
    return false;
}


int* deleteBlanks(int steps[], int& stepCount)
{
    int* stepsSimplified = new int[stepCount];
    int j = 0;
    int i = 0;
    while (steps[i] == 1 || steps[i] == 2 || steps[i] == 3 || steps[i] == 4 || steps[i] == -1)
    {
        if (steps[i] != -1)
        {
            stepsSimplified[j] = steps[i];
            j++;
        }
        i++;
    }
    delete[] steps;
    return stepsSimplified;
}

void updateStepCount(int* step, int& stepCount)
{
    int i = 0;
    while (step[i] == 4 || step[i] == 3 || step[i] == 2 || step[i] == 1 || step[i] == -1)
    {
        if (step[i] != -1)
            i++;
    }
    stepCount = i;
}

int* simplify(int* steps, int& stepCount)
{
    int i;
    int repeatCount = -1;//randomly assign a value that's not 0
    while (repeatCount != 0)
    {
        i = 0;
        repeatCount = 0;
        while (i < stepCount - 1)
        {
            if (check_repeat(&steps[i]))
                repeatCount++;
            i++;
        }
        steps = deleteBlanks(steps, stepCount);
        updateStepCount(steps, stepCount);
    }
    return steps;
}

step* recordStep(int dir, step* add)//up:1 ;down:2 ;left:3 ;right:4
{
    add->next = new step;
    add = add->next;
    add->n = dir;
    add->next = NULL;
    return add;
}

void LLEdgeProcessing(int a[], int target, int dim)//LOWER LEFT corner processing: put the last piece of puzzle on the left column
{
    int sliderLoc = checkLocation(a, 0, dim * dim);
    int targetLoc = checkLocation(a, target, dim * dim);
    while (sliderLoc % dim != 1)
    {
        if (sliderLoc % dim == 0)
            moveSlider(a, sliderLoc, +1, dim, dim);
        else
            moveSlider(a, sliderLoc, -1, dim, dim);
    }
    targetLoc = checkLocation(a, target, dim * dim);
    if (targetLoc / dim == 1)
        moveTargetDown(a, sliderLoc, targetLoc, dim, dim);
    targetLoc = checkLocation(a, target, dim * dim);
    if (targetLoc % dim == dim - 1)
    {
        while (sliderLoc % dim != targetLoc % dim - 1)
        {
            if (sliderLoc % dim > targetLoc % dim - 1)
                moveSlider(a, sliderLoc, -1, dim, dim);
            else
                moveSlider(a, sliderLoc, +1, dim, dim);
            targetLoc = checkLocation(a, target, dim * dim);
        }
        while (sliderLoc / dim != targetLoc / dim)
        {
            if (sliderLoc / dim > targetLoc / dim)
                moveSlider(a, sliderLoc, -dim, dim, dim);
            else
                moveSlider(a, sliderLoc, +dim, dim, dim);
            targetLoc = checkLocation(a, target, dim * dim);
        }
        if (sliderLoc + 1 == targetLoc)
            moveSlider(a, sliderLoc, +1, dim, dim);
    }
    while (sliderLoc % dim != dim - 1)
        moveSlider(a, sliderLoc, +1, dim, dim);//move slider to the right side
    while (sliderLoc / dim != 0)
        moveSlider(a, sliderLoc, -dim, dim, dim);//move slider to the proper location(upper right cornor)
    while (sliderLoc % dim != 0)
        moveSlider(a, sliderLoc, -1, dim, dim);//move slider to the upper left cornor
    int i = 0;
    while (i < dim - 2)
    {
        moveSlider(a, sliderLoc, +dim, dim, dim);
        i++;
    }//move slider down
    targetLoc = checkLocation(a, target, dim * dim);
    while (targetLoc / dim < dim - 2)
    {
        moveTargetDown(a, sliderLoc, targetLoc, dim, dim);
        targetLoc = checkLocation(a, target, dim * dim);
    }
    while (sliderLoc / dim != dim - 1)
        moveSlider(a, sliderLoc, +dim, dim, dim);

    //------------castPuzzle function with some changes----------------//

    targetLoc = checkLocation(a, target, dim * dim);
    int w = dim;//width of cast puzzle
    int h = 2;//height o cast puzzle
    int* b = new int[w * h];//puzzle after cast
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            b[j + i * w] = a[(dim - h + i) * dim + j];
        }
    }
    moveTarget(b, target, w, h);
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            a[(dim - h + i) * dim + j] = b[j + i * w];
        }
    }
    sliderLoc = checkLocation(a, 0, dim * dim);
    delete[] b;

    //-----------end of funciton---------------//

    while (sliderLoc / dim != dim - 1)
        moveSlider(a, sliderLoc, +dim, dim, dim);
    while (sliderLoc % dim != 0)
        moveSlider(a, sliderLoc, -1, dim, dim);//move slider to the lower left corner
    while (sliderLoc / dim != 0)
        moveSlider(a, sliderLoc, -dim, dim, dim);//move slider to the upper right corner
    while (sliderLoc % dim != dim - 1)
        moveSlider(a, sliderLoc, +1, dim, dim);//move slider to the upper right corner
    moveSlider(a, sliderLoc, +dim, dim, dim);
}

void UREdgeProcessing(int a[], int target, int dim)//UPPER RIGHT corner processing: put the last piece of puzzle on the top roll
{
    int sliderLoc = checkLocation(a, 0, dim * dim);
    int targetLoc = checkLocation(a, target, dim * dim);
    while (sliderLoc / dim != 1)
    {
        if (sliderLoc / dim == 0)
            moveSlider(a, sliderLoc, +dim, dim, dim);
        else
            moveSlider(a, sliderLoc, -dim, dim, dim);
    }
    if (targetLoc % dim == 0)
        moveTargetRight(a, sliderLoc, targetLoc, dim, dim);
    while (sliderLoc % dim != 0)
        moveSlider(a, sliderLoc, -1, dim, dim);//move slider to the proper location(left side)
    while (sliderLoc / dim != 0)
        moveSlider(a, sliderLoc, -dim, dim, dim);//move slider to the upper left
    int i = 0;
    while (i < dim - 2)
    {
        moveSlider(a, sliderLoc, +1, dim, dim);
        i++;
    }//move slider to the uppre right
    targetLoc = checkLocation(a, target, dim * dim);
    while (targetLoc % dim < dim - 2)
    {
        moveTargetRight(a, sliderLoc, targetLoc, dim, dim);
        targetLoc = checkLocation(a, target, dim * dim);
    }
    moveSliderBR(a, dim, target, sliderLoc);

    //------------castPuzzle function with some changes----------------//

    targetLoc = checkLocation(a, target, dim * dim);
    int w = 2;//width of cast puzzle
    int h = dim;//height o cast puzzle
    int* b = new int[w * h];//puzzle after cast
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            b[j + i * w] = a[dim - w + j + i * dim];
        }
    }
    moveTarget(b, target, w, h);
    sliderLoc = checkLocation(a, 0, dim * dim);
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            a[dim - w + j + i * dim] = b[j + i * w];
        }
    }
    sliderLoc = checkLocation(a, 0, dim * dim);
    delete[] b;

    //-----------end of funciton---------------//

    while (sliderLoc % dim != dim - 1)
        moveSlider(a, sliderLoc, +1, dim, dim);
    while (sliderLoc / dim != 0)
        moveSlider(a, sliderLoc, -dim, dim, dim);//move slider to the upper right
    while (sliderLoc % dim != 0)
        moveSlider(a, sliderLoc, -1, dim, dim);//move slider to the upper left
    moveSlider(a, sliderLoc, +dim, dim, dim);
}

bool moveSlider(int a[], int& slider, int dir, int w, int h)
{
    if (dir == 1 && slider % w < w - 1)
    {
        int temp = a[slider + dir];
        a[slider + dir] = a[slider];
        a[slider] = temp;
        slider = slider + dir;
        add = recordStep(4, add);
        return true;
    }
    if (dir == -1 && slider % w > 0)
    {
        int temp = a[slider + dir];
        a[slider + dir] = a[slider];
        a[slider] = temp;
        slider = slider + dir;
        add = recordStep(3, add);
        return true;
    }
    if (dir == +w && slider / w < h - 1)
    {
        int temp = a[slider + dir];
        a[slider + dir] = a[slider];
        a[slider] = temp;
        slider = slider + dir;
        add = recordStep(2, add);
        return true;
    }
    if (dir == -w && slider / w > 0)
    {
        int temp = a[slider + dir];
        a[slider + dir] = a[slider];
        a[slider] = temp;
        slider = slider + dir;
        add = recordStep(1, add);
        return true;
    }
    return false;
}

void castPuzzle(int a[], int target, int dim)//target: the one put on the top left
{
    int targetLoc = checkLocation(a, target, dim * dim);
    int sliderLoc = checkLocation(a, 0, dim * dim);
    if (target / dim == 0)
    {
        while (targetLoc % dim < (target % dim) - 1)
        {
            moveTargetRight(a, sliderLoc, targetLoc, dim, dim);
            targetLoc = checkLocation(a, target, dim * dim);
        }
        moveSliderBR(a, dim, target, sliderLoc);
        int w = dim - (target - 1) % dim;//width of cast puzzle
        int h = dim - (target - 1) / dim;//height o cast puzzle
        int* b = new int[w * h];//puzzle after cast
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                b[j + i * w] = a[dim - w + j + i * dim];
            }
        }
        moveTarget(b, target, w, h);
        sliderLoc = checkLocation(a, 0, dim * dim);
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                a[dim - w + j + i * dim] = b[j + i * w];
            }
        }
        delete[] b;
    }
    else
    {
        while (targetLoc / dim < (target - 1) / dim)
        {
            moveTargetDown(a, sliderLoc, targetLoc, dim, dim);
            targetLoc = checkLocation(a, target, dim * dim);
        }
        moveSliderBR(a, dim, target, sliderLoc);
        int w = dim - (target - 1) % dim;//width of cast puzzle
        int h = dim - (target - 1) / dim;//height o cast puzzle
        int* b = new int[w * h];//puzzle after cast
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                b[j + i * w] = a[(dim - h + i) * dim + j];
            }
        }
        moveTarget(b, target, w, h);
        sliderLoc = checkLocation(a, 0, dim * dim);
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                a[(dim - h + i) * dim + j] = b[j + i * w];
            }
        }
        delete[] b;
    }
}

void moveSliderBR(int a[], int dim, int target, int& sliderLoc)//move target to the bottom right
{
    while (sliderLoc % dim != dim - 1)//move slider to the moveable area
    {
        if (a[sliderLoc + 1] != target)
            moveSlider(a, sliderLoc, +1, dim, dim);
        else if (moveSlider(a, sliderLoc, +dim, dim, dim) == true)
            continue;
        else
            moveSlider(a, sliderLoc, -dim, dim, dim);
    }
    while (a[dim * dim - 1] != 0)
        moveSlider(a, sliderLoc, +dim, dim, dim);
}

void moveTargetRight(int a[], int& slider, int targetLoc, int w, int h)//move target right a tile; slider: sliderLoc
{
    while (slider / w != targetLoc / w)//move slider to the target's roll
    {
        if (slider / w > targetLoc / w && slider - w != targetLoc)
            moveSlider(a, slider, -w, w, h);
        if (slider / w > targetLoc / w && slider - w == targetLoc)
            if (moveSlider(a, slider, +1, w, h))
                continue;
            else
                moveSlider(a, slider, -1, w, h);
        if (slider / w < targetLoc / w && slider + w != targetLoc)
            moveSlider(a, slider, +w, w, h);
        if (slider / w < targetLoc / w && slider + w == targetLoc)
            if (moveSlider(a, slider, +1, w, h))
                continue;
            else
                moveSlider(a, slider, -1, w, h);
    }
    while (slider % w != targetLoc % w + 1)//move slider to the right of target
    {
        if (slider % w > targetLoc % w + 1)
            moveSlider(a, slider, -1, w, h);
        else if (slider + 1 != targetLoc)
            moveSlider(a, slider, +1, w, h);
        else if (moveSlider(a, slider, +w, w, h))
            continue;
        else
            moveSlider(a, slider, -w, w, h);
    }
    if (slider / w != targetLoc / w)
    {
        if (slider / w > targetLoc / w)
            moveSlider(a, slider, -w, w, h);
        if (slider / w < targetLoc / w)
            moveSlider(a, slider, +w, w, h);
    }
    if (slider - 1 == targetLoc)
        moveSlider(a, slider, -1, w, h);
}

void moveTargetDown(int a[], int& sliderLoc, int targetLoc, int w, int h)//move target down a tile
{
    while (sliderLoc % w != targetLoc % w)//move slider to the target's column
    {

        if (sliderLoc % w > targetLoc % w && sliderLoc - 1 != targetLoc)
            moveSlider(a, sliderLoc, -1, w, h);
        if (sliderLoc % w > targetLoc % w && sliderLoc - 1 == targetLoc)
            if (moveSlider(a, sliderLoc, +w, w, h))
                continue;
            else
                moveSlider(a, sliderLoc, -w, w, h);
        if (sliderLoc % w < targetLoc % w && sliderLoc + 1 != targetLoc)
            moveSlider(a, sliderLoc, +1, w, h);
        if (sliderLoc % w < targetLoc % w && sliderLoc + 1 == targetLoc)
            if (moveSlider(a, sliderLoc, +w, w, h))
                continue;
            else
                moveSlider(a, sliderLoc, -w, w, h);
    }
    while (sliderLoc / w != targetLoc / w + 1)//move slider below the target
    {
        if (sliderLoc / w > targetLoc / w + 1)
            moveSlider(a, sliderLoc, -w, w, h);
        else if (sliderLoc + w != targetLoc)
            moveSlider(a, sliderLoc, +w, w, h);
        else if (moveSlider(a, sliderLoc, +1, w, h))
            continue;
        else
            moveSlider(a, sliderLoc, -1, w, h);
    }
    if (sliderLoc % w != targetLoc % w)
    {
        if (sliderLoc % w > targetLoc % w)
            moveSlider(a, sliderLoc, -1, w, h);
        if (sliderLoc % w < targetLoc % w)
            moveSlider(a, sliderLoc, +1, w, h);
    }
    if (sliderLoc - w == targetLoc)
        moveSlider(a, sliderLoc, -w, w, h);
}

int checkLocation(int a[], int target, int size)//search target in the size area
{
    for (int i = 0; i < size; i++)
    {
        if (a[i] == target)
            return i;
    }
    return -1;//fail to detect slider's location
}

void moveTarget(int a[], int target, int w, int h)//only works for the puzzle ont the top right; w: width of the moveable area, height: height of the moveable area, target: which number to move
{
    int sliderLoc = checkLocation(a, 0, w * h);
    int targetLoc = checkLocation(a, target, w * h);
    while (targetLoc / w > 0)//move target up
    {
        while (sliderLoc / w != targetLoc / w - 1)
        {
            if (sliderLoc / w > targetLoc / w - 1)
            {
                if (a[sliderLoc - w] != target)
                    moveSlider(a, sliderLoc, -w, w, h);
                else if (moveSlider(a, sliderLoc, +1, w, h))
                    continue;
                else
                    moveSlider(a, sliderLoc, -1, w, h);
            }
            if (sliderLoc / w < targetLoc / w - 1)
                moveSlider(a, sliderLoc, +w, w, h);
        }
        while (sliderLoc % w != targetLoc % w)
        {
            if (sliderLoc % w > targetLoc % w)
                moveSlider(a, sliderLoc, -1, w, h);
            else
                moveSlider(a, sliderLoc, +1, w, h);
        }
        if (a[sliderLoc + w] == target)
            moveSlider(a, sliderLoc, +w, w, h);
        targetLoc = checkLocation(a, target, w * h);
    }
    while (targetLoc % w > 0)//move target left
    {
        while (sliderLoc % w != targetLoc % w - 1)
        {
            if (sliderLoc % w < targetLoc % w - 1)
                moveSlider(a, sliderLoc, +1, w, h);
            if (sliderLoc % w > targetLoc % w - 1)
            {
                if (a[sliderLoc - 1] != target)
                    moveSlider(a, sliderLoc, -1, w, h);
                else if (moveSlider(a, sliderLoc, -w, w, h))
                    continue;
                else
                    moveSlider(a, sliderLoc, +w, w, h);
            }
        }
        while (sliderLoc / w != targetLoc / w)
        {
            if (sliderLoc / w > targetLoc / w)
                moveSlider(a, sliderLoc, -w, w, h);
            else
                moveSlider(a, sliderLoc, +w, w, h);
        }
        if (a[sliderLoc + 1] == target)
            moveSlider(a, sliderLoc, +1, w, h);
        targetLoc = checkLocation(a, target, w * h);
    }
}

int* convertPuzzle(int a[], int dim)//convert puzzle to smaller one: 4*4 -> 3*3
{
    int* b = new int[(dim - 1) * (dim - 1)];
    for (int i = 0; i < dim - 1; i++)
    {
        for (int j = 0; j < dim - 1; j++)
        {
            b[i * (dim - 1) + j] = a[(i + 1) * dim + j + 1];
        }
    }
    for (int i = 0; i < dim - 1; i++)
    {
        for (int j = 0; j < dim - 1; j++)
        {
            if (b[i * (dim - 1) + j] == 0)
                continue;
            int roll = (b[i * (dim - 1) + j] - 1) / dim;//which roll this number locate
            int column = (b[i * (dim - 1) + j] - 1) % dim;
            roll--;
            column--;
            b[i * (dim - 1) + j] = roll * (dim - 1) + column + 1;
        }
    }
    delete[] a;
    return b;
}

bool checkComplete(int a[])
{
    for (int i = 0; i < 3; i++)
    {
        if (a[i] != i + 1)
            return false;
    }
    return true;
}

void twoXtwoSolving(int a[])
{
    int sliderLoc = checkLocation(a, 0, 4);
    while (!checkComplete(a))
    {
        if (a[0] == 0)
        {
            moveSlider(a, sliderLoc, +1, 2, 2);
            continue;
        }

        if (a[1] == 0)
        {
            moveSlider(a, sliderLoc, +2, 2, 2);
            continue;
        }
        if (a[2] == 0)
        {
            moveSlider(a, sliderLoc, -2, 2, 2);
            continue;
        }
        if (a[3] == 0)
        {
            moveSlider(a, sliderLoc, -1, 2, 2);
            continue;
        }
    }
}

void autoComplete(int a[], int dim)//dim:dimension
{
    if (dim == 2)
    {
        twoXtwoSolving(a);
        delete[] a;
        return;
    }
    int i = 1;
    while (i < dim)
    {
        castPuzzle(a, i, dim);
        i++;
    }
    UREdgeProcessing(a, i, dim);
    i = dim + 1;
    while ((i - 1) / dim < dim - 1)
    {
        castPuzzle(a, i, dim);
        i = i + dim;
    }
    LLEdgeProcessing(a, i, dim);
    a = convertPuzzle(a, dim);
    autoComplete(a, dim - 1);
}

int* entry(int a[], int dimension, int& stepsNeeded)
{
    int* puzzle = new  int [dimension * dimension];
    for(int copy = 0; copy < dimension * dimension; copy++)
    {
        puzzle[copy] = a[copy];
    }
    head->n = 0;
    autoComplete(puzzle, dimension);
    add = head;
    int stepCount = 0;
    while (add->next != NULL)
    {
        add = add->next;
        stepCount++;
    }
    int* steps = new int[stepCount];
    int i = 0;
    while (i < stepCount)
    {
        step* temp = head;
        head = head->next;
        steps[i] = head->n;
        i++;
        delete temp;
    }
     steps = simplify(steps, stepCount);
     stepsNeeded = stepCount;
    return steps;
}
