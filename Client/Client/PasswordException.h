#pragma once
#include "ClientException.h"
class PasswordException : ClientException
{
public:
	PasswordException(const std::string&);
};

