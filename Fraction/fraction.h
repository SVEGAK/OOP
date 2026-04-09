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
	//Операторы

	//Геттеры
	int num() { return _num; };
	int denom() { return _denom; };

	//Методы
	std::string to_string() const;
	//Операторы
	//
	//арифметика с присваиванием
	Fraction& operator+=(const Fraction& other);
	Fraction& operator+=(int);
	Fraction& operator-=(const Fraction& other);
	Fraction& operator-=(int);
	Fraction& operator*=(const Fraction& other);
	Fraction& operator*=(int);
	Fraction& operator/=(const Fraction& other);
	Fraction& operator/=(int);
	//Арифметика
	Fraction operator+(int) const;
	Fraction operator+(const Fraction& other) const;
	Fraction operator-(const Fraction& other) const;
	Fraction operator-(int) const;
	Fraction operator*(const Fraction& other) const;
	Fraction operator*(int) const;
	Fraction operator/(const Fraction& other) const;
	Fraction operator/(int) const;
	//Присвоение
	Fraction operator=(const Fraction& other);
	Fraction operator=(int);
	//Сравнение
	bool operator==(const Fraction& other) const;
	bool operator!=(const Fraction& other) const;
	bool operator>(const Fraction& other) const;
	bool operator<(const Fraction& other) const;
	bool operator>=(const Fraction& other) const;
	bool operator<=(const Fraction& other) const;
	//Сравнение с целыми
	bool operator==(int num) const;
	bool operator!=(int num) const;
	bool operator>(int num) const;
	bool operator<(int num) const;
	bool operator>=(int num) const;
	bool operator<=(int num) const;
	
};
