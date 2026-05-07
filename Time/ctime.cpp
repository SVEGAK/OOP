#include "ctime.h"
CTime::CTime() : _hour(0), _minute(0), _seconds(0) {}// Реализация конструктора по умолчанию;

CTime::CTime(char hour, char minute):CTime() { // Доп конструктор - частичная инициализация
	check_object_domain(hour,minute);
	_hour = hour;
	_minute = minute;
	_seconds = 0;
}
CTime::CTime(char hour, char minute, char seconds) { //реализация конструктора инициализации
	check_object_domain(hour, minute,seconds);
	_seconds = seconds;
	_minute = minute;
	_hour = hour;
	
}
//Функция проверки корректности объекта
void CTime::check_object_domain(char hour,char minutes, char seconds) const {
	if ((hour < 0)||(hour > 24)) {
		throw std::domain_error("Hours must be from 0 to 24!");
	}
	if (minutes < 0 || minutes > 60) {
		throw std::domain_error("Minutes count must be from 0 to 60!");
	}
	if (seconds < 0 || seconds > 60) {
		throw std::domain_error("Seconds count must be from 0 to 60!");
	}
}

// реализация геттеров
char CTime::hour() const noexcept { 
	return _hour;
}
char CTime::minute() const noexcept {
	return _minute;
}
char CTime::seconds() const noexcept {
	return _seconds;
}
void CTime::hour(char hour) {// реализация сеттеров
	if ((hour < 0) || (hour > 24)) {
		throw std::invalid_argument("Incorrect hours count");
	}
	_hour = hour;
}
void CTime::minute(char minutes) {
	check_object_domain(0,minutes);
	_minute = minutes;
	
}
void CTime::seconds(char seconds) {
	check_object_domain(0,0,seconds);
	_seconds = seconds;
}


CTime::CTime(const CTime& other) { //реализация конструктора копирования
	_hour = other._hour;
	_minute = other._minute;
	_seconds = other._seconds;
}
CTime CTime::add_seconds(char seconds) { //добавление секунд
	CTime res(*this);
	if (seconds < 0) { throw std::domain_error("Seconds count can't be below zero"); }
	else if (seconds == 0) { return res; }
	if (res._seconds + seconds < 60) {
		res._seconds += seconds;
		return res;
	}
	res._seconds = res._seconds + seconds - 60;
	res = res.add_minutes(1);
	while (res._seconds >= 60) {
		res._seconds = res._seconds - 60;
		res = res.add_minutes(1);
	}
	return res;
}
CTime CTime::add_minutes(char minutes) { //добавление минуты
	CTime res(*this);
	if (minutes < 0) { throw std::domain_error("Minutes count can't be below zero"); }
	else if (minutes == 0) { return res; }

	if (res._minute + minutes < 60) {
		res._minute += minutes;
		return res;
	}
	res._minute = res._minute + minutes - 60;
	res = res.add_hours(1);
	while (res._minute >= 60) {
		res._minute = res._minute - 60;
		res = res.add_hours(1);
	}
	return res;

}
CTime CTime::add_hours(char hours) { //добавление часов
	CTime res(*this);
	if (hours < 0) { throw std::domain_error("Hours count can't be below zero"); }
	else if (hours == 0) { return res; }
	if (res._hour + hours >= 24) {
		res._hour = res._hour + hours - 24;
		return res;
	}
	else {
		res._hour += hours;
		return res;
	}

}
