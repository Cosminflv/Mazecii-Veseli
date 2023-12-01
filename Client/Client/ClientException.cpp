#include "ClientException.h"

ClientException::ClientException(const std::string& message)
	: std::logic_error(message)
{
}

ClientException::ClientException()
	: std::logic_error("Unknown exception")
{
}