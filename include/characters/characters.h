#pragma once
#include <iostream>
#define ListPtr Character*
using namespace std;



	enum CharacterType
	{
		KNIGHT,
		ASSASSIN,
		BERSERK
	};

	class Character
	{
	private:
		CharacterType type;
		float health;
		float armor;
		float damage;
		float triple_hit_chance = 30;
		bool is_ability_used = false;
	public:
		float deal_damage();
		void take_damage(float incoming_damage);
		void use_ability();

		int get_type() const;
		float get_damage() const;
		float get_hp() const;
		float get_armor() const;
		float get_triple_hit_chance() const;
		bool get_is_ability_used() const;

		void set_type(CharacterType type);
		void set_damage(float damage);
		void set_hp(float hp);
		void set_armor(float armor);
		void set_triple_hit_chance(float triple_hit_chance);
		void set_is_ability_used(bool is_ability_used);

		Character();
		Character(CharacterType type, float health, float armor, float damage);
		Character(const	Character& character);
		friend istream& operator>>(istream& in, Character& item);
		friend ostream& operator<<(ostream& out, const Character& item);
		void Swap(Character& other) noexcept;
		Character& operator=(Character other);
	};

	class CharacterList
	{
		ListPtr* _character;
		size_t _size;
	public:

		CharacterList();
		CharacterList(ListPtr* characters, size_t _size);
		~CharacterList();

		ListPtr get_character_by_index(int i);
		void add_character(int index, Character character);
		void delete_character(int index);
		void clear();
		void print_current(int index);
		void show_all();
		void Swap(CharacterList& other) noexcept;
		int index_of_maxdam();
		void Fight(Character& attacker, Character& defender);

		int get_size();
		void set_size(size_t size);

		ListPtr operator[](int index) const;
		ListPtr& operator[](int index);
		CharacterList& operator=(CharacterList other);
		friend bool operator==(const CharacterList& tab, const CharacterList& other);
		friend bool operator!=(const CharacterList& tab, const CharacterList& other);
	};