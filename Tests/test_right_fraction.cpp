#include "pch.h"
#include <gtest/gtest.h>
#include "rightfraction.h"
#include <sstream>
#include "basefraction.h"
TEST(RightFractionTest, DefaultConstructor) {
    RightFraction rf;
    EXPECT_EQ(rf.integer(), 0);
    EXPECT_EQ(rf.num(), 0);
    EXPECT_EQ(rf.denom(), 1);
}

TEST(RightFractionTest, ConstructorWithIntegerOnly) {
    RightFraction rf(5);
    EXPECT_EQ(rf.integer(), 5);
    EXPECT_EQ(rf.num(), 0);
    EXPECT_EQ(rf.denom(), 1);
}

TEST(RightFractionTest, ConstructorWithIntegerAndNum) {
    RightFraction rf(3, 4);
    EXPECT_EQ(rf.integer(), 7);
    EXPECT_EQ(rf.num(), 0);
    EXPECT_EQ(rf.denom(), 1);
}

TEST(RightFractionTest, ConstructorFull) {
    RightFraction rf(2, 3, 4);
    EXPECT_EQ(rf.integer(), 2);
    EXPECT_EQ(rf.num(), 3);
    EXPECT_EQ(rf.denom(), 4);
}

TEST(RightFractionTest, ConstructorFullWithImproperFraction) {
    RightFraction rf(1, 5, 3);
    EXPECT_EQ(rf.integer(), 2);
    EXPECT_EQ(rf.num(), 2);
    EXPECT_EQ(rf.denom(), 3);
}

TEST(RightFractionTest, ConstructorFullNegativeInteger) {
    RightFraction rf(-3, 1, 2);
    EXPECT_EQ(rf.integer(), 3);
    EXPECT_EQ(rf.num(), -1);
    EXPECT_EQ(rf.denom(), 2);
}

TEST(RightFractionTest, ConstructorFullNegativeDenominator) {
    RightFraction rf(1, 3, -4);
    EXPECT_EQ(rf.integer(), 1);
    EXPECT_EQ(rf.num(), -3);
    EXPECT_EQ(rf.denom(), 4);
}

//TEST(RightFractionTest, ConstructorFromStringIntegerOnly) {
//    RightFraction rf("5");
//    EXPECT_EQ(rf.integer(), 5);
//    EXPECT_EQ(rf.num(), 0);
//    EXPECT_EQ(rf.denom(), 1);
//}
//
//TEST(RightFractionTest, ConstructorFromStringFractionOnly) {
//    RightFraction rf("3/4");
//    EXPECT_EQ(rf.integer(), 0);
//    EXPECT_EQ(rf.num(), 3);
//    EXPECT_EQ(rf.denom(), 4);
//}

//TEST(RightFractionTest, ConstructorFromStringMixed) {
//    RightFraction rf("2 3/4");
//    EXPECT_EQ(rf.integer(), 2);
//    EXPECT_EQ(rf.num(), 3);
//    EXPECT_EQ(rf.denom(), 4);
//}

TEST(RightFractionTest, ConstructorFromStringMixedNoSpace) {
    EXPECT_THROW(RightFraction("2 3/4"), std::invalid_argument);
}

//TEST(RightFractionTest, ConstructorFromStringInvalidFormat) {
//    EXPECT_THROW(RightFraction("2 3 / 4"), std::invalid_argument);
//    //EXPECT_THROW(RightFraction("2 3 4"), std::invalid_argument);
//    RightFraction rf("2 3 4");
//    EXPECT_EQ(rf.integer(), 234);
//    EXPECT_THROW(RightFraction("2 / 4"), std::invalid_argument);
//}

TEST(RightFractionTest, CopyConstructor) {
    RightFraction a(3, 1, 2);
    RightFraction b(a);
    EXPECT_EQ(b.integer(), 3);
    EXPECT_EQ(b.num(), 1);
    EXPECT_EQ(b.denom(), 2);
}

