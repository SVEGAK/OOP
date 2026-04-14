#pragma once
#include "fraction.h"
class RightFraction : public Fraction {
	int _integer;
	size_t find_Integer_pos(const std::string& input_str);
	int parseInteger(const std::string& input_str, size_t pos);
	//Целая часть
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
	//Оператор присваивания с изменением типа
	RightFraction& operator=(const BaseFraction&) noexcept;
	RightFraction& operator=(const Fraction&) noexcept;
	//Геттеры
	int integer() const { return _integer; }
	//Функции ввода вывода
	friend std::ostream& operator<<(std::ostream& out, const RightFraction&);
	friend std::istream& operator>>(std::istream& in, RightFraction& frac);
	//Остальные операторы
	// Арифметические операторы с присваиванием
	RightFraction& operator+=(const RightFraction& other);
	RightFraction& operator+=(const Fraction& other);
	RightFraction& operator+=(int num);
	RightFraction& operator-=(const RightFraction& other);
	RightFraction& operator-=(const Fraction& other);
	RightFraction& operator-=(int num);
	RightFraction& operator*=(const RightFraction& other);
	RightFraction& operator*=(const Fraction& other);
	RightFraction& operator*=(int num);
	RightFraction& operator/=(const RightFraction& other);
	RightFraction& operator/=(const Fraction& other);
	RightFraction& operator/=(int num);

	// Арифметические операторы
	RightFraction operator+(const RightFraction& other) const;
	RightFraction operator+(const Fraction& other) const;
	RightFraction operator+(int num) const;
	RightFraction operator-(const RightFraction& other) const;
	RightFraction operator-(const Fraction& other) const;
	RightFraction operator-(int num) const;
	RightFraction operator*(const RightFraction& other) const;
	RightFraction operator*(const Fraction& other) const;
	RightFraction operator*(int num) const;
	RightFraction operator/(const RightFraction& other) const;
	RightFraction operator/(const Fraction& other) const;
	RightFraction operator/(int num) const;

	// Операторы сравнения
	bool operator==(const RightFraction& other) const;
	bool operator!=(const RightFraction& other) const;
	bool operator>(const RightFraction& other) const;
	bool operator<(const RightFraction& other) const;
	bool operator>=(const RightFraction& other) const;
	bool operator<=(const RightFraction& other) const;

	bool operator==(const Fraction& other) const;
	bool operator!=(const Fraction& other) const;
	bool operator>(const Fraction& other) const;
	bool operator<(const Fraction& other) const;
	bool operator>=(const Fraction& other) const;
	bool operator<=(const Fraction& other) const;

	bool operator==(int num) const;
	bool operator!=(int num) const;
	bool operator>(int num) const;
	bool operator<(int num) const;
	bool operator>=(int num) const;
	bool operator<=(int num) const;
};