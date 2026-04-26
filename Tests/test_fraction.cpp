#include "pch.h"
#include "fraction.h"
//КОНСТРУКТОРЫ
TEST(ClassFraction, check_default_constructor) {
	Fraction f1;
	EXPECT_EQ(f1.num(), 0);
	EXPECT_EQ(f1.denom(), 1);
};
TEST(ClassFraction, check_init_constructor) {
	Fraction f1(1, 2);
	EXPECT_EQ(f1.num(), 1);
	EXPECT_EQ(f1.denom(), 2);
};
TEST(ClassFraction, check_init_minus_constructor) {
	Fraction f1(-1, 2);
	EXPECT_EQ(f1.num(), -1);
	EXPECT_EQ(f1.denom(), 2);
};
TEST(ClassFraction, check_init_denom_zero_constructor) {
	
	EXPECT_THROW({
		Fraction f1(1, 0); 
	}, std::invalid_argument);
};
TEST(ClassFraction, check_partion_init_constructor) {
	Fraction f1(4);
	EXPECT_EQ(f1.num(), 4);
	EXPECT_EQ(f1.denom(), 1);
};
TEST(ClassFraction, check_fraction_copy_constructor) {
	Fraction f1(2, 5);
	Fraction f2(f1);
	EXPECT_EQ(f2.num(), 2);
	EXPECT_EQ(f2.denom(), 5);
};
TEST(ClassFraction, check_init_from_string_valid) {
	std::string s = "3/4";
	Fraction f1(s);
	EXPECT_EQ(f1.num(), 3);
	EXPECT_EQ(f1.denom(), 4);
};
TEST(ClassFraction, check_init_from_string_throw_zero_denom) {
	std::string s = "3/0";
	EXPECT_THROW(Fraction f1(s), std::invalid_argument);
};
TEST(ClassFraction, check_init_from_string_throw_empty) {
	std::string s = "";
	EXPECT_THROW(Fraction f1(s), std::invalid_argument);
};
TEST(ClassFraction, check_init_from_string_throw_invalid_format) {
	std::string s = "3 4";
	EXPECT_THROW(Fraction f1(s), std::invalid_argument);
};
TEST(ClassFraction, check_init_from_string_negative) {
	std::string s = "-1/2";
	Fraction f1(s);
	EXPECT_EQ(f1.num(), -1);
	EXPECT_EQ(f1.denom(), 2);
};

//to_string
TEST(ClassFraction, to_string_positive) {
    Fraction f1(3, 4);
    EXPECT_EQ(f1.to_string(), "3/4");
}

TEST(ClassFraction, to_string_negative_numerator) {
    Fraction f1(-3, 4);
    EXPECT_EQ(f1.to_string(), "-3/4");
}

TEST(ClassFraction, to_string_negative_denominator) {
    Fraction f1(3, -4);
    EXPECT_EQ(f1.to_string(), "-3/4"); 
}

TEST(ClassFraction, to_string_whole_number) {
    Fraction f1(5, 1);
    EXPECT_EQ(f1.to_string(), "5/1");
}
//АРИФМЕТИЧЕСКИЕ ОПЕРАЦИИ С ПРИСВОЕНИЕМ
TEST(ClassFraction, op_add_assign_fraction_basic) {
    Fraction f1(1, 2);
    Fraction f2(1, 3);
    f1 += f2;
    EXPECT_EQ(f1.num(), 5);
    EXPECT_EQ(f1.denom(), 6);
}

TEST(ClassFraction, op_add_assign_fraction_negative) {
    Fraction f1(1, 2);
    Fraction f2(-1, 3);
    f1 += f2;
    EXPECT_EQ(f1.num(), 1);
    EXPECT_EQ(f1.denom(), 6);
}

TEST(ClassFraction, op_add_assign_fraction_chain) {
    Fraction f1(1, 4);
    Fraction f2(1, 4);
    Fraction f3(1, 4);
    (f1 += f2) += f3;
    EXPECT_EQ(f1.num(), 3);
    EXPECT_EQ(f1.denom(), 4);
}

TEST(ClassFraction, op_add_assign_int_basic) {
    Fraction f1(1, 2);
    f1 += 2;
    EXPECT_EQ(f1.num(), 5);
    EXPECT_EQ(f1.denom(), 2);
}

TEST(ClassFraction, op_add_assign_int_negative) {
    Fraction f1(3, 4);
    f1 += -1;
    EXPECT_EQ(f1.num(), -1);
    EXPECT_EQ(f1.denom(), 4);
}

TEST(ClassFraction, op_add_assign_int_zero) {
    Fraction f1(3, 5);
    f1 += 0;
    EXPECT_EQ(f1.num(), 3);
    EXPECT_EQ(f1.denom(), 5);
}

