#pragma once
#include "fraction.h"
class RightFraction : public Fraction {
	protected:
	int _integer;
	size_t find_Integer_pos(const std::string& input_str);
	int parseInteger(const std::string& input_str, size_t pos);
	//Целая часть
	BaseFraction to_base_fraction() const noexcept override;
	void simplify() noexcept override;
	std::unique_ptr<BaseFraction> clone() const {
		return std::make_unique<RightFraction>(*this);   // создаём новый RightFraction как копию *this
	}
	void assign(const BaseFraction& other) override{
		_integer = 0;
		_num = other.num();							
		_denom = other.denom();
	}
	public:
	// Конструкторы RightFraction
	RightFraction(); // по умолчанию: 0
	RightFraction(int integer, int num, int denom); // полная инициализация
	RightFraction(int integer, int num); // знаменатель = 1
	RightFraction(int integer); // дробная часть = 0
	RightFraction(const RightFraction&); // копирования
	RightFraction(const std::string& str); // из строки
	RightFraction(const Fraction&); // преобразование из Fraction
	RightFraction(const BaseFraction&); // преобразование из BaseFraction
	//Оператор присваивания с изменением типа
	RightFraction& operator=(const BaseFraction&) noexcept;
	RightFraction& operator=(const Fraction&) noexcept;
	//Геттеры
	int integer() const { return _integer; }
	//Функции ввода вывода
	friend std::ostream& operator<<(std::ostream& out, const RightFraction&);
	friend std::istream& operator>>(std::istream& in, RightFraction& frac);
};