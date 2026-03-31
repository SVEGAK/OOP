#include "pch.h"
#include "main_test_func.h"

TEST(NotRelatedTest, example_test) {
	Circle c1 = { {0, 0}, 2 };
	Circle c2 = { {10, 10}, 3 };
	EXPECT_EQ(get_position(c1, c2), NOT_RELATED);
}

TEST(MatchTest, example_test) {
	Circle c1 = { {3, 4}, 5 };
	Circle c2 = { {3, 4}, 5 };
	EXPECT_EQ(get_position(c1, c2), EQUAL);
}

TEST(ConsernTest, example_test) {
	Circle c1 = { {0, 0}, 3 };
	Circle c2 = { {3, 4}, 2 };
	EXPECT_EQ(get_position(c1, c2), TOUCH);
}

TEST(InsideTest, one_in_two) {
	Circle c1 = { {0, 0}, 1 };
	Circle c2 = { {1, 1}, 6 };
	EXPECT_EQ(get_position(c1, c2), ONE_INSIDE_THE_ANOTHER);
}

TEST(InsideTest, two_in_one) {
	Circle c1 = { {1, 1}, 4 };
	Circle c2 = { {1, 2}, 2 };
	EXPECT_EQ(get_position(c1, c2), ONE_INSIDE_THE_ANOTHER);
}

TEST(IntersectTest, intersect) {
	Circle c1 = { {0, 0}, 10 };
	Circle c2 = { {8, 0}, 3 };
	EXPECT_EQ(get_position(c1, c2), INTERSECTION);
}
