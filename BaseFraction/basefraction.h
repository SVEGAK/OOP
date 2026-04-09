#pragma once
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cmath>
class BaseFraction {
	protected:

	int _num; // Числитель
	int _denom; // Знаменатель
	//Служебные функции 
	int max_delt(int a, int b);//вспомогательная функция для simplify
	virtual void simplify() noexcept; // упрощение дроби
	virtual void to_base_fraction() noexcept;
	static int parseNum(const std::string& str);
	static int parseDenom(const std::string& str);

	public:
	// Конструкторы
	BaseFraction(); // контруктор инициализации по умолчанию
	BaseFraction(int, int);//инициализации
	BaseFraction(int); // Частичная инициализация знаменатель единица
	BaseFraction(const BaseFraction&);// копирования
	BaseFraction(const std::string& str);//Иницализация через строку
	//Методы
	std::string to_string() const;
	//Операторы
	//арифметика с присваиванием
	BaseFraction& operator+=(const BaseFraction& other);
	BaseFraction& operator+=(int);
	BaseFraction& operator-=(const BaseFraction& other);
	BaseFraction& operator-=(int);
	BaseFraction& operator*=(const BaseFraction& other);
	BaseFraction& operator*=(int);
	BaseFraction& operator/=(const BaseFraction& other);
	BaseFraction& operator/=(int);
	//Арифметика
	BaseFraction operator+(int) const;
	BaseFraction operator+(const BaseFraction& other) const;
	BaseFraction operator-(const BaseFraction& other) const;
	BaseFraction operator-(int) const;
	BaseFraction operator*(const BaseFraction& other) const;
	BaseFraction operator*(int) const;
	BaseFraction operator/(const BaseFraction& other) const;
	BaseFraction operator/(int) const;
	//Присвоение
	BaseFraction& operator=(const BaseFraction& other);
	BaseFraction& operator=(int);
	//Сравнение
	bool operator==(const BaseFraction& other) const;
	bool operator!=(const BaseFraction& other) const;
	bool operator>(const BaseFraction& other) const;
	bool operator<(const BaseFraction& other) const;
	bool operator>=(const BaseFraction& other) const;
	bool operator<=(const BaseFraction& other) const;
	//Сравнение с целыми
	bool operator==(int num) const;
	bool operator!=(int num) const;
	bool operator>(int num) const;
	bool operator<(int num) const;
	bool operator>=(int num) const;
	bool operator<=(int num) const;
	//Геттеры
	int num() { return _num; };
	int denom() { return _denom; };

	virtual ~BaseFraction();

}