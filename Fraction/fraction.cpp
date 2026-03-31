#include "fraction.h"
int max_delt(int a, int b) {
	int delt = 1;
	a = abs(a);
	b = abs(b);
	if ((a == 0) && (b != 0)) {
		return b;
	}
	else if ((b == 0) && (a != 0)) {
		return a;
	}

	if (b > a) {
		int c = b;
		b = a;
		a = c;
	}
	for (int i = 1; i < b + 1; i++) {
		if ((a % i == 0) && (b % i == 0)) {
			if (i > delt) {
				delt = i;
			}
		}
	}
	return delt;
}

int Fraction:: parseNum(const std::string& str) {
	std::string input_str = str;
	input_str.erase(std::remove(input_str.begin(), input_str.end(), ' '), input_str.end());

	if (std::count(input_str.begin(), input_str.end(), '/') != 1) {
		throw std::invalid_argument("Invalid format: expected 'num/denom'");
	}

	size_t pos = input_str.find('/');
	if (pos == 0 || pos >= input_str.length() - 1) {
		throw std::invalid_argument("Invalid format: numerator or denominator is empty");
	}

	std::string left = input_str.substr(0, pos);
	int num = std::stoi(left);
	return num;
}

int Fraction:: parseDenom(const std::string& str) {
	std::string input_str = str;
	input_str.erase(std::remove(input_str.begin(), input_str.end(), ' '), input_str.end());

	size_t pos = input_str.find('/');
	std::string right = input_str.substr(pos + 1);
	int denom = std::stoi(right);

	if (denom == 0) {
		throw std::invalid_argument("Division by zero");
	}

	if (denom < 0) {
		throw std::invalid_argument("Negative denominator: sign should be in numerator");
	}

	return denom;
}




Fraction::Fraction() {//Конструктор инициализации по умолчанию
	_num = 1;
	_denom = 1;
}
Fraction::Fraction(int num, int denom) {
	if (denom == 0) {
		throw std::invalid_argument("Division by zero");
	}
	else if (denom < 0) {//Если передали знак в знаменателе то перекидываем его в числитель
		denom *= -1;
		num *= -1;
	}
	_num = num;
	_denom = denom;

}
Fraction::Fraction(int num) {
	_num = num;
	_denom = 1;
}
Fraction::Fraction(const Fraction& other) { // Конструктор копирования
	this->_num = other._num;
	this->_denom = other._denom;
};
Fraction::Fraction(const std::string& input_str) :Fraction(parseNum(input_str), parseDenom(input_str)) {}

std::string Fraction::to_string() const {
	return std::to_string(_num) + "/" + std::to_string(_denom);
}
Fraction& Fraction::simplify() {
	int md = max_delt(_num, _denom);
	if (md > 0) {
		this->_num /= md;
		this->_denom /= md;
	}
	if (_denom < 0) {
		_num *= -1;
		_denom *= -1;
	}
	return (*this);
}
//Арифметические операторы с присвоением
Fraction& Fraction::operator+=(const Fraction& other) {
	this->_num = (_num * other._denom) + (other._num * _denom);
	this->_denom = _denom * other._denom;
	simplify();
	return (*this);
};
Fraction& Fraction::operator+=(int num) {
	this->_num = _num + (num * _denom);
	simplify();
	return (*this);
};
Fraction& Fraction::operator-=(const Fraction& other) {
	this->_num = (_num * other._denom) - (other._num * _denom);
	this->_denom = _denom * other._denom;
	simplify();
	return (*this);
};
Fraction& Fraction::operator-=(int num) {
	this->_num = _num - (num * _denom);
	simplify();
	return (*this);
};
Fraction& Fraction::operator*=(const Fraction& other) {
	if (other._num == 0) {
		this->_num = 0;
		this->_denom = 1;
		return (*this);
	}
	else
		this->_num *= other._num;
	this->_denom *= other._denom;
	simplify();
	return (*this);
};
Fraction& Fraction::operator*=(int num) {
	if (num == 0) {
		this->_num = 0;
		this->_denom = 1;
		return (*this);
	}
	else
		this->_num *= num;
	simplify();
	return (*this);
};
Fraction& Fraction::operator/=(const Fraction& other) {
	int o_num = other._num;
	this->_num *= other._denom;
	if (other._num == 0) {
		throw std::invalid_argument("Division by zero");
	}
	if (other._num < 0) {
		o_num *= -1;
		_num *= -1;
	}
	this->_denom *= o_num;
	simplify();
	return (*this);
};
Fraction& Fraction::operator/=(int num) {
	if (num == 0) {
		throw std::invalid_argument("Division by zero");
	}
	if (num < 0) {
		num *= -1;
		_num *= -1;
	}
	this->_denom *= num;
	simplify();
	return (*this);
};
//Арифметические операторы
Fraction Fraction::operator+(int num) const {
	Fraction res(*this);
	res += num;
	return res;
}

Fraction Fraction::operator+(const Fraction& other) const {
	Fraction res(*this);
	res += other;
	return res;
}

Fraction Fraction::operator-(int num) const {
	Fraction res(*this);
	res -= num;
	return res;
}

Fraction Fraction::operator-(const Fraction& other) const {
	Fraction res(*this);
	res -= other;
	return res;
}

Fraction Fraction::operator*(int num) const {
	Fraction res(*this);
	res *= num;
	return res;
}

Fraction Fraction::operator*(const Fraction& other) const {
	Fraction res(*this);
	res *= other;
	return res;
}

Fraction Fraction::operator/(int num) const {
	Fraction res(*this);
	res /= num;
	return res;
}

Fraction Fraction::operator/(const Fraction& other) const {
	Fraction res(*this);
	res /= other;
	return res;
}
//Операторы присвоения
Fraction Fraction::operator=(const Fraction& other) {
	return Fraction(_num = other._num, _denom = other._denom);

}
Fraction Fraction::operator=(int num) {
	return Fraction(_num = num, _denom = 1);

}
//Операторы сравнения


bool Fraction::operator==(const Fraction& other) const {
	Fraction that(*this);
	Fraction Other(other);
	that.simplify();
	Other.simplify();
	return ((that._num == Other._num) && (that._denom == Other._denom));
}

bool Fraction::operator!=(const Fraction& other) const {
	return !((*this) == other);
}

bool Fraction::operator>(const Fraction& other) const {
	Fraction that(*this);
	Fraction Other(other);
	that.simplify();
	Other.simplify();
	Other._denom *= that._denom;
	Other._num *= that._denom;
	that._denom *= other._denom;
	that._num *= other._denom;
	return (that._num > Other._num);
}

bool Fraction::operator<(const Fraction& other) const {
	return (other > (*this));
}

bool Fraction::operator>=(const Fraction& other) const {
	return (((*this) > other) || ((*this) == other));
}

bool Fraction::operator<=(const Fraction& other) const {
	return (((*this) < other) || ((*this) == other));
}

bool Fraction::operator==(int num) const {
	num *= _denom;
	return ((*this)._num == num);
}

bool Fraction::operator!=(int num) const {
	return !((*this) == num);
}

bool Fraction::operator>(int num) const {
	num *= _denom;
	return ((*this)._num > num);
}

bool Fraction::operator<(int num) const {
	num *= _denom;
	return ((*this)._num < num);
}

bool Fraction::operator>=(int num) const {
	return (((*this) > num) || ((*this) == num));
}

bool Fraction::operator<=(int num) const {
	return (((*this) < num) || ((*this) == num));
}

//int main() {
//
//}