#ifndef PLAY_H
#define PLAY_H
#include <ui_mainwindow.h>
void showStep(int* a, int step,int& i);
int* autoComplete(int array[], Ui::MainWindow* ui,int* s);
bool checkComplete(int* a, int size);
int tile_puzzle(int a[]);
int* initializePuzzle(int a[],int depth, int size);
void setNum(int* a, int choice);
int checkSlider(int* a);
void moveSlide(int* a, int n, int slider);
int operate(int* a, int move, int size);
void setColor(int* a,Ui::MainWindow* ui, int size);
void setText(int* a, Ui::MainWindow* ui, int size);
#endif // PLAY_H
