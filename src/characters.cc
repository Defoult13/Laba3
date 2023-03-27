#include <characters/characters.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <stdexcept>

using namespace std;
using namespace warriors;

const float double_hit_chance = 50;
const float reduce_damage_chance = 40;

Character::Character(CharacterType type, float health, float armor, float damage)
{
	this->type = type;
	this->health = health;
	this->armor = armor;
	this->damage = damage;
}

Character::Character() {
	type = CharacterType::KNIGHT;
	health = 100;
	armor = 30;
	damage = 50;
}

float Character::deal_damage()
{
	srand(time(0));

	switch (type)
	{
	case KNIGHT:
		return damage;
	case ASSASSIN:
		if ((rand() % 100 + 1) <= double_hit_chance)
		{
			return damage * 2;
		}
		else
		{
			return damage;
		}
	case BERSERK:
		if ((rand() % 100 + 1) <= triple_hit_chance)
		{
			return damage * 3;
		}
		else
		{
			return damage;
		}
	default:
		break;
	}
}

void Character::take_damage(float taking_damage)
{
	srand(time(0));

	switch (type)
	{
	case CharacterType::KNIGHT:
		if ((rand() % 100 + 1) <= reduce_damage_chance)
		{
			taking_damage -= (taking_damage * (armor / 100));
			health -= (taking_damage / 2);
			break;
		}
		else
		{
			taking_damage -= (taking_damage * (armor / 100));
			health -= taking_damage;
			break;
		}
	case CharacterType::ASSASSIN:
		if (is_ability_used == true) {
			is_ability_used = false;
			break;
		}
		else {
			taking_damage -= (taking_damage * (armor / 100));
			health -= taking_damage;
			break;
		}
	case CharacterType::BERSERK:
		taking_damage -= (taking_damage * (armor / 100));
		health -= taking_damage;
		break;
	default:
		break;
	}
}

void Character::use_ability()
{
	switch (type)
	{
	case CharacterType::KNIGHT:
		set_armor(armor * 2);
		set_damage(damage / 2);
		break;
	case CharacterType::ASSASSIN:
		set_is_ability_used(true);
		break;
	case CharacterType::BERSERK:
		set_damage(damage * 2);
		set_triple_hit_chance(triple_hit_chance * 2);
		set_armor(armor / 2);
		break;
	default:
		break;
	}
}

int Character::get_type() {
	return type;
}

float Character::get_damage() {
	return damage;
}

float Character::get_hp() {
	return health;
}

float Character::get_armor() {
	return armor;
}

float Character::get_triple_hit_chance() {
	return triple_hit_chance;
}

bool Character::get_is_ability_used() {
	return is_ability_used;
}

void Character::set_type(CharacterType type) {
	this->type = type;
}

void Character::set_damage(float damage) {
	this->damage = damage;
}

void Character::set_hp(float hp) {
	this->health = hp;
}

void Character::set_armor(float armor) {
	this->armor = armor;
}

void Character::set_triple_hit_chance(float triple_hit_chance) {
	this->triple_hit_chance = triple_hit_chance;
}

void Character::set_is_ability_used(bool is_ability_used) {
	this->is_ability_used = is_ability_used;
}

CharacterList::CharacterList() {
	this->_size = 3;
	for (int i = 0; i < _size; ++i) {
		_characters[i] = Character();
	}
}

CharacterList::CharacterList(Character characters[], int _size) {
	this->_size = _size;
	for (int i = 0; i < _size; ++i) {
		this->_characters[i].set_damage(characters[i].get_damage());
		this->_characters[i].set_armor(characters[i].get_armor());
		this->_characters[i].set_hp(characters[i].get_hp());
		this->_characters[i].set_triple_hit_chance(characters[i].get_triple_hit_chance());
		this->_characters[i].set_is_ability_used(characters[i].get_is_ability_used());
	}
}

Character CharacterList::operator[](const int index) const {
	if (index < 0 || _size <= index) {
		throw out_of_range("[CharacterList::operator[]] Index is out of range.");
	}
	return _characters[index];
}

int CharacterList::get_size() {
	return _size;
}
void CharacterList::set_size(int size) {
	this->_size = size;
}

int CharacterList::index_of_maxdam()
{
	int max_index = -1;
	float max_damage = 0;

	for (int i = 0; i < _size; ++i)
	{
		float value = _characters[i].get_damage();
		if (max_index == -1 ||
			max_damage < value)
		{
			max_index = i;
			max_damage = value;
		}
	}

	return max_index;
}

void CharacterList::add_character(int index, Character character)
{
	if (_size == CAP)
	{
		throw runtime_error("Full capacity reached.");
	}

	if (index < 0 || index >= _size)
	{
		throw runtime_error("Index out of range.");
	}

	for (int i = _size - 1; i >= index; --i) { _characters[i] = _characters[i - 1]; }
	_characters[index] = character;
	++_size;
}

void CharacterList::delete_character(int index)
{
	if (_size == 0)
	{
		throw runtime_error("List is empty.");
	}
	for (int i = index; i < _size - 1; ++i) { _characters[i] = _characters[i + 1]; }
	--_size;
}

void CharacterList::clear() { _size = 0; }