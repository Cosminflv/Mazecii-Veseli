#pragma once
#include "ClientException.h"
class LobbyRequestException : public ClientException
{
public:
	LobbyRequestException(const std::string&);
};

