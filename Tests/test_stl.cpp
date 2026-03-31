
#include "pch.h"
#include "stl.h"
#include <vector>

TEST(STLUsing, check_sort) {
	std::vector<float> v1 = { 1.4, 4, 2.4, 7.33, 3, 2.55, 5 };
	
	for (int i = 0; i < v1.size(); i++) {
		std::cout << v1[i] << " ";
	}

	ASSERT_NO_THROW(sorting(v1));
	for (std::vector<float>::iterator it = v1.begin(); it < v1.end(); it++) {
		std::cout << *it << " ";
	}
}