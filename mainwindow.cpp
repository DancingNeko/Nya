#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"play.h"
#include<iostream>
#include<QProcess>
#include<windows.h>
#include<QtCore>
#include<QWidget>
#include <QMessageBox>
using namespace std;

int autoSpeed=1000;
int* a = new int [9];
int* b= new int [16];
int stepCount=0;
int paused=-1;
int dimension;
QImage BCImage1(QString(":/frame1.png"));
QImage BCImage2(QString(":/frame2.png"));
QImage BCImage(QString(":/frame.png"));
QImage BCImage4(QString(":/animeCongrats.png"));
QImage BCImage3(QString(":frame3.png"));
int* steps;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->pushButton_4->setVisible(false);
    ui->pushButton_5->setVisible(false);
    ui->pushButton_6->setVisible(false);
    ui->pushButton_7->setVisible(false);
    ui->pushButton_8->setVisible(false);
    ui->pushButton_9->setVisible(false);
    ui->four_1->setVisible(false);
    ui->four_2->setVisible(false);
    ui->four_3->setVisible(false);
    ui->four_4->setVisible(false);
    ui->four_5->setVisible(false);
    ui->four_6->setVisible(false);
    ui->four_7->setVisible(false);
    ui->four_8->setVisible(false);
    ui->four_9->setVisible(false);
    ui->four_10->setVisible(false);
    ui->four_11->setVisible(false);
    ui->four_12->setVisible(false);
    ui->four_13->setVisible(false);
    ui->four_14->setVisible(false);
    ui->four_15->setVisible(false);
    ui->four_16->setVisible(false);
    QFont font("Arial",60,20);
    ui->pushButton->setFont(font);
    ui->pushButton_2->setFont(font);
    ui->pushButton_3->setFont(font);
    ui->pushButton_4->setFont(font);
    ui->pushButton_5->setFont(font);
    ui->pushButton_6->setFont(font);
    ui->pushButton_7->setFont(font);
    ui->pushButton_8->setFont(font);
    ui->pushButton_9->setFont(font);
    ui->four_1->setFont(font);
    ui->four_2->setFont(font);
    ui->four_3->setFont(font);
    ui->four_4->setFont(font);
    ui->four_5->setFont(font);
    ui->four_6->setFont(font);
    ui->four_7->setFont(font);
    ui->four_8->setFont(font);
    ui->four_9->setFont(font);
    ui->four_10->setFont(font);
    ui->four_11->setFont(font);
    ui->four_12->setFont(font);
    ui->four_13->setFont(font);
    ui->four_14->setFont(font);
    ui->four_15->setFont(font);
    ui->four_16->setFont(font);
    ui->pushButton_9->setStyleSheet("background-color:rgb(0,0,0)");
    QFont fontS("MS Shell Dlg",25,20);
    ui->pushButton_14->setFont(fontS);
    for(int i=0;i<9;i++)
    {
        *(a+i)=i+1;
    }
    *(a+8)=0;
    for(int i=0;i<16;i++)
    {
        *(b+i)=i+1;
    }
    *(b+15)=0;
    ui->label_6->setPixmap(QPixmap::fromImage(BCImage));
    ui->pushButton_10->setStyleSheet("background-color:rgb(142,196,255); color:rgb(255,255,255)");
    ui->restart_2->setStyleSheet("background-color:rgb(142,196,255); color:rgb(255,255,255)");
    ui->pushButton_14->setStyleSheet("background-color:rgb(142,196,255); color:rgb(255,255,255)");
    ui->pushButton_11->setStyleSheet("background-color:rgb(142,196,255); color:rgb(255,255,255)");
    ui->pushButton_12->setStyleSheet("background-color:rgb(142,196,255); color:rgb(255,255,255)");
    ui->pushButton_13->setStyleSheet("background-color:rgb(142,196,255); color:rgb(255,255,255)");
    ui->pushButton_15->setStyleSheet("background-color:rgb(142,196,255); color:rgb(255,255,255)");
    ui->close->setStyleSheet("background-color:rgb(142,196,255); color:rgb(255,255,255)");
    ui->restart->setStyleSheet("background-color:rgb(142,196,255); color:rgb(255,255,255)");
    ui->reset->setStyleSheet("background-color:rgb(142,196,255); color:rgb(255,255,255)");
    ui->label_2->setStyleSheet("color:rgb(255,255,255)");
    ui->label_3->setStyleSheet("color:rgb(255,255,255)");
    ui->label_4->setStyleSheet("color:rgb(255,255,255)");
    ui->label_5->setStyleSheet("color:rgb(255,255,255)");
    ui->label->setPixmap(QPixmap::fromImage(BCImage4));
    ui->label->setVisible(false);
    ui->reset->setVisible(false);
    ui->restart->setVisible(false);
    ui->close->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_10_clicked()
{
    dimension = 3;
    a=initializePuzzle(a,100000,9);
    setText(a,ui,9);
    setColor(a,ui,9);
    ui->pushButton->setVisible(true);
    ui->pushButton_2->setVisible(true);
    ui->pushButton_3->setVisible(true);
    ui->pushButton_4->setVisible(true);
    ui->pushButton_5->setVisible(true);
    ui->pushButton_6->setVisible(true);
    ui->pushButton_7->setVisible(true);
    ui->pushButton_8->setVisible(true);
    ui->pushButton_9->setVisible(true);
    ui->pushButton_10->setVisible(true);
    ui->pushButton_10->setVisible(false);
    ui->pushButton_15->setVisible(false);
}

