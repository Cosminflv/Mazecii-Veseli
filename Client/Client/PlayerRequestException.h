#pragma once

#include "ClientException.h"

class PlayerRequestException : public ClientException
{
public:
	PlayerRequestException(const std::string&);
};
