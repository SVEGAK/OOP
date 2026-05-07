#include "cdate.h"
// Реализация конструктора по умолчанию
CDate::CDate() {
    _year = 0;
    _month = 1;
    _day = 1;
}

// Реализация конструктора инициализации
CDate::CDate(int year, int month, int day): _year(0), _month(0), _day(0) {
    add_year(year);
    add_month(month);
    add_day(day);
}

// Реализация конструктора копирования
CDate::CDate(const CDate& other) {
    _year = other._year;
    _month = other._month;
    _day = other._day;
}
//Реализация дополнительного конструктора инициализации
CDate::CDate(int year, char month) : _year(0), _month(0), _day(0) {
    add_year(year);
    add_month(month);
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
    if (newYear < 0) { throw std::invalid_argument(""); }
    _year = 0;
    add_year(newYear);
}

void CDate::month(int newMonth) {
    if ((newMonth <= 0) || newMonth > 12) { throw std::invalid_argument(""); }
    _month = 0;
    add_month(newMonth);
}

void CDate::day(int newDay) {
    if ((newDay <= 0) || (newDay > 31)) { throw std::invalid_argument(""); }
    _day = 0;
    add_day(newDay);
}

CDate& CDate::add_day(int days) {
    while (days > 0) {
        // Определяем количество дней в текущем месяце
        int daysInMonth;
        if (_month == 2) {
            // Проверка високосности
            bool leap = (_year % 4 == 0 && _year % 100 != 0) || (_year % 400 == 0);
            if (daysInMonth = leap) { daysInMonth = 29; }else { daysInMonth = 28; }
        }
        else if (_month == 4 || _month == 6 || _month == 9 || _month == 11) {
            daysInMonth = 30;
        }
        else {
            daysInMonth = 31;
        }

        // Сколько дней осталось до конца месяца (начиная с завтрашнего дня)
        int daysLeft = daysInMonth - _day;

        if (days <= daysLeft) {
            // Добавляем дни, оставаясь в текущем месяце
            _day += days;
            days = 0;
        }
        else {
            // Переходим на следующий месяц
            days -= (daysLeft + 1);
            _day = 1;                     // первое число следующего месяца
            if (_month == 12) {
                _month = 1;
                _year += 1;                // новый год
            }
            else {
                _month += 1;
            }
        }
    }
    return *this;
}

CDate& CDate::add_month(int month) {
    int interim_res = _month + month - 1;
    _month = (interim_res % 12) + 1;
    if (_month <= 0) _month += 12;
    add_year(interim_res / 12);
    return *this;
}

CDate& CDate::add_year(int year) {
    _year += year;
    return *this;
}
