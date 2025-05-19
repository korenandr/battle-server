#include <gtest/gtest.h>
#include "GAME/Units/UnitFactory.hpp"
#include "GAME/Units/Swordsman.hpp"
#include "GAME/Units/Hunter.hpp"

using namespace sw::game;

class UnitFactoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Common test data
        id = "1";
        x = 5;
        y = 5;
        health = 100;
        strength = 10;
        agility = 5;
        range = 3;
    }

    std::string id;
    int x;
    int y;
    int health;
    int strength;
    int agility;
    int range;
};

TEST_F(UnitFactoryTest, CreateSwordsman) {
    auto unit = UnitFactory::createUnit("Swordsman", id, x, y, health, strength);
    
    ASSERT_NE(unit, nullptr);
    EXPECT_EQ(unit->getId(), id);
    EXPECT_EQ(unit->getType(), "Swordsman");
    EXPECT_EQ(unit->getX(), x);
    EXPECT_EQ(unit->getY(), y);
    EXPECT_EQ(unit->getHealth(), health);
    EXPECT_EQ(unit->getStrength(), strength);
    EXPECT_EQ(unit->getAgility(), 0);  // Swordsmen have no agility
    EXPECT_EQ(unit->getRange(), 1);    // Swordsmen have melee range
}

TEST_F(UnitFactoryTest, CreateHunter) {
    auto unit = UnitFactory::createUnit("Hunter", id, x, y, health, strength, agility, range);
    
    ASSERT_NE(unit, nullptr);
    EXPECT_EQ(unit->getId(), id);
    EXPECT_EQ(unit->getType(), "Hunter");
    EXPECT_EQ(unit->getX(), x);
    EXPECT_EQ(unit->getY(), y);
    EXPECT_EQ(unit->getHealth(), health);
    EXPECT_EQ(unit->getStrength(), strength);
    EXPECT_EQ(unit->getAgility(), agility);
    EXPECT_EQ(unit->getRange(), range);
}

TEST_F(UnitFactoryTest, InvalidUnitType) {
    EXPECT_THROW(
        UnitFactory::createUnit("InvalidType", id, x, y, health),
        std::invalid_argument
    );
}

TEST_F(UnitFactoryTest, EmptyId) {
    EXPECT_THROW(
        UnitFactory::createUnit("Swordsman", "", x, y, health, strength),
        std::invalid_argument
    );
}

TEST_F(UnitFactoryTest, NegativeHealth) {
    EXPECT_THROW(
        UnitFactory::createUnit("Swordsman", id, x, y, -10, strength),
        std::invalid_argument
    );
}

TEST_F(UnitFactoryTest, ZeroHealth) {
    EXPECT_THROW(
        UnitFactory::createUnit("Swordsman", id, x, y, 0, strength),
        std::invalid_argument
    );
}

TEST_F(UnitFactoryTest, NegativeStrength) {
    EXPECT_THROW(
        UnitFactory::createUnit("Swordsman", id, x, y, health, -5),
        std::invalid_argument
    );
}

TEST_F(UnitFactoryTest, NegativeAgility) {
    EXPECT_THROW(
        UnitFactory::createUnit("Hunter", id, x, y, health, strength, -3, range),
        std::invalid_argument
    );
}

TEST_F(UnitFactoryTest, NegativeRange) {
    EXPECT_THROW(
        UnitFactory::createUnit("Hunter", id, x, y, health, strength, agility, -2),
        std::invalid_argument
    );
}

TEST_F(UnitFactoryTest, ZeroRange) {
    EXPECT_THROW(
        UnitFactory::createUnit("Hunter", id, x, y, health, strength, agility, 0),
        std::invalid_argument
    );
} 