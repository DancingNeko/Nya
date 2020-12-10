#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"play.h"
#include<iostream>
#include<QProcess>
#include<windows.h>
#include<QtCore>
#include<QWidget>
#include <QMessageBox>
#include <QTimer>
#include "utilities.h"
#include <assert.h>
using namespace std;

int autoSpeed=1000;
static int* s_9_puzzle = new int [9];
static int* s_16_puzzle= new int [16];
int stepCount=0;
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
    , paused_(AutoState::kInitial)
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
    ui->reset->setFont(fontS);
    ui->horizontalSlider->setValue(66);
    for(int i=0;i<9;i++)
    {
        *(s_9_puzzle+i)=i+1;
    }
    *(s_9_puzzle+8)=0;
    for(int i=0;i<16;i++)
    {
        *(s_16_puzzle+i)=i+1;
    }
    *(s_16_puzzle+15)=0;
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

    QFont fontTriggerButton;
    fontTriggerButton.setFamily(QString::fromUtf8("Arial Black"));
    fontTriggerButton.setPointSize(30);
    fontTriggerButton.setBold(true);
    fontTriggerButton.setUnderline(true);
    fontTriggerButton.setWeight(75);
    createPentaPuzzle();
    createPentaPuzzleTriggerButton();
    setPentaPuzzleVisibility(false);
    setPentaPuzzleTriggerButtonVisibility(true);
    setPentaPuzzleFontAndStyle(font);
    setPentaPuzzleTriggerButtonFontAndStyle(fontTriggerButton, "background-color:rgb(142,196,255); color:rgb(255,255,255)");
    connectPentaPuzzleTriggerButton();
    connectPentaPuzzle();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createPentaPuzzle() {
    assert(pentaPushButton[0] == nullptr);
    for (int i = 0; i < PENTA; i++) {
        for (int j = 0; j < PENTA; j++) {
            int index = i * PENTA + j;
            pentaPushButton[index] = new QPushButton(ui->centralwidget);
            pentaPushButton[index]->setGeometry(QRect(390 + j*100, 110 + i*100, 100, 100 ));
            pentaPushButton[index]->setObjectName(QString("pentaButton_%1").arg(index));
        }
    }
    setPentaPuzzleText();
}

void MainWindow::setPentaPuzzleText(const int * puzzle) {
    static int default_puzzle[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                                   16, 17, 18, 19, 20, 21, 22, 23, 24, 0};
    if (puzzle == nullptr) {
        puzzle = default_puzzle;
    }
    for (int i = 0; i < PENTA * PENTA; i++) {
        pentaPushButton[i]->setText(QString::number(puzzle[i]));
    }
}

void MainWindow::createPentaPuzzleTriggerButton() {
    assert(pentaPuzzleTriggerButton == nullptr);
    this->pentaPuzzleTriggerButton = new QPushButton(ui->centralwidget);
    pentaPuzzleTriggerButton->setObjectName("pentaPuzzleTriggerButton");
    pentaPuzzleTriggerButton->setGeometry(QRect(515, 450, 250, 100));
    pentaPuzzleTriggerButton->setText(QString("5 x 5"));
}

void MainWindow::setPentaPuzzleTriggerButtonVisibility(bool vis) {
    pentaPuzzleTriggerButton->setVisible(vis);
    if (vis) {
        pentaPuzzleTriggerButton->raise();
    }
}
void MainWindow::setPentaPuzzleVisibility(bool vis) {
    for (int i = 0; i < PENTA * PENTA; i++) {
        assert(pentaPushButton[i] != nullptr);
        pentaPushButton[i]->setVisible(vis);
        if (vis) {
            pentaPushButton[i]->raise();
        }
    }
}

