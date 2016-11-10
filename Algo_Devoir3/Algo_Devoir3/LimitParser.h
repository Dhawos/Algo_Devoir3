#pragma once
#include <string>
#include "LayerGraph.h"

class LimitParser
{
private:
	string filename;
	const AFDGraph & graph;
public:
	LimitParser(string filename,const AFDGraph & graph);
	shared_ptr<LayerGraph> parseFile();
	virtual ~LimitParser();

};

