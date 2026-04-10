#include "basefraction.h"
int BaseFraction::max_delt(int a, int b) {
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
int BaseFraction::parseNum(const std::string& str) {
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
int BaseFraction::parseDenom(const std::string& str) {
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

void BaseFraction::simplify() noexcept {}

void BaseFraction::to_base_fraction() noexcept
{
	// в BaseFraction - пуст.
}

BaseFraction::BaseFraction(): _num(1), _denom(1){}
BaseFraction::BaseFraction(int num, int denom): _num(num),_denom(denom)
{
	if (denom == 0) { throw std::invalid_argument("Division by zero."); }
	if (num == 0) { _denom = 1; }
	if (denom < 0) {
		_denom *= -1;
		_num *= -1;
	}
}

BaseFraction::BaseFraction(int num): _num(num),_denom(1){}

BaseFraction::BaseFraction(const BaseFraction& other): _num(other._num),_denom(other._denom){}

BaseFraction::BaseFraction(const std::string& str): _num(parseNum(str)),_denom(parseDenom(str)){}

BaseFraction::~BaseFraction(){}

std::string BaseFraction::to_string() const {
	return std::to_string(_num) + "/" + std::to_string(_denom);
}
//Арифметические операторы с присвоением
BaseFraction& BaseFraction::operator+=(const BaseFraction& other) {
	to_base_fraction();
	this->_num = (_num * other._denom) + (other._num * _denom);
	this->_denom = _denom * other._denom;
	simplify();
	return (*this);
};
BaseFraction& BaseFraction::operator+=(int num) {
	to_base_fraction();
	this->_num = _num + (num * _denom);
	simplify();
	return (*this);
};
BaseFraction& BaseFraction::operator-=(const BaseFraction& other) {
	to_base_fraction();
	this->_num = (_num * other._denom) - (other._num * _denom);
	this->_denom = _denom * other._denom;
	simplify();
	return (*this);
};
BaseFraction& BaseFraction::operator-=(int num) {
	to_base_fraction();
	this->_num = _num - (num * _denom);
	simplify();
	return (*this);
};
BaseFraction& BaseFraction::operator*=(const BaseFraction& other) {
	to_base_fraction();
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
BaseFraction& BaseFraction::operator*=(int num) {
	to_base_fraction();
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
BaseFraction& BaseFraction::operator/=(const BaseFraction& other) {
	to_base_fraction();
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
BaseFraction& BaseFraction::operator/=(int num) {
	to_base_fraction();
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
BaseFraction BaseFraction::operator+(int num) const {
	BaseFraction res(*this);
	res += num;
	return res;
}

BaseFraction BaseFraction::operator+(const BaseFraction& other) const {
	BaseFraction res(*this);
	res += other;
	return res;
}

BaseFraction BaseFraction::operator-(int num) const {
	BaseFraction res(*this);
	res -= num;
	return res;
}

BaseFraction BaseFraction::operator-(const BaseFraction& other) const {
	BaseFraction res(*this);
	res -= other;
	return res;
}

BaseFraction BaseFraction::operator*(int num) const {
	BaseFraction res(*this);
	res *= num;
	return res;
}

BaseFraction BaseFraction::operator*(const BaseFraction& other) const {
	BaseFraction res(*this);
	res *= other;
	return res;
}

BaseFraction BaseFraction::operator/(int num) const {
	BaseFraction res(*this);
	res /= num;
	return res;
}

BaseFraction BaseFraction::operator/(const BaseFraction& other) const {
	BaseFraction res(*this);
	res /= other;
	return res;
}
//Операторы присвоения
BaseFraction& BaseFraction::operator=(const BaseFraction& other) {
	_num = other._num;
	_denom = other._denom;
	return *this;
}
BaseFraction& BaseFraction::operator=(int num) {
	_num = num;
	_denom = 1;
	return *this;
}

//Операторы сравнения
bool BaseFraction::operator==(const BaseFraction& other) const {
	BaseFraction that(*this);
	BaseFraction Other(other);
	that.simplify();
	Other.simplify();
	return ((that._num == Other._num) && (that._denom == Other._denom));
}

bool BaseFraction::operator!=(const BaseFraction& other) const {
	return !((*this) == other);
}

bool BaseFraction::operator>(const BaseFraction& other) const {
	BaseFraction that(*this);
	BaseFraction Other(other);
	that.simplify();
	Other.simplify();
	Other._denom *= that._denom;
	Other._num *= that._denom;
	that._denom *= other._denom;
	that._num *= other._denom;
	return (that._num > Other._num);
}

bool BaseFraction::operator<(const BaseFraction& other) const {
	return (other > (*this));
}

bool BaseFraction::operator>=(const BaseFraction& other) const {
	return (((*this) > other) || ((*this) == other));
}

bool BaseFraction::operator<=(const BaseFraction& other) const {
	return (((*this) < other) || ((*this) == other));
}

bool BaseFraction::operator==(int num) const {
	num *= _denom;
	return ((*this)._num == num);
}

bool BaseFraction::operator!=(int num) const {
	return !((*this) == num);
}

bool BaseFraction::operator>(int num) const {
	num *= _denom;
	return ((*this)._num > num);
}

bool BaseFraction::operator<(int num) const {
	num *= _denom;
	return ((*this)._num < num);
}

bool BaseFraction::operator>=(int num) const {
	return (((*this) > num) || ((*this) == num));
}

bool BaseFraction::operator<=(int num) const {
	return (((*this) < num) || ((*this) == num));
}