void MainWindow::on_pushButton_clicked()
{
    operate(a,0,9);
    setText(a,ui,9);
    setColor(a,ui,9);
}

void MainWindow::on_pushButton_2_clicked()
{
    operate(a,1,9);
    setText(a,ui,9);
    setColor(a,ui,9);
}

void MainWindow::on_pushButton_3_clicked()
{
    operate(a,2,9);
    setText(a,ui,9);
    setColor(a,ui,9);
}

void MainWindow::on_pushButton_4_clicked()
{
    operate(a,3,9);
    setText(a,ui,9);
    setColor(a,ui,9);
}

void MainWindow::on_pushButton_5_clicked()
{
    operate(a,4,9);
    setText(a,ui,9);
    setColor(a,ui,9);
}

void MainWindow::on_pushButton_6_clicked()
{
    operate(a,5,9);
    setText(a,ui,9);
    setColor(a,ui,9);
}

void MainWindow::on_pushButton_7_clicked()
{
    operate(a,6,9);
    setText(a,ui,9);
    setColor(a,ui,9);
}

void MainWindow::on_pushButton_8_clicked()
{
    operate(a,7,9);
    setText(a,ui,9);
    setColor(a,ui,9);
}

void MainWindow::on_pushButton_9_clicked()
{
    operate(a,8,9);
    setText(a,ui,9);
    setColor(a,ui,9);
    if(checkComplete(a, 9))
    {
        repaint();
        Sleep(1000);
        ui->label->setVisible(true);
        repaint();
        Sleep(1000);
        ui->restart->setVisible(true);
        ui->restart->raise();
        ui->close->setVisible(true);
        ui->close->raise();
    }
}


void MainWindow::on_pushButton_11_clicked()
{
    ui->label_6->setPixmap(QPixmap::fromImage(BCImage));
    ui->pushButton_10->setStyleSheet("background-color:rgb(142,196,255); color:rgb(255,255,255)");
    ui->pushButton_14->setStyleSheet("background-color:rgb(142,196,255); color:rgb(255,255,255)");
    ui->pushButton_11->setStyleSheet("background-color:rgb(142,196,255); color:rgb(255,255,255)");
    ui->pushButton_12->setStyleSheet("background-color:rgb(142,196,255); color:rgb(255,255,255)");
    ui->pushButton_13->setStyleSheet("background-color:rgb(142,196,255); color:rgb(255,255,255)");
    ui->label_2->setStyleSheet("color:rgb(255,255,255)");
    ui->label_3->setStyleSheet("color:rgb(255,255,255)");
    ui->label_4->setStyleSheet("color:rgb(255,255,255)");
    ui->label_5->setStyleSheet("color:rgb(255,255,255)");
}

void MainWindow::on_pushButton_12_clicked()
{
    ui->label_6->setPixmap(QPixmap::fromImage(BCImage1));
    ui->pushButton_10->setStyleSheet("background-color:rgb(65,187,105); color:rgb(255,255,255)");
    ui->pushButton_14->setStyleSheet("background-color:rgb(65,187,105); color:rgb(255,255,255)");
    ui->pushButton_11->setStyleSheet("background-color:rgb(65,187,105); color:rgb(255,255,255)");
    ui->pushButton_12->setStyleSheet("background-color:rgb(65,187,105); color:rgb(255,255,255)");
    ui->pushButton_13->setStyleSheet("background-color:rgb(65,187,105); color:rgb(255,255,255)");
    ui->label_2->setStyleSheet("color:rgb(255,255,255)");
    ui->label_3->setStyleSheet("color:rgb(255,255,255)");
    ui->label_4->setStyleSheet("color:rgb(255,255,255)");
    ui->label_5->setStyleSheet("color:rgb(255,255,255)");
}

