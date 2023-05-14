#pragma once
#include <memory>
#include <iostream>
#include <vector>
#define ItemPtr shared_ptr<Character>
using namespace std;



	

	class Character
	{
	public:
		virtual float deal_damage() const = 0;
		virtual void take_damage(float incoming_damage) = 0;
		virtual void use_ability() = 0;

		virtual unique_ptr<Character> clone() const = 0;
		virtual bool equals(shared_ptr<Character> other) const = 0;
		virtual void print(ostream& stream) const = 0;

		virtual ~Character() = default;

		
		float get_damage() const;
		float get_hp() const;
		float get_armor() const;
		bool get_is_ability_used() const;
		
		void set_damage(float damage);
		void set_hp(float hp);
		void set_armor(float armor);

	protected:
		float health;
		float armor;
		float damage;
		Character() = default;
		Character(const Character& character) = default;
		Character& operator=(const Character& other) = default;
		bool is_ability_used = false;
	};

	class Knight : public Character {
		float reduce_damage_chance = 40;
	public:

		Knight();
		Knight(float health, float armor, float damage);
		~Knight() = default;

		unique_ptr<Character> clone() const override;
		bool equals(shared_ptr<Character> other) const override;
		void print(ostream& out) const override;
		friend istream& operator>>(istream& in, shared_ptr<Knight>& item);
		float deal_damage() const override;
		void take_damage(float incoming_damage) override;
		void use_ability() override;
	};

	class Assassin : public Character {
		float double_hit_chance = 50;
	public:

		void set_is_ability_used(bool is_ability_used);
		Assassin();
		Assassin(float health, float armor, float damage);
		~Assassin() = default;

		unique_ptr<Character> clone() const override;
		bool equals(shared_ptr<Character> other) const override;
		void print(ostream& out) const override;
		friend istream& operator>>(istream& in, shared_ptr<Assassin>& item);
		float deal_damage() const override;
		void take_damage(float incoming_damage) override;
		void use_ability() override;
	};

	class Berserk : public Character {
		float triple_hit_chance = 30;
	public:
		void set_triple_hit_chance(float triple_hit_chance);
		float get_triple_hit_chance() const;
		Berserk();
		Berserk(float health, float armor, float damage);
		~Berserk() = default;

		unique_ptr<Character> clone() const override;
		bool equals(shared_ptr<Character> other) const override;
		void print(ostream& out) const override;
		friend istream& operator>>(istream& in, shared_ptr<Berserk>& item);
		float deal_damage() const override;
		void take_damage(float incoming_damage) override;
		void use_ability() override;
	};

	class CharacterList
	{
		vector<ItemPtr> _character;

	public:

		CharacterList();
		CharacterList(vector<ItemPtr> characters);
		CharacterList(vector<ItemPtr> characters, int);
		CharacterList(const CharacterList& other);

		ItemPtr get_character_by_index(int i);
		int size();

		void add_character(int index, ItemPtr character);
		void delete_character(int index);
		void clear();
		void print_current(int index);
		void show_all();
		void Swap(CharacterList& other) noexcept;
		int index_of_maxdam();
		void Fight(Character& attacker, Character& defender);

		ItemPtr operator[](int index) const;
		ItemPtr& operator[](int index);
		CharacterList& operator=(CharacterList other);
		friend bool operator==(const CharacterList& tab, const CharacterList& other);
		friend bool operator!=(const CharacterList& tab, const CharacterList& other);
	};