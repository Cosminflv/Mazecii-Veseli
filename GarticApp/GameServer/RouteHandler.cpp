#include "RouteHandler.h"

RouteHandler::RouteHandler()
{
}

RouteHandler::RouteHandler(const SubRound& subRound) : m_subRound{ subRound }
{
}

bool RouteHandler::checkEnteredMessage(const std::string& message)
{
    return m_subRound.GuessWord(message);
}
