#include "vector.h"
#include "memdata.h"
Vector::Vector(size_t size ) {//конструктор по умолчанию+размеру
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
	_back = list.size()-1;
}

Vector::Vector(double* list, size_t size)
{
	MemData mem(list,size);
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
	MemData mem(std::move( vector._mem));
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
