#include "rightfraction.h"
#include <iomanip>
size_t RightFraction::find_Integer_pos(const std::string& input_str) {//позиция первого пробела после целой части
    size_t pos_f = input_str.find('/');
    if (pos_f == std::string::npos) { // если не нашлось, то это скорее всего просто число
        return (input_str.length());

    }
    if (pos_f != std::string::npos) {
        if ((input_str[pos_f - 1] != ' ') && (input_str[pos_f + 1] != ' ')) {
            throw std::invalid_argument("Invalid format: expected 'Integer num/denom'");
        }
        for (size_t i = pos_f - 1; i > 0; i--) {
            if (input_str[i] == ' ') {
                return i;
            }
        }
    }
    return 0; //если такого пробела нет, то нет и целой части
}
int RightFraction::parseInteger(const std::string& input_str, size_t pos) {//pos - первый справа пробел от Integer
    if (pos == 0) {
        return 0;
    }
    return std::stoi(input_str.substr(0, pos));   
}

void RightFraction::to_base_fraction() noexcept
{
    _num = _num + (_integer * _denom);
    _integer = 0;
}

void RightFraction::simplify() noexcept

{
    int sign = 1;
    if (_num < 0) sign *= -1;//определяем конечный знак числа
    if (_denom < 0) sign *= -1;
    if (_integer < 0) sign *= -1;
    
    _num = abs(_num); _denom = abs(_denom); _integer = abs(_integer);//убираем знаки от чисел
    
    _num = _num + _integer * _denom;
    _integer = 0;
    int md = max_delt(_num, _denom);
    if (md > 0) {
        _num /= md;
        _denom /= md;
    }
    while (_num >= _denom) {
        _num -= _denom;       
        _integer++;
    }
    _num *= sign; //возвращаем знак числу
}

RightFraction::RightFraction(): Fraction(), _integer(0){}

RightFraction::RightFraction(int integer, int num, int denom): Fraction(num, denom), _integer(integer)
{
    if (_integer < 0) {
        _integer *= -1;
        _num *= -1;
    }
    simplify();
}

RightFraction::RightFraction(int integer, int num): RightFraction(integer, num, 1){}

RightFraction::RightFraction(int integer): RightFraction(integer, 0, 1){}

RightFraction::RightFraction(const RightFraction& other): Fraction(other._num,other._denom), _integer(other._integer){}

RightFraction::RightFraction(const std::string& input_str): Fraction(), _integer(0)
{
    size_t Integer_pos = find_Integer_pos(input_str);
    if (Integer_pos == 0) { //число без целой части
        _num = parseNum(input_str);
        _denom = parseDenom(input_str);
        simplify();
        return;
    }
    else if (Integer_pos == input_str.length()) {
        _integer = parseInteger(input_str, Integer_pos);
        _num = 0;
        _denom = 1;
        return;
    }
    _integer = parseInteger(input_str, Integer_pos);
    std::string fraction_str = input_str.substr(Integer_pos);//если целая часть забирает часть строки, выделяем дробь
    _num = parseNum(fraction_str);
    _denom = parseDenom(fraction_str);
    simplify();
}

RightFraction::RightFraction(const Fraction& other): Fraction(other), _integer(0)
{
    simplify();
}
RightFraction::RightFraction(const BaseFraction& other): Fraction(other), _integer(0)
{
    simplify();
}
RightFraction& RightFraction::operator=(const BaseFraction& other) noexcept
{
    (*this)._num = other.num();
    (*this)._denom = other.denom();
    (*this).simplify();
    return (*this);
}

RightFraction& RightFraction::operator=(const Fraction& other) noexcept
{
    (*this)._num = other.num();
    (*this)._denom = other.denom();
    (*this).simplify();
    return (*this);
}

std::ostream& operator<<(std::ostream& out, const RightFraction& obj)
{
    out << obj._integer << ' ' << obj._num << ' / ' << obj._denom;
    return out;
}

std::istream& operator>>(std::istream& in, RightFraction& frac)
{
    std::string input_str;
    std::getline(in >> std::ws, input_str);
    RightFraction obj(input_str);
    frac = std::move(obj);
    return in;
}
//Операторы
// Присваивание с арифметикой
RightFraction& RightFraction::operator+=(const RightFraction& other) {
    to_base_fraction();
    BaseFraction otherCopy = other;
    BaseFraction& thisBase = *this;
    thisBase += otherCopy;
    simplify();
    return *this;
}

RightFraction& RightFraction::operator+=(const Fraction& other) {
    to_base_fraction();
    BaseFraction& thisBase = *this;
    thisBase += other;
    simplify();
    return *this;
}

RightFraction& RightFraction::operator+=(int num) {
    to_base_fraction();
    BaseFraction& thisBase = *this;
    thisBase += num;
    simplify();
    return *this;
}

RightFraction& RightFraction::operator-=(const RightFraction& other) {
    to_base_fraction();
    BaseFraction otherCopy = other;
    BaseFraction& thisBase = *this;
    thisBase -= otherCopy;
    simplify();
    return *this;
}

RightFraction& RightFraction::operator-=(const Fraction& other) {
    to_base_fraction();
    BaseFraction& thisBase = *this;
    thisBase -= other;
    simplify();
    return *this;
}

RightFraction& RightFraction::operator-=(int num) {
    to_base_fraction();
    BaseFraction& thisBase = *this;
    thisBase -= num;
    simplify();
    return *this;
}

