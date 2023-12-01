#pragma once

#include <stdexcept>

class ClientException : public std::logic_error
{
public:
	ClientException();
	ClientException(const std::string&);
};
