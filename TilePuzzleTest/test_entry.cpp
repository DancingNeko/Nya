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
