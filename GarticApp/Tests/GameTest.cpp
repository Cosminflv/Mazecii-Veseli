#include "gtest/gtest.h"
#include "Player.h"


TEST(GameTest, GameTest1)
{
	Player p("TestUsername", PlayerRole::Guesser, 0);

	//EXPECT_EQ(PlayerRole::Guesser, p.GetPlayerRole());
}