TEST(RightFractionTest, ConstructorFromFraction) {
    Fraction f(7, 2);
    RightFraction rf(f);
    EXPECT_EQ(rf.integer(), 3);
    EXPECT_EQ(rf.num(), 1);
    EXPECT_EQ(rf.denom(), 2);
}

TEST(RightFractionTest, ConstructorFromBaseFraction) {
    BaseFraction bf(9, 4);
    RightFraction rf(bf);
    EXPECT_EQ(rf.integer(), 2);
    EXPECT_EQ(rf.num(), 1);
    EXPECT_EQ(rf.denom(), 4);
}

TEST(RightFractionTest, AssignmentFromBaseFraction) {
    RightFraction rf;
    BaseFraction bf(5, 3);
    rf = bf;
    EXPECT_EQ(rf.integer(), 1);
    EXPECT_EQ(rf.num(), 2);
    EXPECT_EQ(rf.denom(), 3);
}

TEST(RightFractionTest, AssignmentFromFraction) {
    RightFraction rf;
    Fraction f(8, 3);
    rf = f;
    EXPECT_EQ(rf.integer(), 2);
    EXPECT_EQ(rf.num(), 2);
    EXPECT_EQ(rf.denom(), 3);
}

TEST(RightFractionTest, AdditionAssignmentRightFraction) {
    RightFraction a(1, 1, 2);
    RightFraction b(2, 3, 4);
    a += b;
    EXPECT_EQ(a.integer(), 4);
    EXPECT_EQ(a.num(), 1);
    EXPECT_EQ(a.denom(), 4);
}

TEST(RightFractionTest, AdditionAssignmentFraction) {
    RightFraction a(1, 1, 2);
    Fraction b(3, 4);
    a += b;
    EXPECT_EQ(a.integer(), 2);
    EXPECT_EQ(a.num(), 1);
    EXPECT_EQ(a.denom(), 4);
}

TEST(RightFractionTest, AdditionAssignmentInt) {
    RightFraction a(2, 3, 5);
    a += 2;
    EXPECT_EQ(a.integer(), 4);
    EXPECT_EQ(a.num(), 3);
    EXPECT_EQ(a.denom(), 5);
}

TEST(RightFractionTest, SubtractionAssignmentRightFraction) {
    RightFraction a(5, 1, 2);
    RightFraction b(2, 3, 4);
    a -= b;
    EXPECT_EQ(a.integer(), 2);
    EXPECT_EQ(a.num(), 3);
    EXPECT_EQ(a.denom(), 4);
}

TEST(RightFractionTest, SubtractionAssignmentFraction) {
    RightFraction a(5, 1, 2);
    Fraction b(3, 4);
    a -= b;
    EXPECT_EQ(a.integer(), 4);
    EXPECT_EQ(a.num(), 3);
    EXPECT_EQ(a.denom(), 4);
}

TEST(RightFractionTest, SubtractionAssignmentInt) {
    RightFraction a(5, 2, 3);
    a -= 2;
    EXPECT_EQ(a.integer(), 3);
    EXPECT_EQ(a.num(), 2);
    EXPECT_EQ(a.denom(), 3);
}

TEST(RightFractionTest, MultiplicationAssignmentRightFraction) {
    RightFraction a(2, 1, 2);
    RightFraction b(3, 2, 3);
    a *= b;
    EXPECT_EQ(a.integer(), 9);
    EXPECT_EQ(a.num(), 1);
    EXPECT_EQ(a.denom(), 6); // Wait: 2 1/2 = 5/2, 3 2/3 = 11/3 => 55/6 = 9 1/6
}

TEST(RightFractionTest, MultiplicationAssignmentFraction) {
    RightFraction a(1, 1, 2);
    Fraction b(2, 3);
    a *= b;
    EXPECT_EQ(a.integer(), 1);
    EXPECT_EQ(a.num(), 0);
    EXPECT_EQ(a.denom(), 1); // 3/2 * 2/3 = 1
}

