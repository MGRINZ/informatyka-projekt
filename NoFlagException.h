#pragma once
#include <iostream>
#include <string>

using namespace std;

class NoFlagException : public exception
{
private:
	string msg;
public:
	NoFlagException(string name);
	const char* what() const throw();
};

