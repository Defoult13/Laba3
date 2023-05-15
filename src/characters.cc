#pragma warning(disable:6386)
#include <characters/characters.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <iostream>
//
using namespace std;


Knight::Knight(float health, float armor, float damage)
{
	this->health = health;
	this->armor = armor;
	this->damage = damage;
}

Knight::Knight() {
	health = 100;
	armor = 40;
	damage = 30;
}

Assassin::Assassin(float health, float armor, float damage)
{
	this->health = health;
	this->armor = armor;
	this->damage = damage;
}

Assassin::Assassin() {
	health = 100;
	armor = 10;
	damage = 50;
}

Berserk::Berserk(float health, float armor, float damage)
{
	this->health = health;
	this->armor = armor;
	this->damage = damage;
}

Berserk::Berserk() {
	health = 100;
	armor = 20;
	damage = 60;
}

CharacterList::CharacterList() {
	for (int i = 0; i < 3; ++i) {
		_character.push_back(make_shared<Knight>());
	}
}

CharacterList::CharacterList(vector<ItemPtr> characters) {
	_character = vector<ItemPtr>(characters.size());
	for (int i = 0; i < _character.size(); ++i) {
		this->_character[i] = make_shared<Knight>();
	}
}

CharacterList::CharacterList(const CharacterList& other) {
	this->_character = other._character;
}

//GETTERS

float Character::get_damage() const {return damage;}

float Character::get_hp() const {return health;}

float Character::get_armor() const {return armor;}

bool Character::get_is_ability_used() const { return is_ability_used; }

float Berserk::get_triple_hit_chance() const {return triple_hit_chance;}




ItemPtr CharacterList::get_character_by_index(int index) {
	return _character[index];
}

int CharacterList::size() {
	return static_cast<int>(_character.size());
}

//SETTERS


void Character::set_damage(float damage) { this->damage = damage; }

void Character::set_hp(float hp) {this->health = hp;}

void Character::set_armor(float armor) {this->armor = armor;}

void Berserk::set_triple_hit_chance(float triple_hit_chance) {this->triple_hit_chance = triple_hit_chance;}

void Assassin::set_is_ability_used(bool is_ability_used) {this->is_ability_used = is_ability_used;}



//OPERATORS
void CharacterList::Swap(CharacterList& other) noexcept {
	swap(_character, other._character);
}

bool Knight::equals(shared_ptr<Character> other) const {
	const auto d_other = dynamic_pointer_cast<Knight>(other);
	if (d_other == nullptr) {
		return false;
	}
	return (health == d_other->health && armor == d_other->armor &&
		damage == d_other->damage && reduce_damage_chance == d_other->reduce_damage_chance);
}

bool Assassin::equals(shared_ptr<Character> other) const {
	const auto d_other = dynamic_pointer_cast<Assassin>(other);
	if (d_other == nullptr) {
		return false;
	}
	return (health == d_other->health && armor == d_other->armor &&
		damage == d_other->damage && double_hit_chance == d_other->double_hit_chance && is_ability_used == d_other->is_ability_used);
}

bool Berserk::equals(shared_ptr<Character> other) const {
	const auto d_other = dynamic_pointer_cast<Berserk>(other);
	if (d_other == nullptr) {
		return false;
	}
	return (health == d_other->health && armor == d_other->armor &&
		damage == d_other->damage && triple_hit_chance == d_other->triple_hit_chance);
}

ItemPtr CharacterList::operator[](int index) const {
	if (index < 0 || index >= _character.size()) {
		throw runtime_error("Index out of range.");
	}
	return _character[index];
}

ItemPtr& CharacterList::operator[](int index) {
	if (index < 0 || index >= _character.size()) {
		throw runtime_error("Index out of range");
	}
	return _character[index];
}

CharacterList& CharacterList::operator=(CharacterList other) {
	Swap(other);
	return *this;
}
bool operator==(const CharacterList& tab, const CharacterList& other) {
	return ((tab._character) == (other._character));
}
bool operator!=(const CharacterList& tab, const CharacterList& other) {
	return !(tab == other);
}


//METHODS

unique_ptr<Character> Knight::clone() const {
	return make_unique<Knight>(health, armor, damage);
}
unique_ptr<Character> Assassin::clone() const {
	return make_unique<Assassin>(health, armor, damage);
}
unique_ptr<Character> Berserk::clone() const {
	return make_unique<Berserk>(health, armor, damage);
}
void Knight::print(ostream& out) const {
	out << "Knight(" << health << ',' << armor << ',' << damage << ')';
}
void Assassin::print(ostream& out) const {
	out << "Assassin(" << health << ',' << armor << ',' << damage << ')';
}
void Berserk::print(ostream& out) const {
	out << "Berserk(" << health << ',' << armor << ',' << damage << ')';
}

float Knight::deal_damage() const {
	int dmg = get_damage();
	return dmg;
}

float Assassin::deal_damage() const {
	srand(time(0));
	if ((rand() % 100 + 1) <= double_hit_chance)
	{
		int dmg = get_damage() * 2;
		return dmg;
	}
	else
	{
		int dmg = get_damage();
		return dmg;
	}
}

float Berserk::deal_damage() const {
	srand(time(0));
	if ((rand() % 100 + 1) <= triple_hit_chance)
	{
		int dmg = get_damage() * 3;
		return dmg;
	}
	else
	{
		int dmg = get_damage();
		return dmg;
	}
}