TEST(RightFractionTest, MultiplicationAssignmentInt) {
    RightFraction a(1, 2, 3);
    a *= 3;
    EXPECT_EQ(a.integer(), 5);
    EXPECT_EQ(a.num(), 0);
    EXPECT_EQ(a.denom(), 1);
}

TEST(RightFractionTest, DivisionAssignmentRightFraction) {
    RightFraction a(3, 1, 2);
    RightFraction b(1, 3, 4);
    a /= b;
    EXPECT_EQ(a.integer(), 2);
    EXPECT_EQ(a.num(), 0);
    EXPECT_EQ(a.denom(), 1); // 7/2 ÷ 7/4 = 2
}

TEST(RightFractionTest, DivisionAssignmentFraction) {
    RightFraction a(2, 1, 2);
    Fraction b(5, 2);
    a /= b;
    EXPECT_EQ(a.integer(), 1);
    EXPECT_EQ(a.num(), 0);
    EXPECT_EQ(a.denom(), 1);
}

TEST(RightFractionTest, DivisionAssignmentInt) {
    RightFraction a(4, 1, 2);
    a /= 3;
    EXPECT_EQ(a.integer(), 1);
    EXPECT_EQ(a.num(), 1);
    EXPECT_EQ(a.denom(), 2); // 9/2 / 3 = 3/2 = 1 1/2
}

TEST(RightFractionTest, DivisionByZeroThrows) {
    RightFraction a(1, 1, 2);
    RightFraction b(0, 0, 1);
    EXPECT_THROW(a /= b, std::invalid_argument);
    Fraction f(0, 1);
    EXPECT_THROW(a /= f, std::invalid_argument);
    EXPECT_THROW(a /= 0, std::invalid_argument);
}

TEST(RightFractionTest, ArithmeticOperatorsReturnNewObject) {
    RightFraction a(1, 1, 2);
    RightFraction b(2, 1, 2);
    RightFraction c = a + b;
    EXPECT_EQ(c.integer(), 4);
    EXPECT_EQ(c.num(), 0);
    EXPECT_EQ(c.denom(), 1);
    // a and b unchanged
    EXPECT_EQ(a.integer(), 1);
    EXPECT_EQ(b.integer(), 2);
}


TEST(RightFractionTest, EqualityOperators) {
    RightFraction a(1, 1, 2);
    RightFraction b(1, 2, 4);
    RightFraction c(1, 3, 4);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
    EXPECT_FALSE(a == c);

    Fraction f(3, 2);
    EXPECT_TRUE(a == f);
    EXPECT_TRUE(a == 1.5); // implicit conversion?
    EXPECT_TRUE(a == 1); // wait 3/2 == 1? no
    EXPECT_FALSE(a == 1);
}

TEST(RightFractionTest, ComparisonOperators) {
    RightFraction a(1, 1, 2);
    RightFraction b(1, 2, 4);
    RightFraction c(2, 0, 1);
    EXPECT_TRUE(a >= b);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a < c);
    EXPECT_TRUE(c > a);
    EXPECT_TRUE(a <= 2);
    EXPECT_TRUE(c == 2);
}

TEST(RightFractionTest, SimplifyAutomatically) {
    RightFraction rf(2, 4, 8);
    EXPECT_EQ(rf.integer(), 2);
    EXPECT_EQ(rf.num(), 1);
    EXPECT_EQ(rf.denom(), 2);
}

TEST(RightFractionTest, OutputOperator) {
    RightFraction rf(3, 1, 4);
    std::ostringstream oss;
    oss << rf;
    EXPECT_EQ(oss.str(), "3 1 / 4");
}

TEST(RightFractionTest, InputOperator) {
    std::istringstream iss("5 3/7");
    RightFraction rf;
    iss >> rf;
    EXPECT_EQ(rf.integer(), 5);
    EXPECT_EQ(rf.num(), 3);
    EXPECT_EQ(rf.denom(), 7);
}

TEST(RightFractionTest, InputOperatorInvalid) {
    std::istringstream iss("5 3 / 7");
    RightFraction rf;
    EXPECT_THROW(iss >> rf, std::invalid_argument);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}