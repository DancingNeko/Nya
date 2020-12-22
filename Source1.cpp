#include<iostream>
#include<string>
#include "utilities.h"
#include "Source1.h"
using namespace std;

struct step
{
    int n;
    step* next;
};
int originalDimension;

void moveSliderBR(int tempPuzzle[], int dim, int target, int& sliderLoc);
void moveTargetRight(int tempPuzzle[], int& slider, int targetLoc, int w, int h);
int checkLocation(int tempPuzzle[], int target, int size);
void moveTarget(int tempPuzzle[], int target, int w, int h);
void autoComplete(int tempPuzzle[], int dim);
bool moveSlider(int tempPuzzle[], int& slider, int dir, int w, int h);
void UREdgeProcessing(int tempPuzzle[], int target, int dim);
void moveTargetDown(int tempPuzzle[], int& sliderLoc, int targetLoc, int w, int h);
void twoXtwoSolving(int tempPuzzle[]);
bool checkComplete(int tempPuzzle[]);
step* recordStep(int dir, step* add);
step* head = new step;
step* add = head;

bool check_repeat(int* tempPuzzle)
{
    if (*tempPuzzle * *(tempPuzzle + 1) == 2 || *tempPuzzle * *(tempPuzzle + 1) == 12)
    {
        *tempPuzzle = -1;
        *(tempPuzzle + 1) = -1;
        return true;
    }
    return false;
}


int* deleteBlanks(int steps[], int& stepCount)
{
    int* stepsSimplified = new int[stepCount];
    memset((char*)stepsSimplified, 0xcd, sizeof(int)*stepCount);
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
    int j = 0;
    while ((step[i] == 4 || step[i] == 3 || step[i] == 2 || step[i] == 1 || step[i] == -1) && j < stepCount)
    {
        if (step[i] != -1)
            i++;
        j++;
    }
    stepCount = i;
}

string generateCode(int* puzzle, int dimension)
{
    string code;
    for (int i = 0; i < dimension * dimension; i++)
    {
        code += (char)(puzzle[i] + 48);
        code += " ";
    }
    return code;
}

int* simplify(int* steps, int& stepCount, int* original, int dimension)
{
    string* recordPuzzle = new string[stepCount + 1];
    int* simplifiedSteps = new int[stepCount];
    int sliderLoc = checkLocation(original, 0, dimension * dimension);
    int i = 0;
    int translate[] = { 0, -dimension, +dimension, -1, +1 };
    do {
        recordPuzzle[i] = generateCode(original, dimension);
        if(i != stepCount)
        moveSlider(original, sliderLoc, translate[*(steps + i)], dimension, dimension);
        i++;
    } while (i <= stepCount);
    i = 0;
    int k = 0;
    while (i < stepCount)
    {
        for (int j =stepCount; j >= i; j--)
        {
            if (recordPuzzle[j] == recordPuzzle[i])
            {
                i = j;
                break;
            }
        }
        simplifiedSteps[k] = steps[i];
        k++;
        i++;
    }
    stepCount = k - 1;
    return simplifiedSteps;
}

step* recordStep(int dir, step* add)//up:1 ;down:2 ;left:3 ;right:4
{
    add->next = new step;
    add = add->next;
    add->n = dir;
    add->next = NULL;
    return add;
}