int Switch=0;
void MainWindow::on_pushButton_13_clicked()
{
    Switch++;
    if(Switch%2==1)
    ui->label_6->setPixmap(QPixmap::fromImage(BCImage2));
    if(Switch%2==0)
    ui->label_6->setPixmap(QPixmap::fromImage(BCImage3));
    repaint();
    ui->pushButton_10->setStyleSheet("background-color:rgb(43,45,122); color:rgb(255,180,241)");
    ui->pushButton_14->setStyleSheet("background-color:rgb(43,45,122); color:rgb(255,180,241)");
    ui->pushButton_11->setStyleSheet("background-color:rgb(43,45,122); color:rgb(255,180,241)");
    ui->pushButton_12->setStyleSheet("background-color:rgb(43,45,122); color:rgb(255,180,241)");
    ui->pushButton_13->setStyleSheet("background-color:rgb(43,45,122); color:rgb(255,180,241)");
    ui->label_2->setStyleSheet("color:rgb(255,180,241)");
    ui->label_3->setStyleSheet("color:rgb(255,180,241)");
    ui->label_4->setStyleSheet("color:rgb(255,180,241)");
    ui->label_5->setStyleSheet("color:rgb(255,180,241)");
}


void MainWindow::on_pushButton_14_toggled(bool checked)
{
    int i=0;
    int stepsNeeded;
    if(checked)
        paused++;
    //auto reply = QMessageBox::question(this, "Save", "Do you want to save your changes?",
    //    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if(paused == 0 && dimension == 3)
    {
        steps = entry(a, dimension, stepsNeeded);
    }
    if(paused == 0 && dimension == 4)
    {
        steps = entry(b, dimension, stepsNeeded);
    }
    //auto reply_1 = QMessageBox::question(this, "Save", "Do you want to save your changes?",
    //    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if(dimension==3)
    {
        while(checked && paused==0)
        {
            if(checkComplete(a,dimension*dimension))
            {

                Sleep(1000);
                ui->label->setVisible(true);
                ui->label->raise();
                repaint();
                Sleep(1000);
                break;
            }
            QApplication::processEvents();
            QString stepCountNum=QString::number(i);
            ui->pushButton_14->setText(stepCountNum);
            showStep(a, *(steps+stepCount), stepCount, dimension);
            setText(a,ui,dimension*dimension);
            setColor(a,ui,dimension*dimension);
            ui->pushButton->repaint();
            ui->pushButton_2->repaint();
            ui->pushButton_3->repaint();
            ui->pushButton_4->repaint();
            ui->pushButton_5->repaint();
            ui->pushButton_6->repaint();
            ui->pushButton_7->repaint();
            ui->pushButton_8->repaint();
            ui->pushButton_9->repaint();
            Sleep(autoSpeed);
            repaint();
            i++;
        }
    }
    if(dimension==4)
    {
        while(checked && paused==0)
        {
            if(checkComplete(b,dimension*dimension))
            {

                Sleep(1000);
                ui->label->setVisible(true);
                ui->label->raise();
                repaint();
                Sleep(1000);
                break;
            }
            QApplication::processEvents();
            QString stepCountNum=QString::number(i);
            ui->pushButton_14->setText(stepCountNum);
            showStep(b, *(steps+stepCount), stepCount, dimension);
            setText(b,ui,dimension*dimension);
            setColor(b,ui,dimension*dimension);
            ui->centralwidget->repaint();
            Sleep(autoSpeed);
            i++;
        }
    }
    if(!checkComplete(a,dimension*dimension)&&dimension==3)
    {
        paused++;
        ui->reset->setVisible(true);
        repaint();
    }
    if(checkComplete(a,dimension*dimension)&&dimension==3)
    {
        ui->restart->setVisible(true);
        ui->restart->raise();
        ui->close->setVisible(true);
        ui->close->raise();
    }
    if(!checkComplete(b,dimension*dimension)&&dimension==4)
    {
        paused++;
        ui->reset->setVisible(true);
        repaint();
    }
    if(checkComplete(b,dimension*dimension)&&dimension==4)
    {
        ui->restart->setVisible(true);
        ui->restart->raise();
        ui->close->setVisible(true);
        ui->close->raise();
    }
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    autoSpeed=1000-10*value;
    QString speedInfo;
    if(value<40)
        speedInfo="slow";
    if(value>=40 && value<=80)
        speedInfo="medium";
    if(value>80)
        speedInfo="fast";
    ui->label_4->setText(speedInfo);
    repaint();
}

