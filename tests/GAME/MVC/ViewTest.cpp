#include "GAME/MVC/View.hpp"
#include "GAME/Units/Hunter.hpp"
#include "GAME/Units/Swordsman.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <sstream>

using namespace sw::game;

class ViewTest : public ::testing::Test {
protected:
    void SetUp() override {
        model = std::make_shared<Model>(5, 5);
        view = std::make_shared<View>(model);
        
        // Add some units to the model
        hunter = std::make_shared<Hunter>("hunter1", 0, 0, 100, 10, 15, 5);
        swordsman = std::make_shared<Swordsman>("sword1", 2, 2, 100, 15);
        model->addUnit(hunter);
        model->addUnit(swordsman);
    }

    std::shared_ptr<Model> model;
    std::shared_ptr<View> view;
    std::shared_ptr<Hunter> hunter;
    std::shared_ptr<Swordsman> swordsman;
};

TEST_F(ViewTest, DisplayUnit) {
    // Test displaying existing unit
    testing::internal::CaptureStdout();
    view->displayUnit("hunter1");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("hunter1") != std::string::npos);
    EXPECT_TRUE(output.find("Hunter") != std::string::npos);

    // Test displaying non-existent unit
    testing::internal::CaptureStdout();
    view->displayUnit("nonexistent");
    output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("not found") != std::string::npos);
}

TEST_F(ViewTest, DisplayAllUnits) {
    testing::internal::CaptureStdout();
    view->displayAllUnits();
    std::string output = testing::internal::GetCapturedStdout();
    
    // Check if both units are displayed
    EXPECT_TRUE(output.find("hunter1") != std::string::npos);
    EXPECT_TRUE(output.find("sword1") != std::string::npos);
    EXPECT_TRUE(output.find("Hunter") != std::string::npos);
    EXPECT_TRUE(output.find("Swordsman") != std::string::npos);
}

TEST_F(ViewTest, DisplayMap) {
    testing::internal::CaptureStdout();
    view->displayMap();
    std::string output = testing::internal::GetCapturedStdout();
    
    // Check if map boundaries are displayed
    EXPECT_TRUE(output.find("-----") != std::string::npos);
    
    // Check if units are displayed at their positions
    EXPECT_TRUE(output.find("H") != std::string::npos); // Hunter
    EXPECT_TRUE(output.find("S") != std::string::npos); // Swordsman
}

TEST_F(ViewTest, DisplayMessage) {
    const std::string testMessage = "Test message";
    testing::internal::CaptureStdout();
    view->displayMessage(testMessage);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find(testMessage) != std::string::npos);
} 