TEST(ClassFraction, op_sub_assign_fraction_basic) {
    Fraction f1(3, 4);
    Fraction f2(1, 2);
    f1 -= f2;
    EXPECT_EQ(f1.num(), 1);
    EXPECT_EQ(f1.denom(), 4);
}

TEST(ClassFraction, op_sub_assign_fraction_negative_result) {
    Fraction f1(1, 4);
    Fraction f2(3, 4);
    f1 -= f2;
    EXPECT_EQ(f1.num(), -1);
    EXPECT_EQ(f1.denom(), 2);
}

TEST(ClassFraction, op_sub_assign_fraction_chain) {
    Fraction f1(1, 2);
    Fraction f2(1, 4);
    Fraction f3(1, 8);
    (f1 -= f2) -= f3;
    EXPECT_EQ(f1.num(), 1);
    EXPECT_EQ(f1.denom(), 8);
}

TEST(ClassFraction, op_sub_assign_int_basic) {
    Fraction f1(5, 2);
    f1 -= 2;
    EXPECT_EQ(f1.num(), 1);
    EXPECT_EQ(f1.denom(), 2);
}

TEST(ClassFraction, op_sub_assign_int_negative_result) {
    Fraction f1(1, 3);
    f1 -= 1;
    EXPECT_EQ(f1.num(), -2);
    EXPECT_EQ(f1.denom(), 3);
}

TEST(ClassFraction, op_sub_assign_int_zero) {
    Fraction f1(7, 8);
    f1 -= 0;
    EXPECT_EQ(f1.num(), 7);
    EXPECT_EQ(f1.denom(), 8);
}

TEST(ClassFraction, op_mul_assign_fraction_basic) {
    Fraction f1(2, 3);
    Fraction f2(3, 4);
    f1 *= f2;
    EXPECT_EQ(f1.num(), 1);
    EXPECT_EQ(f1.denom(), 2);
}

TEST(ClassFraction, op_mul_assign_fraction_negative) {
    Fraction f1(1, 2);
    Fraction f2(-3, 4);
    f1 *= f2;
    EXPECT_EQ(f1.num(), -3);
    EXPECT_EQ(f1.denom(), 8);
}

TEST(ClassFraction, op_mul_assign_fraction_by_zero) {
    Fraction f1(5, 6);
    Fraction f2(0, 1);
    f1 *= f2;
    EXPECT_EQ(f1.num(), 0);
    EXPECT_EQ(f1.denom(), 1);
}

TEST(ClassFraction, op_mul_assign_int_basic) {
    Fraction f1(3, 4);
    f1 *= 2;
    EXPECT_EQ(f1.num(), 3);
    EXPECT_EQ(f1.denom(), 2);
}

TEST(ClassFraction, op_mul_assign_int_negative) {
    Fraction f1(1, 2);
    f1 *= -3;
    EXPECT_EQ(f1.num(), -3);
    EXPECT_EQ(f1.denom(), 2);
}

TEST(ClassFraction, op_mul_assign_int_zero) {
    Fraction f1(5, 7);
    f1 *= 0;
    EXPECT_EQ(f1.num(), 0);
    EXPECT_EQ(f1.denom(), 1);
}

TEST(ClassFraction, op_div_assign_fraction_basic) {
    Fraction f1(3, 4);
    Fraction f2(3, 2);
    f1 /= f2;
    EXPECT_EQ(f1.num(), 1);
    EXPECT_EQ(f1.denom(), 2);
}

TEST(ClassFraction, op_div_assign_fraction_negative) {
    Fraction f1(1, 2);
    Fraction f2(-1, 4);
    f1 /= f2;
    EXPECT_EQ(f1.num(), -2);
    EXPECT_EQ(f1.denom(), 1);
}

TEST(ClassFraction, op_div_assign_fraction_by_zero) {
    Fraction f1(1, 2);
    Fraction f2(0, 1);
    EXPECT_THROW(f1 /= f2, std::invalid_argument);
}

TEST(ClassFraction, op_div_assign_int_basic) {
    Fraction f1(3, 4);
    f1 /= 2;
    EXPECT_EQ(f1.num(), 3);
    EXPECT_EQ(f1.denom(), 8);
}

TEST(ClassFraction, op_div_assign_int_negative) {
    Fraction f1(1, 2);
    f1 /= -2;
    EXPECT_EQ(f1.num(), -1);
    EXPECT_EQ(f1.denom(), 4);
}

TEST(ClassFraction, op_div_assign_int_by_zero) {
    Fraction f1(3, 4);
    EXPECT_THROW(f1 /= 0, std::invalid_argument);
}

