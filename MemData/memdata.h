#pragma once
#include <initializer_list>

#define MEM_STEP 15

inline int calculate_capacity(size_t size);

class Vector;

class MemData {
    double* _data;             // хранилище данных
    size_t _size;              // размер заполненной части хранилища
    size_t _capacity;          // вместимость хранилища
public:
    MemData(size_t size = 0);                     // конструктор по размеру + по умолчанию
    MemData(std::initializer_list<double> list);  // конструктор по списку инициализации
    MemData(double* data, size_t size);           // конструктор инициализации
    MemData(const MemData& memdata);              // конструктор копирования
    MemData(MemData&& memdata) noexcept;          // конструктор с move-семантикой
    ~MemData();                              // деструктор

    inline bool is_empty() const noexcept;   // проверка на пустоту
    inline bool is_full() const noexcept;    // проверка на переполнение

    inline size_t size() const noexcept;                 // геттер размера
    inline size_t capacity() const noexcept;             // геттер вместимости
    inline const double* const data() const noexcept;    // геттер хранилища

    void set_memory(size_t size) noexcept;                                         // установка памяти без сохранения данных
    void reset_memory(size_t size, size_t start_index = 0) noexcept;          // перевыделение памяти с сохранением данных
    inline void clear_memory() noexcept;                                             // очистка памяти

    MemData& operator=(const MemData& other) noexcept;         // оператор присваивания
    MemData& operator=(MemData&& other) noexcept;              // оператор присваивания с move-семантикой

    friend class Vector;
};
inline bool MemData::is_empty() const noexcept
{
    if ((_size > 0)&&(_data != nullptr)) {
        return false;
    }
    else if ((_size == 0) || (_data == nullptr)) {
        return true;
    }
}
inline bool MemData::is_full() const noexcept
{
    if ((_size == _capacity)&&(_size > 0)) {
        return true;
    }
    return false;
}
inline size_t MemData::size() const noexcept
{
    return _size;
};
inline size_t MemData::capacity() const noexcept
{
    return _capacity;
}
inline const double* const MemData::data() const noexcept
{
    return _data;
}
inline void MemData::clear_memory() noexcept // решил сделать inline, тк функция достаточно маленькая
{
    delete[] _data;
    _data = nullptr;
}
inline int calculate_capacity(size_t size)
{
    if (size == 0) {
        return 0;
    }
    return (size + MEM_STEP);
}
