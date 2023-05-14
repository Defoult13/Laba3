#include <gtest/gtest.h>
#include <characters/characters.h>


TEST(CharacterTests, DealDamage) {
	// Arrange
	Knight p1 = Knight(100, 30, 20);
	Assassin p2 = Assassin(100, 20, 30);
	Berserk p3 = Berserk(100, 20, 20);
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
	Knight p1 = Knight(100, 30, 20);
	Assassin p2 = Assassin(100, 20, 30);
	Berserk p3 = Berserk(100, 20, 20);
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
	Knight p1 = Knight(100, 30, 20);
	Assassin p2 = Assassin(100, 20, 30);
	Berserk p3 = Berserk(100, 20, 20);
	bool is_ability_used = false;
	float triple_hit_chance = 30;
	// Act
	p1.use_ability();
	p2.use_ability();
	p3.use_ability();
	// Assert
	EXPECT_EQ(p1.get_armor(), 31);
	EXPECT_EQ(p1.get_damage(), 19);
	EXPECT_TRUE(p2.get_is_ability_used());
	EXPECT_EQ(p3.get_damage(), 22);
	EXPECT_EQ(p3.get_triple_hit_chance(), 32);
	EXPECT_EQ(p3.get_armor(), 19);

}

TEST(CharacterTests, SettersAndGetters) {
	Assassin p2 = Assassin(100, 30, 20);

	p2.set_damage(60);
	p2.set_hp(80);
	p2.set_armor(40);
	p2.set_is_ability_used(true);

	EXPECT_EQ(p2.get_damage(), 60);
	EXPECT_EQ(p2.get_hp(), 80);
	EXPECT_EQ(p2.get_armor(), 40);
	EXPECT_TRUE(p2.get_is_ability_used());
}


TEST(CharacterListTests, AddCharacter) {
	CharacterList tab = CharacterList();
	ItemPtr p1 = make_shared<Assassin>(100, 30, 50);
	tab.add_character(1, p1);

	
	EXPECT_EQ(tab[1]->get_hp(), 100);
	EXPECT_EQ(tab[1]->get_damage(), 50);
	EXPECT_EQ(tab[1]->get_armor(), 30);

}

TEST(CharacterListTests, DeleteCharacter) {
	CharacterList tab = CharacterList();
	tab.delete_character(0);

	EXPECT_EQ(tab.size(), 2);
	EXPECT_EQ(tab[0]->get_hp(), 100);
}

TEST(CharacterListTests, ClearList) {
	CharacterList tab = CharacterList();
	tab.clear();

	EXPECT_EQ(tab.size(), 0);
}

TEST(CharacterListTests, IndexOfMaxDam) {
	CharacterList tab;
	tab.add_character(0, make_shared<Knight>(100, 40, 30));
	tab.add_character(1, make_shared<Assassin>(100, 10, 20));
	tab.add_character(2, make_shared<Berserk>(100, 20, 40));

	EXPECT_EQ(tab.index_of_maxdam(), 2);
}
