#include "gmock/gmock.h"
#include "baseball.cpp"

class BaseballGameFixture : public ::testing::Test {
protected:
	Baseball* game;

	void SetUp() override {
		game = new Baseball("123");
	}

	void TearDown() override {
		delete game;
	}
};

// Normal game flow tests
TEST_F(BaseballGameFixture, NoStrikeNoBall) {
	GuessResult result = game->guess("456");
	EXPECT_FALSE(result.solved);
	EXPECT_EQ(result.strikes, 0);
	EXPECT_EQ(result.balls, 0);
}

TEST_F(BaseballGameFixture, TwoStrikesNoBall) {
	GuessResult result = game->guess("129");
	EXPECT_FALSE(result.solved);
	EXPECT_EQ(result.strikes, 2);
	EXPECT_EQ(result.balls, 0);
}

TEST_F(BaseballGameFixture, NoStrikeOneBall) {
	GuessResult result = game->guess("240");
	EXPECT_FALSE(result.solved);
	EXPECT_EQ(result.strikes, 0);
	EXPECT_EQ(result.balls, 1);
}

TEST_F(BaseballGameFixture, OneStrikeTwoBalls) {
	GuessResult result = game->guess("321");
	EXPECT_FALSE(result.solved);
	EXPECT_EQ(result.strikes, 1);
	EXPECT_EQ(result.balls, 2);
}

TEST_F(BaseballGameFixture, Solved) {
	GuessResult result = game->guess("123");
	EXPECT_TRUE(result.solved);
	EXPECT_EQ(result.strikes, 3);
	EXPECT_EQ(result.balls, 0);
}

// Error handling tests
TEST_F(BaseballGameFixture, GuessTooShort) {
	EXPECT_THROW(game->guess("12"), length_error);
}

TEST_F(BaseballGameFixture, GuessTooLong) {
	EXPECT_THROW(game->guess("1234"), length_error);
}

TEST_F(BaseballGameFixture, GuessNonDigit) {
	EXPECT_THROW(game->guess("1a3"), invalid_argument);
}

TEST(BaseballGameInit, AnswerTooShort) {
	EXPECT_THROW(Baseball("12"), length_error);
}

TEST(BaseballGameInit, AnswerNonDigit) {
	EXPECT_THROW(Baseball("1a3"), invalid_argument);
}

int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
