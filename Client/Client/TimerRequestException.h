#pragma once

#include "ClientException.h"

class TimerRequestException : ClientException
{
public:
	TimerRequestException(const std::string&);
};
