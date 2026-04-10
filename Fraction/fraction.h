#pragma once
#include "basefraction.h"

class Fraction: public BaseFraction{
	private:
	//Служебные функции 
	void simplify() noexcept override; // упрощение дроби
	public:
	// Конструкторы
	Fraction(); // контруктор инициализации по умолчанию
	Fraction(int, int);//инициализации
	Fraction(int); // Частичная инициализация знаменатель единица
	Fraction(const Fraction&);// копирования
	Fraction(const std::string& str);//Иницализация через строку
	Fraction(const BaseFraction&);//Конструктор преобразования типа
	//Оператор присваивания с преобразованием
	Fraction& operator=(const BaseFraction&) noexcept;
	
};
