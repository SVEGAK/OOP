#pragma once
#include <stdexcept>
class CTime {
	char _hour;
	char _minute;
	char _seconds;
public:
	CTime(); // Конструктор по умолчанию
	//Конструкторы копирования
	CTime(const CTime&); // должны передать именно оригинал, чтобы не плодить копии. const чтобы не сломать оригинал
	//конструктор инициализации
	CTime(char, char, char);
	//дополнительные контрукторы
	CTime(char, char);
	//геттеры
	char hour() const noexcept;// const noexcept - запрет на изменение объекта + игнор исключений
	char minute() const noexcept;
	char seconds() const noexcept;
	//сеттеры (должны кидать исключения и менять объект поэтому не константные)
	void hour(char);
	void minute(char);
	void seconds(char);
	CTime add_minutes(char);
	CTime add_hours(char);
	CTime add_seconds(char);
private:
	CTime check_object_domain() const;
};
CTime::CTime() { // Реализация конструктора по умолчанию
	_hour = 0;
	_minute = 0;
	_seconds = 0;
};
CTime::CTime(char hour, char minute) { // Доп конструктор - частичная инициализация
	_hour = hour;
	_minute = minute;
	_seconds = 0;
}
CTime::CTime(char hour, char minute, char seconds) { //реализация конструктора инициализации
	_seconds = seconds;
	_minute = minute;
	_hour = hour;

}
CTime CTime::check_object_domain() const{
	CTime res(*this);
	if (res._hour < 0) {
		throw std::domain_error("Hours must be from 0 to 24!");
	}
	if (res._minute < 0 || res._minute > 60) {
		throw std::domain_error("Minutes count must be from 0 to 60!");
	}
	if (res._seconds < 0 || res._seconds > 60) {
		throw std::domain_error("Seconds count must be from 0 to 60!");
	}
}
char CTime::hour() const noexcept{ // реализация геттеров
	return _hour;
};
char CTime::minute() const noexcept{
	return _minute;
};
char CTime::seconds() const noexcept{
	return _seconds;
};
void CTime::hour(char hour) {// реализация сеттеров
	_hour = hour;
};
void CTime::minute(char minute) {
	_minute = minute;
};
void CTime::seconds(char seconds) {
	_seconds = seconds;
};
	

CTime::CTime(const CTime& other) { //реализация конструктора копирования
	this->_hour = other._hour;
	this->_minute = other._minute;
	this->_seconds = other._seconds;
}
CTime CTime::add_seconds(char seconds) { //добавление секунд
	CTime res(*this);
	check_object_domain();
	if (res._seconds + seconds >= 60) {
		res._seconds = res._seconds + seconds - 60;
		res = res.add_minutes(1);
		return res;
	}
	else {
		res._seconds += seconds;
		return res;
	}
	res._seconds += seconds;
	return res;
}
CTime CTime::add_minutes(char minutes) { //добавление минуты
	CTime res(*this);
	check_object_domain();
	if (res._minute + minutes >= 60){
		res._minute = res._minute + minutes - 60;
		res = res.add_hours(1);
		return res;
	}else{
		res._minute += minutes;
		return res;
	}
	
}
CTime CTime::add_hours(char hours) { //добавление часов
	CTime res(*this);
	check_object_domain();
	if (res._hour + hours > 24) {
		res._hour = res._hour + hours - 24;
		return res;
	}
	else {
		res._hour += hours;
		return res;
	}
	
}
