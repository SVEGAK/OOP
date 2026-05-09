#include "complex.h"
Complex::Complex() { // Реализация конструктора по умолчанию
	_re = 0;
	_im = 0;
}
Complex::Complex(double re, double im) {
	_re = re;
	_im = im;
}
Complex::Complex(const Complex& other) {//Реализация конструктора копирования
	_re = other._re;
	_im = other._im;
}
Complex::Complex(std::string input_str) {
    // Удаляем все пробелы
    input_str.erase(std::remove(input_str.begin(), input_str.end(), ' '), input_str.end());

    if (input_str.empty()) {
        throw std::invalid_argument("Empty string");
    }

    bool is_i = false;
    if (input_str.back() == 'i') {
        input_str.pop_back();
        is_i = true;
    }

    if (input_str.empty()) { // строка была "i"
        _re = 0;
        _im = 1;
        return;
    }

    // Подсчитываем знаки '+' и '-', начиная с индекса 1 (первый символ может быть знаком числа)
    int sights_count = 0;
    size_t pos = std::string::npos; // положение последнего найденного знака (разделителя)
    for (size_t i = input_str.size() - 1; i > 0; i--) {
        if (input_str[i] == '+' || input_str[i] == '-') {
            sights_count++;
            if (pos == std::string::npos) {
                pos = i;   // запоминаем самый правый знак (разделитель мнимой части)
            }
        }
    }

    if (sights_count > 2) {
        throw std::invalid_argument("Invalid string format: more than two signs");
    }

    // Случай 1: Знаков в строке нет
    if (sights_count == 0) {
        if (is_i) {
            // Только мнимое число
            if (input_str == "+" || input_str == "-") input_str += "1";
            _re = 0;
            _im = std::stod(input_str);
        }
        else {
            // Действительное число
            if (input_str == "+" || input_str == "-") input_str += "0";
            _re = std::stod(input_str);
            _im = 0;
        }
        return;
    }

    // Случай 2: sights_count == 1 или 2
    // pos указывает на знак, разделяющий действительную и мнимую части
    if (pos == std::string::npos || pos == 0) {
        throw std::invalid_argument("Invalid sign placement");
    }

    std::string re_str = input_str.substr(0, pos);
    std::string im_str = input_str.substr(pos);

    // Если мнимая часть состоит только из знака, добавляем единицу
    if (im_str == "+" || im_str == "-") im_str += "1";
    // Если действительная часть пуста 
    if (re_str.empty()) re_str = "0";
    _re = std::stod(re_str);
    _im = std::stod(im_str);
}
//Арифметические операторы
Complex& Complex::operator+=(const Complex& other) {
	_re += other._re;
	_im += other._im;
	return *this;  
}
Complex& Complex::operator-=(const Complex& other) {
	_re -= other._re;
	_im -= other._im;
	return *this;
}
Complex& Complex::operator*=(const Complex& other) {
	_re *= other._re;
	_im *= other._im;
	return *this;
}
Complex& Complex::operator/=(const Complex& other) {
	double denom = other._re * other._re + other._im * other._im;
	if (denom == 0.0) {
		throw std::logic_error("division by zero complex number");
	}
	double re = (_re * other._re + _im * other._im) / denom;
	double im = (_im * other._re - _re * other._im) / denom;
	_re = re;
	_im = im;
	return *this;
}

Complex Complex::operator+(const Complex& other) const {
	Complex res(*this);
	res += other;
	return res;
}
Complex Complex::operator-(const Complex& other) const {
	Complex res(*this);
	res -= other;
	return res;

}
Complex Complex::operator*(const Complex& other) const {
	Complex res(*this);
	res *= other;
	return res;

}
Complex Complex::operator/(const Complex& other) const {
	Complex res(*this);
	res /= other;
	return res;

}

bool Complex::operator==(const Complex& other) const {
	return ((_re == other._re) && (_im == other._im));
}
bool Complex::operator!=(const Complex& other) const {
	return !((*this) == other);

}
Complex Complex::operator=(const Complex& other) {
	_re = other._re;
	_im = other._im;
	return (*this);
}