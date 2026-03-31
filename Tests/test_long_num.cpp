#include "pch.h"
#include "long_number.h"

TEST(ClassLongNumber, check_default_constructor) {
	LongNumber n1;
	EXPECT_EQ(n1.get_lnum(), 0);
	EXPECT_EQ(n1.get_len(), 1);
};

TEST(ClassLongNumber, check_init_constructor) {
	LongNumber n1("1222222222222222222");
	LongNumber n2(n1);
	EXPECT_EQ(n2.get_lnum(), 1222222222222222222);
};

TEST(ClassLongNumber, check_int_constructor) {
	LongNumber n1(14);
	EXPECT_EQ(n1.get_sign(), 1);
	EXPECT_EQ(n1.get_lnum(), 14);

};
TEST(ClassLongNumber, check_int_negative_constructor) {
	LongNumber n1(-14);
	EXPECT_EQ(n1.get_sign(), -1);
	EXPECT_EQ(n1.get_lnum(), 14);

};
TEST(ClassLongNumber, operator_plus_equal_positive_positive) {
	LongNumber n1("123");
	LongNumber n2("456");
	n1 += n2;
	EXPECT_EQ(n1.get_lnum(), 579);
	EXPECT_EQ(n1.get_sign(), 1);
};

TEST(ClassLongNumber, operator_plus_equal_with_carry) {
	LongNumber n1("999");
	LongNumber n2("1");
	n1 += n2;
	EXPECT_EQ(n1.get_lnum(), 1000);
	EXPECT_EQ(n1.get_len(), 4);
};

TEST(ClassLongNumber, operator_plus_equal_negative_negative) {
	LongNumber n1("-123");
	LongNumber n2("-456");
	n1 += n2;
	EXPECT_EQ(n1.get_lnum(), 579);
	EXPECT_EQ(n1.get_sign(), -1);
};

TEST(ClassLongNumber, operator_plus_equal_positive_negative) {
	LongNumber n1("100");
	LongNumber n2("-30");
	n1 += n2;
	EXPECT_EQ(n1.get_lnum(), 70);
	EXPECT_EQ(n1.get_sign(), 1);
};

TEST(ClassLongNumber, operator_plus_equal_negative_positive) {
	LongNumber n1("-100");
	LongNumber n2("30");
	n1 += n2;
	EXPECT_EQ(n1.get_lnum(), 70);
	EXPECT_EQ(n1.get_sign(), -1);
};

TEST(ClassLongNumber, operator_plus_equal_equal_numbers_different_signs) {
	LongNumber n1("50");
	LongNumber n2("-50");
	n1 += n2;
	EXPECT_EQ(n1.get_lnum(), 0);
	EXPECT_EQ(n1.get_sign(), 1);
};

TEST(ClassLongNumber, operator_plus_equal_with_zero) {
	LongNumber n1("123");
	LongNumber n2("0");
	n1 += n2;
	EXPECT_EQ(n1.get_lnum(), 123);
};

TEST(ClassLongNumber, operator_plus_equal_different_lengths) {
	LongNumber n1("99");
	LongNumber n2("111");
	n1 += n2;
	EXPECT_EQ(n1.get_lnum(), 210);
};



TEST(ClassLongNumber, operator_minus_equal_positive_positive) {
	LongNumber n1("100");
	LongNumber n2("30");
	n1 -= n2;
	EXPECT_EQ(n1.get_lnum(), 70);
	EXPECT_EQ(n1.get_sign(), 1);
};

TEST(ClassLongNumber, operator_minus_equal_with_borrow) {
	LongNumber n1("100");
	LongNumber n2("99");
	n1 -= n2;
	EXPECT_EQ(n1.get_lnum(), 1);
	EXPECT_EQ(n1.get_len(), 1);
};

TEST(ClassLongNumber, operator_minus_equal_positive_negative) {
	LongNumber n1("50");
	LongNumber n2("-50");
	n1 -= n2;
	EXPECT_EQ(n1.get_lnum(), 100);
	EXPECT_EQ(n1.get_sign(), 1);
};

TEST(ClassLongNumber, operator_minus_equal_negative_positive) {
	LongNumber n1("-50");
	LongNumber n2("50");
	n1 -= n2;
	EXPECT_EQ(n1.get_lnum(), 100);
	EXPECT_EQ(n1.get_sign(), -1);
};

TEST(ClassLongNumber, operator_minus_equal_equal_numbers) {
	LongNumber n1("75");
	LongNumber n2("75");
	n1 -= n2;
	EXPECT_EQ(n1.get_lnum(), 0);
	EXPECT_EQ(n1.get_sign(), 1);
};

