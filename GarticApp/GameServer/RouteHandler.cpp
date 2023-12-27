#include "RouteHandler.h"

RouteHandler::RouteHandler()
{
}

RouteHandler::RouteHandler(const Game& game) : m_game{ game }
{
}

bool RouteHandler::CheckEnteredMessage(const std::string& message)
{
    RoundPtr round = m_game.GetRound();
    SubRoundPtr subround = round->GetSubround();
    return subround->GuessWord(message);
}

void RouteHandler::AddPlayer(const std::string& username)
{
    PlayerPtr newPlayer = std::make_shared<Player>(username, PlayerRole::Guesser, 0);
    m_game.AddPlayer(newPlayer);
}

void RouteHandler::WriteMessage(const std::string& username, const std::string& message)
{
    m_game.GetChat().WriteMessage({ username, message});
}

std::string RouteHandler::PickWord(uint16_t difficulty)
{
    return m_game.GetRound()->GetSubround()->SelectRandomWord(difficulty);
}

std::string RouteHandler::HideTheWord(std::string word)
{
    return m_game.GetRound()->GetSubround()->HideWord(word);
}

