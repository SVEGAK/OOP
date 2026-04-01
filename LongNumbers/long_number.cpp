#include "long_number.h"
#include <stdexcept>
#include <cmath>
#include <string>

//Конструкторы
LongNumber:: LongNumber() {
	_len = 1;
	_lnumber = new int[_len];
	_lnumber[0] = 0;
	_sign = 1;
}
LongNumber::LongNumber(const LongNumber& other) {
	_len = other._len;
	_lnumber = new int[_len];
	for (int i = 0; i < _len; i++) {
		_lnumber[i] = other._lnumber[i];
	}
	_sign = other._sign;
}
LongNumber::LongNumber(const std::string& str) {
	std::string input_str = str;
	input_str.erase(std::remove(input_str.begin(), input_str.end(), '+'), input_str.end());//убираем + тк он не влияет на знак
	int i = 0;
	int mk = 0;//количество минусов
	while (input_str[i] == '-') {
		mk++;
		i++;
	}
	if (mk % 2 == 0) { //если количество минусов четно то это +
		_sign = 1;
	}
	else {
		_sign = -1;
	}
	
	input_str.erase(std::remove(input_str.begin(), input_str.end(), '-'), input_str.end());//убираем -чтобы получить число

	_len = static_cast<int>(input_str.length());
	_lnumber = new int[_len];
	for (int i = 0; i < _len; i++) {
		if ((57 >= input_str[i])&&(input_str[i] >= 48)) {
			_lnumber[i] = input_str[i] - '0';	
		}else {
			throw std::invalid_argument("incorrect symbol is: " + std::string(1, input_str[i]));
		}
		  
		
	}
}
LongNumber::LongNumber(long long int num) {
	_len = 0;
	_sign = 1;
	if (num < 0) {
		_sign = -1;
		num *= -1;
	}
	long long int num_cpy = num;
	while (num_cpy > 0) {
		num_cpy /= 10;
		_len++;
	}
	_lnumber = new int[_len];
	for (int i = _len - 1; i >= 0; i--) {
		_lnumber[i] = num % 10;
		num = num/10;
	}
}
LongNumber::~LongNumber() {
	if (_lnumber) {
		delete[] _lnumber;
	}
}
long long int LongNumber ::  pow_long(int x, int a) {
	long long int res = 1;
	while (a > 0) {
		a--;
		res *= x;
	}
	return res;
}
void LongNumber::remove_leading_zeros() {
	int zero_count = 0;
	while (zero_count < _len - 1 && _lnumber[zero_count] == 0) {
		zero_count++;
	}
	if (zero_count > 0) {
		for (int k = 0; k < _len - zero_count; k++) {
			_lnumber[k] = _lnumber[k + zero_count];
		}
		_len -= zero_count;
	}
}
long long int LongNumber::get_lnum() {//вывод числа как int
	long long int res = 0;
	int cur = 0;
	long long int category = 1;
	if (_len  == 1) {
		res = _lnumber[0];
		return res;
	}
	for (int i = 0; i < _len; i++) {
		cur = _len - i - 1;
		category = pow_long(10,cur);
		res += (_lnumber[i] * category);

	}
	return res;
}
int LongNumber::get_len() {//вывод числа как int
	return _len;
}
int LongNumber::get_sign() {//вывод числа как int
	return _sign;
}
LongNumber& LongNumber:: resize_sum(int add_len,int p) {
	int* lnumber_rz = nullptr;
	int new_len = _len + add_len;
	lnumber_rz = new int[new_len];
	try {
		for (int i = 0; i < add_len; i++) {
			lnumber_rz[i] = p;
		}

		for (int i = add_len; i < new_len; i++) {
			lnumber_rz[i] = _lnumber[i - add_len];
		}
	}
	catch (const std::exception& e) {
		throw std::out_of_range("");
	}
	delete[] _lnumber; // удаляем старый массив по еще не замененному указателю
	_lnumber = lnumber_rz;
	_len = new_len;
	
	return (*this);//возвращает ссылку на измененный объект
};
bool LongNumber::equals(const LongNumber& other) const {
	if (_sign != other._sign) return false;
	if (_len != other._len) return false;

	for (int i = 0; i < _len; i++) {
		if (_lnumber[i] != other._lnumber[i]) return false;
	}
	return true;
}

