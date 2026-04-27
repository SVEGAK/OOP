#pragma once
#include <iostream>
#include "memdata.h"
#include <stdexcept>
class Vector {
    MemData _mem;         // хранилище данных + размер  + вместимость
    size_t _front;        // индекс первого элемента
    size_t _back;         // индекс последнего элемента
    void make_buffer();
public:
    Vector(size_t size = 0);                 // конструктор по размеру + по умолчанию
    Vector(std::initializer_list<double>);   // конструктор по списку инициализации
    Vector(double* list, size_t size);       // конструктор инициализации
    Vector(const Vector& vector);            // конструктор копирования
    Vector(Vector&& vector) noexcept;        // конструктор с move-семантикой
    ~Vector() = default;                     // деструктор

    inline bool is_empty() const noexcept;          // проверка на пустоту
    inline bool is_full() const noexcept;           // проверка на переполнение

    inline size_t size() const noexcept;            // геттер размера
    inline size_t capacity() const noexcept;        // геттер вместимости
    inline double front() const;                    // геттер первого элемента
    inline double back() const;                     // геттер последнего элемента
    inline size_t front_pos() const;                // геттер индекса первого элемента
    inline size_t back_pos() const;                 // геттер индекса последнего элемента

    inline double& set_front();                       // сеттер первого элемента
    inline double& set_back();                        // сеттер последнего элемента

    void push_front(double elem) noexcept;          // вставка элемента в начало
    void push_back(double elem) noexcept;           // вставка элемента в конец
    void insert(double elem, size_t pos);           // вставка элемента по позиции
    void push_when_empty(double elem) noexcept;     //вспомогательная функция для вставки
    void pop_when_empty() noexcept;                 //вспомогательная функция для удаления
    inline void size_decrease() noexcept;           //вспомогательная функция уменьшения size
    inline void size_increase() noexcept;           //вспомогательная функция увеличения size
    void pop_front();                               // удаление элемента из начала
    void pop_back();                                // удаление элемента из конца
    void erase(size_t pos);                         // удаление элемента по позиции
    
    Vector& operator=(const Vector& vector) noexcept;      // оператор присваивания
    Vector& operator=(Vector&& vector) noexcept;           // оператор присваивания с move-семантикой

    double operator[](size_t pos) const noexcept;       // оператор обращения по индексу константный
    double& operator[](size_t pos) noexcept;            // оператор обращения по индексу

    friend std::ostream& operator<<(std::ostream&, const Vector&);     // вывод
    friend std::istream& operator>>(std::istream&, Vector&);           // ввод
};


inline bool Vector::is_empty() const noexcept
{
    return _mem.is_empty();
}

inline bool Vector::is_full() const noexcept
{
    if ((_back == (_mem._capacity - 1)) || (_mem.is_full())||(_front == 0)) { return true; }
    return false;
}

inline size_t Vector::size() const noexcept
{
    return (*this)._mem.size();
}

inline size_t Vector::capacity() const noexcept
{
    return (*this)._mem.capacity();
}

inline size_t Vector::front_pos() const
{
    return _front;
}

inline size_t Vector::back_pos() const
{
    return _back;
}

inline double Vector::front() const
{
    if (_mem.is_empty()) { throw std::out_of_range("Buffer ring is empty"); }
    double res = _mem.data()[_front];
    return res;
}
inline double Vector::back() const
{
    if (_mem.is_empty()) { throw std::out_of_range("Buffer ring is empty"); }
    double res = _mem.data()[_back];
    return res;
}
inline void Vector::size_decrease() noexcept
{
    (*this)._mem._size--;
}

inline void Vector::size_increase() noexcept
{
    (*this)._mem._size++;
}
inline double& Vector::set_front() {
    if (is_empty()) {
        throw std::out_of_range("Vector::front() called on empty vector");
    }
    return _mem._data[_front];
}

inline double& Vector::set_back() {
    if (is_empty()) {
        throw std::out_of_range("Vector::back() called on empty vector");
    }
    //size_t last_index = (_back - 1 + _mem.capacity()) % _mem.capacity();
    return _mem._data[_back];
}