TEST(ClassLongNumber, operator_minus_equal_with_zero) {
	LongNumber n1("123");
	LongNumber n2("0");
	n1 -= n2;
	EXPECT_EQ(n1.get_lnum(), 123);
};


TEST(ClassLongNumber, operator_plus_positive_positive) {
	LongNumber n1("123");
	LongNumber n2("456");
	LongNumber result = n1 + n2;
	EXPECT_EQ(result.get_lnum(), 579);
	EXPECT_EQ(n1.get_lnum(), 123); 
	EXPECT_EQ(n2.get_lnum(), 456);
};

TEST(ClassLongNumber, operator_plus_with_carry) {
	LongNumber n1("999");
	LongNumber n2("1");
	LongNumber result = n1 + n2;
	EXPECT_EQ(result.get_lnum(), 1000);
	EXPECT_EQ(result.get_len(), 4);
};

TEST(ClassLongNumber, operator_plus_different_signs) {
	LongNumber n1("100");
	LongNumber n2("-30");
	LongNumber result = n1 + n2;
	EXPECT_EQ(result.get_lnum(), 70);
	EXPECT_EQ(result.get_sign(), 1);
};

TEST(ClassLongNumber, operator_plus_chain) {
	LongNumber n1("10");
	LongNumber n2("20");
	LongNumber n3("30");
	LongNumber result = n1 + n2 + n3;
	EXPECT_EQ(result.get_lnum(), 60);
};



TEST(ClassLongNumber, operator_minus_positive_positive) {
	LongNumber n1("100");
	LongNumber n2("30");
	LongNumber result = n1 - n2;
	EXPECT_EQ(result.get_lnum(), 70);
	EXPECT_EQ(n1.get_lnum(), 100); 
	EXPECT_EQ(n2.get_lnum(), 30);
};

TEST(ClassLongNumber, operator_minus_with_borrow) {
	LongNumber n1("100");
	LongNumber n2("99");
	LongNumber result = n1 - n2;
	EXPECT_EQ(result.get_lnum(), 1);
	EXPECT_EQ(result.get_len(), 1);
};

TEST(ClassLongNumber, operator_minus_negative_result) {
	LongNumber n1("30");
	LongNumber n2("100");
	LongNumber result = n1 - n2;
	EXPECT_EQ(result.get_lnum(), 70);
	EXPECT_EQ(result.get_sign(), -1);
};

TEST(ClassLongNumber, operator_minus_chain) {
	LongNumber n1("100");
	LongNumber n2("20");
	LongNumber n3("10");
	LongNumber result = n1 - n2 - n3;
	EXPECT_EQ(result.get_lnum(), 70);
};



TEST(ClassLongNumber, arithmetic_with_zero) {
	LongNumber n1("0");
	LongNumber n2("0");
	LongNumber result = n1 + n2;
	EXPECT_EQ(result.get_lnum(), 0);
	EXPECT_EQ(result.get_sign(), 1);
};



TEST(ClassLongNumber, arithmetic_self_operation) {
	LongNumber n1("50");
	n1 += n1;
	EXPECT_EQ(n1.get_lnum(), 100);

	LongNumber n2("100");
	n2 -= n2;
	EXPECT_EQ(n2.get_lnum(), 0);
};




TEST(ClassLongNumber, operator_multiply_equal_positive_positive) {
	LongNumber n1("12");
	LongNumber n2("34");
	n1 *= n2;
	EXPECT_EQ(n1.get_lnum(), 408);
	EXPECT_EQ(n1.get_sign(), 1);
};

TEST(ClassLongNumber, operator_multiply_equal_by_zero) {
	LongNumber n1("123");
	LongNumber n2("0");
	n1 *= n2;
	EXPECT_EQ(n1.get_lnum(), 0);
	EXPECT_EQ(n1.get_sign(), 1);
};

TEST(ClassLongNumber, operator_multiply_equal_zero_by_number) {
	LongNumber n1("0");
	LongNumber n2("123");
	n1 *= n2;
	EXPECT_EQ(n1.get_lnum(), 0);
	EXPECT_EQ(n1.get_sign(), 1);
};

TEST(ClassLongNumber, operator_multiply_equal_negative_positive) {
	LongNumber n1("-12");
	LongNumber n2("34");
	n1 *= n2;
	EXPECT_EQ(n1.get_lnum(), 408);
	EXPECT_EQ(n1.get_sign(), -1);
};

TEST(ClassLongNumber, operator_multiply_equal_positive_negative) {
	LongNumber n1("12");
	LongNumber n2("-34");
	n1 *= n2;
	EXPECT_EQ(n1.get_lnum(), 408);
	EXPECT_EQ(n1.get_sign(), -1);
};

