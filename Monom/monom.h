#pragma once
#define N 3 //
class Monom {
	double _coeff;
	int* _powers;
public:
	Monom();
	Monom(double, const int*); 
	Monom(const Monom&); //Конструктор перемещения
	Monom(Monom&&); //Конструктор копирование перемещения
	~Monom(); //Деструктор
	//Операторы 
	friend Monom operator*(const Monom&);
	friend Monom operator*(const Monom&, double);
	friend Monom operator*(double, const Monom&);
	Monom& operator*=(const Monom&);
	//Monom& operator=(const Monom&);
};