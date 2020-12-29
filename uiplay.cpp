
#include <assert.h>
#include "uiplay.h"

void setPuzzleColor(const int * tempPuzzle, QPushButton * buttons[], int size) {
    assert(tempPuzzle != nullptr);
    assert(size > 0);

    QString strSpaceStyle("background-color:rgb(0,0,0)");
    QString strTileStyle("background-color:rgb(255, 255, 255)");
    for (int i = 0; i < size; i++) {
        assert(buttons[i] != nullptr);
        buttons[i]->setStyleSheet(tempPuzzle[i] == 0 ? strSpaceStyle : strTileStyle);
    }
}

void setPuzzleColor(const int* b, Ui::MainWindow* ui, int size)
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


void setPuzzleText(const int * tempPuzzle, QPushButton * buttons[], int size) {
    assert(tempPuzzle != nullptr);
    assert(size > 0);

    for (int i = 0; i < size; i++) {
        assert(buttons[i] != nullptr);
        buttons[i]->setText(QString::number(tempPuzzle[i]));
    }
}

void setPuzzleText(const int* tempPuzzle, Ui::MainWindow* ui, int size)
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
