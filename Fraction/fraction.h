#pragma once
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cmath>


class Fraction {
	int _num; // Числитель
	int _denom; // Знаменатель
	//Служебные функции 
	Fraction& simplify(); // упрощение дроби
	static int parseNum(const std::string& str);
	static int parseDenom(const std::string& str);
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