TEST(ClassFraction, op_assign_modifies_original) {
    Fraction f1(1, 2);
    Fraction f2(1, 3);
    int num_before = f1.num();
    f1 += f2;
    EXPECT_NE(f1.num(), num_before);
    EXPECT_EQ(f1.num(), 5);
}


//ОБЫЧНЫЕ АРИФМЕТИЧЕСКИЕ ОПЕРАЦИИ

TEST(ClassFraction, op_add_fraction_basic) {
    Fraction f1(1, 2);
    Fraction f2(1, 3);
    Fraction result = f1 + f2;
    EXPECT_EQ(result.num(), 5);
    EXPECT_EQ(result.denom(), 6);
    EXPECT_EQ(f1.num(), 1);
    EXPECT_EQ(f1.denom(), 2);
}

TEST(ClassFraction, op_add_int_basic) {
    Fraction f1(1, 2);
    Fraction result = f1 + 2;
    EXPECT_EQ(result.num(), 5);
    EXPECT_EQ(result.denom(), 2);
    EXPECT_EQ(f1.num(), 1);
}

TEST(ClassFraction, op_sub_fraction_basic) {
    Fraction f1(3, 4);
    Fraction f2(1, 2);
    Fraction result = f1 - f2;
    EXPECT_EQ(result.num(), 1);
    EXPECT_EQ(result.denom(), 4);
    EXPECT_EQ(f1.num(), 3);
}

TEST(ClassFraction, op_sub_int_basic) {
    Fraction f1(5, 2);
    Fraction result = f1 - 2;
    EXPECT_EQ(result.num(), 1);
    EXPECT_EQ(result.denom(), 2);
    EXPECT_EQ(f1.num(), 5);
}

TEST(ClassFraction, op_mul_fraction_basic) {
    Fraction f1(2, 3);
    Fraction f2(3, 4);
    Fraction result = f1 * f2;
    EXPECT_EQ(result.num(), 1);
    EXPECT_EQ(result.denom(), 2);
    EXPECT_EQ(f1.num(), 2);
}

TEST(ClassFraction, op_mul_int_basic) {
    Fraction f1(3, 4);
    Fraction result = f1 * 2;
    EXPECT_EQ(result.num(), 3);
    EXPECT_EQ(result.denom(), 2);
    EXPECT_EQ(f1.num(), 3);
}

TEST(ClassFraction, op_mul_fraction_zero) {
    Fraction f1(5, 6);
    Fraction f2(0, 1);
    Fraction result = f1 * f2;
    EXPECT_EQ(result.num(), 0);
    EXPECT_EQ(result.denom(), 1);
}

TEST(ClassFraction, op_mul_int_zero) {
    Fraction f1(5, 7);
    Fraction result = f1 * 0;
    EXPECT_EQ(result.num(), 0);
    EXPECT_EQ(result.denom(), 1);
}

TEST(ClassFraction, op_div_fraction_basic) {
    Fraction f1(3, 4);
    Fraction f2(3, 2);
    Fraction result = f1 / f2;
    EXPECT_EQ(result.num(), 1);
    EXPECT_EQ(result.denom(), 2);
}

TEST(ClassFraction, op_div_int_basic) {
    Fraction f1(3, 4);
    Fraction result = f1 / 2;
    EXPECT_EQ(result.num(), 3);
    EXPECT_EQ(result.denom(), 8);
}

TEST(ClassFraction, op_div_fraction_by_zero) {
    Fraction f1(1, 2);
    Fraction f2(0, 1);
    EXPECT_THROW(f1 / f2, std::invalid_argument);
}

TEST(ClassFraction, op_div_int_by_zero) {
    Fraction f1(3, 4);
    EXPECT_THROW(f1 / 0, std::invalid_argument);
}

TEST(ClassFraction, op_chain_arithmetic) {
    Fraction f1(1, 2);
    Fraction f2(1, 4);
    Fraction f3(1, 8);
    Fraction result = f1 + f2 + f3;
    EXPECT_EQ(result.num(), 7);
    EXPECT_EQ(result.denom(), 8);
}

TEST(ClassFraction, op_mixed_arithmetic) {
    Fraction f1(1, 2);
    Fraction result = (f1 + 1) * 2;
    EXPECT_EQ(result.num(), 3);
    EXPECT_EQ(result.denom(), 1);
}

TEST(ClassFraction, op_negative_numbers) {
    Fraction f1(1, 2);
    Fraction f2(-1, 4);
    Fraction result = f1 + f2;
    EXPECT_EQ(result.num(), 1);
    EXPECT_EQ(result.denom(), 4);
}

