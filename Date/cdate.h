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
    CDate(int year, char month, char day);
    //Дополнительные конструкторы
    CDate(int year, char month);
    // Геттеры
    int year() const noexcept;
    char month() const noexcept;
    char day() const noexcept;

    // Сеттеры
    void year(int newYear);
    void month(char newMonth);
    void day(char newDay);

    
    CDate add_day(int days);
    CDate add_month(char _month);
    CDate add_year(int year);

    
};

// Реализация конструктора по умолчанию
CDate::CDate() {
    _year = 1;
    _month = 1;
    _day = 1;
}

// Реализация конструктора инициализации
CDate::CDate(int year, char month, char day) {
    _year = year;
    _month = month;
    _day = day;
}

// Реализация конструктора копирования
CDate::CDate(const CDate& other) {
    _year = other._year;
    _month = other._month;
    _day = other._day;
}
//Реализация дополнительного конструктора инициализации
CDate::CDate(int year, char month) {
    _year = year;
    _month = month;
    _day = 1;
}
int CDate::year() const noexcept {//Реализация геттеров
    return _year;
}

char CDate::month() const noexcept {
    return _month;
}

char CDate::day() const noexcept {
    return _day;
}

void CDate::year(int newYear) {//Реализация сеттеров
    _year = newYear;
}

void CDate::month(char newMounth) {
    // TODO: добавить проверку для месяца
    _month = newMounth;
}

void CDate::day(char newDay) {
    // TODO: добавить проверку для дня
    _day = newDay;
}

CDate CDate::add_day(int days) {
    CDate res(*this);
    while (days > 0) {
        // Определяем количество дней в текущем месяце res
        int daysInMonth;
        if (res._month == 2) {
            // Проверка високосности
            bool leap = (res._year % 4 == 0 && res._year % 100 != 0) || (res._year % 400 == 0);
            daysInMonth = leap ? 29 : 28;
        }
        else if (res._month == 4 || res._month == 6 || res._month == 9 || res._month == 11) {
            daysInMonth = 30;
        }
        else {
            daysInMonth = 31;
        }

        // Сколько дней осталось до конца месяца (начиная с завтрашнего дня)
        int daysLeft = daysInMonth - res._day;

        if (days <= daysLeft) {
            // Добавляем дни, оставаясь в текущем месяце
            res._day += days;
            days = 0;
        }
        else {
            // Переходим на следующий месяц
            days -= daysLeft+1;
            res._day = 1;                     // первое число следующего месяца
            if (res._month == 12) {
                res._month = 1;
                res._year += 1;                // новый год
            }
            else {
                res._month += 1;
            }
        }
    }
    return res;
}
CDate CDate::add_month(char month){
    CDate res(*this);
    char interim_res = res._month + month;
    res._month = interim_res % 12;
    res = res.add_year((interim_res - res._month) / 12);
    return res;
    
    
}

CDate CDate::add_year(int year) {
    CDate res(*this);
    res._year+=year;
    return res;
};