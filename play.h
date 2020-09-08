#ifndef PLAY_H
#define PLAY_H
#include <ui_mainwindow.h>
void showStep(int* a, int step,int& i);
int* autoComplete(int array[], Ui::MainWindow* ui,int* s);
bool checkComplete(int* a, Ui::MainWindow* ui);
int tile_puzzle(int a[]);
int* initializePuzzle(int a[],int depth);
void setNum(int* a, int choice);
int checkSlider(int* a);
void moveSlide(int* a, int n, int slider);
int operate(int* a, int move);
void setColor(int* a,Ui::MainWindow* ui);
void setText(int* a, Ui::MainWindow* ui);
#endif // PLAY_H
