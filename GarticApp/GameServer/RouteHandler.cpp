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
    SubRoundPtr subround = round.get()->GetSubround();
    return subround->GuessWord(message);
}

void RouteHandler::AddPlayer(PlayerPtr newPlayer)
{
    m_game.AddPlayer(newPlayer);
}

void RouteHandler::WriteMessage(const std::string& username, const std::string& message)
{
    m_game.GetChat().WriteMessage({ username, message});
}
