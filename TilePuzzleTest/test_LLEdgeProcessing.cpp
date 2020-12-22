
#include <gtest/gtest.h>

#include "Source1.h"

TEST(LLEdgeProcessing, test_4x4_1) {
    const int arr[] = {
        1, 2, 3, 4,
        5, 11, 12, 7,
        9, 15, 8, 6,
        10, 14, 13, 0,
    };
    int* arrMalloc = new int[16];
    memcpy((char*)arrMalloc, (char*)arr, sizeof(int) * 16);
    LLEdgeProcessing(arrMalloc, 13, 4);
    ASSERT_EQ(13, arrMalloc[12]);

    delete[] arrMalloc;
}

TEST(LLEdgeProcessing, test_5x5_1) {
    const int arr[] = {
        1, 2, 3, 4, 5,
        6, 10, 17, 7, 9,
        11, 15, 19, 21, 20,
        16, 0, 22, 24, 23,
        14, 12, 13, 8, 18,
    };
    int* arrMalloc = new int[25];
    memcpy((char*)arrMalloc, (char*)arr, sizeof(int) * 25);
    LLEdgeProcessing(arrMalloc, 21, 5);
    ASSERT_EQ(21, arrMalloc[20]);

    delete[] arrMalloc;
}

TEST(LLEdgeProcessing, test_5x5_2) {
    const int arr[] = {
        1, 2, 3, 4, 5,
        6, 20, 21, 22, 8,
        11, 24, 12, 7, 9,
        16, 0, 15, 14, 17,
        13, 19, 18, 23, 10,
    };
    int* arrMalloc = new int[25];
    memcpy((char*)arrMalloc, (char*)arr, sizeof(int) * 25);
    LLEdgeProcessing(arrMalloc, 21, 5);
    ASSERT_EQ(21, arrMalloc[20]);

    delete[] arrMalloc;
}


