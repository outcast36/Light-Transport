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
    EXPECT_EQ(merged.getEntry(), p1);
    EXPECT_EQ(merged.getExit(), p4);
}

TEST(SpanTest, GetEntry) {
    Collision p1, p2;
    p1.t = 1;
    p2.t = 3;
    const Span span_test(p1,p2);
    EXPECT_EQ(span_test.getEntry(), p1);
}

TEST(SpanTest, GetExit) {
    Collision p1, p2;
    p1.t = 1;
    p2.t = 3;
    const Span span_test(p1,p2);
    EXPECT_EQ(span_test.getExit(), p2);
}

TEST(SpanTest, SetExit) {
    Collision p1, p2, p3;
    p1.t = 1;
    p2.t = 3;
    p3.t = 7;
    Span span_test(p1,p2);
    span_test.setExit(p3);
    EXPECT_EQ(span_test.getExit(), p3);
}

TEST(SpanTest, SetEntry) {
    Collision p1, p2, p3;
    p1.t = 5;
    p2.t = 10;
    p3.t = 8;
    Span span_test(p1,p2);
    span_test.setEntry(p3);
    EXPECT_EQ(span_test.getEntry(), p3);
}