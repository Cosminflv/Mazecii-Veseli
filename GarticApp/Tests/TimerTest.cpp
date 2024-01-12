#include "Timer.h";

#include "gtest/gtest.h"

TEST(TimeRanOutTest, RanOut1)
{
	Timer t(500, true);

	t.StartTimer();

	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	t.StopTimer();

	EXPECT_EQ(t.IsTimeExpired(), false);
}

TEST(TimeRanOutTest, RanOut2)
{
	Timer t(1, true);

	t.StartTimer();

	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	EXPECT_EQ(t.IsTimeExpired(), true);
}

TEST(TimerResetTest, TimerReset1)
{
	Timer t(1, true);

	t.StartTimer();

	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	t.ResetTimer();

	EXPECT_EQ(t.GetRemainingTime(), std::chrono::milliseconds(1));
}