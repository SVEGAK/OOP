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