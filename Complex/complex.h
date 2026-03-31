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
	Complex();
	double re() { return _re; } // геттеры
	double im() { return _im; }
	//Конструкторы(default,init,copy,string)
	Complex(const Complex&); // конструктор копирования
	Complex(double, double);
	//
	Complex(std::string); //  инициализация через строку
	//Операторы
	Complex operator+(const Complex& other) const;
	Complex operator-(const Complex& other) const;
	Complex operator*(const Complex& other) const;
	Complex operator/(const Complex& other) const;
	Complex operator+=(const Complex& other);
	Complex operator-=(const Complex& other);
	Complex& operator*=(const Complex& other);
	Complex operator/=(const Complex& other);
	bool operator==(const Complex& other) const;
	bool operator!=(const Complex& other) const;
	Complex operator=(const Complex& other);

};
Complex::Complex() { // Реализация конструктора по умолчанию
	_re = 0;
	_im = 0;
};
Complex::Complex(double re, double im) {
	_re = re;
	_im = im;
};
Complex::Complex(const Complex& other) {//Реализация конструктора копирования
	this->_re = other._re;
	this->_im = other._im;
};
Complex::Complex(std::string input_str) {// оператор считывания комплексного числа из строки re + im*i
	input_str.erase(std::remove(input_str.begin(), input_str.end(), ' '), input_str.end());
	if (!input_str.empty() && input_str.back() == 'i') {
		input_str.pop_back();
	}
	else throw std::invalid_argument("0");
	size_t pos = input_str.find_last_of("+-");
	if (pos != std::string::npos && pos > 0) {
		std::string left = input_str.substr(0, pos);
		std::string right = input_str.substr(pos);
		_re = std::stod(left);
		_im = std::stod(right);
	}
	else throw std::invalid_argument("1");

}

Complex Complex::operator+(const Complex& other) const{
	return Complex(_re + other._re, _im + other._im);

};
Complex Complex::operator-(const Complex& other) const {
	return Complex(_re - other._re, _im - other._im);

};
Complex Complex::operator*(const Complex& other) const {
	return Complex(_re * other._re, _im * other._im);

};
Complex Complex::operator/(const Complex& other) const {
	if (other._im == 0 || other._re == 0) {
		throw std::logic_error("divison on zero");
	}
	return Complex(_re / other._re, _im/ other._im);

};
Complex Complex::operator+=(const Complex& other){
	return Complex(_re += other._re, _im += other._im);

};
Complex Complex::operator-=(const Complex& other) {
	return Complex(_re -= other._re, _im -= other._im);

};
Complex& Complex::operator*=(const Complex& other) {
	Complex res(*this);
	res = Complex(_re *= other._re, _im *= other._im);
	return res;
	

};
Complex Complex::operator/=(const Complex& other) {
	if (other._im == 0 || other._re == 0) {
		throw std::logic_error("divison on zero");
	}
	return Complex(_re /= other._re, _im /= other._im);

};
bool Complex::operator==(const Complex& other) const{
	if ((_re == other._re) && (_im == other._im)) {
		return true;
	}return false;

};
bool Complex::operator!=(const Complex& other) const {
	if ((_re != other._re) && (_im != other._im)) {
		return true;
	}return false;

};
Complex Complex::operator=(const Complex& other) {
	return Complex(_re = other._re, _im = other._im);

};