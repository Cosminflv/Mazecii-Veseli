#include "RouteHandler.h"
#include <ranges>

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

std::vector<PlayerPtr> RouteHandler::GetLoggedInUsers()
{
    return m_loggedInUsers;
}

std::optional<PlayerPtr> RouteHandler::GetPlayerWithUsername(const std::string& username)
{
    auto it = std::ranges::find_if(m_loggedInUsers, [&](const PlayerPtr player)
        {
            return player->GetUsername() == username;
        });
 
    return (it != m_loggedInUsers.end()) ? std::make_optional(*it) : std::nullopt;
}

bool RouteHandler::CheckEnteredMessage(const std::string_view& message)
{
    RoundPtr round = m_game->GetRound();
    SubRoundPtr subround = round->GetSubround();
    return subround->GuessWord(message);
}

void RouteHandler::AddLoggedInUsers(const std::string& username)
{
    PlayerPtr newUser;
    if (m_loggedInUsers.size() == 0)
    {
        newUser = std::make_shared<Player>(username, AdminRole::NonAdmin, PlayerRole::Painter);
        m_game->AddPlayer(newUser);
    }
    else
    {
        newUser = std::make_shared<Player>(username, AdminRole::NonAdmin, PlayerRole::Guesser);
    }
    m_loggedInUsers.push_back(newUser);
}

void RouteHandler::AddPlayer(const std::string& username)
{
    std::optional<PlayerPtr> newPlayer = GetPlayerWithUsername(username);
    if (newPlayer.has_value())
    {
        m_game->AddPlayer(newPlayer.value());
    }
    else
    {
        std::cout << "\nPlayer not found.\n\n";
    }
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
            player->SetSecond(30 + (30 - remainingSeconds.count())); 
            player->AlreadyGuessed(false);
        }
    }

    if (T.IsTimeExpired())
    {
        for (const auto& player : players)
        {
            if (username == player->GetUsername())
            {
                player->SetScore(-50);
                player->SetSecond(60); // "60 va fi timpul alocat pentru jucatorii care nu au furnizat un raspuns corect" -> document Proiecte MC++, pentru a calcula scorul unui Painter         
            }
        }
    }
}