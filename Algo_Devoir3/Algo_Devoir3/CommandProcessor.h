#pragma once
#include <memory>
#include "LayerGraph.h"
using std::shared_ptr;
using std::string;
class CommandProcessor
{
private:
	shared_ptr<LayerGraph> layerGraph;
	bool& shouldExit;
public:
	CommandProcessor(shared_ptr<LayerGraph> layerGraph, bool &shouldExit);
	virtual ~CommandProcessor();
	void printHelp();
	void quit();
	void processCommand(string command);
	void findMinimumPath();
};

