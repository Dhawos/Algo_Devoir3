#pragma once
#include "State.h"
#include "AFDGraph.h"
#include <memory>
using std::shared_ptr;

class LayerGraph
{
private:
	State sourceState;
	vector<vector<State>> layers;
	State finalState;
public:
	LayerGraph(AFDGraph graph, int wordLength);
	/*void addState(shared_ptr<State> state);
	void removeState(shared_ptr<State> state);*/
	virtual ~LayerGraph();
};

