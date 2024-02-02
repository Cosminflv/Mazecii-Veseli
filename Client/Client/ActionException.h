#pragma once
#include "ClientException.h"

class ActionException :   public ClientException
{
public:
	ActionException(const std::string& exp);
};

