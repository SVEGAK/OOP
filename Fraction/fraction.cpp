#include "fraction.h"
void Fraction::simplify() noexcept {
	int md = max_delt(_num, _denom);
	if (md > 0) {
		_num /= md;
		_denom /= md;
	}
	if (_denom < 0) {
		_num *= -1;
		_denom *= -1;
	}
}

Fraction::Fraction() : BaseFraction() {}

Fraction::Fraction(int num, int denom) : BaseFraction(num, denom) {}

Fraction::Fraction(int num): BaseFraction(num){}

Fraction::Fraction(const Fraction& other): BaseFraction(other) {}

Fraction::Fraction(const std::string& str): BaseFraction(str) {}

Fraction::Fraction(const BaseFraction& other): BaseFraction(other){}

Fraction& Fraction::operator=(const BaseFraction& other) noexcept
{
	(*this)._num = other.num();
	(*this)._denom = other.denom();
	return (*this);
}


// Арифметические операторы (создают Fraction res, а не BaseFraction)
Fraction Fraction::operator+(int num) const {
    Fraction res(*this);
    res += num;
    return res;
}
Fraction Fraction::operator+(const BaseFraction& other) const {
    Fraction res(*this);
    res += other;
    return res;
}
Fraction Fraction::operator-(int num) const {
    Fraction res(*this);
    res -= num;
    return res;
}
Fraction Fraction::operator-(const BaseFraction& other) const {
    Fraction res(*this);
    res -= other;
    return res;
}
Fraction Fraction::operator*(int num) const {
    Fraction res(*this);
    res *= num;
    return res;
}
Fraction Fraction::operator*(const BaseFraction& other) const {
    Fraction res(*this);
    res *= other;
    return res;
}
Fraction Fraction::operator/(int num) const {
    Fraction res(*this);
    res /= num;
    return res;
}
Fraction Fraction::operator/(const BaseFraction& other) const {
    Fraction res(*this);
    res /= other;
    return res;
}

// Операторы сравнения (локальные переменные типа Fraction)
bool Fraction::operator==(const BaseFraction& other) const {
    Fraction that(*this);
    Fraction Other(other);
    that.simplify();
    Other.simplify();
    return ((that._num == Other._num) && (that._denom == Other._denom));
}

bool Fraction::operator!=(const BaseFraction& other) const {
    return !((*this) == other);
}

bool Fraction::operator>(const BaseFraction& other) const {
    Fraction that(*this);
    Fraction Other(other);
    that.simplify();
    Other.simplify();
    Other._denom *= that._denom;
    Other._num *= that._denom;
    that._denom *= other.denom();
    that._num *= other.denom();
    return (that._num > Other._num);
}

bool Fraction::operator<(const BaseFraction& other) const {
    return (other > (*this));
}

bool Fraction::operator>=(const BaseFraction& other) const {
    return (((*this) > other) || ((*this) == other));
}

bool Fraction::operator<=(const BaseFraction& other) const {
    return (((*this) < other) || ((*this) == other));
}