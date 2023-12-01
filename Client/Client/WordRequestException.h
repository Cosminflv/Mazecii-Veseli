#pragma once

#include "ClientException.h"

class WordRequestException : ClientException
{
public:
	WordRequestException(const std::string&);
};
