#include "pch.h"
#include "CppUnitTest.h"
#include "Chat.h"
#include "Game.h"
#include "SubRound.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestsNative
{
	TEST_CLASS(ChatTests)
	{
	public:
		
        TEST_METHOD(ChatWriteMessage)
        {
            Chat c;

            c.WriteMessage({ "PlayerName", "this is a test message" });

            std::vector<std::pair<std::string, std::string>> expectedMessages = { { "PlayerName", "this is a test message" } };

            auto actualMessages = c.getChatVector();

            // Assert to check if the actual messages are equal to the expected messages
            Assert::AreEqual(expectedMessages.size(), actualMessages.size(), L"Message vector sizes are not equal");

            for (size_t i = 0; i < expectedMessages.size(); ++i)
            {
                Assert::AreEqual(expectedMessages[i].first, actualMessages[i].first, L"Player names are not equal");
                Assert::AreEqual(expectedMessages[i].second, actualMessages[i].second, L"Messages are not equal");
            }
        }

        TEST_METHOD(ChatEmpty)
        {
            Chat c;

            auto messages = c.getChatVector();

            Assert::AreEqual(0, (int)messages.size());
        }
	};

    TEST_CLASS(TimerTests)
    {
    public:
        TEST_METHOD(IsTimeExpired1)
        {
            Timer t(500, true);

            t.StartTimer();

            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            t.StopTimer();

            Assert::AreEqual(false, t.IsTimeExpired());
        }

        TEST_METHOD(IsTimeExpired2)
        {
            Timer t(1, true);

            t.StartTimer();

            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            Assert::AreEqual(true, t.IsTimeExpired());
        }

        TEST_METHOD(ResetTimer)
        {
            Timer t(1, true);

            t.StartTimer();

            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            t.ResetTimer();

            Assert::AreEqual(false, t.IsTimeExpired());
        }
    };

    TEST_CLASS(SubroundTests)
    {
    public:
        TEST_METHOD(InitTest)
        {
            SubRound s("pineapple", 3);

            std::string expectedWord = "pineapple";
            std::string resultWord = s.GetSeenWord();

            Assert::AreEqual(expectedWord, resultWord);
        }

        TEST_METHOD(GuessWordTest)
        {
            SubRound s("pineapple", 3);

            bool result = s.GuessWord("pineapple");

            Assert::AreEqual(true, result);
        }

        //TEST_METHOD(SelectRandomWordTest) CANNOT BE TESTED
        //{
        //    SubRound s;

        //    auto result = s.SelectRandomWord(static_cast<uint16_t>(1));

        //    Assert::IsFalse(result.empty());
        //}

        TEST_METHOD(HideWordTest)
        {
            SubRound s;

            std::string result = s.HideWord("pineapple");
            std::string expectedResult = "---------";

            Assert::AreEqual(expectedResult, result);
        }

        TEST_METHOD(UpdateWordWithLetters_EmptyCurrentWord)
        {
            SubRound subRound; // Assuming default constructor is available
            std::string seenWord = "example";
            std::string currentWord = "";

            std::string result = subRound.UpdateWordWithLetters(seenWord, currentWord);

            Assert::AreEqual(size_t(0), result.size(), L"Result should be an empty string when currentWord is empty.");
        }

        TEST_METHOD(MakeAllLettersFalse_SetsAllToFalse)
        {
            std::string sizeWord = "example"; // Example word
            SubRound subRound(sizeWord, 3);
            subRound.MakeAllLettersFalse(sizeWord);

            // Accessor method or friend class needed to get the value of m_letterShown
            const std::vector<bool>& letterShown = subRound.GetLetterShown();

            Assert::AreEqual(sizeWord.size(), letterShown.size(), L"m_letterShown size does not match sizeWord size.");

            for (bool letterState : letterShown)
            {
                Assert::IsFalse(letterState, L"Not all elements in m_letterShown are set to false.");
            }
        }

        TEST_METHOD(UpdateWordWithLetters_NonEmptyCurrentWord)
        {
            std::string seenWord = "example";
            SubRound subRound(seenWord, 3);
            std::string currentWord = "*******"; // Masked word
            std::string initialCurrentWord = "*******";
            subRound.MakeAllLettersFalse(seenWord);
            std::string result = subRound.UpdateWordWithLetters(seenWord, currentWord);

            Assert::IsTrue(result != initialCurrentWord, L"currentWord should be updated with at least one letter from seenWord.");
            Assert::IsTrue(result.find('*') != std::string::npos, L"currentWord should still contain some masked letters.");
            Assert::IsTrue(result.size() == seenWord.size(), L"Updated word should have the same size as seenWord.");
        }

        TEST_METHOD(MakeAllLettersFalse_EmptyString)
        {
            SubRound subRound;
            std::string emptyWord = ""; // Empty word
            subRound.MakeAllLettersFalse(emptyWord);

            const std::vector<bool>& letterShown = subRound.GetLetterShown();

            Assert::AreEqual(size_t(0), letterShown.size(), L"m_letterShown should be empty when the input string is empty.");
        }

        TEST_METHOD(NonOneGuessed_AllPlayersNotGuessed)
        {
            SubRound s;

            PlayerPtr player1 = std::make_shared<Player>("Player1", PlayerRole::Guesser, 0);
            PlayerPtr player2 = std::make_shared<Player>("Player2", PlayerRole::Guesser, 0);
            PlayerPtr player3 = std::make_shared<Player>("Player2", PlayerRole::Guesser, 0);

            std::vector<PlayerPtr> players = { player1, player2, player3 };

            Assert::IsTrue(s.NoOneGuessed(players));
        }

        TEST_METHOD(NonOneGuessed_SomePlayersGuessed)
        {
            SubRound s;

            PlayerPtr player1 = std::make_shared<Player>("Player1", PlayerRole::Guesser, 0);
            PlayerPtr player2 = std::make_shared<Player>("Player2", PlayerRole::Guesser, 0);
            PlayerPtr player3 = std::make_shared<Player>("Player2", PlayerRole::Guesser, 0);

            player2->SetSecond(27); // player2 guessed at second 27
   
            std::vector<PlayerPtr> players = { player1, player2, player3 };

            Assert::IsFalse(s.NoOneGuessed(players));
        }

        TEST_METHOD(AverageSeconds_EmptyPlayerVector)
        {
            SubRound s;
            std::vector<PlayerPtr> players;

            int result = s.AverageSeconds(players);

            Assert::AreEqual(0, result);
        }

        TEST_METHOD(AverageSeconds_SinglePlayer)
        {
            SubRound s;

            PlayerPtr player = std::make_shared<Player>("Player1", PlayerRole::Guesser, 0);
            player->SetSecond(60);

            std::vector<PlayerPtr> players = { player };

            int result = s.AverageSeconds(players);

            Assert::AreEqual(60, result);
        }

        TEST_METHOD(AverageSeconds_MultiplePlayers1)
        {
            SubRound s;
            PlayerPtr player1 = std::make_shared<Player>("Player1", PlayerRole::Guesser, 0);
            PlayerPtr player2 = std::make_shared<Player>("Player2", PlayerRole::Guesser, 0);
            PlayerPtr player3 = std::make_shared<Player>("Player3", PlayerRole::Guesser, 0);
            player1->SetSecond(60);
            player2->SetSecond(30);
            player3->SetSecond(90);
            std::vector<PlayerPtr> players = { player1, player2, player3 };

            int result = s.AverageSeconds(players);

            Assert::AreEqual(60, result);
        }

        TEST_METHOD(AverageSeconds_MultiplePlayers2)
        {
            SubRound s;
            PlayerPtr player1 = std::make_shared<Player>("Player1", PlayerRole::Guesser, 0);
            PlayerPtr player2 = std::make_shared<Player>("Player2", PlayerRole::Guesser, 0);
            PlayerPtr player3 = std::make_shared<Player>("Player3", PlayerRole::Guesser, 0);
            player1->SetSecond(50);
            player2->SetSecond(45);
            player3->SetSecond(15);
            std::vector<PlayerPtr> players = { player1, player2, player3 };
            int expectedResult = (50 + 45 + 15) / 3;

            int result = s.AverageSeconds(players);

            Assert::AreEqual(expectedResult, result);
        }

        TEST_METHOD(CalculatePainterScore_EmptyPlayerVector)
        {
            SubRound s;
            std::vector<PlayerPtr> players;

            int result = s.CalculatePainterScore(players);

            Assert::AreEqual(-100, result);
        }

        TEST_METHOD(CalculatePainterScore_NoPlayerGuessed)
        {
            SubRound s;
            PlayerPtr player1 = std::make_shared<Player>("Player1", PlayerRole::Guesser, 0);
            PlayerPtr player2 = std::make_shared<Player>("Player2", PlayerRole::Guesser, 0);
            PlayerPtr player3 = std::make_shared<Player>("Player3", PlayerRole::Guesser, 0);
            std::vector<PlayerPtr> players = { player1, player2, player3 };

            int result = s.CalculatePainterScore(players);

            Assert::AreEqual(-100, result);
        }

        TEST_METHOD(CalculatePainterScore_OnePlayerGuessed)
        {
            SubRound s;
            PlayerPtr player1 = std::make_shared<Player>("Player1", PlayerRole::Guesser, 0);
            PlayerPtr player2 = std::make_shared<Player>("Player2", PlayerRole::Guesser, 0);
            PlayerPtr player3 = std::make_shared<Player>("Player3", PlayerRole::Guesser, 0);
            
            player1->SetSecond(30);
            std::vector<PlayerPtr> players = { player1, player2, player3 };

            int result = s.CalculatePainterScore(players);

            Assert::AreEqual(16, result);
        }

        TEST_METHOD(CalculatePainterScore_AllPlayersGuessed)
        {
            SubRound s;
            PlayerPtr player1 = std::make_shared<Player>("Player1", PlayerRole::Guesser, 0);
            PlayerPtr player2 = std::make_shared<Player>("Player2", PlayerRole::Guesser, 0);
            PlayerPtr player3 = std::make_shared<Player>("Player3", PlayerRole::Guesser, 0);

            player1->SetSecond(30);
            player2->SetSecond(50);
            player3->SetSecond(10);

            std::vector<PlayerPtr> players = { player1, player2, player3 };

            int result = s.CalculatePainterScore(players);

            Assert::AreEqual(50, result);
        }
    };
}
