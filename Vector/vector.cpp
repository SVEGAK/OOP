#include "vector.h"
#include "memdata.h"
#include <string>
#include <iostream>
#include <cmath>
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
	if ((_back == (capacity() - 1)) && !(_mem.is_full())) {
		_mem.reset_memory(size()+1, _front, 0);//просто сдвигаем массив влево если есть свободное место
		_front = 0;
		_back = _front + size()-1;
		_mem._data[_back] = elem;
		return;

	}else if (is_full()) {
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
	else {
		size_increase();
		_back++;
	}

	size_t phys_pos = (pos + _front)%capacity();
	for (size_t i = _back; i > phys_pos; i--) {
		_mem._data[i] = _mem._data[i - 1];
	}
	_mem._data[phys_pos] = elem;
	return;
}
void Vector::push_front(value_type elem) noexcept
{
	if ((size() == 0)|| (is_empty())) {//если объект пуст
		push_when_empty(elem);
		return;
	}
	if ((is_full())||(_front == _back)||(_front == 0)) {
		_mem.reset_memory(size() + 1,_front, FRONT_BUFFER); //увеличиваем на 1 ячейку size + выделяем буфер
		_front = FRONT_BUFFER-1;//берем элемент перед тем который уже стоит первым
		_back = _front + size() - 1;
		(*this)[0] = elem;
		return;
	}
	_front--;
	(*this)[0] = elem;
	size_increase();
	return;
}
void Vector::push_when_empty(value_type elem) noexcept 
{
	_front = 0;
	_mem.set_memory(_front);
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
	size_decrease();
	compress();
}

void Vector::pop_back()
{
	if (((*this).size() == 0) || (*this).is_empty()) {//если объект пуст или даже nullptr
		throw std::out_of_range("Can't pop empty list.");
	}
	if (_back == 0) {
		_mem._data[_back] = 0;
		_back = 0;
		size_decrease();
		compress();
		return;
	}
	else if (_back < 0) { throw std::out_of_range("back pos element out of massive."); }
	_mem._data[_back] = 0;
	_back--;
	size_decrease();
	compress();
}

void Vector::erase(size_t pos)// pos - логический индекс
{
	if (pos >= size()) {// size_t беззнаковый тип
		throw std::out_of_range("Pop position must be in [" + std::to_string(0) + ';' + std::to_string(size() - 1) + "].");
	}
	if (((*this).is_empty())) {//учитываем если буфер пуст( в том числе nullptr)
		throw std::out_of_range("Can't pop empty list.");
	}
	if (pos == 0){
		(*this).pop_front();
		return;
	}else if (pos == (_mem._size - 1)){
		(*this).pop_back();
		return;
	}
	for (size_t i = pos; i < size() - 1; i++) {//сдвиг элементов влево
		(*this)[i] = (*this)[i + 1];
	}
	_mem.reset_memory(_mem._size - 1, _front,0);
	_front = 0;	_back = _front + size() - 1;
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
	os << "{ ";
	for (size_t i = 0; i < v.size(); i++) {
		if (i > 0) os << ", ";
		os << v[i];
	}
	os << " }";
	return os;
}
std::istream& operator>>(std::istream& is, Vector& v) {
	size_t len = 0;
	is >> len;
	v._mem.set_memory(len);
	for (size_t i = 0; i < len;i++) {
		value_type temp = 0;
		is >> temp;
		v.push_back(temp);
	}
	return is;
}

void Vector::push_back_n(const value_type* values, size_t n) {
	if (n == 0) return;
	for (size_t i = 0;i < n;i++) {
		(*this).push_back(values[i]);
	}
}

void Vector::push_front_n(const value_type* values, size_t n) {
	if (n == 0) return;
	for (size_t i = 0;i < n;i++) {
		if (i == 0) {
			(*this).push_front(values[0]);
			continue;
		}
		(*this).insert(values[i], i);
	}
}

void Vector::insert_n(size_t pos, const value_type* values, size_t n) {
	if (n == 0) return;
	if (pos == 0) { push_front_n(values, n); return; }
	if (pos == size()) { push_back_n(values, n); return; }
	for (size_t i = 0; i < n; i++) {
		(*this).insert(values[i], pos+i);
	}
}

void Vector::erase_n(size_t pos, size_t n) {
	if (n == 0) return;
	if (pos + n > size()) {
		throw std::out_of_range("erase_n range out of bounds");
	}
	for (size_t i = 0; i < n;i++) {
		erase(pos);
	}

}