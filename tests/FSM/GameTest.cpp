#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <FSM/Game.hpp>
#include <FSM/State.hpp>
#include <memory>

namespace sw::fsm::test {

using ::testing::_;

// Mock State for testing
class MockState final : public IGameState {
public:
    MOCK_METHOD(void, enter, (Game&), (override));
    MOCK_METHOD(void, update, (Game&), (override));
    MOCK_METHOD(void, exit, (Game&), (override));
};

class GameTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup command line arguments
        static const char* args[] = {"test", "commands_example.txt"};

        game = std::make_unique<Game>(2, const_cast<char**>(args));
    }

    void TearDown() override {
        game.reset();
    }

    std::unique_ptr<Game> game;
};

TEST_F(GameTest, InitialState) {
    EXPECT_EQ(game->getStateName(), SimulationInitState::Name);
}

} // namespace sw::fsm::test 