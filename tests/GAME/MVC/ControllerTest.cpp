#include "GAME/MVC/Controller.hpp"
#include "IO/Commands/Command.hpp"
#include "IO/System/EventLog.hpp"
#include <gtest/gtest.h>
#include <memory>

using namespace sw::game;
using namespace sw::io;

// Mock Command class for testing
class MockCommand : public Command {
public:
    explicit MockCommand(const std::string& type) : type_(type) {}
    void execute(const std::shared_ptr<Controller>& controller) override {
        executed_ = true;
        controller_ = controller;
    }
    bool wasExecuted() const { return executed_; }
    std::shared_ptr<Controller> getController() const { return controller_; }

private:
    std::string type_;
    bool executed_ = false;
    std::shared_ptr<Controller> controller_;
};

class ControllerTest : public ::testing::Test {
protected:
    void SetUp() override {
        model = std::make_shared<Model>(10, 10);
        view = std::make_shared<View>(model);
        eventLog = std::make_shared<sw::EventLog>();
        controller = std::make_shared<Controller>(model, view, eventLog);
    }

    std::shared_ptr<Model> model;
    std::shared_ptr<View> view;
    std::shared_ptr<sw::EventLog> eventLog;
    std::shared_ptr<Controller> controller;
};

TEST_F(ControllerTest, ComponentAccess) {
    EXPECT_EQ(controller->getModel(), model);
    EXPECT_EQ(controller->getView(), view);
    EXPECT_EQ(controller->getEventLog(), eventLog);
}

TEST_F(ControllerTest, CommandHandling) {
    auto mockCommand = std::make_shared<MockCommand>("test");
    
    // Test command execution
    controller->handleCommand(mockCommand);
    EXPECT_TRUE(mockCommand->wasExecuted());
    EXPECT_EQ(mockCommand->getController(), controller);
}

TEST_F(ControllerTest, InvalidCommand) {
    // Test handling null command
    EXPECT_THROW(controller->handleCommand(nullptr), std::invalid_argument);
}

TEST_F(ControllerTest, CommandExecutionOrder) {
    auto command1 = std::make_shared<MockCommand>("first");
    auto command2 = std::make_shared<MockCommand>("second");
    
    controller->handleCommand(command1);
    controller->handleCommand(command2);
    
    EXPECT_TRUE(command1->wasExecuted());
    EXPECT_TRUE(command2->wasExecuted());
    EXPECT_EQ(command1->getController(), controller);
    EXPECT_EQ(command2->getController(), controller);
} 