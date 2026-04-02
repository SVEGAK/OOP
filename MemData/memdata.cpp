#pragma once
#include "memdata.h"

MemData::MemData(size_t size) {
	_size = size;
	_capacity = _size;
	_data = new double[_capacity];

}
MemData::MemData(std::initializer_list<double> list)
	
{
	
	_size = list.size();
	_capacity = _size;
	_data = new double[_capacity];
	const double* list_begin_p = list.begin();
	for (size_t i = 0; i < _size; i++) {
		_data[i] = *(list_begin_p + i);
	}
}
MemData::MemData(double* data, size_t size)
{
	_size = size;
	_capacity = _size;
	_data = new double[_capacity];
	for (size_t i = 0; i < size; i++) {
		_data[i] = data[i];
	}
}
MemData::MemData(const MemData& memdata)
{
	_size = memdata._size;
	_capacity = memdata._capacity;
	_data = new double[_capacity];
	for (size_t i = 0; i < _size; i++) {
		_data[i] = memdata._data[i];
	}
}
MemData::MemData(MemData&& memdata) noexcept
{
	_size = memdata._size;
	_capacity = memdata._capacity;
	_data = memdata._data;
	memdata._data = nullptr;
	memdata._size = 0;
	memdata._capacity = 0;
}
MemData::~MemData()
{
	if (_data) {
		delete[] _data;
	}
}

void MemData::set_memory(size_t size) noexcept
{
	_size = size;
	_capacity = _size;
	delete[] _data;
	_data = new double[_capacity];
}

void MemData::reset_memory(size_t size, size_t start_index) noexcept
{
	if (size == _size) {
		double* old = _data;
		_data = new double[_capacity];
		for (size_t i = 0; i < _size; i++) {
			_data[i] = old[i + start_index];
		}
		delete[] old;
		return;
	}
	size_t old_size = _size;
	if(size > _size){
		_size = size;
		_capacity = calculate_capacity(_size);
		double* old = _data;
		_data = new double[_capacity];
		for (size_t i = start_index; i < (start_index + old_size); i++) {
			_data[i] = old[i-start_index];
		}
		delete[] old;
	}
	else {
		_size = size;
		_capacity = calculate_capacity(_size);
		double* old = _data;
		_data = new double[_capacity];
		for (size_t i = start_index; i < (start_index + old_size); i++) {
			_data[i] = old[i - start_index];
		}
		delete[] old;
	}
	return;
}



MemData& MemData::operator=(const MemData& other) noexcept
{
	if (this != &other) {
		(*this)._size = other._size;
		(*this)._capacity = other._capacity;
		(*this)._data = new double[(*this)._capacity];
		for (size_t i = 0; i < _capacity; i++) {
			(*this)._data[i] = other._data[i];
		}
	}
	return (*this);
}

MemData& MemData::operator=(MemData&& other) noexcept
{
	if (this != &other) {
		(*this)._size = other._size;
		(*this)._capacity = other._capacity;
		(*this)._data = other._data;
		other._size = 0;
		other._capacity = 0;
		other._data = nullptr;
	}
	return (*this);
};




