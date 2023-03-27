#pragma once

namespace warriors {

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

		int get_type();
		float get_damage();
		float get_hp();
		float get_armor();
		float get_triple_hit_chance();
		bool get_is_ability_used();

		void set_type(CharacterType type);
		void set_damage(float damage);
		void set_hp(float hp);
		void set_armor(float armor);
		void set_triple_hit_chance(float triple_hit_chance);
		void set_is_ability_used(bool is_ability_used);

		Character();
		Character(CharacterType type, float health, float armor, float damage);
	};

	class CharacterList
	{
	public:

		CharacterList();
		CharacterList(Character characters[], int size);

		void add_character(int index, Character character);
		void delete_character(int index);
		void clear();

		Character operator[](int index) const;

		int get_size();
		void set_size(int size);
		int index_of_maxdam();
	private:
		static const int CAP = 10;
		Character _characters[CAP];
		int _size;
	};
}