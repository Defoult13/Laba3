#include <characters/characters.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <iostream>

using namespace std;


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

Character::Character(const Character& character) {
	this->type = character.type;
	this->health = character.health;
	this->armor = character.armor;
	this->damage = character.damage;
	this->triple_hit_chance = character.triple_hit_chance;
	this->is_ability_used = character.is_ability_used;
}

CharacterList::CharacterList() {
	this->_size = 3;
	_character = new Character * [_size];
	for (int i = 0; i < _size; ++i) {
		_character[i] = new Character();
	}
}

CharacterList::CharacterList(ListPtr* characters, size_t _size) {
	this->_size = _size;
	_character = new Character * [_size];
	for (int i = 0; i < _size; ++i) {
		this->_character[i] = new Character();
		this->_character[i]->set_damage(characters[i]->get_damage());
		this->_character[i]->set_armor(characters[i]->get_armor());
		this->_character[i]->set_hp(characters[i]->get_hp());
		this->_character[i]->set_triple_hit_chance(characters[i]->get_triple_hit_chance());
		this->_character[i]->set_is_ability_used(characters[i]->get_is_ability_used());
	}
}

int Character::get_type() const {
	return type;
}

float Character::get_damage() const {
	return damage;
}

float Character::get_hp() const {
	return health;
}

float Character::get_armor() const {
	return armor;
}

float Character::get_triple_hit_chance() const {
	return triple_hit_chance;
}

bool Character::get_is_ability_used() const {
	return is_ability_used;
}

int CharacterList::get_size() {
	return _size;
}

ListPtr CharacterList::get_character_by_index(int index) {
	return _character[index];
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

void CharacterList::set_size(size_t size) {
	_size = size;
}

ListPtr CharacterList::operator[](int index) const {
	if (index < 0 || _size <= index) {
		throw out_of_range("[CharacterList::operator[]] Index is out of range.");
	}
	return _character[index];
}

ListPtr& CharacterList::operator[](int index) {
	if (index < 0 || _size <= index) {
		throw out_of_range("[CharacterList::operator[]] Index is out of range.");
	}
	return _character[index];
}

istream& operator>>(std::istream& in, CharacterType& item_type) {
	int type;
	in >> type;
	switch (type) {
	case 0:
		item_type = KNIGHT;
		break;
	case 1:
		item_type = ASSASSIN;
		break;
	case 2:
		item_type = BERSERK;
		break;
	default:
		throw std::runtime_error("Wrong type exception");
	}
	return in;
}

istream& operator>>(istream& in, Character& item) {
	cout << "Pick character:\n 0 - KNIGHT\n 1 - ASSASSIN\n 2 - BERSERK\n";
	in >> item.type;
	cout << "Enter health:\n";
	in >> item.health;
	cout << "Enter armor:\n";
	in >> item.armor;
	cout << "Enter damage:\n";
	in >> item.damage;
	return in;
}

ostream& operator<<(ostream& out, const Character& item) {
	return out << "Player(" << "Health: " << item.health << "," << "Armor: " << item.armor << "," << "Damage: " << item.damage << ")";
}
bool operator==(const Character& item, const Character& other) {
	return (item.get_type() == other.get_type() && item.get_hp() == other.get_hp() && item.get_armor() == other.get_armor() && item.get_damage() == other.get_damage());
}
bool operator!=(const Character& item, const Character& other) {
	return !(item == other);
}
Character& Character::operator=(Character other) {
	Swap(other);
	return *this;
}
CharacterList& CharacterList::operator=(CharacterList other) {
	Swap(other);
	return *this;
}
bool operator==(const CharacterList& tab, const CharacterList& other) {
	return (tab._size == other._size && **(tab._character) == **(other._character));
}
bool operator!=(const CharacterList& tab, const CharacterList& other) {
	return !(tab == other);
}

CharacterList::~CharacterList() {
	for (int i = 0; i < _size; ++i) {
		delete _character[i];
	}
	delete[] _character;
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
	case KNIGHT:
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
	case ASSASSIN:
		if (is_ability_used == true) {
			is_ability_used = false;
			break;
		}
		else {
			taking_damage -= (taking_damage * (armor / 100));
			health -= taking_damage;
			break;
		}
	case BERSERK:
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
	case KNIGHT:
		set_armor(armor + 1);
		set_damage(damage - 1);
		break;
	case ASSASSIN:
		set_is_ability_used(true);
		break;
	case BERSERK:
		set_damage(damage + 2);
		set_triple_hit_chance(triple_hit_chance + 2);
		set_armor(armor - 1);
		break;
	default:
		break;
	}
}
void Character::Swap(Character& other) noexcept {
	swap(type, other.type);
	swap(health, other.health);
	swap(armor, other.armor);
	swap(damage, other.damage);
	swap(triple_hit_chance, other.triple_hit_chance);
	swap(is_ability_used, other.is_ability_used);
}