TEST(ClassLongNumber, operator_multiply_equal_negative_negative) {
	LongNumber n1("-12");
	LongNumber n2("-34");
	n1 *= n2;
	EXPECT_EQ(n1.get_lnum(), 408);
	EXPECT_EQ(n1.get_sign(), 1);
};

TEST(ClassLongNumber, operator_multiply_equal_single_digit) {
	LongNumber n1("5");
	LongNumber n2("6");
	n1 *= n2;
	EXPECT_EQ(n1.get_lnum(), 30);
	EXPECT_EQ(n1.get_sign(), 1);
};

TEST(ClassLongNumber, operator_multiply_equal_large_numbers) {
	LongNumber n1("999");
	LongNumber n2("999");
	n1 *= n2;
	EXPECT_EQ(n1.get_lnum(), 998001);
	EXPECT_EQ(n1.get_sign(), 1);
};

TEST(ClassLongNumber, operator_multiply_equal_by_one) {
	LongNumber n1("123");
	LongNumber n2("1");
	n1 *= n2;
	EXPECT_EQ(n1.get_lnum(), 123);
	EXPECT_EQ(n1.get_sign(), 1);
};

TEST(ClassLongNumber, operator_multiply_equal_self) {
	LongNumber n1("12");
	n1 *= n1;
	EXPECT_EQ(n1.get_lnum(), 144);
	EXPECT_EQ(n1.get_sign(), 1);
};



TEST(ClassLongNumber, operator_multiply_positive_positive) {
	LongNumber n1("12");
	LongNumber n2("34");
	LongNumber result = n1 * n2;
	EXPECT_EQ(result.get_lnum(), 408);
	EXPECT_EQ(result.get_sign(), 1);
	EXPECT_EQ(n1.get_lnum(), 12); 
	EXPECT_EQ(n2.get_lnum(), 34);
};

TEST(ClassLongNumber, operator_multiply_by_zero) {
	LongNumber n1("123");
	LongNumber n2("0");
	LongNumber result = n1 * n2;
	EXPECT_EQ(result.get_lnum(), 0);
	EXPECT_EQ(result.get_sign(), 1);
};

TEST(ClassLongNumber, operator_multiply_negative_positive) {
	LongNumber n1("-12");
	LongNumber n2("34");
	LongNumber result = n1 * n2;
	EXPECT_EQ(result.get_lnum(), 408);
	EXPECT_EQ(result.get_sign(), -1);
};

TEST(ClassLongNumber, operator_multiply_positive_negative) {
	LongNumber n1("12");
	LongNumber n2("-34");
	LongNumber result = n1 * n2;
	EXPECT_EQ(result.get_lnum(), 408);
	EXPECT_EQ(result.get_sign(), -1);
};

TEST(ClassLongNumber, operator_multiply_negative_negative) {
	LongNumber n1("-12");
	LongNumber n2("-34");
	LongNumber result = n1 * n2;
	EXPECT_EQ(result.get_lnum(), 408);
	EXPECT_EQ(result.get_sign(), 1);
};

TEST(ClassLongNumber, operator_multiply_single_digit) {
	LongNumber n1("5");
	LongNumber n2("6");
	LongNumber result = n1 * n2;
	EXPECT_EQ(result.get_lnum(), 30);
	EXPECT_EQ(result.get_sign(), 1);
};

TEST(ClassLongNumber, operator_multiply_large_numbers) {
	LongNumber n1("999");
	LongNumber n2("999");
	LongNumber result = n1 * n2;
	EXPECT_EQ(result.get_lnum(), 998001);
	EXPECT_EQ(result.get_sign(), 1);
};

TEST(ClassLongNumber, operator_multiply_chain) {
	LongNumber n1("2");
	LongNumber n2("3");
	LongNumber n3("4");
	LongNumber result = n1 * n2 * n3;
	EXPECT_EQ(result.get_lnum(), 24);
	EXPECT_EQ(result.get_sign(), 1);
};

TEST(ClassLongNumber, operator_multiply_by_one) {
	LongNumber n1("123");
	LongNumber n2("1");
	LongNumber result = n1 * n2;
	EXPECT_EQ(result.get_lnum(), 123);
	EXPECT_EQ(result.get_sign(), 1);
};

TEST(ClassLongNumber, operator_multiply_self) {
	LongNumber n1("12");
	LongNumber result = n1 * n1;
	EXPECT_EQ(result.get_lnum(), 144);
	EXPECT_EQ(n1.get_lnum(), 12); 
};


