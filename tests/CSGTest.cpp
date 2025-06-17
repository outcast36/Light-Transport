#include <gtest/gtest.h>
#include "CSG.h"

TEST(CSGTest, MergeLists1) {
    Span test1 = Span::initParametersOnly(1,2);
    Span test2 = Span::initParametersOnly(3,4);
    Span test3 = Span::initParametersOnly(5,11);
    Span test4 = Span::initParametersOnly(1,3);
    Span test5 = Span::initParametersOnly(7,9);
    Span test6 = Span::initParametersOnly(10,11);
    Span test7 = Span::initParametersOnly(12,12);
    std::vector<Span> list1 = {test1, test2, test3};
    std::vector<Span> list2 = {test4, test5, test6, test7};
    std::vector<Span> merged_list = mergeIntervalLists(list1, list2);
    EXPECT_EQ(merged_list.size(), 7);
    EXPECT_EQ(merged_list[0].asInterval().start, 1);
    EXPECT_EQ(merged_list[0].asInterval().end, 3);
    EXPECT_EQ(merged_list[1].asInterval().start, 1);
    EXPECT_EQ(merged_list[1].asInterval().end, 2);
    EXPECT_EQ(merged_list[6].asInterval().start, 12);
    EXPECT_EQ(merged_list[6].asInterval().end, 12);
}

TEST(CSGTest, MergeLists2) {
    Span test1 = Span::initParametersOnly(-10,102746);
    Span test2 = Span::initParametersOnly(-2e9, 2e9);
    std::vector<Span> list1 = {test1};
    std::vector<Span> list2 = {test2};
    std::vector<Span> merged = mergeIntervalLists(list1, list2);
    EXPECT_EQ(merged.size(), 2);
    EXPECT_EQ(merged[0].asInterval().start, -2e9);
    EXPECT_EQ(merged[0].asInterval().end, 2e9);
    EXPECT_EQ(merged[1].asInterval().start, -10);
    EXPECT_EQ(merged[1].asInterval().end, 102746);
}

TEST(CSGTest, MergeLists3) {
    Span test1 = Span::initParametersOnly(-2e9, 2e9);
    Span test2 = Span::initParametersOnly(1,2);
    Span test3 = Span::initParametersOnly(2,10);
    Span test4 = Span::initParametersOnly(11,12);
    Span test5 = Span::initParametersOnly(13,14);
    Span test6 = Span::initParametersOnly(15,21);
    std::vector<Span> list1 = {test1};
    std::vector<Span> list2 = {test2, test3, test4, test5, test6};
    std::vector<Span> merged = mergeIntervalLists(list1, list2);
    EXPECT_EQ(merged.size(), 6);
    EXPECT_EQ(merged[0].asInterval().start, -2e9);
    EXPECT_EQ(merged[0].asInterval().end, 2e9);
    EXPECT_EQ(merged[1].asInterval().start, 1);
    EXPECT_EQ(merged[1].asInterval().end, 2);
    EXPECT_EQ(merged[3].asInterval().start, 11);
    EXPECT_EQ(merged[3].asInterval().end, 12);
}

TEST(CSGTest, MergeLists4) {
    Span test1 = Span::initParametersOnly(-2e9, 2e9);
    Span test2 = Span::initParametersOnly(1,2);
    Span test3 = Span::initParametersOnly(2,10);
    Span test4 = Span::initParametersOnly(11,12);
    Span test5 = Span::initParametersOnly(13,14);
    Span test6 = Span::initParametersOnly(15,21);
    std::vector<Span> list1 = {test1};
    std::vector<Span> list2 = {test2, test3, test4, test5, test6};
    std::vector<Span> merged = mergeIntervalLists(list2, list1);
    EXPECT_EQ(merged.size(), 6);
    EXPECT_EQ(merged[0].asInterval().start, -2e9);
    EXPECT_EQ(merged[0].asInterval().end, 2e9);
    EXPECT_EQ(merged[1].asInterval().start, 1);
    EXPECT_EQ(merged[1].asInterval().end, 2);
    EXPECT_EQ(merged[3].asInterval().start, 11);
    EXPECT_EQ(merged[3].asInterval().end, 12);
}