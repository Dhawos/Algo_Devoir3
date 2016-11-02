#pragma once
#include "State.h"
#include <memory>
using std::shared_ptr;

class LayerGraph
{
private:
	shared_ptr<State> sourceState;
	shared_ptr<State> finalState;
	vector<shared_ptr<State>> states;
public:
	LayerGraph(int firstStateId);
	void addState(shared_ptr<State> state);
	void removeState(shared_ptr<State> state);
	virtual ~LayerGraph();
};