RightFraction& RightFraction::operator*=(const RightFraction& other) {
    to_base_fraction();
    BaseFraction otherCopy = other;
    BaseFraction& thisBase = *this;
    thisBase *= otherCopy;
    simplify();
    return *this;
}

RightFraction& RightFraction::operator*=(const Fraction& other) {
    to_base_fraction();
    BaseFraction& thisBase = *this;
    thisBase *= other;
    simplify();
    return *this;
}

RightFraction& RightFraction::operator*=(int num) {
    to_base_fraction();
    BaseFraction& thisBase = *this;
    thisBase *= num;
    simplify();
    return *this;
}

RightFraction& RightFraction::operator/=(const RightFraction& other) {
    to_base_fraction();
    BaseFraction otherCopy = other;
    BaseFraction& thisBase = *this;
    thisBase /= otherCopy;
    simplify();
    return *this;
}

RightFraction& RightFraction::operator/=(const Fraction& other) {
    to_base_fraction();
    BaseFraction& thisBase = *this;
    thisBase /= other;
    simplify();
    return *this;
}

RightFraction& RightFraction::operator/=(int num) {
    to_base_fraction();
    BaseFraction& thisBase = *this;
    thisBase /= num;
    simplify();
    return *this;
}

// Арифметические операторы
RightFraction RightFraction::operator+(const RightFraction& other) const {
    RightFraction res(*this);
    res += other;
    return res;
}

RightFraction RightFraction::operator+(const Fraction& other) const {
    RightFraction res(*this);
    res += other;
    return res;
}

RightFraction RightFraction::operator+(int num) const {
    RightFraction res(*this);
    res += num;
    return res;
}

RightFraction RightFraction::operator-(const RightFraction& other) const {
    RightFraction res(*this);
    res -= other;
    return res;
}

RightFraction RightFraction::operator-(const Fraction& other) const {
    RightFraction res(*this);
    res -= other;
    return res;
}

RightFraction RightFraction::operator-(int num) const {
    RightFraction res(*this);
    res -= num;
    return res;
}

RightFraction RightFraction::operator*(const RightFraction& other) const {
    RightFraction res(*this);
    res *= other;
    return res;
}

RightFraction RightFraction::operator*(const Fraction& other) const {
    RightFraction res(*this);
    res *= other;
    return res;
}

RightFraction RightFraction::operator*(int num) const {
    RightFraction res(*this);
    res *= num;
    return res;
}

RightFraction RightFraction::operator/(const RightFraction& other) const {
    RightFraction res(*this);
    res /= other;
    return res;
}

RightFraction RightFraction::operator/(const Fraction& other) const {
    RightFraction res(*this);
    res /= other;
    return res;
}

RightFraction RightFraction::operator/(int num) const {
    RightFraction res(*this);
    res /= num;
    return res;
}
// Операторы сравнения

bool RightFraction::operator==(const RightFraction& other) const {
    BaseFraction thisBase(_num + _integer * _denom, _denom);
    BaseFraction otherBase(other._num + other._integer * other._denom, other._denom);
    return thisBase == otherBase;
}

bool RightFraction::operator!=(const RightFraction& other) const {
    return !(*this == other);
}

bool RightFraction::operator>(const RightFraction& other) const {
    BaseFraction thisBase(_num + _integer * _denom, _denom);
    BaseFraction otherBase(other._num + other._integer * other._denom, other._denom);
    return thisBase > otherBase;
}

bool RightFraction::operator<(const RightFraction& other) const {
    return other > *this;
}

bool RightFraction::operator>=(const RightFraction& other) const {
    return (*this > other) || (*this == other);
}

bool RightFraction::operator<=(const RightFraction& other) const {
    return (*this < other) || (*this == other);
}

bool RightFraction::operator==(const Fraction& other) const {
    BaseFraction thisBase(_num + _integer * _denom, _denom);
    BaseFraction otherBase(other.num(), other.denom());
    return thisBase == otherBase;
}

bool RightFraction::operator!=(const Fraction& other) const {
    return !(*this == other);
}

bool RightFraction::operator>(const Fraction& other) const {
    BaseFraction thisBase(_num + _integer * _denom, _denom);
    BaseFraction otherBase(other.num(), other.denom());
    return thisBase > otherBase;
}

bool RightFraction::operator<(const Fraction& other) const {
    BaseFraction thisBase(_num + _integer * _denom, _denom);
    BaseFraction otherBase(other.num(), other.denom());
    return thisBase < otherBase;
}

bool RightFraction::operator>=(const Fraction& other) const {
    return (*this > other) || (*this == other);
}

bool RightFraction::operator<=(const Fraction& other) const {
    return (*this < other) || (*this == other);
}

bool RightFraction::operator==(int num) const {
    BaseFraction thisBase(_num + _integer * _denom, _denom);
    return thisBase == num;
}

bool RightFraction::operator!=(int num) const {
    return !(*this == num);
}

bool RightFraction::operator>(int num) const {
    BaseFraction thisBase(_num + _integer * _denom, _denom);
    return thisBase > num;
}

bool RightFraction::operator<(int num) const {
    BaseFraction thisBase(_num + _integer * _denom, _denom);
    return thisBase < num;
}

bool RightFraction::operator>=(int num) const {
    return (*this > num) || (*this == num);
}

bool RightFraction::operator<=(int num) const {
    return (*this < num) || (*this == num);
}