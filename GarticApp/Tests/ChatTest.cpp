#include "Chat.h"
#include "Chat.cpp"

#include "gtest/gtest.h"

TEST(ChatTests, WriteMessage1)
{
	Chat c;

	c.WriteMessage({ "PlayerName", "this is a test message" });

	std::vector<std::pair<std::string, std::string>> expectedMessages = { { "PlayerName", "this is a test message" } };

	EXPECT_EQ(expectedMessages, c.getChatVector());
}

TEST(ChatTests, HavenWrittenYetTest)
{
	Chat c;

	EXPECT_TRUE(c.getChatVector().empty());
}
