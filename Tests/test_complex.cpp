#include "pch.h"
#include "complex.h"

TEST(ClassComplex, check_default_constructor) {
	Complex c1;
	EXPECT_DOUBLE_EQ(c1.re(), 0);
	EXPECT_DOUBLE_EQ(c1.im(), 0);
};
TEST(ClassComplex, check_init_double_constructor) {
	Complex c1(1.5,2.37);
	EXPECT_DOUBLE_EQ(c1.re(), 1.5);
	EXPECT_DOUBLE_EQ(c1.im(), 2.37);
};
TEST(ClassComplex, check_complex_copy_constructor) {
	Complex c1(72.32, 2.37);
	Complex c2(c1);
	EXPECT_DOUBLE_EQ(c2.re(), 72.32);
	EXPECT_DOUBLE_EQ(c2.im(), 2.37);
};
TEST(ClassComplex, check_operator_plus) {
	Complex c1(1, 2.37);
	Complex c2(1,1.23);
	Complex c3 = c1 + c2;
	EXPECT_DOUBLE_EQ(c3.re(), 2);
	EXPECT_DOUBLE_EQ(c3.im(), 3.60);
};
TEST(ClassComplex, check_operator_minus) {
	Complex c1(1, 2.37);
	Complex c2(1, 1.27);
	Complex c3 = c1 - c2;
	EXPECT_DOUBLE_EQ(c3.re(), 0);
	EXPECT_DOUBLE_EQ(c3.im(), 1.1);
};
TEST(ClassComplex, check_operator_multiplication) {
	Complex c1(1, 5);
	Complex c2(1, 2);
	Complex c3 = c1 * c2;
	EXPECT_DOUBLE_EQ(c3.re(), 1);
	EXPECT_DOUBLE_EQ(c3.im(), 10);
};
TEST(ClassComplex, check_operator_division) {
	Complex c1(5, 10);
	Complex c2(2, 2);
	Complex c3 = c1 / c2;
	EXPECT_DOUBLE_EQ(c3.re(), 2.5);
	EXPECT_DOUBLE_EQ(c3.im(), 5);
};

TEST(ClassComplex, check_operator_plus_equal) {
	Complex c1(1, 2.37);
	Complex c2(1, 1.23);
	c1 += c2;
	EXPECT_DOUBLE_EQ(c1.re(), 2);
	EXPECT_DOUBLE_EQ(c1.im(), 3.60);
};
TEST(ClassComplex, check_operator_minus_equal) {
	Complex c1(1, 2.37);
	Complex c2(1, 1.27);
	c1 -= c2;
	EXPECT_DOUBLE_EQ(c1.re(), 0);
	EXPECT_DOUBLE_EQ(c1.im(), 1.1);
};
TEST(ClassComplex, check_operator_multiplication_equal) {
	Complex c1(1, 5);
	Complex c2(1, 2);
	c1 *= c2;
	EXPECT_DOUBLE_EQ(c1.re(), 1);
	EXPECT_DOUBLE_EQ(c1.im(), 10);
};
TEST(ClassComplex, check_operator_equal_division) {
	Complex c1(5, 10);
	Complex c2(2, 2);
	c1 /= c2;
	EXPECT_DOUBLE_EQ(c1.re(), 2.5);
	EXPECT_DOUBLE_EQ(c1.im(), 5);
};
TEST(ClassComplex, check_operator_double_equal) {
	Complex c1(1, 1);
	Complex c2(1, 1);
	Complex c3(2, 3);

	EXPECT_TRUE(c1 == c2);
	EXPECT_FALSE(c1 == c3);
	EXPECT_DOUBLE_EQ(c1.re(), 1);
	EXPECT_DOUBLE_EQ(c1.im(), 1);
	EXPECT_DOUBLE_EQ(c2.re(), 1);
	EXPECT_DOUBLE_EQ(c2.im(), 1);
};
TEST(ClassComplex, check_operator_not_equal) {
	Complex c1(1, 1);
	Complex c2(1, 1);
	Complex c3(2, 3);
	EXPECT_FALSE(c1 != c2);
	EXPECT_TRUE(c1 != c3);
	EXPECT_DOUBLE_EQ(c1.re(), 1);
	EXPECT_DOUBLE_EQ(c1.im(), 1);
}
TEST(ClassComplex, check_doequal) {
	Complex c1(1, 1);
	Complex c2(2, 3);
	c1 = c2;
	EXPECT_DOUBLE_EQ(c1.re(), 2);
	EXPECT_DOUBLE_EQ(c1.im(), 3);
}
TEST(ClassComplex, check_excpeption_equal_division) {
	Complex c1(5, 10);
	Complex c2(0, 0);
	EXPECT_THROW(c1 /= c2,std::exception);
};
TEST(ClassComplex, check_expect) {
	Complex c1(5, 10);
	Complex c2(0, 0);
	EXPECT_THROW(Complex c3 = c1 / c2, std::exception);
};
TEST(ClassComplex, check_init_from_string_no_throw) {
	std::string s = "3.2 + 4i";
	Complex c1(s);
	EXPECT_DOUBLE_EQ(c1.re(), 3.2);
	EXPECT_DOUBLE_EQ(c1.im(), 4);
};
TEST(ClassComplex, check_init_from_string_throw_0_withot_i) {
	std::string s = "3.2 + 4";
	EXPECT_THROW(Complex c1(s), std::exception);
};
TEST(ClassComplex, check_init_from_string_throw_0_empty) {
	std::string s = " ";
	EXPECT_THROW(Complex c1(s), std::exception);
};
TEST(ClassComplex, check_init_from_string_throw_1) {
	std::string s = "3.2  4i";
	EXPECT_THROW(Complex c1(s), std::exception);
};