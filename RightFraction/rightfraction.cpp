#include "rightfraction.h"
#include <iomanip>
BaseFraction RightFraction::to_base_fraction() const noexcept
{
    BaseFraction obj(_num + (_integer * _denom), _denom);
    return obj;
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
    size_t whitespace = input_str.find(' ');
    size_t del_op = input_str.find('/');
    if (del_op != std::string::npos) {
        if (whitespace != std::string::npos && whitespace < del_op) {
            _integer = std::stoi(input_str.substr(0, whitespace));
            _num = std::stoi(input_str.substr(whitespace+1, del_op- whitespace - 1));
            _denom = std::stoi(input_str.substr(del_op+1)); 
        }
        else {
            _num = std::stoi(input_str.substr(0, del_op));
            _denom = std::stoi(input_str.substr(del_op + 1));
        }
       
    }
    else {
        _integer = std::stoi(input_str);
    }
    if (_denom == 0) {
        throw std::domain_error("Denominator cannot be zero in fraction: " + input_str);
    }
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
    _integer = 0;
    _num = other.num();
    _denom = other.denom();
    simplify();
    return (*this);
}

RightFraction& RightFraction::operator=(const Fraction& other) noexcept
{
    _integer = 0;
    _num = other.num();
    _denom = other.denom();
    simplify();
    return (*this);
}

std::ostream& operator<<(std::ostream& out, const RightFraction& obj)
{
    out << obj._integer << ' ' << obj._num << "/" << obj._denom;
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