#include <gtest/gtest.h>
#include "Interval.h"

TEST(IntervalTest, IntervalSize) {
    Interval test1(3,7);
    Interval test2(-2e9, 2e9);
    Interval test3(0.0, 0.0);
    EXPECT_EQ(test1.size(), 4.0);
    EXPECT_EQ(test2.size(), 4e9);
    EXPECT_EQ(test3.size(), 0.0);
}

TEST(IntervalTest, EmptyInterval) {
    Interval test1;
    Interval test2(1.0, -1.0);
    Interval test3(1.0, 1.0);
    Interval test4(2,5);
    Interval test5(-2e9, 2e9);
    EXPECT_EQ(test1.empty(), true);
    EXPECT_EQ(test2.empty(), true);
    EXPECT_EQ(test3.empty(), false);
    EXPECT_EQ(test4.empty(), false);
    EXPECT_EQ(test5.empty(), false);
}

TEST(IntervalTest, IntervalContains) {
    Interval test1(-5.0, -1.0);
    EXPECT_EQ(test1.contains(-4.9999999999999), true);
    EXPECT_EQ(test1.contains(-5.0), true);
    EXPECT_EQ(test1.contains(-1.0), true);
    EXPECT_EQ(test1.exclusiveContains(-5.0), false);
    EXPECT_EQ(test1.exclusiveContains(-1.0), false);
    EXPECT_EQ(test1.exclusiveContains(-0.999999999), false);
    EXPECT_EQ(test1.exclusiveContains(-1.00000000000001), true);
    EXPECT_EQ(test1.exclusiveContains(-3.25), true);
}