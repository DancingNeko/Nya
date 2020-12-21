
#include <gtest/gtest.h>
#include "Source1.h"

TEST(convertPuzzle, test_4x4_to_3x3) {
    static int arr[] = {
        1, 2, 3, 4,
        5, 15, 14, 12,
        9, 11, 10, 8,
        13, 7, 6, 0,
    };
    int* arrMalloc = new int[16];
    memcpy((char*)arrMalloc, (char*)arr, sizeof(int) * 16);
    int* arrConverted = convertPuzzle(arrMalloc, 4);
    ASSERT_EQ(arrConverted[0], 8);
    ASSERT_EQ(arrConverted[1], 7);
    ASSERT_EQ(arrConverted[2], 6);
    ASSERT_EQ(arrConverted[3], 5);
    ASSERT_EQ(arrConverted[4], 4);
    ASSERT_EQ(arrConverted[5], 3);
    ASSERT_EQ(arrConverted[6], 2);
    ASSERT_EQ(arrConverted[7], 1);
    ASSERT_EQ(arrConverted[8], 0);
    delete[]arrConverted;
    arrConverted = nullptr;
}

TEST(convertPuzzle, test_3x3_to_2x2) {
    static int arr[] = {
        1, 2, 3,
        4, 6, 5,
        7, 0, 8,
    };
    int* arrMalloc = new int[9];
    memcpy((char*)arrMalloc, arr, sizeof(int) * 9);
    int* arrConverted = convertPuzzle(arrMalloc, 3);
    ASSERT_EQ(arrConverted[0], 2);
    ASSERT_EQ(arrConverted[1], 1);
    ASSERT_EQ(arrConverted[2], 0);
    ASSERT_EQ(arrConverted[3], 3);
    delete[]arrConverted;
    arrConverted = nullptr;
}