//ОПЕРАТОРЫ СРАВНЕНИЯ

TEST(ClassFraction, cmp_eq_fraction_true) {
    Fraction f1(1, 2);
    Fraction f2(2, 4);
    EXPECT_TRUE(f1 == f2);
}

TEST(ClassFraction, cmp_eq_fraction_false) {
    Fraction f1(1, 2);
    Fraction f2(1, 3);
    EXPECT_FALSE(f1 == f2);
}

TEST(ClassFraction, cmp_ne_fraction_true) {
    Fraction f1(1, 2);
    Fraction f2(1, 3);
    EXPECT_TRUE(f1 != f2);
}

TEST(ClassFraction, cmp_ne_fraction_false) {
    Fraction f1(1, 2);
    Fraction f2(2, 4);
    EXPECT_FALSE(f1 != f2);
}

TEST(ClassFraction, cmp_gt_fraction_true) {
    Fraction f1(3, 4);
    Fraction f2(1, 2);
    EXPECT_TRUE(f1 > f2);
}

TEST(ClassFraction, cmp_gt_fraction_false) {
    Fraction f1(1, 4);
    Fraction f2(1, 2);
    EXPECT_FALSE(f1 > f2);
}

TEST(ClassFraction, cmp_lt_fraction_true) {
    Fraction f1(1, 4);
    Fraction f2(1, 2);
    EXPECT_TRUE(f1 < f2);
}

TEST(ClassFraction, cmp_lt_fraction_false) {
    Fraction f1(3, 4);
    Fraction f2(1, 2);
    EXPECT_FALSE(f1 < f2);
}

TEST(ClassFraction, cmp_ge_fraction_true) {
    Fraction f1(1, 2);
    Fraction f2(2, 4);
    EXPECT_TRUE(f1 >= f2);
}

TEST(ClassFraction, cmp_ge_fraction_false) {
    Fraction f1(1, 4);
    Fraction f2(1, 2);
    EXPECT_FALSE(f1 >= f2);
}

TEST(ClassFraction, cmp_le_fraction_true) {
    Fraction f1(1, 2);
    Fraction f2(2, 4);
    EXPECT_TRUE(f1 <= f2);
}

TEST(ClassFraction, cmp_le_fraction_false) {
    Fraction f1(3, 4);
    Fraction f2(1, 2);
    EXPECT_FALSE(f1 <= f2);
}

TEST(ClassFraction, cmp_eq_int_true) {
    Fraction f1(4, 2);
    EXPECT_TRUE(f1 == 2);
}

TEST(ClassFraction, cmp_eq_int_false) {
    Fraction f1(1, 2);
    EXPECT_FALSE(f1 == 2);
}

TEST(ClassFraction, cmp_ne_int_true) {
    Fraction f1(1, 2);
    EXPECT_TRUE(f1 != 2);
}

TEST(ClassFraction, cmp_ne_int_false) {
    Fraction f1(4, 2);
    EXPECT_FALSE(f1 != 2);
}

TEST(ClassFraction, cmp_gt_int_true) {
    Fraction f1(5, 2);
    EXPECT_TRUE(f1 > 2);
}

TEST(ClassFraction, cmp_gt_int_false) {
    Fraction f1(3, 2);
    EXPECT_FALSE(f1 > 2);
}

TEST(ClassFraction, cmp_lt_int_true) {
    Fraction f1(3, 2);
    EXPECT_TRUE(f1 < 2);
}

TEST(ClassFraction, cmp_lt_int_false) {
    Fraction f1(5, 2);
    EXPECT_FALSE(f1 < 2);
}

TEST(ClassFraction, cmp_ge_int_true) {
    Fraction f1(4, 2);
    EXPECT_TRUE(f1 >= 2);
}

TEST(ClassFraction, cmp_ge_int_false) {
    Fraction f1(3, 2);
    EXPECT_FALSE(f1 >= 2);
}

TEST(ClassFraction, cmp_le_int_true) {
    Fraction f1(4, 2);
    EXPECT_TRUE(f1 <= 2);
}

TEST(ClassFraction, cmp_le_int_false) {
    Fraction f1(5, 2);
    EXPECT_FALSE(f1 <= 2);
}

TEST(ClassFraction, cmp_negative_numbers) {
    Fraction f1(-1, 2);
    Fraction f2(-3, 4);
    EXPECT_TRUE(f1 > f2);
    EXPECT_FALSE(f1 < f2);
}

TEST(ClassFraction, cmp_zero) {
    Fraction f1(0, 1);
    Fraction f2(0, 5);
    EXPECT_TRUE(f1 == f2);
    EXPECT_TRUE(f1 == 0);
}