void LLEdgeProcessing(int tempPuzzle[], int target, int dim)//LOWER LEFT corner processing: put the last piece of puzzle on the left column
{
    int sliderLoc = checkLocation(tempPuzzle, 0, dim * dim);
    int targetLoc = checkLocation(tempPuzzle, target, dim * dim);
    while (sliderLoc % dim != 1)
    {
        if (sliderLoc % dim == 0)
            moveSlider(tempPuzzle, sliderLoc, +1, dim, dim);
        else
            moveSlider(tempPuzzle, sliderLoc, -1, dim, dim);
    }
    targetLoc = checkLocation(tempPuzzle, target, dim * dim);
    while (targetLoc / dim < dim - 2) { // let's move targe to the last two rows, which is movable area for LLEdgeProcessing.
        moveTargetDown(tempPuzzle, sliderLoc, targetLoc, dim, dim);
        targetLoc = checkLocation(tempPuzzle, target, dim * dim);
    }
    if (targetLoc % dim == dim - 1)
    {
        while (sliderLoc % dim != targetLoc % dim - 1)
        {
            if (sliderLoc % dim > targetLoc % dim - 1)
                moveSlider(tempPuzzle, sliderLoc, -1, dim, dim);
            else
                moveSlider(tempPuzzle, sliderLoc, +1, dim, dim);
            targetLoc = checkLocation(tempPuzzle, target, dim * dim);
        }
        while (sliderLoc / dim != targetLoc / dim)
        {
            if (sliderLoc / dim > targetLoc / dim)
                moveSlider(tempPuzzle, sliderLoc, -dim, dim, dim);
            else
                moveSlider(tempPuzzle, sliderLoc, +dim, dim, dim);
            targetLoc = checkLocation(tempPuzzle, target, dim * dim);
        }
        if (sliderLoc + 1 == targetLoc)
            moveSlider(tempPuzzle, sliderLoc, +1, dim, dim);
    }
    while (sliderLoc % dim != dim - 1)
        moveSlider(tempPuzzle, sliderLoc, +1, dim, dim);//move slider to the right side
    while (sliderLoc / dim != 0)
        moveSlider(tempPuzzle, sliderLoc, -dim, dim, dim);//move slider to the proper location(upper right cornor)
    while (sliderLoc % dim != 0)
        moveSlider(tempPuzzle, sliderLoc, -1, dim, dim);//move slider to the upper left cornor
    int i = 0;
    while (i < dim - 2)
    {
        moveSlider(tempPuzzle, sliderLoc, +dim, dim, dim);
        i++;
    }//move slider down
    targetLoc = checkLocation(tempPuzzle, target, dim * dim);
    while (targetLoc / dim < dim - 2)
    {
        moveTargetDown(tempPuzzle, sliderLoc, targetLoc, dim, dim);
        targetLoc = checkLocation(tempPuzzle, target, dim * dim);
    }
    while (sliderLoc / dim != dim - 1)
        moveSlider(tempPuzzle, sliderLoc, +dim, dim, dim);

    //------------castPuzzle function with some changes----------------//

    targetLoc = checkLocation(tempPuzzle, target, dim * dim);
    int w = dim;//width of cast puzzle
    int h = 2;//height o cast puzzle
    int* b = new int[w * h];//puzzle after cast
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            b[j + i * w] = tempPuzzle[(dim - h + i) * dim + j];
        }
    }
    moveTarget(b, target, w, h);
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            tempPuzzle[(dim - h + i) * dim + j] = b[j + i * w];
        }
    }
    sliderLoc = checkLocation(tempPuzzle, 0, dim * dim);
    delete[] b;

    //-----------end of funciton---------------//

    while (sliderLoc / dim != dim - 1)
        moveSlider(tempPuzzle, sliderLoc, +dim, dim, dim);
    while (sliderLoc % dim != 0)
        moveSlider(tempPuzzle, sliderLoc, -1, dim, dim);//move slider to the lower left corner
    while (sliderLoc / dim != 0)
        moveSlider(tempPuzzle, sliderLoc, -dim, dim, dim);//move slider to the upper right corner
    while (sliderLoc % dim != dim - 1)
        moveSlider(tempPuzzle, sliderLoc, +1, dim, dim);//move slider to the upper right corner
    moveSlider(tempPuzzle, sliderLoc, +dim, dim, dim);
}

