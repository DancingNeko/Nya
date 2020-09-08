#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"play.h"
#include<iostream>
#include<QProcess>
#include<windows.h>
using namespace std;

int autoSpeed=1000;
int stepSize=150;
int* a = new int [9];
int* s=new int[stepSize];
int stepCount=0;
QImage BCImage1(QString(":/frame1.png"));
QImage BCImage2(QString(":/frame2.png"));
QImage BCImage(QString(":/frame.png"));
QImage BCImage4(QString(":/animeCongrats.png"));

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFont font("SimSun-ExtB",60,75);
    ui->pushButton->setFont(font);
    ui->pushButton_2->setFont(font);
    ui->pushButton_3->setFont(font);
    ui->pushButton_4->setFont(font);
    ui->pushButton_5->setFont(font);
    ui->pushButton_6->setFont(font);
    ui->pushButton_7->setFont(font);
    ui->pushButton_8->setFont(font);
    ui->pushButton_9->setFont(font);
    ui->pushButton_9->setStyleSheet("background-color:rgb(0,0,0)");
    QFont fontS("MS Shell Dlg",25,20);
    ui->pushButton_14->setFont(fontS);
    ui->pushButton_14->setStyleSheet("background-color:rgb(0,0,0); color:rgb(255,255,255)");
    for(int i=0;i<9;i++)
    {
        *(a+i)=i+1;
    }
    *(a+8)=0;
    setText(a,ui);
    setColor(a,ui);
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
    ui->label->setPixmap(QPixmap::fromImage(BCImage4));
    ui->label->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_10_clicked()
{
    a=initializePuzzle(a,100000);
    setText(a,ui);
    setColor(a,ui);
    ui->pushButton_10->setVisible(false);
}

void MainWindow::on_pushButton_clicked()
{
    operate(a,0);
    setText(a,ui);
    setColor(a,ui);
    checkComplete(a, ui);
}

void MainWindow::on_pushButton_2_clicked()
{
    operate(a,1);
    setText(a,ui);
    setColor(a,ui);
    checkComplete(a, ui);
}

void MainWindow::on_pushButton_3_clicked()
{
    operate(a,2);
    setText(a,ui);
    setColor(a,ui);
   checkComplete(a, ui);
}

void MainWindow::on_pushButton_4_clicked()
{
    operate(a,3);
    setText(a,ui);
    setColor(a,ui);
    checkComplete(a, ui);
}

void MainWindow::on_pushButton_5_clicked()
{
    operate(a,4);
    setText(a,ui);
    setColor(a,ui);
    checkComplete(a, ui);
}

void MainWindow::on_pushButton_6_clicked()
{
    operate(a,5);
    setText(a,ui);
    setColor(a,ui);
    checkComplete(a,ui);
}

void MainWindow::on_pushButton_7_clicked()
{
    operate(a,6);
    setText(a,ui);
    setColor(a,ui);
    checkComplete(a, ui);
}

void MainWindow::on_pushButton_8_clicked()
{
    operate(a,7);
    setText(a,ui);
    setColor(a,ui);
    checkComplete(a, ui);
}

void MainWindow::on_pushButton_9_clicked()
{
    operate(a,8);
    setText(a,ui);
    setColor(a,ui);
    checkComplete(a, ui);
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

void MainWindow::on_pushButton_13_clicked()
{
    ui->label_6->setPixmap(QPixmap::fromImage(BCImage2));
    ui->pushButton_10->setStyleSheet("background-color:rgb(255,158,217); color:rgb(159,116,255)");
    ui->pushButton_14->setStyleSheet("background-color:rgb(255,158,217); color:rgb(159,116,255)");
    ui->pushButton_11->setStyleSheet("background-color:rgb(255,158,217); color:rgb(159,116,255)");
    ui->pushButton_12->setStyleSheet("background-color:rgb(255,158,217); color:rgb(159,116,255)");
    ui->pushButton_13->setStyleSheet("background-color:rgb(255,158,217); color:rgb(159,116,255)");
    ui->label_2->setStyleSheet("color:rgb(159,116,255)");
    ui->label_3->setStyleSheet("color:rgb(159,116,255)");
    ui->label_4->setStyleSheet("color:rgb(159,116,255)");
    ui->label_5->setStyleSheet("color:rgb(159,116,255)");
}

void MainWindow::on_pushButton_14_clicked()
{
    if(stepCount == 0)
    {
    s=autoComplete(a, ui, s);
    }
    while(checkComplete(a,ui))
    {
        showStep(a, *(s+stepCount), stepCount);
        setText(a,ui);
        setColor(a,ui);
        Sleep(autoSpeed);
        repaint();
    }
    repaint();
    Sleep(1000);
    ui->label->setVisible(true);
    repaint();
    Sleep(4000);
    QCoreApplication::exit(0);
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    autoSpeed=1000-10*value;
    QString speedInfo;
    speedInfo=QString::number((float)1000/autoSpeed);
    ui->label_4->setText(speedInfo);
    repaint();
}