bool LongNumber::is_zero() const {
	if (_len == 0) return true;
	for (int i = 0; i < _len; i++) {
		if (_lnumber[i] != 0) return false;
	}
	return true;
}
int LongNumber::compare_abs(const LongNumber& a, const LongNumber& b) { // Сравнение чисел по МОДУЛЮ
	if (a._len > b._len) return 1;
	if (a._len < b._len) return -1;

	for (int i = 0; i < a._len; i++) {
		if (a._lnumber[i] > b._lnumber[i]) return 1;
		if (a._lnumber[i] < b._lnumber[i]) return -1;
	}
	return 0;
}

//Арифметические операторы с присвоением
LongNumber& LongNumber::operator+=(const LongNumber& other) {
	if (other.is_zero()) return *this; // Если одно из слагаемых 0 то ничего не делаем
	if (this->is_zero()) {
		*this = other;
		return *this;
	}
	LongNumber Other(other); //Создаю копию other для более удобной работы
	if ((*this)._sign == Other._sign) { // если знаки равны то это всегда сумма
		if (_len > Other._len) {
			Other.resize_sum(_len - Other._len, 0);
		}
		else if (_len < Other._len) {
			this->resize_sum(Other._len - _len, 0);
		}
		 //Случай с одинаковыми знаками
			int s = 0;
			int p = 0;
			for (int i = (*this)._len - 1; i >= 0; i--) {
		
				s = (*this)._lnumber[i] + Other._lnumber[i] + p;

				(*this)._lnumber[i] = s % 10;
				if (s > 9) {
					p = 1;
					if (i == 0) {
						(*this).resize_sum(1,p);
					}

				}
				else {
					p = 0;
				}

			}
		}else{
		if (compare_abs(*this, Other) == 0 ) { //числа равны по модулю
			delete[] _lnumber;
			_len = 1;
			_lnumber = new int[1];
			_lnumber[0] = 0;
			(*this)._sign = 1;
			return (*this);
		}
		else if (compare_abs(*this, Other) == 1) {// первое больше по модулю
			int  p= 0;
			Other.resize_sum(_len - Other._len, 0);
			for (int i = (*this)._len - 1; i >= 0; i--) {
				int sub = Other._lnumber[i] + p;
				p = 0;
				if ((*this)._lnumber[i] < sub) {
					(*this)._lnumber[i] += 10;
					p = 1;
				}
				(*this)._lnumber[i] -= sub;
			}
			remove_leading_zeros();
		}
		else {
				LongNumber temp(*this);
				*this = Other;
				(*this)._sign = Other._sign;
				int p = 0;
				temp.resize_sum(_len - temp._len, 0);
				for (int i = (*this)._len - 1; i >= 0; i--) {
					int sub = temp._lnumber[i] + p;
					p = 0;
					if ((*this)._lnumber[i] < sub) {
						(*this)._lnumber[i] += 10;
						p = 1;
					}
					(*this)._lnumber[i] -= sub;
				}
				remove_leading_zeros();
		}

	}
	return (*this);
};
LongNumber& LongNumber::operator=(const LongNumber& other) {
	if (this == &other) return *this;
	delete[] _lnumber; 
	_len = other._len;
	_sign = other._sign;
	_lnumber = new int[_len];
	for (int i = 0; i < _len; i++) {
		_lnumber[i] = other._lnumber[i];
	}
	return *this;
}

LongNumber& LongNumber::operator-=(const LongNumber& other) {
	LongNumber neg_other(other);
	neg_other._sign *= -1;
	*this += neg_other;	
	return (*this);
};


LongNumber LongNumber::operator+(const LongNumber& other) const {
	LongNumber result(*this);
	result += other;
	return result;
}

LongNumber LongNumber::operator-(const LongNumber& other) const {
	LongNumber result(*this);
	result -= other;
	return result;
}
LongNumber LongNumber::operator*(const LongNumber& other) const {
	LongNumber result(*this);
	result *= other;
	return result;
}
LongNumber& LongNumber::operator*=(const LongNumber& other) {
	//  умножение на ноль
	if (other.is_zero() || this->is_zero()) {
		delete[] _lnumber;
		_len = 1;
		_lnumber = new int[1];
		_lnumber[0] = 0;
		_sign = 1;
		return *this;
	}


	int result_sign = _sign * other._sign;


	LongNumber num1(*this);
	LongNumber num2(other);

	// результат может иметь максимум len1 + len2 цифр
	int new_len = num1._len + num2._len;
	int* result = new int[new_len];


	for (int i = 0; i < new_len; i++) {
		result[i] = 0;
	}


	for (int i = num1._len - 1; i >= 0; i--) {
		for (int j = num2._len - 1; j >= 0; j--) {
			int product = num1._lnumber[i] * num2._lnumber[j];
			int pos1 = i + j;      // Позиция для переноса
			int pos2 = i + j + 1;  // Позиция для текущей цифры

			int sum = product + result[pos2];
			result[pos2] = sum % 10;
			result[pos1] += sum / 10;
		}
	}


	int start = 0;
	while (start < new_len - 1 && result[start] == 0) {
		start++;
	}


	delete[] _lnumber;


	_len = new_len - start;
	_lnumber = new int[_len];
	for (int i = 0; i < _len; i++) {
		_lnumber[i] = result[start + i];
	}

	_sign = result_sign;

	delete[] result;
	return *this;
}

