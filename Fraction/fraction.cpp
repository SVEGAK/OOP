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
