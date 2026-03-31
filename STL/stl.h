#pragma once
#include <vector>
#include <algorithm>
template<typename T> void sorting(std::vector<T>& data);

//template<typename T> bool comp(T a, T b); //сравнение объектов
template<typename T>
void sorting(std::vector<T>& data) {
	std::sort(data.begin(), data.end(), std::greater<T>());
}