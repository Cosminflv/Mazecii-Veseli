#include "RouteHandler.h"

RouteHandler::RouteHandler()
{
}

RouteHandler::RouteHandler(const Game& game) : m_game{ game }
{
}

bool RouteHandler::checkEnteredMessage(const std::string& message)
{
    RoundPtr round = m_game.GetRound();
    SubRoundPtr subround = round.get()->GetSubround();
    return subround->GuessWord(message);
}

void RouteHandler::addPlayer(PlayerPtr newPlayer)
{
    m_game.AddPlayer(newPlayer);
}
