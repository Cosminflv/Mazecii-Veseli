#include "PlayerRequestException.h"

PlayerRequestException::PlayerRequestException(const std::string& message) : ClientException(message)
{
}
