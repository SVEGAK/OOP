#include "vector.h"
#include "memdata.h"
#include <string>
Vector::Vector(size_t size) {//конструктор по умолчанию+размеру
	MemData object(size);
	_front = 0;
	if ((size != 0) && (size > 0)) {
		_back = size - 1;
	}
	else {
		_back = size;
	}

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
	if ((size != 0) && (size > 0)) {
		_back = size - 1;
	}
	else {
		_back = size;
	}
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
	if (((*this).size() == 0)|| (*this).is_empty()) {//если объект пуст или даже nullptr
		push_when_empty(elem);
		return;
	}
	if ((*this).is_full()) {
		_front = 5;
		(*this)._mem.reset_memory((*this)._mem.size() + 1,_front); //увеличиваем на 1 ячейку size + выделяем буфер
	}
	_back++;
	(*this)._mem._data[_back] = elem;

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
		_front = 5;
		(*this)._mem.reset_memory((*this).size()+1, _front); //увеличиваем на MEM_STEP size + выделяем буфер MEMSTEP
		_back = (*this).size()+_front;
		double old_subj = elem;
		double temp = 0;
		size_t i = static_cast<size_t>(pos+_front);
		if (pos > ((*this).capacity() / 2)) {
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
		_front = 5;
		(*this)._mem.reset_memory((*this)._mem.size() + 1,_front); //увеличиваем на 1 ячейку size + выделяем буфер
		(*this)._mem._data[_front] = elem;
		return;
	}
	_front--;
	(*this)._mem._data[_front] = elem;
	return;
}
void Vector::push_when_empty(double elem) noexcept 
{
	_front = 2;
	(*this)._mem.set_memory(_front + 1);
	_back = _front;
	(*this)._mem._data[_front] = elem;
	return;
}