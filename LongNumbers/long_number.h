#pragma once
#include <string>
#include <iostream>
class LongNumber {
	int* _lnumber;
	int _len; // длина числа
	int _sign;
	LongNumber& resize_sum(int add_len, int p);
	bool equals(const LongNumber& other) const;
	bool is_zero() const;
	int compare_abs(const LongNumber& a, const LongNumber& b);
	long long int pow_long(int x, int a);
	void remove_leading_zeros();

public:
	LongNumber();
	LongNumber(const LongNumber&);
	LongNumber(const std::string&);
	LongNumber(long long int num);
	~LongNumber();
	//Операторы
	//арифметика с присваиванием
	LongNumber& operator+=(const LongNumber& other);
	LongNumber& operator-=(const LongNumber& other);
	LongNumber& operator*=(const LongNumber& other);
	LongNumber operator++(int);
	LongNumber operator--(int);
	LongNumber& operator++();
	LongNumber& operator--();
	//Обычная арифметика
	LongNumber operator+(const LongNumber& other) const ;
	LongNumber operator-(const LongNumber& other) const;
	LongNumber operator*(const LongNumber& other) const;
	LongNumber& operator=(const LongNumber& other);

	bool operator==(const LongNumber& other) const;
	bool operator>(const LongNumber& other) const;
	bool operator<(const LongNumber& other) const;
	bool operator>=(const LongNumber& other) const;
	bool operator<=(const LongNumber& other) const;
	bool operator!=(const LongNumber& other) const;
	LongNumber operator-() const;
	int operator[](int pos) const;
	//Внешние перегрузки:
	friend std::ostream& operator<<(std::ostream& out, const LongNumber& num);
	friend std::istream& operator>>(std::istream& input, LongNumber& num);

	friend LongNumber operator+(long long int num, const LongNumber& lnum);
	friend LongNumber operator+(const LongNumber& lnum, long long int num);
	friend LongNumber operator-(long long int num, const LongNumber& lnum);
	friend LongNumber operator-(const LongNumber& lnum, long long int num);
	//Геттеры
	long long int get_lnum();
	int get_len();
	int get_sign();
	
};
