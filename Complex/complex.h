#pragma once
#include <string>
#include <stdexcept>
// +, -, *,/ / += -= *= /=
// ==
// != 
// =
//Конструкторы(default, init, copy, string)
class Complex {
	double _re;
	double _im;
public:
	double re() { return _re; } // геттеры
	double im() { return _im; }
	//Конструкторы(default,init,copy,string)
	Complex();
	Complex(const Complex&); // конструктор копирования
	Complex(double, double);
	Complex(std::string); //  инициализация через строку

	//Операторы

	Complex& operator+=(const Complex& other);
	Complex& operator-=(const Complex& other);
	Complex& operator*=(const Complex& other);
	Complex& operator/=(const Complex& other);

	Complex operator+(const Complex& other) const;
	Complex operator-(const Complex& other) const;
	Complex operator*(const Complex& other) const;
	Complex operator/(const Complex& other) const;
	
	bool operator==(const Complex& other) const;
	bool operator!=(const Complex& other) const;
	Complex operator=(const Complex& other);

};