void MainWindow::setPentaPuzzleTriggerButtonFontAndStyle(QFont font, const char *style) {
    assert(pentaPuzzleTriggerButton != nullptr);
    pentaPuzzleTriggerButton->setFont(font);
    if (style == nullptr)
        return;
    pentaPuzzleTriggerButton->setStyleSheet(style);
}
void MainWindow::setPentaPuzzleFontAndStyle(QFont font, const char * style) {
    for (int i = 0; i < PENTA * PENTA; i++) {
        assert(pentaPushButton[i] != nullptr);
        pentaPushButton[i]->setFont(font);
    }
    if (style == nullptr)
        return;
    for (int i = 0; i < PENTA * PENTA; i++) {
        assert(pentaPushButton[i] != nullptr);
        pentaPushButton[i]->setStyleSheet(style);
    }
}
void MainWindow::connectPentaPuzzleTriggerButton() {
    assert(pentaPuzzleTriggerButton != nullptr);
    auto res = connect(pentaPuzzleTriggerButton, SIGNAL(clicked()), this, SLOT(on_penta_puzzle_trigger_clicked()));
}
void MainWindow::connectPentaPuzzle() {
    for (int i = 0; i < PENTA*PENTA; i++) {
        auto res = connect(pentaPushButton[i], SIGNAL(clicked()), this, SLOT(on_penta_puzzle_clicked()));
    }
}


void MainWindow::on_pushButton_10_clicked() // 3 x 3 button
{
    dimension = 3;
    s_9_puzzle=initializePuzzle(s_9_puzzle,100000,9);
    setText(s_9_puzzle,ui,9);
    setColor(s_9_puzzle,ui,9);
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
    setPentaPuzzleTriggerButtonVisibility(false);
    setPentaPuzzleVisibility(false);
}

void MainWindow::on_pushButton_clicked()
{
    operate(s_9_puzzle,0,9);
    setText(s_9_puzzle,ui,9);
    setColor(s_9_puzzle,ui,9);
}

void MainWindow::on_pushButton_2_clicked()
{
    operate(s_9_puzzle,1,9);
    setText(s_9_puzzle,ui,9);
    setColor(s_9_puzzle,ui,9);
}

void MainWindow::on_pushButton_3_clicked()
{
    operate(s_9_puzzle,2,9);
    setText(s_9_puzzle,ui,9);
    setColor(s_9_puzzle,ui,9);
}

void MainWindow::on_pushButton_4_clicked()
{
    operate(s_9_puzzle,3,9);
    setText(s_9_puzzle,ui,9);
    setColor(s_9_puzzle,ui,9);
}

void MainWindow::on_pushButton_5_clicked()
{
    operate(s_9_puzzle,4,9);
    setText(s_9_puzzle,ui,9);
    setColor(s_9_puzzle,ui,9);
}

void MainWindow::on_pushButton_6_clicked()
{
    operate(s_9_puzzle,5,9);
    setText(s_9_puzzle,ui,9);
    setColor(s_9_puzzle,ui,9);
}

void MainWindow::on_pushButton_7_clicked()
{
    operate(s_9_puzzle,6,9);
    setText(s_9_puzzle,ui,9);
    setColor(s_9_puzzle,ui,9);
}

void MainWindow::on_pushButton_8_clicked()
{
    operate(s_9_puzzle,7,9);
    setText(s_9_puzzle,ui,9);
    setColor(s_9_puzzle,ui,9);
}

void MainWindow::on_pushButton_9_clicked()
{
    operate(s_9_puzzle,8,9);
    setText(s_9_puzzle,ui,9);
    setColor(s_9_puzzle,ui,9);
    if(checkComplete(s_9_puzzle, 9))
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
    ui->pushButton_15->setStyleSheet("background-color:rgb(142,196,255); color:rgb(255,255,255)");
    ui->restart_2->setStyleSheet("background-color:rgb(142,196,255); color:rgb(255,255,255)");
    ui->reset->setStyleSheet("background-color:rgb(142,196,255); color:rgb(255,255,255)");
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
    ui->pushButton_15->setStyleSheet("background-color:rgb(65,187,105); color:rgb(255,255,255)");
    ui->restart_2->setStyleSheet("background-color:rgb(65,187,105); color:rgb(255,255,255)");
    ui->reset->setStyleSheet("background-color:rgb(65,187,105); color:rgb(255,255,255)");
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
    ui->pushButton_15->setStyleSheet("background-color:rgb(43,45,122); color:rgb(255,180,241)");
    ui->restart_2->setStyleSheet("background-color:rgb(43,45,122); color:rgb(255,180,241)");
    ui->reset->setStyleSheet("background-color:rgb(43,45,122); color:rgb(255,180,241)");
    ui->label_2->setStyleSheet("color:rgb(255,180,241)");
    ui->label_3->setStyleSheet("color:rgb(255,180,241)");
    ui->label_4->setStyleSheet("color:rgb(255,180,241)");
    ui->label_5->setStyleSheet("color:rgb(255,180,241)");
}