void UREdgeProcessing(int tempPuzzle[], int target, int dim)//UPPER RIGHT corner processing: put the last piece of puzzle on the top roll
{
    int sliderLoc = checkLocation(tempPuzzle, 0, dim * dim);
    int targetLoc = checkLocation(tempPuzzle, target, dim * dim);
    while (sliderLoc / dim != 1)
    {
        if (sliderLoc / dim == 0)
            moveSlider(tempPuzzle, sliderLoc, +dim, dim, dim);
        else
            moveSlider(tempPuzzle, sliderLoc, -dim, dim, dim);
    }
    if (targetLoc % dim == 0)
        moveTargetRight(tempPuzzle, sliderLoc, targetLoc, dim, dim);
    while (sliderLoc % dim != 0)
        moveSlider(tempPuzzle, sliderLoc, -1, dim, dim);//move slider to the proper location(left side)
    while (sliderLoc / dim != 0)
        moveSlider(tempPuzzle, sliderLoc, -dim, dim, dim);//move slider to the upper left
    int i = 0;
    while (i < dim - 2)
    {
        moveSlider(tempPuzzle, sliderLoc, +1, dim, dim);
        i++;
    }//move slider to the uppre right
    targetLoc = checkLocation(tempPuzzle, target, dim * dim);
    while (targetLoc % dim < dim - 2)
    {
        moveTargetRight(tempPuzzle, sliderLoc, targetLoc, dim, dim);
        targetLoc = checkLocation(tempPuzzle, target, dim * dim);
    }
    moveSliderBR(tempPuzzle, dim, target, sliderLoc);

    //------------castPuzzle function with some changes----------------//

    targetLoc = checkLocation(tempPuzzle, target, dim * dim);
    int w = 2;//width of cast puzzle
    int h = dim;//height o cast puzzle
    int* b = new int[w * h];//puzzle after cast
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            b[j + i * w] = tempPuzzle[dim - w + j + i * dim];
        }
    }
    moveTarget(b, target, w, h);
    sliderLoc = checkLocation(tempPuzzle, 0, dim * dim);
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            tempPuzzle[dim - w + j + i * dim] = b[j + i * w];
        }
    }
    sliderLoc = checkLocation(tempPuzzle, 0, dim * dim);
    delete[] b;

    //-----------end of funciton---------------//

    while (sliderLoc % dim != dim - 1)
        moveSlider(tempPuzzle, sliderLoc, +1, dim, dim);
    while (sliderLoc / dim != 0)
        moveSlider(tempPuzzle, sliderLoc, -dim, dim, dim);//move slider to the upper right
    while (sliderLoc % dim != 0)
        moveSlider(tempPuzzle, sliderLoc, -1, dim, dim);//move slider to the upper left
    moveSlider(tempPuzzle, sliderLoc, +dim, dim, dim);
}

bool moveSlider(int tempPuzzle[], int& slider, int dir, int w, int h)
{
    if (dir == 1 && slider % w < w - 1)
    {
        int temp = tempPuzzle[slider + dir];
        tempPuzzle[slider + dir] = tempPuzzle[slider];
        tempPuzzle[slider] = temp;
        slider = slider + dir;
        add = recordStep(4, add);
        return true;
    }
    if (dir == -1 && slider % w > 0)
    {
        int temp = tempPuzzle[slider + dir];
        tempPuzzle[slider + dir] = tempPuzzle[slider];
        tempPuzzle[slider] = temp;
        slider = slider + dir;
        add = recordStep(3, add);
        return true;
    }
    if (dir == +w && slider / w < h - 1)
    {
        int temp = tempPuzzle[slider + dir];
        tempPuzzle[slider + dir] = tempPuzzle[slider];
        tempPuzzle[slider] = temp;
        slider = slider + dir;
        add = recordStep(2, add);
        return true;
    }
    if (dir == -w && slider / w > 0)
    {
        int temp = tempPuzzle[slider + dir];
        tempPuzzle[slider + dir] = tempPuzzle[slider];
        tempPuzzle[slider] = temp;
        slider = slider + dir;
        add = recordStep(1, add);
        return true;
    }
    return false;
}

