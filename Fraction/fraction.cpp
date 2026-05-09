#include "fraction.h"
int Fraction::max_delt(int a, int b)
{
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

BaseFraction Fraction::to_base_fraction() const noexcept
{
	BaseFraction obj(_num, _denom);
	return obj;
}

Fraction::Fraction() : BaseFraction() {}

Fraction::Fraction(int num, int denom) : BaseFraction(num, denom) {}

Fraction::Fraction(int num): BaseFraction(num){}

Fraction::Fraction(const Fraction& other): BaseFraction(other) {}

Fraction::Fraction(const std::string& str): BaseFraction(str) {}

Fraction::Fraction(const BaseFraction& other): BaseFraction(other) {
	simplify();
}

Fraction& Fraction::operator=(const BaseFraction& other) noexcept
{
	_num = other.num();
	_denom = other.denom();
	simplify();
	return (*this);
}