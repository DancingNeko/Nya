#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"play.h"
#include<iostream>
#include<QProcess>
#include<windows.h>
#include<QtCore>
#include<QWidget>
using namespace std;

int autoSpeed=1000;
int stepSize=150;
int* a = new int [9];
int* s=new int[stepSize];
int stepCount=0;
int paused=-1;
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
}

void MainWindow::on_pushButton_2_clicked()
{
    operate(a,1);
    setText(a,ui);
    setColor(a,ui);
}

void MainWindow::on_pushButton_3_clicked()
{
    operate(a,2);
    setText(a,ui);
    setColor(a,ui);
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
}

void MainWindow::on_pushButton_6_clicked()
{
    operate(a,5);
    setText(a,ui);
    setColor(a,ui);
}

void MainWindow::on_pushButton_7_clicked()
{
    operate(a,6);
    setText(a,ui);
    setColor(a,ui);
}

void MainWindow::on_pushButton_8_clicked()
{
    operate(a,7);
    setText(a,ui);
    setColor(a,ui);
}

void MainWindow::on_pushButton_9_clicked()
{
    operate(a,8);
    setText(a,ui);
    setColor(a,ui);
    if(checkComplete(a, ui))
    {
        repaint();
        Sleep(1000);
        ui->label->setVisible(true);
        repaint();
        Sleep(4000);
        QCoreApplication::exit(0);
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
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


void MainWindow::on_pushButton_14_toggled(bool checked)
{
    if(stepCount == 0)
    {
    s=autoComplete(a, ui, s);
    }
    int i=0;
    if(checked)
        paused++;
    while(checked && paused==0)
    {
        if(checkComplete(a,ui))
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
        showStep(a, *(s+stepCount), stepCount);
        setText(a,ui);
        setColor(a,ui);
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
    if(!checkComplete(a,ui))
    {
        paused++;
        ui->reset->setVisible(true);
        repaint();
    }
    if(checkComplete(a,ui))
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
    for(int i=0;i<stepSize;i++)
    {
        *(s+i)=0;
    }
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
