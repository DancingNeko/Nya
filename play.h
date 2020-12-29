#ifndef PLAY_H
#define PLAY_H

void showStep(int* a, int step,int& i, int dim);
bool checkComplete(int* a, int size);
int tile_puzzle(int a[]);
int* initializePuzzle(int a[],int depth, int size);
void setNum(int* a, int choice);
int checkSlider(int* a);
void moveSlide(int* a, int n, int slider);
int operate(int* a, int move, int size);

#endif // PLAY_H
