#pragma once
#include <exception>
class NotFoundException :
	public std::exception
{
public:
	NotFoundException();
	virtual ~NotFoundException();
};

