#include "rightfraction.h"

void RightFraction::to_base_fraction() noexcept
{
    _num = _num + (_integer * _denom);
    _integer = 0;
}

void RightFraction::simplify() noexcept
{
    _num = _num + _integer * _denom;
    int md = max_delt(_num, _denom);
    if (md > 0) {
        _num /= md;
        _denom /= md;
    }
    if (_denom < 0) {
        _num *= -1;
        _denom *= -1;
    }
    while (_num > _denom) {
        _num -= _denom;
        _integer++;
    }
}

RightFraction::RightFraction(): Fraction(), _integer(0)
{
}

RightFraction::RightFraction(int integer, int num, int denom): Fraction(num, denom), _integer(0)
{
    if (denom == 0) {
        throw std::invalid_argument("Denominator cannot be zero");
    }

    if (_denom < 0) {
        _num = -_num;
        _denom = -_denom;
    }

    if (abs(_num) >= _denom) {
        int whole = abs(_num) / _denom;
        _integer = integer + whole;
        _num = (_num < 0) ? -(abs(_num) % _denom) : (abs(_num) % _denom);
    }
    else {
        _integer = integer;
    }

    simplify();
}

RightFraction::RightFraction(int integer, int num): RightFraction(integer, num, 1){}

RightFraction::RightFraction(int integer): RightFraction(integer, 0, 1){}

RightFraction::RightFraction(const RightFraction& other): Fraction(other), _integer(other._integer){}

RightFraction::RightFraction(const std::string& str): Fraction(), _integer(0)
{
    size_t pos = str.find(' ');
    if (pos != std::string::npos) {
        _integer = std::stoi(str.substr(0, pos));
        std::string fracPart = str.substr(pos + 1);
        size_t slashPos = fracPart.find('/');
        if (slashPos != std::string::npos) {
            int num = std::stoi(fracPart.substr(0, slashPos));
            int denom = std::stoi(fracPart.substr(slashPos + 1));
            if (denom == 0) {
                throw std::invalid_argument("Denominator cannot be zero");
            }
            _num = num;
            _denom = denom;
        }
        else {
            _num = std::stoi(fracPart);
            _denom = 1;
        }
    }
    else {
        size_t slashPos = str.find('/');
        if (slashPos != std::string::npos) {
            _num = std::stoi(str.substr(0, slashPos));
            _denom = std::stoi(str.substr(slashPos + 1));
            if (_denom == 0) {
                throw std::invalid_argument("Denominator cannot be zero");
            }
        }
        else {
            _integer = std::stoi(str);
            _num = 0;
            _denom = 1;
        }
    }

    if (_denom < 0) {
        _num = -_num;
        _denom = -_denom;
    }

    if (abs(_num) >= _denom) {
        int whole = abs(_num) / _denom;
        _integer += (_num < 0) ? -whole : whole;
        _num = (_num < 0) ? -(abs(_num) % _denom) : (abs(_num) % _denom);
    }

    simplify();
}

RightFraction::RightFraction(const Fraction& other): Fraction(other), _integer(0)
{
    if (abs(_num) >= _denom) {
        _integer = abs(_num) / _denom;
        _num = (_num < 0) ? -(abs(_num) % _denom) : (abs(_num) % _denom);
    }
}

RightFraction::RightFraction(const BaseFraction& other): Fraction(other), _integer(0)
{
    if (abs(_num) >= _denom) {
        _integer = abs(_num) / _denom;
        _num = (_num < 0) ? -(abs(_num) % _denom) : (abs(_num) % _denom);
    }
}