TEST(ClassLongNumber, operator_equal_positive_positive_same) {
	LongNumber n1("123");
	LongNumber n2("123");
	EXPECT_TRUE(n1 == n2);
};

TEST(ClassLongNumber, operator_equal_positive_positive_different) {
	LongNumber n1("123");
	LongNumber n2("456");
	EXPECT_FALSE(n1 == n2);
};

TEST(ClassLongNumber, operator_equal_negative_negative_same) {
	LongNumber n1("-123");
	LongNumber n2("-123");
	EXPECT_TRUE(n1 == n2);
};

TEST(ClassLongNumber, operator_equal_negative_negative_different) {
	LongNumber n1("-123");
	LongNumber n2("-456");
	EXPECT_FALSE(n1 == n2);
};

TEST(ClassLongNumber, operator_greater_test1) {
	LongNumber n1("100");
	LongNumber n2("50");
	EXPECT_TRUE(n1 > n2);
};

TEST(ClassLongNumber, operator_greater_test2) {
	LongNumber n1("-50");
	LongNumber n2("-100");
	EXPECT_TRUE(n1 > n2);
};

TEST(ClassLongNumber, operator_greater_test3) {
	LongNumber n1("50");
	LongNumber n2("50");
	EXPECT_FALSE(n1 > n2);
};

TEST(ClassLongNumber, operator_greater_test4) {
	LongNumber n1("-50");
	LongNumber n2("50");
	EXPECT_FALSE(n1 > n2);
};

TEST(ClassLongNumber, operator_less_test1) {
	LongNumber n1("50");
	LongNumber n2("100");
	EXPECT_TRUE(n1 < n2);
};

TEST(ClassLongNumber, operator_less_test2) {
	LongNumber n1("-100");
	LongNumber n2("-50");
	EXPECT_TRUE(n1 < n2);
};

TEST(ClassLongNumber, operator_less_test3) {
	LongNumber n1("50");
	LongNumber n2("50");
	EXPECT_FALSE(n1 < n2);
};

TEST(ClassLongNumber, operator_less_test4) {
	LongNumber n1("50");
	LongNumber n2("-50");
	EXPECT_FALSE(n1 < n2);
};

TEST(ClassLongNumber, operator_greater_equal_test1) {
	LongNumber n1("100");
	LongNumber n2("50");
	EXPECT_TRUE(n1 >= n2);
};

TEST(ClassLongNumber, operator_greater_equal_test2) {
	LongNumber n1("50");
	LongNumber n2("50");
	EXPECT_TRUE(n1 >= n2);
};

TEST(ClassLongNumber, operator_greater_equal_test3) {
	LongNumber n1("-50");
	LongNumber n2("-100");
	EXPECT_TRUE(n1 >= n2);
};

TEST(ClassLongNumber, operator_greater_equal_test4) {
	LongNumber n1("50");
	LongNumber n2("100");
	EXPECT_FALSE(n1 >= n2);
};

TEST(ClassLongNumber, operator_less_equal_test1) {
	LongNumber n1("50");
	LongNumber n2("100");
	EXPECT_TRUE(n1 <= n2);
};

TEST(ClassLongNumber, operator_less_equal_test2) {
	LongNumber n1("50");
	LongNumber n2("50");
	EXPECT_TRUE(n1 <= n2);
};

TEST(ClassLongNumber, operator_less_equal_test3) {
	LongNumber n1("-100");
	LongNumber n2("-50");
	EXPECT_TRUE(n1 <= n2);
};

TEST(ClassLongNumber, operator_less_equal_test4) {
	LongNumber n1("100");
	LongNumber n2("50");
	EXPECT_FALSE(n1 <= n2);
};

TEST(ClassLongNumber, operator_not_equal_test1) {
	LongNumber n1("123");
	LongNumber n2("456");
	EXPECT_TRUE(n1 != n2);
};

TEST(ClassLongNumber, operator_not_equal_test2) {
	LongNumber n1("123");
	LongNumber n2("123");
	EXPECT_FALSE(n1 != n2);
};

TEST(ClassLongNumber, operator_not_equal_test3) {
	LongNumber n1("-123");
	LongNumber n2("123");
	EXPECT_TRUE(n1 != n2);
};

TEST(ClassLongNumber, operator_not_equal_test4) {
	LongNumber n1("0");
	LongNumber n2("0");
	EXPECT_FALSE(n1 != n2);
};
TEST(ClassLongNumber, unary_minus_positive) {
	LongNumber n1("123");
	LongNumber result = -n1;
	EXPECT_EQ(result.get_lnum(), 123);
	EXPECT_EQ(result.get_sign(), -1);
};