bool LongNumber::operator==(const LongNumber& other) const {
	if (this->is_zero() && other.is_zero()) {
		return true;
	}

	if (_sign != other._sign) {
		return false;
	}

	if (_len != other._len) {
		return false;
	}

	for (int i = 0; i < _len; i++) {
		if (_lnumber[i] != other._lnumber[i]) {
			return false;
		}
	}

	return true;
}



bool LongNumber::operator>(const LongNumber& other) const {
	if (this->is_zero() && other.is_zero()) {
		return false;
	}

	if (_sign != other._sign) {
		return _sign > other._sign;
	}

	if (_sign == 1) {
		if (_len != other._len) {
			return _len > other._len;
		}
		for (int i = 0; i < _len; i++) {
			if (_lnumber[i] != other._lnumber[i]) {
				return _lnumber[i] > other._lnumber[i];
			}
		}
		return false;
	}
	else {
		if (_len != other._len) {
			return _len < other._len;
		}
		for (int i = 0; i < _len; i++) {
			if (_lnumber[i] != other._lnumber[i]) {
				return _lnumber[i] < other._lnumber[i];
			}
		}
		return false;
	}
}

bool LongNumber::operator<(const LongNumber& other) const {
	return other > *this;
}

bool LongNumber::operator>=(const LongNumber& other) const {
	return !(*this < other);
}

bool LongNumber::operator<=(const LongNumber& other) const {
	return !(*this > other);
}

bool LongNumber::operator!=(const LongNumber& other) const {
	return !(*this == other);
}


LongNumber LongNumber::operator-() const {
	LongNumber result(*this);
	if (!result.is_zero()) {
		result._sign *= -1;
	}
	return result;
}



LongNumber LongNumber::operator++(int)
{
	LongNumber old(*this);
	(*this) += LongNumber(1);
	return old;
}

LongNumber LongNumber::operator--(int)
{
	LongNumber old(*this);
	(*this) -= LongNumber(1);
	return old;
}

LongNumber& LongNumber::operator++()
{
	(*this) += LongNumber(1);
	return (*this);
}

LongNumber& LongNumber::operator--()
{
	(*this) -= LongNumber(1);
	return (*this);
}

int LongNumber::operator[](int pos) const
{
	if ((pos < 0)||(pos >= _len) ){
		throw std::out_of_range("Number index out of range.");
	}
	if (pos == 0) {
		return (_lnumber[pos] * _sign);
	}
	return _lnumber[pos];
}

std::ostream& operator<<(std::ostream& out, const LongNumber& num)
{
	if (num.is_zero()) {
		out << 0;
		return out;
	}
	if (num._sign == -1) {
		out << '-';
	}
	for (int i = 0; i < num._len; i++) {
		out << num._lnumber[i];
	}
	return out;
}

std::istream& operator>>(std::istream& input,  LongNumber& num)
{
	std::string s;
	input >> s;
	if (s.length() > 0) {
		num = LongNumber(s);
	}
	return input;
}

LongNumber operator+(long long int num,const LongNumber& lnum)
{
	
	return lnum + LongNumber(num);
}
LongNumber operator+(const LongNumber& lnum, long long int num)
{
	return lnum + LongNumber(num);
}

LongNumber operator-(long long int num, const LongNumber& lnum)
{
	return LongNumber(num) - lnum;
}
LongNumber operator-(const LongNumber& lnum, long long int num)
{
	return lnum - LongNumber(num);
}

std::string LongNumber:: to_string()
{
	std::string res_str;
	if (_sign == -1) {
		res_str = '-';
	}
	for (size_t i = 0; i < _len; i++) {
		res_str += static_cast<char>(_lnumber[i] + '0');
	}
	return res_str;
};
