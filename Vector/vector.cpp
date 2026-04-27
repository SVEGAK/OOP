#include "vector.h"
#include "memdata.h"
#include <string>
#include <iostream>

Vector::Vector(size_t size) {//конструктор по умолчанию+размеру
	MemData object(size);
	_front = 0;
	if (size == 0) {_back = size;}
	else {_back = size-1;}
	_mem = object;
}

Vector::Vector(std::initializer_list<double> list)
{
	_front = 0;
	MemData md(list);
	_mem = md;
	_back = list.size() - 1;
}

Vector::Vector(double* list, size_t size)
{
	MemData mem(list, size);
	_front = 0;
	_mem = mem;
	if (size == 0) { _back = size; }
	else { _back = size - 1; }
}

Vector::Vector(const Vector& vector)
{
	_front = vector._front;
	_back = vector._back;
	MemData mem(vector._mem);
	_mem = mem;
}

Vector::Vector(Vector&& vector) noexcept
{
	_front = vector._front;
	_back = vector._back;
	MemData mem(std::move(vector._mem));
	_mem = mem;
	vector._front = 0;
	vector._back = 0;
}

Vector& Vector::operator=(const Vector& vector) noexcept
{
	_front = vector._front;
	_back = vector._back;
	_mem = vector._mem;
	return (*this);
}

Vector& Vector::operator=(Vector&& vector) noexcept
{
	_front = vector._front;
	_back = vector._back;
	_mem = std::move(vector._mem);
	vector._front = 0;
	vector._back = 0;
	return (*this);
}
double Vector::operator[](size_t pos) const noexcept {
	return _mem._data[pos];
}
double& Vector::operator[](size_t pos) noexcept
{
	return _mem._data[pos];
}
void Vector::push_back(double elem) noexcept {
	if (((*this).size() == 0) || (*this).is_empty()) {//если объект пуст или даже nullptr
		push_when_empty(elem);
		return;
	}
	
	if ((*this).is_full()) {
		(*this)._mem.reset_memory((*this).size()+1,_front,FRONT_BUFFER); // выделяем буфер
		_front = FRONT_BUFFER;
		_back = _front + (*this).size() - 1; //пересчитываю back
		(*this)._mem._data[_back] = elem;// ставлю элемент в нововыделенную ячейку
		return;
	}
	_back++;
	(*this)._mem._data[_back] = elem;
	(*this).size_increase();
	return;
}
void Vector::insert(double elem, size_t pos)
{
	if ((pos > _back) || (pos < _front)) {
		throw std::out_of_range("Insert position must be in [" + std::to_string(_front) + ';' +	std::to_string(_back) + "].");
	}
	if (((*this).is_empty())|| ((*this).size() == 0)) {//учитываем если буфер пуст( в том числе nullptr)
		push_when_empty(elem);
		return;
	}
	if ((*this).is_full()) { 
		(*this)._mem.reset_memory((*this).size()+1,_front, FRONT_BUFFER); //увеличиваем на MEM_STEP size + выделяем буфер MEMSTEP
		_front = FRONT_BUFFER;
		_back = (*this).size()+_front-1;
		double old_subj = elem;
		double temp = 0;
		size_t i = static_cast<size_t>( pos + _front );
		if (pos > ((*this).capacity() / 2)) {//cap = 19
			for (i; i < _back; i++) {
				temp = (*this)._mem._data[i];
				(*this)._mem._data[i] = old_subj;
				old_subj = temp;
			}
			
		}else {
			for (i; i > _front-2; i--) {
				temp = (*this)._mem._data[i];
				(*this)._mem._data[i] = old_subj;
				old_subj = temp;
			}
			
		}
		return;
	}
}
void Vector::push_front(double elem) noexcept
{
	if (((*this).size() == 0)|| ((*this).is_empty())) {//если объект пуст
		push_when_empty(elem);
		return;
	}
	if (((*this).is_full())||(_front == _back)) {
		(*this)._mem.reset_memory((*this)._mem.size() + 1,_front,FRONT_BUFFER); //увеличиваем на 1 ячейку size + выделяем буфер
		_front = FRONT_BUFFER-1;//берем элемент перед тем который уже стоит первым 
		(*this)._mem._data[_front] = elem;
		return;
	}
	_front--;
	(*this)._mem._data[_front] = elem;
	(*this).size_increase();
	return;
}
void Vector::push_when_empty(double elem) noexcept 
{
	_front = FRONT_BUFFER;
	if ((*this).capacity() < _front+1) {
		(*this)._mem.set_memory(_front); //передается size = 5
	}
	_back = _front;
	(*this)._mem._data[_front] = elem;
	(*this).size_increase();
	return;
}
void Vector::pop_when_empty() noexcept
{
	return;
}
void Vector::pop_front()
{
	if (((*this).size() == 0) || (*this).is_empty()) {//если объект пуст или даже nullptr
		throw std::out_of_range("Can't pop empty list.");
	}
	(*this)._mem._data[_front] = 0;
	_front++;
	(*this).size_decrease();
	//Нужно ли сжать массив?
}

void Vector::pop_back()
{
	if (((*this).size() == 0) || (*this).is_empty()) {//если объект пуст или даже nullptr
		throw std::out_of_range("Can't pop empty list.");
	}
	(*this)._mem._data[_back] = 0;
	_back--;
	(*this).size_decrease();
	//нужно ли уменьшить массив?
}

void Vector::erase(size_t pos)
{
	if ((pos > _back) || (pos < _front)) {
		throw std::out_of_range("Pop position must be in [" + std::to_string(_front) + ';' + std::to_string(_back) + "].");
	}
	if (((*this).is_empty()) || ((*this).size() == 0)) {//учитываем если буфер пуст( в том числе nullptr)
		throw std::out_of_range("Can't pop empty list.");
	}
	if ((*this).is_full()) {
		double old_subj = 0;
		double temp = -1;
		size_t i = static_cast<size_t>(pos + _front);
		if (pos > ((*this).capacity() / 2)) {
			_back--;
			size_t i = _back;
			for (i; i > (pos + _front); i--) {
				temp = (*this)._mem._data[i];
				(*this)._mem._data[i] = old_subj;
				old_subj = temp;
			}
		}
		else {
			_front++;
			size_t i = _front;
			for (i; i < (_front+pos); i++) {
				temp = (*this)._mem._data[i];
				(*this)._mem._data[i] = old_subj;
				old_subj = temp;
			}
		}
		//нужно ли сжать массив?
		(*this).size_decrease();
		return;
	}
	else {
		throw std::exception("Bad way");
	}
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
	size_t front = v.front_pos();
	size_t back = front + v.size()-1;
	os << "[";
	for (size_t i = front; i < back+1; i++) {
		if (i > front) os << ", ";
		os << v[i];
	}
	os << "]";
	return os;
}

std::istream& operator>>(std::istream& is, Vector& v) {
	double value;
	char ch;

	// пропускаем открывающую скобку
	if (is.peek() == '[') is.get(ch);

	// читаем числа через запятую или пробел
	while (is >> value) { //значение из потока считывается, то условие возвр true
		v.push_back(value);

		if (is.peek() == ',' || is.peek() == ' ' || is.peek() == '\t') {
			is.get(ch);
		}

		// Если закрывающая скобка — конец
		if (is.peek() == ']') {
			is.get(ch);
			break;
		}
	}

	// если ошибка ввода не из-за конца формата
	if (is.eof() || is.peek() == ']') {
		is.clear(is.rdstate() & ~std::ios::eofbit);
	}

	return is;
}