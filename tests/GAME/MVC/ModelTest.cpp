#include "GAME/MVC/Model.hpp"
#include "GAME/Units/Hunter.hpp"
#include "GAME/Units/Swordsman.hpp"
#include <gtest/gtest.h>
#include <memory>

using namespace sw::game;

class ModelTest : public ::testing::Test {
protected:
    void SetUp() override {
        model = std::make_shared<Model>(10, 10);
        hunter = std::make_shared<Hunter>("hunter1", 0, 0, 100, 10, 15, 5);
        swordsman = std::make_shared<Swordsman>("sword1", 5, 5, 100, 15);
    }

    std::shared_ptr<Model> model;
    std::shared_ptr<Hunter> hunter;
    std::shared_ptr<Swordsman> swordsman;
};

TEST_F(ModelTest, MapSize) {
    EXPECT_EQ(model->getMapWidth(), 10);
    EXPECT_EQ(model->getMapHeight(), 10);

    model->setMapSize(15, 20);
    EXPECT_EQ(model->getMapWidth(), 15);
    EXPECT_EQ(model->getMapHeight(), 20);
}

TEST_F(ModelTest, PositionValidation) {
    EXPECT_TRUE(model->isPositionValid(0, 0));
    EXPECT_TRUE(model->isPositionValid(9, 9));
    EXPECT_FALSE(model->isPositionValid(-1, 0));
    EXPECT_FALSE(model->isPositionValid(0, -1));
    EXPECT_FALSE(model->isPositionValid(10, 0));
    EXPECT_FALSE(model->isPositionValid(0, 10));
}

TEST_F(ModelTest, UnitManagement) {
    // Add units
    model->addUnit(hunter);
    model->addUnit(swordsman);

    // Test getting units
    EXPECT_EQ(model->getUnit("hunter1"), hunter);
    EXPECT_EQ(model->getUnit("sword1"), swordsman);
    EXPECT_EQ(model->getUnit("nonexistent"), nullptr);

    // Test getting all units
    auto allUnits = model->getAllUnits();
    EXPECT_EQ(allUnits.size(), 2);
    EXPECT_EQ(allUnits["hunter1"], hunter);
    EXPECT_EQ(allUnits["sword1"], swordsman);

    // Test position occupation
    EXPECT_TRUE(model->isPositionOccupied(0, 0));
    EXPECT_TRUE(model->isPositionOccupied(5, 5));
    EXPECT_FALSE(model->isPositionOccupied(1, 1));

    // Test removing units
    model->removeUnit("hunter1");
    EXPECT_EQ(model->getUnit("hunter1"), nullptr);
    EXPECT_FALSE(model->isPositionOccupied(0, 0));
    EXPECT_EQ(model->getAllUnits().size(), 1);
}

TEST_F(ModelTest, InvalidOperations) {
    // Test adding unit at invalid position
    auto invalidUnit = std::make_shared<Hunter>("invalid", 15, 15, 100, 10, 15, 5);
    EXPECT_THROW(model->addUnit(invalidUnit), std::out_of_range);

    // Test adding unit at occupied position
    model->addUnit(hunter);
    auto overlappingUnit = std::make_shared<Swordsman>("overlap", 0, 0, 100, 15);
    EXPECT_THROW(model->addUnit(overlappingUnit), std::runtime_error);
} 