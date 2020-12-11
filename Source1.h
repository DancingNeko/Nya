#ifndef SOURCE1_H
#define SOURCE1_H

int* entry(int puzzle[], int dimension, int& stepsNeeded);

//
void castPuzzle(int tempPuzzle[], int target, int dim);

// convert puzzle with dimension ${dim} to puzzle with dimension ${dim-1}
int* convertPuzzle(int tempPuzzle[], int dim);

//LOWER LEFT corner processing: put the last piece of puzzle on the left column
void LLEdgeProcessing(int tempPuzzle[], int target, int dim); 

//UPPER RIGHT corner processing: put the last piece of puzzle on the top roll
void UREdgeProcessing(int tempPuzzle[], int target, int dim);

#endif // SOURCE1_H