void MainWindow::on_reset_clicked()
{
    delete[] steps;
    steps=NULL;
    paused=-1;
    stepCount=0;
    ui->pushButton_14->setText("Auto");
    ui->reset->setVisible(false);
}

void MainWindow::on_close_clicked()
{
     QCoreApplication::exit(0);
}

void MainWindow::on_restart_clicked()
{
    QCoreApplication::exit(0);
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void MainWindow::on_four_1_clicked()
{
    operate(b,0,16);
    setText(b,ui,16);
    setColor(b,ui,16);
}

void MainWindow::on_four_2_clicked()
{
    operate(b,1,16);
    setText(b,ui,16);
    setColor(b,ui,16);
}

void MainWindow::on_four_3_clicked()
{
    operate(b,2,16);
    setText(b,ui,16);
    setColor(b,ui,16);
}

void MainWindow::on_four_4_clicked()
{
    operate(b,3,16);
    setText(b,ui,16);
    setColor(b,ui,16);
}

void MainWindow::on_four_5_clicked()
{
    operate(b,4,16);
    setText(b,ui,16);
    setColor(b,ui,16);
}

void MainWindow::on_four_6_clicked()
{
    operate(b,5,16);
    setText(b,ui,16);
    setColor(b,ui,16);
}

void MainWindow::on_four_7_clicked()
{
    operate(b,6,16);
    setText(b,ui,16);
    setColor(b,ui,16);
}

void MainWindow::on_four_8_clicked()
{
    operate(b,7,16);
    setText(b,ui,16);
    setColor(b,ui,16);
}

void MainWindow::on_four_9_clicked()
{
    operate(b,8,16);
    setText(b,ui,16);
    setColor(b,ui,16);
}

void MainWindow::on_four_10_clicked()
{
    operate(b,9,16);
    setText(b,ui,16);
    setColor(b,ui,16);
}

void MainWindow::on_four_11_clicked()
{
    operate(b,10,16);
    setText(b,ui,16);
    setColor(b,ui,16);
}

void MainWindow::on_four_12_clicked()
{
    operate(b,11,16);
    setText(b,ui,16);
    setColor(b,ui,16);
}

void MainWindow::on_four_13_clicked()
{
    operate(b,12,16);
    setText(b,ui,16);
    setColor(b,ui,16);
}

void MainWindow::on_four_14_clicked()
{
    operate(b,13,16);
    setText(b,ui,16);
    setColor(b,ui,16);
}

void MainWindow::on_four_15_clicked()
{
    operate(b,14,16);
    setText(b,ui,16);
    setColor(b,ui,16);
}

void MainWindow::on_four_16_clicked()
{
    operate(b,15,16);
    setText(b,ui,16);
    setColor(b,ui,16);
    if(checkComplete(b, 16))
    {
        cout<<"done"<<endl;
        repaint();
        Sleep(1000);
        ui->label->setVisible(true);
        ui->label->raise();
        repaint();
        Sleep(1000);
        ui->restart->setVisible(true);
        ui->restart->raise();
        ui->close->setVisible(true);
        ui->close->raise();
    }
}

void MainWindow::on_pushButton_15_clicked()
{
    dimension = 4;
    b=initializePuzzle(b,100000,16);
    setText(b,ui,16);
    setColor(b,ui,16);
    ui->four_1->setVisible(true);
    ui->four_2->setVisible(true);
    ui->four_3->setVisible(true);
    ui->four_4->setVisible(true);
    ui->four_5->setVisible(true);
    ui->four_6->setVisible(true);
    ui->four_7->setVisible(true);
    ui->four_8->setVisible(true);
    ui->four_9->setVisible(true);
    ui->four_10->setVisible(true);
    ui->four_11->setVisible(true);
    ui->four_12->setVisible(true);
    ui->four_13->setVisible(true);
    ui->four_14->setVisible(true);
    ui->four_15->setVisible(true);
    ui->four_16->setVisible(true);
    ui->pushButton_10->setVisible(false);
    ui->pushButton_15->setVisible(false);
    ui->pushButton_14->setVisible(true);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    ui->label_5->setVisible(true);
    ui->horizontalSlider->setVisible(true);
}


void MainWindow::on_restart_2_clicked()
{
    QCoreApplication::exit(0);
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}