void MainWindow::automate_callback() {
    int* puzzle = dimension == 3 ? s_9_puzzle : s_16_puzzle;
    if (paused_ != kRunning) {
        return;
    }
    if (checkComplete(puzzle, dimension * dimension)) {
        // auto-play completed
        switchAutoState();
        return;
    }
    
    QString stepCountNum = QString::number(stepCount);
    ui->pushButton_14->setText(stepCountNum);
    LOGINFO("automate_callback begin ... ");
    printPuzzle(puzzle, dimension);
    LOGINFO("stepCount: {}", stepCount);
    LOGINFO("automate_callback end ... ");
    showStep(puzzle, steps[stepCount], stepCount, dimension);
    setText(puzzle, ui, dimension * dimension);
    setColor(puzzle, ui, dimension * dimension);
    ui->centralwidget->repaint();
    QTimer::singleShot(autoSpeed, this, &MainWindow::automate_callback);
}

void MainWindow::on_pushButton_14_toggled(bool checked) // Auto button
{
    if (dimension == 0) {
        return;
    }
    int stepsNeeded;
    switchAutoState();
    int* puzzle = dimension == 3 ? s_9_puzzle : s_16_puzzle;
    if(paused_ == kRunning)
    {
        LOGINFO("on_14_toggled begin ...");
        steps = entry(puzzle, dimension, stepsNeeded);
        stepCount = 0;
        printPuzzle(puzzle, dimension);
        LOGINFO("on_14_toggled end ...");
        QTimer::singleShot(autoSpeed, this, &MainWindow::automate_callback);
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
    stepCount=0;

    switchAutoState();
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
    operate(s_16_puzzle,0,16);
    setText(s_16_puzzle,ui,16);
    setColor(s_16_puzzle,ui,16);
}

void MainWindow::on_four_2_clicked()
{
    operate(s_16_puzzle,1,16);
    setText(s_16_puzzle,ui,16);
    setColor(s_16_puzzle,ui,16);
}

void MainWindow::on_four_3_clicked()
{
    operate(s_16_puzzle,2,16);
    setText(s_16_puzzle,ui,16);
    setColor(s_16_puzzle,ui,16);
}

void MainWindow::on_four_4_clicked()
{
    operate(s_16_puzzle,3,16);
    setText(s_16_puzzle,ui,16);
    setColor(s_16_puzzle,ui,16);
}

void MainWindow::on_four_5_clicked()
{
    operate(s_16_puzzle,4,16);
    setText(s_16_puzzle,ui,16);
    setColor(s_16_puzzle,ui,16);
}

void MainWindow::on_four_6_clicked()
{
    operate(s_16_puzzle,5,16);
    setText(s_16_puzzle,ui,16);
    setColor(s_16_puzzle,ui,16);
}

void MainWindow::on_four_7_clicked()
{
    operate(s_16_puzzle,6,16);
    setText(s_16_puzzle,ui,16);
    setColor(s_16_puzzle,ui,16);
}

void MainWindow::on_four_8_clicked()
{
    operate(s_16_puzzle,7,16);
    setText(s_16_puzzle,ui,16);
    setColor(s_16_puzzle,ui,16);
}

void MainWindow::on_four_9_clicked()
{
    operate(s_16_puzzle,8,16);
    setText(s_16_puzzle,ui,16);
    setColor(s_16_puzzle,ui,16);
}

void MainWindow::on_four_10_clicked()
{
    operate(s_16_puzzle,9,16);
    setText(s_16_puzzle,ui,16);
    setColor(s_16_puzzle,ui,16);
}

void MainWindow::on_four_11_clicked()
{
    operate(s_16_puzzle,10,16);
    setText(s_16_puzzle,ui,16);
    setColor(s_16_puzzle,ui,16);
}

void MainWindow::on_four_12_clicked()
{
    operate(s_16_puzzle,11,16);
    setText(s_16_puzzle,ui,16);
    setColor(s_16_puzzle,ui,16);
}

void MainWindow::on_four_13_clicked()
{
    operate(s_16_puzzle,12,16);
    setText(s_16_puzzle,ui,16);
    setColor(s_16_puzzle,ui,16);
}

void MainWindow::on_four_14_clicked()
{
    operate(s_16_puzzle,13,16);
    setText(s_16_puzzle,ui,16);
    setColor(s_16_puzzle,ui,16);
}

void MainWindow::on_four_15_clicked()
{
    operate(s_16_puzzle,14,16);
    setText(s_16_puzzle,ui,16);
    setColor(s_16_puzzle,ui,16);
}

void MainWindow::on_four_16_clicked()
{
    operate(s_16_puzzle,15,16);
    setText(s_16_puzzle,ui,16);
    setColor(s_16_puzzle,ui,16);
    if(checkComplete(s_16_puzzle, 16))
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
    s_16_puzzle=initializePuzzle(s_16_puzzle,100000,16);
    setText(s_16_puzzle,ui,16);
    setColor(s_16_puzzle,ui,16);
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
    setPentaPuzzleTriggerButtonVisibility(false);
    setPentaPuzzleVisibility(false);
}


void MainWindow::on_restart_2_clicked()
{
    QCoreApplication::exit(0);
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void MainWindow::switchAutoState() {
    
    switch (paused_) {
    case kInitial:
        paused_ = kRunning;
        toBeRunning();
        break;
    case kRunning:
    {
        int* puzzle = dimension == 3 ? s_9_puzzle : s_16_puzzle;
        if (checkComplete(puzzle, dimension * dimension)) {
            paused_ = kInitial;
            toBeInitial();
        }
        else {
            paused_ = kPaused;
            toBePaused();
        }
    }
        break;
    case kPaused:
        paused_ = kInitial;
        toBeInitial();
        break;
    default:
        assert(!"Unknown Auto State.");
        break;
    }
}

void MainWindow::toBeRunning() {
    // do nothing
}

void MainWindow::toBePaused() {
    // display reset button and hide auto button
    ui->reset->setVisible(true);
    ui->pushButton_14->setVisible(false);
}

void MainWindow::toBeInitial() {
    // display auto button and hide reset button
    ui->reset->setVisible(false);
    ui->pushButton_14->setText("Auto");
    ui->pushButton_14->setVisible(true);

    int* puzzle = dimension == 3 ? s_9_puzzle : s_16_puzzle;
    if (checkComplete(puzzle, dimension * dimension)) {
        ui->label->setVisible(true);
        ui->label->raise();
        ui->restart->setVisible(true);
        ui->restart->raise();
        ui->close->setVisible(true);
        ui->close->raise();
    }
    else {
        ui->restart->setVisible(false);
        ui->close->setVisible(false);
    }
}

void MainWindow::on_penta_puzzle_trigger_clicked() {
    setPentaPuzzleVisibility(true);
    ui->pushButton_10->setVisible(false);
    ui->pushButton_15->setVisible(false);
    this->pentaPuzzleTriggerButton->setVisible(false);
    ui->label_3->setVisible(true);
    ui->label_4->setVisible(true);
    ui->label_5->setVisible(true);
    ui->horizontalSlider->setVisible(true);
}

static int getPuzzleButtonIndex(QPushButton *puzzle[], QPushButton * btn, int size) {
    for (int i = 0; i < size; i++) {
        if (puzzle[i] == btn)
            return i;
    }
    return -1;
}

void MainWindow::on_penta_puzzle_clicked() {
    auto sender = qobject_cast<QPushButton*>(QObject::sender());
    int ix = getPuzzleButtonIndex(pentaPushButton, sender, PENTA*PENTA);
    assert(ix >= 0);
}
