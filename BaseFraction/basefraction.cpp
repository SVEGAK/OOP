#include "basefraction.h"
#include <cmath>

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

BaseFraction BaseFraction::to_base_fraction() const noexcept
{
	BaseFraction obj((*this));
	return obj;
}


BaseFraction::BaseFraction(): _num(0), _denom(1){}
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
	BaseFraction this_base = (*this).to_base_fraction();
	BaseFraction other_base_copy = other.to_base_fraction();
	this_base._num = (this_base._num * other_base_copy._denom) + (other_base_copy._num * this_base._denom);
	this_base._denom = this_base._denom * other_base_copy._denom;
	(*this) = this_base;
	simplify();
	return (*this);
}
BaseFraction& BaseFraction::operator+=(int num) {
	BaseFraction this_base = (*this).to_base_fraction();
	this_base._num = this_base._num + (num * this_base._denom);
	(*this) = this_base;
	simplify();
	return (*this);
}
BaseFraction& BaseFraction::operator-=(const BaseFraction& other) {
	BaseFraction this_base = (*this).to_base_fraction();
	BaseFraction other_base_copy = other.to_base_fraction();
	this_base._num = (this_base._num * other_base_copy._denom) - (other_base_copy._num * this_base._denom);
	this_base._denom = this_base._denom * other_base_copy._denom;
	(*this) = this_base;
	simplify();
	return (*this);
}
BaseFraction& BaseFraction::operator-=(int num) {
	BaseFraction this_base = (*this).to_base_fraction();
	this_base._num = this_base._num - (num * this_base._denom);
	(*this) = this_base;
	simplify();
	return (*this);
}
BaseFraction& BaseFraction::operator*=(const BaseFraction& other) {
	BaseFraction this_base = (*this).to_base_fraction();
	BaseFraction other_base_copy = other.to_base_fraction();
	if ((other_base_copy._num == 0)||(this_base._num == 0)) {
		this_base._num = 0;
		this_base._denom = 1;
		(*this) = this_base;
		return (*this);
	}
	else
	this_base._num *= other_base_copy._num;
	this_base._denom *= other_base_copy._denom;
	(*this) = this_base;
	simplify();
	return (*this);
}
BaseFraction& BaseFraction::operator*=(int num) {
	BaseFraction this_base = (*this).to_base_fraction();
	if ((num == 0)||(this_base._num == 0)) {
		this_base._num = 0;
		this_base._denom = 1;
		(*this) = this_base;
		return (*this);
	}
	else
		this_base._num *= num;
	(*this) = this_base;
	simplify();
	return (*this);
}
BaseFraction& BaseFraction::operator/=(const BaseFraction& other) {
	BaseFraction this_base = (*this).to_base_fraction();
	BaseFraction other_base_copy = other.to_base_fraction();
	if ((other_base_copy._num == 0)) {
		throw std::domain_error("Division by zero");
	}
	this_base._num *= other_base_copy._denom;
	if (other_base_copy._num < 0) {//Перенос знака в числитель текущей дроби
		other_base_copy._num *= -1;
		this_base._num *= -1;
	}
	this_base._denom *= other_base_copy._num;
	(*this) = this_base;
	simplify();
	return (*this);
}
BaseFraction& BaseFraction::operator/=(int num) {
	BaseFraction this_base = (*this).to_base_fraction();
	if (num == 0) {
		throw std::domain_error("Division by zero");
	}
	if (num < 0) {
		num *= -1;
		this_base._num *= -1;
	}
	this_base._denom *= num;
	(*this) = this_base;
	simplify();
	return (*this);
}
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
//BullandCows сделать приложение читабельным +
//CDate CTime доделать +
//to_base_fraction изменить так чтобы он возращал объект BaseFraction 
//Complex переделать операторы без дублирования
//Конструктор по строке Complex исправить
//Добавить перемешивание и сортировку в vector