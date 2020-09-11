#include<stdlib.h>
#include<time.h>
using namespace std;
#include <ui_mainwindow.h>
#include<windows.h>
#include<QProcess>

void moveSlide(int* a, int n, int slider)
{
    int temp = *(a + n);
    *(a + n) = *(a + slider);
    *(a + slider) = temp;
}

int checkSlider(int* a)
{
    for (int i = 0; i < 9; i++)
    {
        if (*(a + i) == 0)
            return i;
    }
}

int operate(int* a, int move, int size)
{
    if(size==9)
    {
    int slider = checkSlider(a);
    if (slider - move == 1 || slider - move == -1 || slider - move == 3 || slider - move == -3)
    {
        moveSlide(a, move, slider);
        return 1;
    }
    else
        return 0;
    }
    if(size==16)
    {
        int slider = checkSlider(a);
        if (slider - move == 1 || slider - move == -1 || slider - move == 4 || slider - move == -4)
        {
            moveSlide(a, move, slider);
            return 1;
        }
        else
            return 0;
    }
}

void setNum(int* a, int choice)
{
    int* b = new int[choice];
    int n = 0;
    for (int i = 0; i < 9; i++)
    {
        int count = 0;
        for (int j = 0; j < 9; j++)
        {
            if (a[j] == i)
                count = 1;
        }
        if (count == 0)
        {
            b[n] = i;
            n++;
        }
    }
    int randSeed = rand() % choice;
    *(a + 9 - choice) = b[randSeed];
    delete[] b;
}

bool Up(int a[],int slider, int size)
{
    if(size==9)
    {
        for (int i = 0; i< 9; i++)
        {
            if (a[i] == slider)
            {
                if (i < 3)
                    return false;
                int temp = a[i];
                a[i] = a[i - 3];
                a[i - 3] = temp;
                return true;
            }
        }
    }
    if(size==16)
    {
        for (int i = 0; i< 16; i++)
        {
            if (a[i] == slider)
            {
                if (i < 4)
                    return false;
                int temp = a[i];
                a[i] = a[i - 4];
                a[i - 4] = temp;
                return true;
            }
        }
    }
}
bool Down(int a[], int slider, int size)
{
    if(size==9)
    {
        for (int i = 0; i < 9; i++)
        {
            if (a[i] == slider)
            {
                if (i > 5)
                    return false;
                int temp = a[i];
                a[i] = a[i + 3];
                a[i + 3] = temp;
                return true;
            }
        }
    }
    if(size==16)
    {
        for (int i = 0; i< 16; i++)
        {
            if (a[i] == slider)
            {
                if (i > 11)
                    return false;
                int temp = a[i];
                a[i] = a[i + 4];
                a[i + 4] = temp;
                return true;
            }
        }
    }
}
bool Left(int a[], int slider, int size)
{
    if(size==9)
    {
        for (int i = 0; i < 9; i++)
        {
            if (a[i] == slider)
            {
                if (i%3==0)
                    return false;
                int temp = a[i];
                a[i] = a[i - 1];
                a[i - 1] = temp;
                return true;
            }
        }
    }
    if(size==16)
    {
        for (int i = 0; i< 16; i++)
        {
            if (a[i] == slider)
            {
                if (i%4==0)
                    return false;
                int temp = a[i];
                a[i] = a[i - 1];
                a[i - 1] = temp;
                return true;
            }
        }
    }
}
bool Right(int a[], int slider, int size)
{
    if(size==9)
    {
        for (int i = 0; i < 9; i++)
        {
            if (a[i] == slider)
            {
                if (i % 3 == 2)
                    return false;
                int temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
                return true;
            }
        }
    }
    if(size==16)
    {
        for (int i = 0; i< 16; i++)
        {
            if (a[i] == slider)
            {
                if (i%4==3)
                    return false;
                int temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
                return true;
            }
        }
    }
}

int* initializePuzzle(int a[], int depth, int size)
{
    int count = 0;
    srand((unsigned)time(NULL));
    while (count<depth)
    {
        int s=0;
        int seed = rand() % 4;
        if (seed == 0)
            if (Up(a, s, size) == 1)
            {
                count++;
            }
        if (seed == 1)
            if (Down(a, s, size) == 1)
            {
                count++;
            }
        if (seed == 2)
            if (Left(a, s, size) == 1)
            {
                count++;
            }
        if (seed == 3)
            if (Right(a, s, size) == 1)
            {
                count++;
            }
    }
    return a;
}

void setText(int* a, Ui::MainWindow* ui, int size)
{
    if(size==9)
    {
    QString b[9];
    for(int i=0;i<9;i++)
    {
        b[i]=QString::number(*(a+i));
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
            b[i]=QString::number(*(a+i));
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

bool checkComplete(int* a, int size)
{
    for(int i=0;i<size-1;i++)
    {
        if(*(a+i)!=i+1)
            return false;
    }
    return true;
}

void up(int* a)
{
    int i=0;
    while(*(a+i)!=0)
        i++;
    int temp=*(a+i);
    *(a+i)=*(a+i-3);
    *(a+i-3)=temp;
}
void down(int* a)
{
    int i=0;
    while(*(a+i)!=0)
        i++;
    int temp=*(a+i);
    *(a+i)=*(a+i+3);
    *(a+i+3)=temp;
}
void left(int* a)
{
    int i=0;
    while(*(a+i)!=0)
        i++;
    int temp=*(a+i);
    *(a+i)=*(a+i-1);
    *(a+i-1)=temp;
}
void right(int* a)
{
    int i=0;
    while(*(a+i)!=0)
        i++;
    int temp=*(a+i);
    *(a+i)=*(a+i+1);
    *(a+i+1)=temp;
}

void showStep(int* a,int step, int& i)
{
     if(step==1)
         up(a);
     if(step==2)
         down(a);
     if(step==3)
         left(a);
     if(step==4)
         right(a);
     i++;
}
