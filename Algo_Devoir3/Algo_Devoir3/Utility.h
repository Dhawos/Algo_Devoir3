#pragma once
#include <vector>
class Utility
{
public:
	static std::vector<std::string> split(const std::string &s, char delim);
private:
	Utility();
	~Utility();
};

