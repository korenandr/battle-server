#include "GAME/Units/Swordsman.hpp"

#include <stdexcept>

#include <gtest/gtest.h>

using namespace sw::game;

class SwordsmanTest : public ::testing::Test {
protected:
    void SetUp() override {
        swordsman = std::make_unique<Swordsman>("sword1", 0, 0, 100, 15);
    }

    std::unique_ptr<Swordsman> swordsman;
};

TEST_F(SwordsmanTest, Creation) {
    EXPECT_EQ(swordsman->getId(), "sword1");
    EXPECT_EQ(swordsman->Unit::getX(), 0);
    EXPECT_EQ(swordsman->Unit::getY(), 0);
    EXPECT_EQ(swordsman->getHealth(), 100);
    EXPECT_EQ(swordsman->getStrength(), 15);
}

TEST_F(SwordsmanTest, InvalidCreation) {
    EXPECT_THROW(Swordsman("sword1", 0, 0, 100, -15), std::invalid_argument);
}

TEST_F(SwordsmanTest, Movement) {
    swordsman->moveTo(3, 4);
    EXPECT_EQ(swordsman->Unit::getX(), 3);
    EXPECT_EQ(swordsman->Unit::getY(), 4);
}

TEST_F(SwordsmanTest, Combat) {
    EXPECT_TRUE(swordsman->isAlive());
    swordsman->takeDamage(30);
    EXPECT_EQ(swordsman->getHealth(), 70);
    EXPECT_TRUE(swordsman->isAlive());
    swordsman->takeDamage(70);
    EXPECT_EQ(swordsman->getHealth(), 0);
    EXPECT_FALSE(swordsman->isAlive());
}

TEST_F(SwordsmanTest, UnitType) {
    EXPECT_EQ(swordsman->getType(), "Swordsman");
} 