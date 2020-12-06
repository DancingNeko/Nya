 #include<stdlib.h>
#include<time.h>
using namespace std;
#include <ui_mainwindow.h>
#include<windows.h>
#include<QProcess>
#include <assert.h>

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
    if(size==9)
    {
        for (int i = 0; i< 9; i++)
        {
            if (tempPuzzle[i] == slider)
            {
                if (i < 3)
                    return false;
                int temp = tempPuzzle[i];
                tempPuzzle[i] = tempPuzzle[i - 3];
                tempPuzzle[i - 3] = temp;
                return true;
            }
        }
    }
    if(size==16)
    {
        for (int i = 0; i< 16; i++)
        {
            if (tempPuzzle[i] == slider)
            {
                if (i < 4)
                    return false;
                int temp = tempPuzzle[i];
                tempPuzzle[i] = tempPuzzle[i - 4];
                tempPuzzle[i - 4] = temp;
                return true;
            }
        }
    }
    return false;
}
bool Down(int tempPuzzle[], int slider, int size)
{
    if(size==9)
    {
        for (int i = 0; i < 9; i++)
        {
            if (tempPuzzle[i] == slider)
            {
                if (i > 5)
                    return false;
                int temp = tempPuzzle[i];
                tempPuzzle[i] = tempPuzzle[i + 3];
                tempPuzzle[i + 3] = temp;
                return true;
            }
        }
    }
    if(size==16)
    {
        for (int i = 0; i< 16; i++)
        {
            if (tempPuzzle[i] == slider)
            {
                if (i > 11)
                    return false;
                int temp = tempPuzzle[i];
                tempPuzzle[i] = tempPuzzle[i + 4];
                tempPuzzle[i + 4] = temp;
                return true;
            }
        }
    }
    return false;
}
bool Left(int tempPuzzle[], int slider, int size)
{
    if(size==9)
    {
        for (int i = 0; i < 9; i++)
        {
            if (tempPuzzle[i] == slider)
            {
                if (i%3==0)
                    return false;
                int temp = tempPuzzle[i];
                tempPuzzle[i] = tempPuzzle[i - 1];
                tempPuzzle[i - 1] = temp;
                return true;
            }
        }
    }
    if(size==16)
    {
        for (int i = 0; i< 16; i++)
        {
            if (tempPuzzle[i] == slider)
            {
                if (i%4==0)
                    return false;
                int temp = tempPuzzle[i];
                tempPuzzle[i] = tempPuzzle[i - 1];
                tempPuzzle[i - 1] = temp;
                return true;
            }
        }
    }
    return false;
}
bool Right(int tempPuzzle[], int slider, int size)
{
    if(size==9)
    {
        for (int i = 0; i < 9; i++)
        {
            if (tempPuzzle[i] == slider)
            {
                if (i % 3 == 2)
                    return false;
                int temp = tempPuzzle[i];
                tempPuzzle[i] = tempPuzzle[i + 1];
                tempPuzzle[i + 1] = temp;
                return true;
            }
        }
    }
    if(size==16)
    {
        for (int i = 0; i< 16; i++)
        {
            if (tempPuzzle[i] == slider)
            {
                if (i%4==3)
                    return false;
                int temp = tempPuzzle[i];
                tempPuzzle[i] = tempPuzzle[i + 1];
                tempPuzzle[i + 1] = temp;
                return true;
            }
        }
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

void setText(int* tempPuzzle, Ui::MainWindow* ui, int size)
{
    if(size==9)
    {
    QString b[9];
    for(int i=0;i<9;i++)
    {
        b[i]=QString::number(*(tempPuzzle+i));
    }
    ui->pushButton->setText(b[0]);
    ui->pushButton_2->setText(b[1]);
    ui->pushButton_3->setText(b[2]);
    ui->pushButton_4->setText(b[3]);
    ui->pushButton_5->setText(b[4]);
    ui->pushButton_6->setText(b[5]);
    ui->pushButton_7->setText(b[6]);
    ui->pushButton_8->setText(b[7]);
    ui->pushButton_9->setText(b[8]);
    }
    if(size==16)
    {
        QString b[16];
        for(int i=0;i<16;i++)
        {
            b[i]=QString::number(*(tempPuzzle+i));
        }
        ui->four_1->setText(b[0]);
        ui->four_2->setText(b[1]);
        ui->four_3->setText(b[2]);
        ui->four_4->setText(b[3]);
        ui->four_5->setText(b[4]);
        ui->four_6->setText(b[5]);
        ui->four_7->setText(b[6]);
        ui->four_8->setText(b[7]);
        ui->four_9->setText(b[8]);
        ui->four_10->setText(b[9]);
        ui->four_11->setText(b[10]);
        ui->four_12->setText(b[11]);
        ui->four_13->setText(b[12]);
        ui->four_14->setText(b[13]);
        ui->four_15->setText(b[14]);
        ui->four_16->setText(b[15]);

    }
}

void setColor(int* b, Ui::MainWindow* ui, int size)
{
    if(size==9)
    {
    if(b[0]==0)
        ui->pushButton->setStyleSheet("background-color:rgb(0,0,0)");
    else
         ui->pushButton->setStyleSheet("background-color:rgb(255,255,255)");
    if(b[1]==0)
        ui->pushButton_2->setStyleSheet("background-color:rgb(0,0,0)");
    else
         ui->pushButton_2->setStyleSheet("background-color:rgb(255,255,255)");
    if(b[2]==0)
        ui->pushButton_3->setStyleSheet("background-color:rgb(0,0,0)");
    else
         ui->pushButton_3->setStyleSheet("background-color:rgb(255,255,255)");
    if(b[3]==0)
        ui->pushButton_4->setStyleSheet("background-color:rgb(0,0,0)");
    else
         ui->pushButton_4->setStyleSheet("background-color:rgb(255,255,255)");
    if(b[4]==0)
        ui->pushButton_5->setStyleSheet("background-color:rgb(0,0,0)");
    else
         ui->pushButton_5->setStyleSheet("background-color:rgb(255,255,255)");
    if(b[5]==0)
        ui->pushButton_6->setStyleSheet("background-color:rgb(0,0,0)");
    else
         ui->pushButton_6->setStyleSheet("background-color:rgb(255,255,255)");
    if(b[6]==0)
        ui->pushButton_7->setStyleSheet("background-color:rgb(0,0,0)");
    else
         ui->pushButton_7->setStyleSheet("background-color:rgb(255,255,255)");
    if(b[7]==0)
        ui->pushButton_8->setStyleSheet("background-color:rgb(0,0,0)");
    else
         ui->pushButton_8->setStyleSheet("background-color:rgb(255,255,255)");
    if(b[8]==0)
        ui->pushButton_9->setStyleSheet("background-color:rgb(0,0,0)");
    else
         ui->pushButton_9->setStyleSheet("background-color:rgb(255,255,255)");
    }
    if(size==16)
    {
        if(b[0]==0)
            ui->four_1->setStyleSheet("background-color:rgb(0,0,0)");
        else
             ui->four_1->setStyleSheet("background-color:rgb(255,255,255)");
        if(b[1]==0)
            ui->four_2->setStyleSheet("background-color:rgb(0,0,0)");
        else
             ui->four_2->setStyleSheet("background-color:rgb(255,255,255)");
        if(b[2]==0)
            ui->four_3->setStyleSheet("background-color:rgb(0,0,0)");
        else
             ui->four_3->setStyleSheet("background-color:rgb(255,255,255)");
        if(b[3]==0)
            ui->four_4->setStyleSheet("background-color:rgb(0,0,0)");
        else
             ui->four_4->setStyleSheet("background-color:rgb(255,255,255)");
        if(b[4]==0)
            ui->four_5->setStyleSheet("background-color:rgb(0,0,0)");
        else
             ui->four_5->setStyleSheet("background-color:rgb(255,255,255)");
        if(b[5]==0)
            ui->four_6->setStyleSheet("background-color:rgb(0,0,0)");
        else
             ui->four_6->setStyleSheet("background-color:rgb(255,255,255)");
        if(b[6]==0)
            ui->four_7->setStyleSheet("background-color:rgb(0,0,0)");
        else
             ui->four_7->setStyleSheet("background-color:rgb(255,255,255)");
        if(b[7]==0)
            ui->four_8->setStyleSheet("background-color:rgb(0,0,0)");
        else
             ui->four_8->setStyleSheet("background-color:rgb(255,255,255)");
        if(b[8]==0)
            ui->four_9->setStyleSheet("background-color:rgb(0,0,0)");
        else
             ui->four_9->setStyleSheet("background-color:rgb(255,255,255)");
        if(b[9]==0)
            ui->four_10->setStyleSheet("background-color:rgb(0,0,0)");
        else
             ui->four_10->setStyleSheet("background-color:rgb(255,255,255)");
        if(b[10]==0)
            ui->four_11->setStyleSheet("background-color:rgb(0,0,0)");
        else
             ui->four_11->setStyleSheet("background-color:rgb(255,255,255)");
        if(b[11]==0)
            ui->four_12->setStyleSheet("background-color:rgb(0,0,0)");
        else
             ui->four_12->setStyleSheet("background-color:rgb(255,255,255)");
        if(b[12]==0)
            ui->four_13->setStyleSheet("background-color:rgb(0,0,0)");
        else
             ui->four_13->setStyleSheet("background-color:rgb(255,255,255)");
        if(b[13]==0)
            ui->four_14->setStyleSheet("background-color:rgb(0,0,0)");
        else
             ui->four_14->setStyleSheet("background-color:rgb(255,255,255)");
        if(b[14]==0)
            ui->four_15->setStyleSheet("background-color:rgb(0,0,0)");
        else
             ui->four_15->setStyleSheet("background-color:rgb(255,255,255)");
        if(b[15]==0)
            ui->four_16->setStyleSheet("background-color:rgb(0,0,0)");
        else
             ui->four_16->setStyleSheet("background-color:rgb(255,255,255)");
    }
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
