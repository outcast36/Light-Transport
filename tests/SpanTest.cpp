#include <gtest/gtest.h>
#include "Span.h"

TEST(SpanTest, PrintSpan) {
    Collision p1, p2;
    p1.t = 1;
    p2.t = 3;
    const Span span_test(p1,p2);
    std::string exp = "[1.000, 3.000]";
    EXPECT_EQ(span_test.printSpan(), exp);
}

TEST(SpanTest, MergeOverlap) {
    Collision p1, p2, p3, p4;
    p1.t = 1;
    p2.t = 3;
    p3.t = 2;
    p4.t = 5;
    const Span span_1(p1,p2);
    const Span span_2(p3,p4);
    Span merged = mergeOverlap(span_1, span_2);
    Interval merged_interval = merged.asInterval();
    EXPECT_EQ(merged_interval.start, 1.0);
    EXPECT_EQ(merged_interval.end, 5.0);
}