#include "GAME/Units/Hunter.hpp"
#include <stdexcept>

#include <gtest/gtest.h>

using namespace sw::game;

class HunterTest : public ::testing::Test {
protected:
    void SetUp() override {
        hunter = std::make_unique<Hunter>("hunter1", 0, 0, 100, 10, 15, 5);
    }

    std::unique_ptr<Hunter> hunter;
};

TEST_F(HunterTest, Creation) {
    EXPECT_EQ(hunter->getId(), "hunter1");
    EXPECT_EQ(hunter->Unit::getX(), 0);
    EXPECT_EQ(hunter->Unit::getY(), 0);
    EXPECT_EQ(hunter->getHealth(), 100);
    EXPECT_EQ(hunter->getStrength(), 10);
    EXPECT_EQ(hunter->getAgility(), 15);
    EXPECT_EQ(hunter->getRange(), 5);
}

TEST_F(HunterTest, InvalidCreation) {
    EXPECT_THROW(Hunter("hunter1", 0, 0, 100, -10, 15, 5), std::invalid_argument);
    EXPECT_THROW(Hunter("hunter1", 0, 0, 100, 10, -15, 5), std::invalid_argument);
    EXPECT_THROW(Hunter("hunter1", 0, 0, 100, 10, 15, -5), std::invalid_argument);
}

TEST_F(HunterTest, Movement) {
    hunter->moveTo(5, 5);
    EXPECT_EQ(hunter->Unit::getX(), 5);
    EXPECT_EQ(hunter->Unit::getY(), 5);
}

TEST_F(HunterTest, Combat) {
    EXPECT_TRUE(hunter->isAlive());
    hunter->takeDamage(50);
    EXPECT_EQ(hunter->getHealth(), 50);
    EXPECT_TRUE(hunter->isAlive());
    hunter->takeDamage(50);
    EXPECT_EQ(hunter->getHealth(), 0);
    EXPECT_FALSE(hunter->isAlive());
}

TEST_F(HunterTest, Range) {
    EXPECT_TRUE(hunter->canShootAt(2, 3));  // Within range
    EXPECT_TRUE(hunter->canShootAt(5, 0));  // At max range
    EXPECT_FALSE(hunter->canShootAt(6, 0)); // Beyond range
    EXPECT_FALSE(hunter->canShootAt(3, 3)); // Beyond range
}

TEST_F(HunterTest, UnitType) {
    EXPECT_EQ(hunter->getType(), "Hunter");
} 