TEST(ClassLongNumber, unary_minus_negative) {
	LongNumber n1("-123");
	LongNumber result = -n1;
	EXPECT_EQ(result.get_lnum(), 123);
	EXPECT_EQ(result.get_sign(), 1);
};

TEST(ClassLongNumber, unary_minus_zero) {
	LongNumber n1("0");
	LongNumber result = -n1;
	EXPECT_EQ(result.get_lnum(), 0);
	EXPECT_EQ(result.get_sign(), 1);
};

TEST(ClassLongNumber, unary_minus_original_unchanged) {
	LongNumber n1("123");
	LongNumber result = -n1;
	EXPECT_EQ(n1.get_sign(), 1);
	EXPECT_EQ(result.get_sign(), -1);
};

TEST(ClassLongNumber, operator_plus_postfix) {
	LongNumber n1(123);
	n1++;
	EXPECT_EQ(n1.get_sign(), 1);
	EXPECT_EQ(n1.get_lnum(), 124);
};
TEST(ClassLongNumber, operator_minus_postfix) {
	LongNumber n1(123);
	LongNumber res = n1--;
	EXPECT_EQ(res.get_sign(), 1);
	EXPECT_EQ(res.get_lnum(), 123);
	EXPECT_EQ(n1.get_sign(), 1);
	EXPECT_EQ(n1.get_lnum(), 122);
};
TEST(ClassLongNumber, operator_plus_prefix) {
	LongNumber n1(123);
	++n1;
	EXPECT_EQ(n1.get_sign(), 1);
	EXPECT_EQ(n1.get_lnum(), 124);
};
TEST(ClassLongNumber, operator_minus_prefix) {
	LongNumber n1(123);
	--n1;
	EXPECT_EQ(n1.get_sign(), 1);
	EXPECT_EQ(n1.get_lnum(), 122);
};

TEST(ClassLongNumber, operator_index_zero) {
	LongNumber n1(-123);
	int res = n1[0];
	EXPECT_EQ(res, -1);
};
TEST(ClassLongNumber, operator_index_correct) {
	LongNumber n1(123);
	int res = n1[1];
	EXPECT_EQ(res, 2);
};
TEST(ClassLongNumber, operator_index_out_of_range) {
	LongNumber n1(123);
	EXPECT_THROW(n1[4] , std::out_of_range);
};

TEST(ClassLongNumber, operator_output_string) {
	LongNumber n1(123);
	std::ostringstream out;
	out << n1;
	EXPECT_EQ("123", out.str());
};
TEST(ClassLongNumber, operator_output_string_negative) {
	LongNumber n1(-123);
	std::ostringstream out;
	out << n1;
	EXPECT_EQ("-123", out.str());
};
TEST(ClassLongNumber, operator_input_string) {
	LongNumber n1;
	std::istringstream input("123");
	input >> n1;
	EXPECT_EQ(n1.get_lnum(), 123);
};
TEST(ClassLongNumber, operator_input_string_negative) {
	LongNumber n1;
	std::istringstream input("-123");
	input >> n1;
	EXPECT_EQ(n1.get_lnum(), 123);
	EXPECT_EQ(n1.get_sign(), -1);
};
TEST(ClassLongNumber, operator_input_string_big) {
	LongNumber n1;
	std::istringstream input("-12349999999999999999");
	input >> n1;
	EXPECT_EQ(n1.get_lnum(), 12349999999999999999);
	EXPECT_EQ(n1.get_sign(), -1);
};

TEST(ClassLongNumber, operator_minus_num_all_positive) {
	LongNumber n1("100");
	LongNumber result = n1 - 30;
	EXPECT_EQ(result.get_lnum(), 70);
	EXPECT_EQ(result.get_sign(), 1);
};
TEST(ClassLongNumber, operator_plus_num_all_positive) {
	LongNumber n1("100");
	LongNumber result = n1 + 30;
	EXPECT_EQ(result.get_lnum(), 130);
	EXPECT_EQ(result.get_sign(), 1);
};
TEST(ClassLongNumber, operator_plus_num_reverse_all_positive) {
	LongNumber n1("100");
	LongNumber result = 30 + n1;
	EXPECT_EQ(result.get_lnum(), 130);
	EXPECT_EQ(result.get_sign(), 1);
};
TEST(ClassLongNumber, operator_minus_res_negative) {
	LongNumber n1("100");
	LongNumber result = 30 - n1;
	EXPECT_EQ(result.get_lnum(), 70);
	EXPECT_EQ(result.get_sign(), -1);
};