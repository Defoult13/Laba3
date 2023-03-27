#include <gtest/gtest.h>
#include <characters/characters.h>

using namespace warriors;

TEST(CharacterTests, DealDamage) {
	// Arrange
	Character p1(CharacterType::KNIGHT, 100, 30, 20);
	Character p2(CharacterType::ASSASSIN, 100, 20, 30);
	Character p3(CharacterType::BERSERK, 100, 20, 20);
	// Act
	float dd1 = p1.deal_damage();
	float dd2 = p2.deal_damage();
	float dd3 = p3.deal_damage();
	// Assert
	EXPECT_EQ(dd1, 20);
	EXPECT_TRUE(dd2 == 30 or dd2 == 60);
	EXPECT_TRUE(dd3 == 20 or dd3 == 60);
}

TEST(CharacterTests, TakeDamage) {
	// Arrange
	Character p1(CharacterType::KNIGHT, 100, 30, 20);
	Character p2(CharacterType::ASSASSIN, 100, 20, 30);
	Character p3(CharacterType::BERSERK, 100, 20, 20);
	// Act
	p1.take_damage(40);
	p2.take_damage(60);
	p3.take_damage(80);
	// Assert
	EXPECT_TRUE(p1.get_hp() == 72 or p1.get_hp() == 86);
	EXPECT_EQ(p2.get_hp(), 52);
	EXPECT_EQ(p3.get_hp(), 36);

}

TEST(CharacterTests, UseAbility) {
	// Arrange
	Character p1(CharacterType::KNIGHT, 100, 30, 20);
	Character p2(CharacterType::ASSASSIN, 100, 20, 30);
	Character p3(CharacterType::BERSERK, 100, 20, 20);
	bool is_ability_used = false;
	float triple_hit_chance = 30;
	// Act
	p1.use_ability();
	p2.use_ability();
	p3.use_ability();
	// Assert
	EXPECT_EQ(p1.get_armor(), 60);
	EXPECT_EQ(p1.get_damage(), 10);
	EXPECT_TRUE(p2.get_is_ability_used());
	EXPECT_EQ(p3.get_damage(), 40);
	EXPECT_EQ(p3.get_triple_hit_chance(), 60);
	EXPECT_EQ(p3.get_armor(), 10);

}

TEST(CharacterTests, SettersAndGetters) {
	Character p1(CharacterType::KNIGHT, 100, 30, 20);

	p1.set_damage(60);
	p1.set_hp(80);
	p1.set_armor(40);
	p1.set_triple_hit_chance(10);
	p1.set_is_ability_used(true);

	EXPECT_EQ(p1.get_damage(), 60);
	EXPECT_EQ(p1.get_hp(), 80);
	EXPECT_EQ(p1.get_armor(), 40);
	EXPECT_EQ(p1.get_triple_hit_chance(), 10);
	EXPECT_TRUE(p1.get_is_ability_used());
}

TEST(CharacterListTests, CharacterListSize) {
	CharacterList list = CharacterList();

	EXPECT_EQ(list.get_size(), 3);
}

TEST(CharacterListTests, AddCharacter) {
	CharacterList tab = CharacterList();
	Character p1(CharacterType::ASSASSIN, 100, 30, 50);
	tab.add_character(1, p1);

	EXPECT_EQ(tab.get_size(), 4);
	EXPECT_EQ(tab[1].get_hp(), 100);
	EXPECT_EQ(tab[1].get_damage(), 50);
	EXPECT_EQ(tab[0].get_type(), 0);
	EXPECT_EQ(tab[1].get_armor(), 30);

}

TEST(CharacterListTests, DeleteCharacter) {
	CharacterList tab = CharacterList();
	tab.delete_character(0);

	EXPECT_EQ(tab.get_size(), 2);
	EXPECT_EQ(tab[0].get_type(), 0);
	EXPECT_EQ(tab[1].get_hp(), 100);
}

TEST(CharacterListTests, ClearList) {
	CharacterList tab = CharacterList();
	tab.clear();

	EXPECT_EQ(tab.get_size(), 0);
}

TEST(CharacterListTests, IndexOfStrongest) {
	CharacterList tab = CharacterList();
	Character p1(CharacterType::ASSASSIN, 100, 30, 90);
	tab.add_character(1, p1);

	EXPECT_EQ(tab.index_of_maxdam(), 1);
}

TEST(CharacterListTest, ExceptionTest) {
	CharacterList l1 = CharacterList();
	l1.set_size(0);
	EXPECT_ANY_THROW(l1.delete_character(5), std::runtime_error);
}

TEST(CharacterListTest, ExceptionTest2) {
	CharacterList l2 = CharacterList();
	l2.set_size(11);
	Character c = Character();
	EXPECT_ANY_THROW(l2.add_character(50, c), std::runtime_error);
}