#include <gtest/gtest.h>

#include "Source1.h"

class Test_castPuzzle_Case : public testing::Test {
protected:
    virtual void SetUp() {
        int arr[] = {
            1, 3, 14, 5,
            13, 2, 4, 0,
            15, 7, 11, 12,
            6, 8, 10, 9,
        };
        memcpy((char*)puzzle_, (char*)arr, sizeof(int) * PUZZLE_SIZE);
    }
    virtual void TearDown() {}

protected:
    enum {PUZZLE_SIZE=16};
    int puzzle_[PUZZLE_SIZE];
};

TEST_F(Test_castPuzzle_Case, test_1) {
    castPuzzle(this->puzzle_, 1, 4);
    ASSERT_EQ(puzzle_[0], 1);

    castPuzzle(puzzle_, 2, 4);
    ASSERT_EQ(puzzle_[0], 1);
    ASSERT_EQ(puzzle_[1], 2);

    castPuzzle(puzzle_, 3, 4);
    ASSERT_EQ(puzzle_[0], 1);
    ASSERT_EQ(puzzle_[1], 2);
    ASSERT_EQ(puzzle_[2], 3);

    castPuzzle(puzzle_, 5, 4);
    ASSERT_EQ(puzzle_[0], 1);
    ASSERT_EQ(puzzle_[1], 2);
    ASSERT_EQ(puzzle_[2], 3);
    ASSERT_EQ(puzzle_[4], 5);

    castPuzzle(puzzle_, 9, 4);
    ASSERT_EQ(puzzle_[0], 1);
    ASSERT_EQ(puzzle_[1], 2);
    ASSERT_EQ(puzzle_[2], 3);
    ASSERT_EQ(puzzle_[4], 5);
    ASSERT_EQ(puzzle_[8], 9);
}
