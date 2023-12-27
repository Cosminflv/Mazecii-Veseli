#include "Game.h"
#include "Player.h"
#include "Round.h"
#include <map>
#include <set>

Game::Game(std::vector<PlayerPtr> players, std::map<PlayerPtr, int> leaderboard) :
	m_players{ players },
	m_leaderboard{ leaderboard }
{
	m_gameChat.WriteMessage({ "Server", "Hello" });
	m_gameStatus = EGameStatus::Lobby;
}

Game::Game()
{
	RoundPtr newRound = std::make_shared<Round>();
	m_currRound = newRound;
	m_gameChat.WriteMessage({ "Server", "Hello" });
	m_gameStatus = EGameStatus::Lobby;
}


std::vector<PlayerPtr> Game::GetPlayers() const
{
	return m_players;
}

RoundPtr Game::GetRound() const
{
	if (m_currRound != nullptr)
		return m_currRound;
	return nullptr;
}

Chat& Game::GetChat() const
{
	return m_gameChat;
}

EGameStatus Game::GetGameStatus() const
{
	return m_gameStatus;
}

std::string Game::GetGameStatusAsString() const
{

	return m_gameStatus == EGameStatus::Lobby ? "Lobby" : "Playing";
}

bool Game::CheckUniquePlayerUsername(PlayerPtr player) const
{
	std::set<std::string> setOfUsernames;

	for (auto player : m_players)
	{
		setOfUsernames.insert(player->GetUsername());
	}

	return setOfUsernames.find(player->GetUsername()) != setOfUsernames.end() ? false : true;
}

std::map<PlayerPtr, int>Game::GetLeaderboard() const
{
	return m_leaderboard;
}

void Game::CreateRound(const std::vector<PlayerPtr>& players)
{
	RoundPtr newRound = std::make_shared<Round>(players);

	m_currRound = newRound;
}

void Game::PlayRound()
{

}

void Game::StartGame()
{
	m_gameStatus = EGameStatus::Playing;
}

void Game::EndGame()
{
	std::cout << "Jocul s-a incheiat!\n";
	//afisare clasament
	std::string choice;
	std::cout << "Doriti sa reluati jocul? (Da/Nu): ";
	std::cin >> choice;

	if (choice == "Da") {
		ResetGame();
		StartGame();
	}
	else {
		std::cout << "Jocul s-a incheiat.\n";
	}
}

void Game::ResetGame()
{
	for (PlayerPtr player : m_players)
		player->SetScore(0);
	m_currRound = RoundPtr();
}

void Game::UpdateLeaderboard()
{
	m_leaderboard.clear();
	for (PlayerPtr player : m_players) {
		int roundScore = player->GetScore();
		m_leaderboard[player] += roundScore;
	}
}
void Game::AddPlayer(PlayerPtr player)
{
	m_players.size() == 0 ? player.get()->SetAdminRole(AdminRole::Admin) : player.get()->SetAdminRole(AdminRole::NonAdmin);

	m_players.push_back(player);
}

Game::~Game()
{
	m_players.clear();
	m_leaderboard.clear();
}