void Knight::take_damage(float taking_damage) {
	srand(time(0));
	if ((rand() % 100 + 1) <= reduce_damage_chance)
	{
		taking_damage -= (taking_damage * (armor / 100));
		set_hp(get_hp() - taking_damage / 2);
	}
	else
	{
		taking_damage -= (taking_damage * (armor / 100));
		set_hp(get_hp() - taking_damage);
	}
}

void Assassin::take_damage(float taking_damage) {
	if (is_ability_used == true) {
		is_ability_used = false;
	}
	else {
		taking_damage -= (taking_damage * (armor / 100));
		set_hp(get_hp() - taking_damage);
	}
}

void Berserk::take_damage(float taking_damage) {
	taking_damage -= (taking_damage * (armor / 100));
	set_hp(get_hp() - taking_damage);
}

void Knight::use_ability() {
	set_armor(armor + 1);
	set_damage(damage - 1);
}

void Assassin::use_ability() {
	set_is_ability_used(true);
}

void Berserk::use_ability() {
	set_damage(damage + 2);
	set_triple_hit_chance(triple_hit_chance + 2);
	set_armor(armor - 1);
}

int CharacterList::index_of_maxdam()
{
	int index = 0;
	float max_dam = _character[0]->get_damage();
	for (int i = 0; i < _character.size(); ++i)
	{
		float value = _character[i]->get_damage();
		if (value > max_dam)
		{
			index = i;
			max_dam = value;
		}
	}

	return index;
}

void CharacterList::add_character(int index, ItemPtr character)
{
	if (index < 0 || index > _character.size())
	{
		throw runtime_error("Index out of range.");
	}
	_character.insert(_character.begin() + index, character);
}

void CharacterList::delete_character(int index)
{
	if (index < 0 || index > _character.size())
	{
		throw runtime_error("List is empty.");
	}
	_character.erase(_character.begin() + index);
}

void CharacterList::clear() {
	_character.clear();
}

istream& operator>>(istream& in, shared_ptr<Knight>& item) {
	cout << "Enter health:\n";
	in >> item->health;
	cout << "Enter armor:\n";
	in >> item->armor;
	cout << "Enter damage:\n";
	in >> item->damage;
	return in;
}
istream& operator>>(istream& in, shared_ptr<Assassin>& item) {
	cout << "Enter health:\n";
	in >> item->health;
	cout << "Enter armor:\n";
	in >> item->armor;
	cout << "Enter damage:\n";
	in >> item->damage;
	return in;
}

istream& operator>>(istream& in, shared_ptr<Berserk>& item) {
	cout << "Enter health:\n";
	in >> item->health;
	cout << "Enter armor:\n";
	in >> item->armor;
	cout << "Enter damage:\n";
	in >> item->damage;
	return in;
}

void CharacterList::print_current(int index) {
	_character[index]->print(cout);
}
void CharacterList::show_all() {
	for (int i = 0; i < _character.size(); ++i) {
		cout << i << ":";
		print_current(i);
		cout << endl;
	}
}

void CharacterList::Fight(ItemPtr& attacker, ItemPtr& defender) {
	Knight knig = Knight();
	Assassin assas = Assassin();
	Berserk bers = Berserk();
	while (attacker->get_hp() > 0 && defender->get_hp() > 0){
		int action = rand() % 2;
		int turn = rand() % 2;
		if (turn == 0) {
			if (action == 0) {
				if (defender->get_is_ability_used()) {
					cout << "Персонаж 2 увернулся от атаки" << endl;
					system("pause");
				}
				defender->take_damage(attacker->deal_damage());
				cout << "Персонаж 2 получил урон!" << endl;
				cout << "Здоровье персонажа 2: " << defender->get_hp() << endl;
				system("pause");
			}
			else {

				attacker->use_ability();
				if (typeid(*attacker) == typeid(knig)) {
					cout << "Персонажу 2 увеличена броня ценой урона" << endl;
					system("pause");
				}
				else if (typeid(*attacker) == typeid(bers)) {
					cout << "Персонажу 2 увеличен урон и шанс крита,ценой брони" << endl;
					system("pause");
				}
				else {
					cout << "Персонаж 2 готовится увернуться от следующей атаки" << endl;
					system("pause");
				}
			}
		}
		else if (turn == 1) {
			 
			if (action == 0) {
				if (attacker->get_is_ability_used()) {
					cout << "Персонаж 1 увернулся от атаки" << endl;
					system("pause");
				}
				attacker->take_damage(defender->deal_damage());
				cout << "Персонаж 1 получил урон!" << endl;
				cout << "Здоровье персонажа 1: " << attacker->get_hp() << endl;
				system("pause");
			}
			else {

				defender->use_ability();
				if (typeid(*defender) == typeid(knig)) {
					cout << "Персонажу 2 увеличена броня ценой урона" << endl;
					system("pause");
				}
				else if (typeid(*defender) == typeid(bers)) {
					cout << "Персонажу 2 увеличен урон и шанс крита,ценой брони" << endl;
					system("pause");
				}
				else {
					cout << "Персонаж 2 готовится увернуться от следующей атаки" << endl;
					system("pause");
				}
			}
		}
	}
	if (defender->get_hp() <= 0) cout << "Персонаж 1 победил" << endl;
	else if (attacker->get_hp() <= 0) cout << "Персонаж 2 победил" << endl;
}