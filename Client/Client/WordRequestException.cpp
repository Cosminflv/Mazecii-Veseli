#include "WordRequestException.h"

WordRequestException::WordRequestException(const std::string& message) : ClientException(message)
{
}
