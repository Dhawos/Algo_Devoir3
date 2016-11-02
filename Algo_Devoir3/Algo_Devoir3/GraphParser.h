#pragma once
#include<string>
#include <memory>
#include "AFDGraph.h"
using std::shared_ptr;
using std::string;
class GraphParser
{
private:
	string filename;
public:
	GraphParser(string filename);
	shared_ptr<AFDGraph> parseFile();
	virtual ~GraphParser();
};