void castPuzzle(int tempPuzzle[], int target, int dim)//target: the one put on the top left
{
    int targetLoc = checkLocation(tempPuzzle, target, dim * dim);
    int sliderLoc = checkLocation(tempPuzzle, 0, dim * dim);
    if (target / dim == 0)
    {
        while (targetLoc % dim < (target % dim) - 1)
        {
            moveTargetRight(tempPuzzle, sliderLoc, targetLoc, dim, dim);
            targetLoc = checkLocation(tempPuzzle, target, dim * dim);
        }
        moveSliderBR(tempPuzzle, dim, target, sliderLoc);
        int w = dim - (target - 1) % dim;//width of cast puzzle
        int h = dim - (target - 1) / dim;//height o cast puzzle
        int* b = new int[w * h];//puzzle after cast
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                b[j + i * w] = tempPuzzle[dim - w + j + i * dim];
            }
        }
        moveTarget(b, target, w, h);
        sliderLoc = checkLocation(tempPuzzle, 0, dim * dim);
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                tempPuzzle[dim - w + j + i * dim] = b[j + i * w];
            }
        }
        delete[] b;
    }
    else
    {
        while (targetLoc / dim < (target - 1) / dim)
        {
            moveTargetDown(tempPuzzle, sliderLoc, targetLoc, dim, dim);
            targetLoc = checkLocation(tempPuzzle, target, dim * dim);
        }
        moveSliderBR(tempPuzzle, dim, target, sliderLoc);
        int w = dim - (target - 1) % dim;//width of cast puzzle
        int h = dim - (target - 1) / dim;//height o cast puzzle
        int* b = new int[w * h];//puzzle after cast
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                b[j + i * w] = tempPuzzle[(dim - h + i) * dim + j];
            }
        }
        moveTarget(b, target, w, h);
        sliderLoc = checkLocation(tempPuzzle, 0, dim * dim);
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                tempPuzzle[(dim - h + i) * dim + j] = b[j + i * w];
            }
        }
        delete[] b;
    }
}

void moveSliderBR(int tempPuzzle[], int dim, int target, int& sliderLoc)//move target to the bottom right
{
    while (sliderLoc % dim != dim - 1)//move slider to the moveable area
        {
            if (tempPuzzle[sliderLoc + 1] != target)
                moveSlider(tempPuzzle, sliderLoc, +1, dim, dim);
            else if (moveSlider(tempPuzzle, sliderLoc, +dim, dim, dim) == true)
                continue;
            else
                moveSlider(tempPuzzle, sliderLoc, -dim, dim, dim);
        }
        while (tempPuzzle[dim * dim - 1] != 0)
        {
            if (tempPuzzle[sliderLoc + dim] != target && sliderLoc / dim != dim - 1)
                moveSlider(tempPuzzle, sliderLoc, +dim, dim, dim);
            else if (moveSlider(tempPuzzle, sliderLoc, +1, dim, dim))
                continue;
            else
                moveSlider(tempPuzzle, sliderLoc, -1, dim, dim);
        }
}

void moveTargetRight(int tempPuzzle[], int& slider, int targetLoc, int w, int h)//move target right tempPuzzle tile; slider: sliderLoc
{
    while (slider / w != targetLoc / w)//move slider to the target's roll
    {
        if (slider / w > targetLoc / w && slider - w != targetLoc)
            moveSlider(tempPuzzle, slider, -w, w, h);
        if (slider / w > targetLoc / w && slider - w == targetLoc)
            if (moveSlider(tempPuzzle, slider, +1, w, h))
                continue;
            else
                moveSlider(tempPuzzle, slider, -1, w, h);
        if (slider / w < targetLoc / w && slider + w != targetLoc)
            moveSlider(tempPuzzle, slider, +w, w, h);
        if (slider / w < targetLoc / w && slider + w == targetLoc)
            if (moveSlider(tempPuzzle, slider, +1, w, h))
                continue;
            else
                moveSlider(tempPuzzle, slider, -1, w, h);
    }
    while (slider % w != targetLoc % w + 1)//move slider to the right of target
    {
        if (slider % w > targetLoc % w + 1)
            moveSlider(tempPuzzle, slider, -1, w, h);
        else if (slider + 1 != targetLoc)
            moveSlider(tempPuzzle, slider, +1, w, h);
        else if (moveSlider(tempPuzzle, slider, +w, w, h))
            continue;
        else
            moveSlider(tempPuzzle, slider, -w, w, h);
    }
    if (slider / w != targetLoc / w)
    {
        if (slider / w > targetLoc / w)
            moveSlider(tempPuzzle, slider, -w, w, h);
        if (slider / w < targetLoc / w)
            moveSlider(tempPuzzle, slider, +w, w, h);
    }
    if (slider - 1 == targetLoc)
        moveSlider(tempPuzzle, slider, -1, w, h);
}

