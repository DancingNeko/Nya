
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <gtest/gtest.h>

/// #include "tilepuzzleconsole.h"

using namespace std;

/// const int MIN_DIMENSION_SIZE = 3;
/// const int MAX_DIMENSION_SIZE = 4;
/// 
/// bool input_num(int& dim, int min_value, int max_value) {
///     dim = -1;
///     char buf[256];
///     sprintf_s(buf, 255, "please input valid value (value >= %d, value <= %d)", min_value, max_value);
///     while ((dim < min_value || dim > max_value) && dim != 0) {
///         cout << buf << endl;
///         cin >> dim;
///     }
///     return dim != 0;
/// }
/// 
/// bool check_puzzle(int* a, int dim) {
///     set<int> validSet;
///     for (int i = 0; i < dim * dim; i++) {
///         validSet.insert(a[i]);
///     }
///     return validSet.size() == (size_t)dim * dim;
/// }
/// 
/// bool input_puzzle(int* a, int dim) {
///     cout << "please input puzzle: " << endl;
///     for (int i = 0; i < dim * dim; i++) {
///         cout << "the " << i << "th value:" << endl;
///         input_num(a[i], 0, dim * dim);
///     }
///     // check duplicate values
///     return check_puzzle(a, dim);
/// }
/// 
/// void print_puzzle(int* a, int dim) {
///     cout << "puzzle: " << endl;
///     for (int i = 0; i < dim; i++) {
///         for (int j = 0; j < dim; j++) {
///             cout << a[i * dim + j] << " ";
///         }
///         cout << endl;
///     }
/// }
/// 
/// int testWithInput(int argc, char** argv) {
/// 
///     int dim = 0;
///     input_num(dim, MIN_DIMENSION_SIZE, MAX_DIMENSION_SIZE);
///     if (dim == 0) {
///         return 0;
///     }
///     assert(dim > 2);
///     assert(dim < 5);
///     int* puzzle = new int[(size_t)dim * dim];
///     memset(puzzle, 0, sizeof(int) * dim * dim);
///     bool ret = input_puzzle(puzzle, dim);
///     if (!ret) {
///         cout << "Invalid puzzle" << endl;
///         return 0;
///     }
///     print_puzzle(puzzle, dim);
///     int steps = 0;
///     entry(puzzle, dim, steps);
///     cout << "done. steps: " << steps << endl;
///     return 0;
/// }

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

