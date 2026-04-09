#pragma once
#include "fraction.h"
class RightFraction : public Fraction {
	int _integer;//Целая часть
	void to_base_fraction() noexcept override;
	void simplify() noexcept override;
	public:
	// Конструкторы RightFraction
	RightFraction(); // по умолчанию: 0
	RightFraction(int integer, int num, int denom); // полная инициализация
	RightFraction(int integer, int num); // знаменатель = 1
	RightFraction(int integer); // дробная часть = 0
	RightFraction(const RightFraction&); // копирования
	RightFraction(const std::string& str); // из строки
	RightFraction(const Fraction&); // преобразование из Fraction
	RightFraction(const BaseFraction&); // преобразование из BaseFraction
	
};