int CharacterList::index_of_maxdam()
{
	int max_index = -1;
	float max_damage = 0;

	for (int i = 0; i < _size; ++i)
	{
		float value = _character[i]->get_damage();
		if (max_index == -1 || max_damage < value)
		{
			max_index = i;
			max_damage = value;
		}
	}

	return max_index;
}

void CharacterList::add_character(int index, Character character)
{
	if (index < 0 || index >= _size)
	{
		throw runtime_error("Index out of range.");
	}

	++_size;
	ListPtr* characters = new Character * [_size];
	for (int i = 0; i < index; ++i) {
		characters[i] = new Character(*this->_character[i]);
	}
	characters[index] = new Character(character);
	for (int i = _size - 1; i > index; --i) {
		characters[i] = new Character(*this->_character[i - 1]);
	}

	swap(this->_character, characters);

}

void CharacterList::delete_character(int index)
{
	if (_size <= 0)
	{
		throw runtime_error("List is empty.");
	}
	for (int i = index; i < _size - 1; ++i) {
		_character[i] = _character[i + 1];
	}
	--_size;
}

void CharacterList::clear() {
	_character = nullptr;
	_size = 0;
}

void CharacterList::Swap(CharacterList& other) noexcept {
	swap(_character, other._character);
	swap(_size, other._size);
}
void CharacterList::print_current(int index) {
	cout << *_character[index];
}
void CharacterList::show_all() {
	for (int i = 0; i < _size; ++i) {
		cout << i << ":";
		print_current(i);
		cout << endl;
	}
}

void CharacterList::Fight(Character& attacker, Character& defender) {
	while (attacker.get_hp() > 0 && defender.get_hp() > 0){
		int action = rand() % 2;
		int turn = rand() % 2;
		if (turn == 0) {
			if (action == 0) {
				if (defender.get_is_ability_used()) {
					cout << "Персонаж 2 увернулся от атаки" << endl;
					system("pause");
				}
				defender.take_damage(attacker.deal_damage());
				cout << "Персонаж 2 получил урон!" << endl;
				cout << "Здоровье персонажа 2: " << defender.get_hp() << endl;
				system("pause");
			}
			else {

				attacker.use_ability();
				if (attacker.get_type() == KNIGHT) {
					cout << "Увеличена броня ценой урона" << endl;
					system("pause");
				}
				else if (attacker.get_type() == BERSERK) {
					cout << "Увеличен урон и шанс крита,ценой брони" << endl;
					system("pause");
				}
				else {
					cout << "Уворот от следующей атаки" << endl;
					system("pause");
				}
			}
		}
		else if (turn == 1) {
			 
			if (action == 0) {
				if (attacker.get_is_ability_used()) {
					cout << "Персонаж 1 увернулся от атаки" << endl;
					system("pause");
				}
				attacker.take_damage(defender.deal_damage());
				cout << "Персонаж 1 получил урон!" << endl;
				cout << "Здоровье персонажа 1: " << attacker.get_hp() << endl;
				system("pause");
			}
			else {

				defender.use_ability();
				if (defender.get_type() == KNIGHT) {
					cout << "Увеличена броня ценой урона" << endl;
					system("pause");
				}
				else if (defender.get_type() == BERSERK) {
					cout << "Увеличен урон и шанс крита,ценой брони" << endl;
					system("pause");
				}
				else {
					cout << "Уворот от следующей атаки" << endl;
					system("pause");
				}
			}
		}
	}
	if (defender.get_hp() <= 0) cout << "Персонаж 1 победил" << endl;
	else if (attacker.get_hp() <= 0) cout << "Персонаж 2 победил" << endl;
	system("pause");
}