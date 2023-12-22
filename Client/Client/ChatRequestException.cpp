#include "ChatRequestException.h"

ChatRequestException::ChatRequestException(const std::string& message) : ClientException(message)
{
}