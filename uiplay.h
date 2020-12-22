#ifndef UIPLAY_H
#define UIPLAY_H
#include <ui_mainwindow.h>

void setPuzzleColor(const int * tempPuzzle, QPushButton * buttons[], int size);
void setPuzzleColor(const int* a,Ui::MainWindow* ui, int size);
void setPuzzleText(const int * tempPuzzle, QPushButton * buttons[], int size);
void setPuzzleText(const int* a, Ui::MainWindow* ui, int size);

#endif // UIPLAY_H
