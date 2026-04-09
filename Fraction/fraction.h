#pragma once
//#include <string>
//#include <stdexcept>
//#include <algorithm>
//#include <cmath>
#include "basefraction.h"

class Fraction: public BaseFraction{
	//Служебные функции 
	void simplify() noexcept override; // упрощение дроби
public:
	// Конструкторы
	Fraction(); // контруктор инициализации по умолчанию
	Fraction(int, int);//инициализации
	Fraction(int); // Частичная инициализация знаменатель единица
	Fraction(const Fraction&);// копирования
	Fraction(const std::string& str);//Иницализация через строку
};
