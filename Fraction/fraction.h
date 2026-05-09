#pragma once
#include "basefraction.h"

class Fraction: public BaseFraction{
	protected:
	//Служебные функции 
	int max_delt(int a, int b);//вспомогательная функция для simplify
	virtual void simplify() noexcept override; // упрощение дроби
	BaseFraction to_base_fraction() const noexcept override;
	std::unique_ptr<BaseFraction> clone() const {
		return std::make_unique<Fraction>(*this);   // создаём новый Fraction как копию *this
	}
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
