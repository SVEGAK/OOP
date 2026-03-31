#include "pch.h"
#include "CDate.h"

TEST(ClassCDate, check_default_constructor) {
	ASSERT_NO_THROW(CDate d1);
	CDate d1;
	EXPECT_EQ(d1.year(), 1);
	EXPECT_EQ(d1.month(), 1);
	EXPECT_EQ(d1.day(), 1);
}
TEST(ClassCDate, check_init_constructor) {
	ASSERT_NO_THROW(CDate d1);
	CDate d1(2011, 3, 29);
	EXPECT_EQ(d1.year(), 2011);
	EXPECT_EQ(d1.month(), 3);
	EXPECT_EQ(d1.day(), 29);
}
TEST(ClassCDate, check_copy_constructor) {
	ASSERT_NO_THROW(CDate d1);
	CDate d1(2011, 3, 29);
	CDate c2(d1);
	EXPECT_EQ(c2.year(), 2011);
	EXPECT_EQ(c2.month(), 3);
	EXPECT_EQ(c2.day(), 29);
}
TEST(ClassCDate, check_another_constructor) {
	ASSERT_NO_THROW(CDate d1);
	CDate d1(2011, 3);
	EXPECT_EQ(d1.year(), 2011);
	EXPECT_EQ(d1.month(), 3);
	EXPECT_EQ(d1.day(), 1);
}
TEST(ClassCDate, check_set_year_constructor) {
	ASSERT_NO_THROW(CDate d1);
	CDate d1(2011, 3, 29);
	d1.year(2023);
	EXPECT_EQ(d1.year(), 2023);
	EXPECT_EQ(d1.month(), 3);
	EXPECT_EQ(d1.day(), 29);
}
TEST(ClassCDate, check_set_month_constructor) {
	ASSERT_NO_THROW(CDate d1);
	CDate d1(2011, 3, 29);
	d1.month(29);
	EXPECT_EQ(d1.year(), 2011);
	EXPECT_EQ(d1.month(), 29);
	EXPECT_EQ(d1.day(), 29);
}
TEST(ClassCDate, check_set_day_constructor) {
	ASSERT_NO_THROW(CDate d1);
	CDate d1(2011, 3, 29);
	d1.day(20);
	EXPECT_EQ(d1.year(), 2011);
	EXPECT_EQ(d1.month(), 3);
	EXPECT_EQ(d1.day(), 20);
}
TEST(ClassCDate, check_add_months_constructor) {
	
	CDate d1(2011, 3, 29);
	CDate d2;
	d2 = d1.add_month(37);
	EXPECT_EQ(d2.year(), 2014);
	EXPECT_EQ(d2.month(), 4);
	EXPECT_EQ(d2.day(), 29);
}
TEST(ClassCDate, check_add_year_constructor) {
	
	CDate d1(2011, 3, 29);
	CDate d2;
	d2 = d1.add_year(7);
	EXPECT_EQ(d2.year(), 2018);
	EXPECT_EQ(d2.month(), 3);
	EXPECT_EQ(d2.day(), 29);
}
TEST(ClassCDate, check_add_day_constructor) {

	CDate d1(2011, 4, 1);
	CDate d2;
	d2 = d1.add_day(60);
	EXPECT_EQ(d2.year(), 2011);
	EXPECT_EQ(d2.month(), 5);
	EXPECT_EQ(d2.day(), 31);
}