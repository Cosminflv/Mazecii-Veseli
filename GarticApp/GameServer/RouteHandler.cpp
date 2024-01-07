#include "RouteHandler.h"

RouteHandler::RouteHandler()
{
}

RouteHandler::RouteHandler(std::shared_ptr<Game> game) : m_game{ std::move(game) }
{
}

std::shared_ptr<Game> RouteHandler::GetGame()
{
    return m_game;
}

bool RouteHandler::CheckEnteredMessage(const std::string& message)
{
    RoundPtr round = m_game->GetRound();
    SubRoundPtr subround = round->GetSubround();
    return subround->GuessWord(message);
}

void RouteHandler::AddPlayer(const std::string& username)
{
    PlayerPtr newPlayer = std::make_shared<Player>(username, PlayerRole::Guesser, 0);
    m_game->AddPlayer(newPlayer);
}

void RouteHandler::WriteMessage(const std::string& username, const std::string& message)
{
    m_game->GetChat().WriteMessage({ username, message});
}

std::string RouteHandler::PickWord(uint16_t difficulty)
{
    return m_game->GetRound()->GetSubround()->SelectRandomWord(difficulty);
}

std::string RouteHandler::HideTheWord(std::string word)
{
    return m_game->GetRound()->GetSubround()->HideWord(word);
}

std::string RouteHandler::UpdateWord(std::string& seenWord, std::string &currentWord)
{
    return m_game->GetRound()->GetSubround()->UpdateWordWithLetters(seenWord, currentWord);
}

void RouteHandler::CalculateScoreForGuesser(const std::string& username, std::vector<PlayerPtr>players, Timer& T)
{
	std::chrono::seconds second = std::chrono::duration_cast<std::chrono::seconds>(T.GetRemainingTime());
	std::cout << username << " guessed at second: " << second << "\n";
	for (auto player : players)
	{
		if (username == player->GetUsername())
		{
			player->CalcultateScore(second);
			std::cout << "Scorul player-ului " << player->GetUsername() << ": " << player->GetScore() << "\n";
		}
	}
	if (T.IsTimeExpired())
	{
		std::cout << "true";
		for (auto player : players)
		{
			if (username == player->GetUsername())
			{
				player->SetScore(-50);
				std::cout << "Timp expirat. Scorulul player-ului " << player->GetUsername() << ": " << player->GetScore() << "\n";
			}
		}
	}
}

	//wonScore = subround.calculateScore(
	//totalScore = m_game.GetLeaderBoard()[username] + wonScore
	//update leaderboard m_game.UpdateLeaderBoard(username, totalScore)
	//toate wrappuite intr-o metoda din handler

