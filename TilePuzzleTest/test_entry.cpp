#include <gtest/gtest.h>

#include "Source1.h"

TEST(entry, test_1) {
    static int arr[] = {
        0, 2, 3, 4,
        1, 9, 5, 8,
        11, 7, 6, 15,
        13, 10, 12, 14,
    };
    int* arrMalloc = new int[16];
    memcpy((char*)arrMalloc, (char*)arr, sizeof(int) * 16);
    int stepCount = 0;
    int* theSteps = entry(arrMalloc, 4, stepCount);
    ASSERT_GT(stepCount, 0);
    delete[]theSteps;
    theSteps = nullptr;
}

TEST(entry, test_hang_case) {
    static int arr[] = {
        2, 3, 5, 4,
        1, 13, 10, 9,
        15, 7, 0, 8,
        6, 11, 12, 14,
    };
    int* arrMalloc = new int[16];
    memcpy((char*)arrMalloc, (char*)arr, sizeof(int) * 16);
    int stepCount = 0;
    int* theSteps = entry(arrMalloc, 4, stepCount);
    ASSERT_GT(stepCount, 0);
    delete[]theSteps;
    theSteps = nullptr;
}

TEST(entry, test_5x5_puzzle) {
    static int arr[] = {
        14, 4, 10, 9, 1,
        20, 17, 16, 23, 6,
        8, 7, 11, 15, 21,
        13, 2, 3, 19, 0,
        12, 22, 5, 24, 18,
    };

    int* arrMalloc = new int[25];
    memcpy((char*)arrMalloc, (char*)arr, sizeof(int) * 25);
    int stepCount = 0;
    int* theSteps = entry(arrMalloc, 5, stepCount);
    ASSERT_GT(stepCount, 0);
    delete[]theSteps;
    theSteps = nullptr;
}

TEST(entry, test_5x5_puzzle_1) {
    int arr[] = {
        1, 20, 2, 16, 7,
        24, 18, 0, 22, 9,
        14, 6, 4, 17, 21,
        11, 5, 13, 23, 3,
        19, 12, 8, 15, 10,
    };
    int* arrMalloc = new int[25];
    memcpy((char*)arrMalloc, (char*)arr, sizeof(int) * 25);
    int stepCount = 0;
    int* theSteps = entry(arrMalloc, 5, stepCount);
    ASSERT_GT(stepCount, 0);
    delete[]theSteps;
    theSteps = nullptr;
}
