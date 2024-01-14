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

bool RouteHandler::CheckEnteredMessage(const std::string_view& message)
{
    RoundPtr round = m_game->GetRound();
    SubRoundPtr subround = round->GetSubround();
    return subround->GuessWord(message);
}

void RouteHandler::AddPlayer(const std::string& username)
{
    PlayerPtr newPlayer;
    if (m_game->GetPlayers().size() == 0)
         newPlayer = std::make_shared<Player>(username, PlayerRole::Painter, 0);
    else
         newPlayer = std::make_shared<Player>(username, PlayerRole::Guesser, 0);
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

void RouteHandler::CalculateScoreForGuesser(const std::string& username, std::vector<PlayerPtr>& players, Timer& T)
{
    std::chrono::seconds remainingSeconds = std::chrono::duration_cast<std::chrono::seconds>(T.GetRemainingTime());
    std::cout << username << " guessed at second: " << remainingSeconds.count() << "\n";

    for (const auto& player : players)
    {
        if (username == player->GetUsername() && player->HasNotGuessedYet())
        {
            player->CalculateGuesserScore(remainingSeconds);
            player->SetSecond(30 + (30 - remainingSeconds.count())); // a ghicit la secunda 40 -> inseamna ca a ghicit in 20 de sec; second.count()=40; 30+(30-40)=30-10=20 secunde.
            player->AlreadyGuessed(false);
            std::cout << "Scorul player-ului " << player->GetUsername() << ": " << player->GetScore() << "\n";
        }
    }

    if (T.IsTimeExpired())
    {
        std::cout << "true";

        for (const auto& player : players)
        {
            if (username == player->GetUsername())
            {
                player->SetScore(-50);
                player->SetSecond(60); // "60 va fi timpul alocat pentru jucatorii care nu au furnizat un raspuns corect" -> document Proiecte MC++, pentru a calcula scorul unui Painter
                std::cout << "Timp expirat. Scorulul player-ului " << player->GetUsername() << ": " << player->GetScore() << "\n";
            }
        }
    }
}



