#pragma once
#include <exception>
class InvalidEdgeException : public std::exception
{
public:
	InvalidEdgeException();
	~InvalidEdgeException();
};

