#pragma once
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <iostream>

class BaseFraction {

protected:

	int _num; // Числитель
	int _denom; // Знаменатель
	//Служебные функции 
	virtual void simplify() noexcept;// упрощение дроби
	virtual BaseFraction to_base_fraction() const noexcept;
	static int parseNum(const std::string& str);
	static int parseDenom(const std::string& str);
	virtual std::unique_ptr<BaseFraction> clone() const {
		return std::make_unique<BaseFraction>(*this);   // создаём новый BaseFraction как копию *this
	}
	//Проблему с simlify() в операторах +-/* решил с помощью функции возвращающей умный указатель
	virtual void assign(const BaseFraction& other) {//Виртуальная функция для присваивания чтобы 
		_num = other.num();							//обойти игнорирование поля _integer при присваивании в операторах
		_denom = other.denom();										
	}

public:
	// Конструкторы
	BaseFraction(); // контруктор инициализации по умолчанию
	BaseFraction(int, int);//инициализации
	BaseFraction(int); // Частичная инициализация знаменатель единица
	BaseFraction(const BaseFraction&);// копирования
	BaseFraction(const std::string& str);//Иницализация через строку
	//Методы
	virtual std::string to_string() const;
	//Операторы
	//арифметика с присваиванием
	BaseFraction& operator+=(const BaseFraction& other);
	BaseFraction& operator+=(int);
	BaseFraction& operator-=(const BaseFraction& other);
	BaseFraction& operator-=(int);
	BaseFraction& operator*=(const BaseFraction& other);
	BaseFraction& operator*=(int);
	BaseFraction& operator/=(const BaseFraction& other);
	BaseFraction& operator/=(int);
	//Арифметика
	BaseFraction operator+(int) const;
	BaseFraction operator+(const BaseFraction& other) const;
	BaseFraction operator-(const BaseFraction& other) const;
	BaseFraction operator-(int) const;
	BaseFraction operator*(const BaseFraction& other) const;
	BaseFraction operator*(int) const;
	BaseFraction operator/(const BaseFraction& other) const;
	BaseFraction operator/(int) const;
	//Присвоение
	BaseFraction& operator=(const BaseFraction& other);
	BaseFraction& operator=(int);
	//Сравнение
	bool operator==(const BaseFraction& other) const;
	bool operator!=(const BaseFraction& other) const;
	bool operator>(const BaseFraction& other) const;
	bool operator<(const BaseFraction& other) const;
	bool operator>=(const BaseFraction& other) const;
	bool operator<=(const BaseFraction& other) const;
	//Сравнение с целыми
	bool operator==(int num) const;
	bool operator!=(int num) const;
	bool operator>(int num) const;
	bool operator<(int num) const;
	bool operator>=(int num) const;
	bool operator<=(int num) const;
	//Геттеры
	int num() const{ return _num; };
	int denom() const{ return _denom; };

	virtual ~BaseFraction();

	//friend std::ostream& operator<<(std::ostream&, const BaseFraction&);
	//friend std::istream& operator>>(std::istream& in, BaseFraction& frac);

};