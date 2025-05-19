#include <gtest/gtest.h>

namespace sw::game::test {

class GameTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

};

TEST_F(GameTest, MockTest) {
    EXPECT_EQ(true, true);
}

} // namespace sw::game::test 