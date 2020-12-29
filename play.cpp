 #include<stdlib.h>
#include<time.h>
using namespace std;
#include <assert.h>

// -------------------------------------------------------------------------------------
// static functions
static int getDimensionBySize(int size) {
    switch (size) {
    case 9:
        return 3;
    case 16:
        return 4;
    case 25:
        return 5;
    default:
        assert(!"Invalide size.");
        return 4;
    }
}

static int getSizeByDimension(int dim) {
    assert(dim > 2 && dim < 6);
    return dim * dim;
}

static void swapTiles(int * puzzle, int ix1, int ix2) {
    assert(puzzle != nullptr);
    assert(ix1 >= 0 && ix2 >= 0);
    int tmp = puzzle[ix1];
    puzzle[ix1] = puzzle[ix2];
    puzzle[ix2] = tmp;
}

// -------------------------------------------------------------------------------------

void moveSlide(int* tempPuzzle, int n, int slider)
{
    int temp = *(tempPuzzle + n);
    *(tempPuzzle + n) = *(tempPuzzle + slider);
    *(tempPuzzle + slider) = temp;
}

int checkSlider(int* tempPuzzle, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (*(tempPuzzle + i) == 0)
            return i;
    }
    assert(!"Failed to check slider");
    return -1;
}

int operate(int* tempPuzzle, int move, int size)
{
    if(size==9)
    {
    int slider = checkSlider(tempPuzzle, size);
    if (slider - move == 1 || slider - move == -1 || slider - move == 3 || slider - move == -3)
    {
        moveSlide(tempPuzzle, move, slider);
        return 1;
    }
    else
        return 0;
    }
    if(size==16)
    {
        int slider = checkSlider(tempPuzzle, size);
        if (slider - move == 1 || slider - move == -1 || slider - move == 4 || slider - move == -4)
        {
            moveSlide(tempPuzzle, move, slider);
            return 1;
        }
        else
            return 0;
    }
    return 0;
}

void setNum(int* tempPuzzle, int choice)
{
    int* b = new int[choice];
    int n = 0;
    for (int i = 0; i < 9; i++)
    {
        int count = 0;
        for (int j = 0; j < 9; j++)
        {
            if (tempPuzzle[j] == i)
                count = 1;
        }
        if (count == 0)
        {
            b[n] = i;
            n++;
        }
    }
    int randSeed = rand() % choice;
    *(tempPuzzle + 9 - choice) = b[randSeed];
    delete[] b;
}

bool Up(int tempPuzzle[],int slider, int size)
{
    int dim = getDimensionBySize(size);
    for (int i = 0; i < size; i++) {
        if (tempPuzzle[i] == slider) {
            if (i - dim < 0)
                return false;
            swapTiles(tempPuzzle, i, i - dim);
            return true;
        }
    }
    return false;
}

bool Down(int tempPuzzle[], int slider, int size)
{
    int dim = getDimensionBySize(size);
    for (int i = 0; i < size; i++) {
        if (tempPuzzle[i] != slider)
            continue;
        if (i + dim > size - 1)
            return false;
        swapTiles(tempPuzzle, i, i + dim);
    }

    return false;
}
bool Left(int tempPuzzle[], int slider, int size)
{
    int dim = getDimensionBySize(size);
    for (int i = 0; i < size; i++) {
        if (tempPuzzle[i] != slider)
            continue;;
        if (i % dim == 0)
            return  false;
        swapTiles(tempPuzzle, i, i - 1);
    }

    return false;
}
bool Right(int tempPuzzle[], int slider, int size)
{
    int dim = getDimensionBySize(size);
    for (int i = 0; i < size; i++) {
        if (tempPuzzle[i] != slider)
            continue;
        if ((i+1) % dim == 0)
            return false;
        swapTiles(tempPuzzle, i, i+1);
    }

    return false;
}

int* initializePuzzle(int tempPuzzle[], int depth, int size)
{
    int count = 0;
    srand((unsigned)time(NULL));
    while (count<depth)
    {
        int s=0;
        int seed = rand() % 4;
        if (seed == 0)
            if (Up(tempPuzzle, s, size) == 1)
            {
                count++;
            }
        if (seed == 1)
            if (Down(tempPuzzle, s, size) == 1)
            {
                count++;
            }
        if (seed == 2)
            if (Left(tempPuzzle, s, size) == 1)
            {
                count++;
            }
        if (seed == 3)
            if (Right(tempPuzzle, s, size) == 1)
            {
                count++;
            }
    }
    return tempPuzzle;
}

bool checkComplete(int* tempPuzzle, int size)
{
    for(int i=0;i<size-1;i++)
    {
        if(*(tempPuzzle+i)!=i+1)
            return false;
    }
    return true;
}

void up(int* tempPuzzle,int dim)
{
    int i=0;
    while(*(tempPuzzle+i)!=0)
        i++;
    int temp=*(tempPuzzle+i);
    *(tempPuzzle+i)=*(tempPuzzle+i-dim);
    *(tempPuzzle+i-dim)=temp;
}
void down(int* tempPuzzle,int dim)
{
    int i=0;
    while(*(tempPuzzle+i)!=0)
        i++;
    int temp=*(tempPuzzle+i);
    *(tempPuzzle+i)=*(tempPuzzle+i+dim);
    *(tempPuzzle+i+dim)=temp;
}
void left(int* tempPuzzle,int dim)
{
    int i=0;
    while(*(tempPuzzle+i)!=0)
        i++;
    int temp=*(tempPuzzle+i);
    *(tempPuzzle+i)=*(tempPuzzle+i-1);
    *(tempPuzzle+i-1)=temp;
}
void right(int* tempPuzzle,int dim)
{
    int i=0;
    while(*(tempPuzzle+i)!=0)
        i++;
    int temp=*(tempPuzzle+i);
    *(tempPuzzle+i)=*(tempPuzzle+i+1);
    *(tempPuzzle+i+1)=temp;
}

void showStep(int* tempPuzzle,int step, int& i, int dim)
{
     if(step==1)
         up(tempPuzzle,dim);
     if(step==2)
         down(tempPuzzle,dim);
     if(step==3)
         left(tempPuzzle,dim);
     if(step==4)
         right(tempPuzzle,dim);
     i++;
}
