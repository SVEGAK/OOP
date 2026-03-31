#include "pch.h"
#include "ctime.h"

TEST(ClassTime, check_default_constructor) {
	ASSERT_NO_THROW(CTime c1);
	CTime c1;
	EXPECT_EQ(c1.hour(), 0);
	EXPECT_EQ(c1.minute(), 0);
	EXPECT_EQ(c1.seconds(), 0);
}
TEST(ClassTime, check_init_constructor) {
	ASSERT_NO_THROW(CTime c1);
	CTime c1(11,43,35);
	EXPECT_EQ(c1.hour(), 11);
	EXPECT_EQ(c1.minute(), 43);
	EXPECT_EQ(c1.seconds(), 35);
}
TEST(ClassTime, check_copy_constructor) {
	ASSERT_NO_THROW(CTime c1);
	CTime c1(11,43,35);
	CTime c2(c1);
	EXPECT_EQ(c2.hour(),11);
	EXPECT_EQ(c2.minute(), 43);
	EXPECT_EQ(c2.seconds(), 35);
}
TEST(ClassTime, check_another_constructor) {
	ASSERT_NO_THROW(CTime c1);
	CTime c1(11, 43);
	EXPECT_EQ(c1.hour(), 11);
	EXPECT_EQ(c1.minute(), 43);
	EXPECT_EQ(c1.seconds(), 0);
}
TEST(ClassTime, check_add_minutes_constructor) {
	ASSERT_NO_THROW(CTime c1);
	CTime c1(11, 43,35);
	CTime c2;
	c2 = c1.add_minutes(7);
	EXPECT_EQ(c2.hour(), 11);
	EXPECT_EQ(c2.minute(),50);
	EXPECT_EQ(c2.seconds(), 35);
}
TEST(ClassTime, check_set_hour_constructor) {
	ASSERT_NO_THROW(CTime c1);
	CTime c1(11, 43, 35);
	c1.hour(23);
	EXPECT_EQ(c1.hour(), 23);
	EXPECT_EQ(c1.minute(), 43);
	EXPECT_EQ(c1.seconds(), 35);
}
TEST(ClassTime, check_set_minute_constructor) {
	ASSERT_NO_THROW(CTime c1);
	CTime c1(11, 43, 35);
	c1.minute(35);
	EXPECT_EQ(c1.hour(), 11);
	EXPECT_EQ(c1.minute(), 35);
	EXPECT_EQ(c1.seconds(), 35);
}
TEST(ClassTime, check_set_second_constructor) {
	ASSERT_NO_THROW(CTime c1);
	CTime c1(11, 43, 35);
	c1.seconds(40);
	EXPECT_EQ(c1.hour(), 11);
	EXPECT_EQ(c1.minute(), 43);
	EXPECT_EQ(c1.seconds(), 40);
}
TEST(ClassTime, check_add_hours_constructor) {

	CTime d1(11, 3, 29);
	CTime d2;
	d2 = d1.add_hours(3);
	EXPECT_EQ(d2.hour(), 14);
	EXPECT_EQ(d2.minute(), 3);
	EXPECT_EQ(d2.seconds(), 29);
}
TEST(ClassCTime, check_add_minutes_constructor) {

	CTime d1(11, 3, 29);
	CTime d2;
	d2 = d1.add_minutes(70);
	EXPECT_EQ(d2.hour(), 12);
	EXPECT_EQ(d2.minute(), 13);
	EXPECT_EQ(d2.seconds(), 29);
}
TEST(ClassCTime, check_add_seconds_constructor) {

	CTime d1(11, 59, 29);
	CTime d2;
	d2 = d1.add_seconds(70);
	EXPECT_EQ(d2.hour(), 12);
	EXPECT_EQ(d2.minute(), 0);
	EXPECT_EQ(d2.seconds(), 39);
}