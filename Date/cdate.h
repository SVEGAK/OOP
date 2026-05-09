#pragma once
#include <iostream>
#include <stdexcept>
class CDate {
    unsigned int _year;
    char _month;  
    char _day;
public:
    // Конструктор по умолчанию
    CDate();

    // Конструктор копирования
    CDate(const CDate&);

    // Конструктор инициализации
    CDate(int year, int month, int day);
    //Дополнительные конструкторы
    CDate(int year, char month);
    // Геттеры
    int year() const noexcept;
    char month() const noexcept;
    char day() const noexcept;

    // Сеттеры
    void year(int newYear);
    void month(int newMonth);
    void day(int newDay);

    
    CDate& add_day(int days);
    CDate& add_month(int _month);
    CDate& add_year(int year);

    
};


