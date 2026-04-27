#pragma once
#include "memdata.h"

MemData::MemData(size_t size) {
	_capacity = calculate_capacity(size);
	_size = 0;
	
	_data = new value_type[_capacity];

}
MemData::MemData(std::initializer_list<value_type> list)
	
{
	_size = list.size();
	_capacity = _size;
	_data = new value_type[_capacity];
	const value_type* list_begin_p = list.begin();
	for (size_t i = 0; i < _size; i++) {
		_data[i] = *(list_begin_p + i);
	}
}
MemData::MemData(value_type* data, size_t size)
{
	_size = size;
	_capacity = calculate_capacity(_size);
	_data = new value_type[_capacity];
	for (size_t i = 0; i < size; i++) {
		_data[i] = data[i];
	}
}
MemData::MemData(const MemData& memdata)
{
	_size = memdata._size;
	_capacity = memdata._capacity;
	_data = new value_type[_capacity];
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
	_size = 0;
	_capacity = calculate_capacity(size);
	delete[] _data;
	_data = new value_type[_capacity];
}

void MemData::reset_memory(size_t size, size_t start_index, size_t placement_offset) noexcept //start index - индекс начала элементов в старом массиве
{
	value_type* old_data = _data;
	_capacity = calculate_capacity(size + placement_offset);
	_data = new value_type[_capacity];
	if (size > _size){
		for (size_t i = 0;i < _size; i++) {
			_data[i+ placement_offset] = old_data[i + start_index];
		}
	}
	else { //size <= _size
		for (size_t i = 0;i < size; i++) {
			_data[i+ placement_offset] = old_data[i + start_index];
		}
	}
	_size = size;
	delete[] old_data;
	return;
}



MemData& MemData::operator=(const MemData& other) noexcept
{
	if (this != &other) {
		(*this)._size = other._size;
		(*this)._capacity = other._capacity;
		(*this)._data = new value_type[(*this)._capacity];
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




