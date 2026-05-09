#pragma once

class Character {
	int _health;
	int _power;
public:
	Character();
	Character(const Character& other);
	Character(int numerator, int denominator = 1);

	inline int health() const noexcept;
	inline int power() const noexcept;

	//virtual void attack(Character);
	//virtual void attaked(Character);
};

inline int Character::health() const noexcept {
	return _health;
}

inline int Character::power() const noexcept {
	return _power;

}

class Warrior : public Character {
	int _armor;
public:

	//void attack(Character);
};