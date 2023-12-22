#pragma once
#include "ClientException.h"
class ChatRequestException :
    public ClientException
{
public:
    ChatRequestException(const std::string&);
};

