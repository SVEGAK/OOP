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
	pos = (pos + _front) % capacity();
	return _mem._data[pos];
}
double& Vector::operator[](size_t pos) noexcept
{
	pos = (pos + _front) % capacity();
	return (_mem._data[pos]);
}
void Vector::push_back(double elem) noexcept {
	if ((size() == 0) || is_empty()) {//если объект пуст или даже nullptr
		push_when_empty(elem);
		return;
	}
	
	if (is_full()) {
		_mem.reset_memory(size()+1,_front,FRONT_BUFFER); // выделяем буфер
		_front = FRONT_BUFFER;
		_back = _front + size() - 1; //пересчитываю back
		_mem._data[_back] = elem;// ставлю элемент в нововыделенную ячейку
		return;
	}
	_back++;
	_mem._data[_back] = elem;
	size_increase();
	return;
}
void Vector::insert(double elem, size_t pos)
{
	if (pos > size()) {
		throw std::out_of_range("Insert position must be in [0;" + std::to_string(size()) + "].");
	}

	if (is_empty() || size() == 0) {
		push_when_empty(elem);
		return;
	}

	if (is_full()) {
		_mem.reset_memory(size() + 1, _front, FRONT_BUFFER);
		_front = FRONT_BUFFER;
		_back = _front + size() - 1;
	}

	size_t phys_pos = (pos + _front)%capacity();
	for (size_t i = _back + 1; i > phys_pos; i--) {
		_mem._data[i] = _mem._data[i - 1];
	}
	_mem._data[phys_pos] = elem;
	++_back;
	return;
}
void Vector::push_front(value_type elem) noexcept
{
	if (((*this).size() == 0)|| ((*this).is_empty())) {//если объект пуст
		push_when_empty(elem);
		return;
	}
	if (((*this).is_full())||(_front == _back)) {
		(*this)._mem.reset_memory((*this)._mem.size() + 1,_front,FRONT_BUFFER); //увеличиваем на 1 ячейку size + выделяем буфер
		_front = FRONT_BUFFER-1;//берем элемент перед тем который уже стоит первым 
		(*this)[0] = elem;
		return;
	}
	_front--;
	(*this)[0] = elem;
	(*this).size_increase();
	return;
}
void Vector::push_when_empty(value_type elem) noexcept 
{
	_front = FRONT_BUFFER;
	if (capacity() < _front+1) {
		_mem.set_memory(_front); //передается size = 5
	}
	_back = _front;
	(*this)[0] = elem;
	size_increase();
	return;
}
void Vector::pop_when_empty() noexcept
{
	return;
}
void Vector::pop_front()
{
	if ((_mem.size() == 0) || (*this).is_empty()) {//если объект пуст или даже nullptr
		throw std::out_of_range("Can't pop empty list.");
	}
	(*this)[0] = 0;
	_front = (_front+1)%capacity();
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
	if (pos == 0) { (*this).pop_front(); return; }
	else if (pos == _mem._size) { (*this).pop_back(); return; }
	double old_subj = 0;
	double temp = -1;
	for (size_t i = _front; i < pos+1; i++) {
		(*this)[i] = temp;
		(*this)[i] = old_subj;
		old_subj = temp;
	}
	_mem.reset_memory(_mem._size - 1, _front + 1,FRONT_BUFFER);
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