#include "stdafx.h"
#include "Utility.h"
#include <fstream>
#include <sstream>
using std::getline;
using std::string;
using std::ifstream;

std::vector<std::string> Utility::split(const std::string &s, char delim) {
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
		// elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
	}
	return elems;

}

Utility::Utility()
{
}


Utility::~Utility()
{
}