void moveTargetDown(int tempPuzzle[], int& sliderLoc, int targetLoc, int w, int h)//move target down tempPuzzle tile
{
    while (sliderLoc % w != targetLoc % w)//move slider to the target's column
    {

        if (sliderLoc % w > targetLoc % w && sliderLoc - 1 != targetLoc)
            moveSlider(tempPuzzle, sliderLoc, -1, w, h);
        if (sliderLoc % w > targetLoc % w && sliderLoc - 1 == targetLoc)
            if (moveSlider(tempPuzzle, sliderLoc, +w, w, h))
                continue;
            else
                moveSlider(tempPuzzle, sliderLoc, -w, w, h);
        if (sliderLoc % w < targetLoc % w && sliderLoc + 1 != targetLoc)
            moveSlider(tempPuzzle, sliderLoc, +1, w, h);
        if (sliderLoc % w < targetLoc % w && sliderLoc + 1 == targetLoc)
            if (moveSlider(tempPuzzle, sliderLoc, +w, w, h))
                continue;
            else
                moveSlider(tempPuzzle, sliderLoc, -w, w, h);
    }
    while (sliderLoc / w != targetLoc / w + 1)//move slider below the target
    {
        if (sliderLoc / w > targetLoc / w + 1)
            moveSlider(tempPuzzle, sliderLoc, -w, w, h);
        else if (sliderLoc + w != targetLoc)
            moveSlider(tempPuzzle, sliderLoc, +w, w, h);
        else if (moveSlider(tempPuzzle, sliderLoc, +1, w, h))
            continue;
        else
            moveSlider(tempPuzzle, sliderLoc, -1, w, h);
    }
    if (sliderLoc % w != targetLoc % w)
    {
        if (sliderLoc % w > targetLoc % w)
            moveSlider(tempPuzzle, sliderLoc, -1, w, h);
        if (sliderLoc % w < targetLoc % w)
            moveSlider(tempPuzzle, sliderLoc, +1, w, h);
    }
    if (sliderLoc - w == targetLoc)
        moveSlider(tempPuzzle, sliderLoc, -w, w, h);
}

int checkLocation(int tempPuzzle[], int target, int size)//search target in the size area
{
    for (int i = 0; i < size; i++)
    {
        if (tempPuzzle[i] == target)
            return i;
    }
    return -1;//fail to detect slider's location
}

void moveTarget(int tempPuzzle[], int target, int w, int h)//only works for the puzzle ont the top right; w: width of the moveable area, height: height of the moveable area, target: which number to move
{
    int sliderLoc = checkLocation(tempPuzzle, 0, w * h);
    int targetLoc = checkLocation(tempPuzzle, target, w * h);
    while (targetLoc / w > 0)//move target up
    {
        while (sliderLoc / w != targetLoc / w - 1)
        {
            if (sliderLoc / w > targetLoc / w - 1)
            {
                if (tempPuzzle[sliderLoc - w] != target)
                    moveSlider(tempPuzzle, sliderLoc, -w, w, h);
                else if (moveSlider(tempPuzzle, sliderLoc, +1, w, h))
                    continue;
                else
                    moveSlider(tempPuzzle, sliderLoc, -1, w, h);
            }
            if (sliderLoc / w < targetLoc / w - 1)
                moveSlider(tempPuzzle, sliderLoc, +w, w, h);
        }
        while (sliderLoc % w != targetLoc % w)
        {
            if (sliderLoc % w > targetLoc % w)
                moveSlider(tempPuzzle, sliderLoc, -1, w, h);
            else
                moveSlider(tempPuzzle, sliderLoc, +1, w, h);
        }
        if (tempPuzzle[sliderLoc + w] == target)
            moveSlider(tempPuzzle, sliderLoc, +w, w, h);
        targetLoc = checkLocation(tempPuzzle, target, w * h);
    }
    while (targetLoc % w > 0)//move target left
    {
        while (sliderLoc % w != targetLoc % w - 1)
        {
            if (sliderLoc % w < targetLoc % w - 1)
                moveSlider(tempPuzzle, sliderLoc, +1, w, h);
            if (sliderLoc % w > targetLoc % w - 1)
            {
                if (tempPuzzle[sliderLoc - 1] != target)
                    moveSlider(tempPuzzle, sliderLoc, -1, w, h);
                else if (moveSlider(tempPuzzle, sliderLoc, -w, w, h))
                    continue;
                else
                    moveSlider(tempPuzzle, sliderLoc, +w, w, h);
            }
        }
        while (sliderLoc / w != targetLoc / w)
        {
            if (sliderLoc / w > targetLoc / w)
                moveSlider(tempPuzzle, sliderLoc, -w, w, h);
            else
                moveSlider(tempPuzzle, sliderLoc, +w, w, h);
        }
        if (tempPuzzle[sliderLoc + 1] == target)
            moveSlider(tempPuzzle, sliderLoc, +1, w, h);
        targetLoc = checkLocation(tempPuzzle, target, w * h);
    }
}

