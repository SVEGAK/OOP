#include "arena.h"

Character::Character() : _health(0), _power(1) {}

Character::Character(const Character& other)
	: _health(other._health), _power(other._power) {
}
Character::Character(int health, int power) : _health(health), _power(power) {}