#include "NoFlagException.h"
#include <string>

NoFlagException::NoFlagException(string flagName)
{
	msg = "Flag " + flagName + " does not exists";
}

const char * NoFlagException::what() const throw()
{
	return msg.c_str();
}