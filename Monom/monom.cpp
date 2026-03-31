#include "monom.h"
Monom::Monom() {
	_coeff = 0;
	_powers = new int[N];
	for (int i = 0; i < N; i++) {
		_powers[i] = 0;
	}
};
Monom::Monom(const Monom& other) {
	_coeff = other._coeff;
	_powers = new int[N];

	for (int i = 0; i < N; i++) {
		_powers[i] = other._powers[i];
	}
};
Monom::Monom(double coeff, const int* power) {
	_coeff = coeff;
	_powers = new int[N];
	for (int i = 0; i < N; i++) {
		_powers[i] = power[i];
	}
};
Monom::~Monom() {
	if (_powers) {
		delete [] _powers;
	}
	
}

Monom::Monom(Monom&& other) { // Два && чтобы отличать от копирования
	_coeff = other._coeff;
	_powers = other._powers;
	other._powers = nullptr;
};
Monom operator*(const Monom& monom,double num) {
	Monom res(monom._coeff *num, monom._powers);
	return res;
}
Monom operator*(double num, const Monom& monom) {
	return monom * num;
}
Monom operator*(const Monom& other) {
	Monom res;
	res._coeff *= other._coeff;
	//res._coeff = res._coeff* other._coeff;
	for (int i = 0; i < N; i++) {
		res._powers += other._powers[i];
	};
	return res;
};
//Monom& Monom::operator*=(const Monom& other) {
//	*this = (*this) * other;
//
//	return *this;
//};
//Monom& operator=(const Monom* other) {
//	if (this != &other) {
//		this->coeff = other._coeff;
//		for (int i = 0; i < N; i++) {
//			this->powers[i] = other._powers[i];
//		}
//
//	};
//}