int* convertPuzzle(int tempPuzzle[], int dim)//convert puzzle to smaller one: 4*4 -> 3*3
{
    int* b = new int[(dim - 1) * (dim - 1)];
    for (int i = 0; i < dim - 1; i++)
    {
        for (int j = 0; j < dim - 1; j++)
        {
            b[i * (dim - 1) + j] = tempPuzzle[(i + 1) * dim + j + 1];
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
    delete[] tempPuzzle;
    return b;
}

bool checkComplete(int tempPuzzle[])
{
    for (int i = 0; i < 3; i++)
    {
        if (tempPuzzle[i] != i + 1)
            return false;
    }
    return true;
}

void twoXtwoSolving(int tempPuzzle[])
{
    int sliderLoc = checkLocation(tempPuzzle, 0, 4);
    while (!checkComplete(tempPuzzle))
    {
        if (tempPuzzle[0] == 0)
        {
            moveSlider(tempPuzzle, sliderLoc, +1, 2, 2);
            continue;
        }

        if (tempPuzzle[1] == 0)
        {
            moveSlider(tempPuzzle, sliderLoc, +2, 2, 2);
            continue;
        }
        if (tempPuzzle[2] == 0)
        {
            moveSlider(tempPuzzle, sliderLoc, -2, 2, 2);
            continue;
        }
        if (tempPuzzle[3] == 0)
        {
            moveSlider(tempPuzzle, sliderLoc, -1, 2, 2);
            continue;
        }
    }
}

void autoComplete(int tempPuzzle[], int dim)//dim:dimension
{
    if (dim == 2)
    {
        twoXtwoSolving(tempPuzzle);
        delete[] tempPuzzle;
        return;
    }
    int i = 1;
    while (i < dim)
    {
        castPuzzle(tempPuzzle, i, dim);
        i++;
    }
    UREdgeProcessing(tempPuzzle, i, dim);
    i = dim + 1;
    while ((i - 1) / dim < dim - 1)
    {
        castPuzzle(tempPuzzle, i, dim);
        i = i + dim;
    }
    LLEdgeProcessing(tempPuzzle, i, dim);
    tempPuzzle = convertPuzzle(tempPuzzle, dim);
    autoComplete(tempPuzzle, dim - 1);
}



int* entry(int tempPuzzle[], int dimension, int& stepsNeeded)
{
    printPuzzle(tempPuzzle, dimension);
    int* puzzle = new  int [dimension * dimension];
    for(int copy = 0; copy < dimension * dimension; copy++)
    {
        puzzle[copy] = tempPuzzle[copy];
    }
    int* puzzleBackup = new int[dimension * dimension];
    memcpy_s(puzzleBackup, dimension * dimension * sizeof(int), puzzle, dimension * dimension * sizeof(int));
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
     steps = simplify(steps, stepCount,puzzleBackup,dimension);
     delete []puzzleBackup;
     stepsNeeded = stepCount;
    return steps;
}
