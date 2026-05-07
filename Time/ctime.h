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
	void check_object_domain(char hour = 0, char minutes = 0, char seconds = 0) const;
};
