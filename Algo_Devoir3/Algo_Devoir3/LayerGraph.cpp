#include "stdafx.h"
#include "LayerGraph.h"
#include "Edge.h"
#include <vector>
using std::vector;


LayerGraph::LayerGraph(int firstStateId)
{
	vector<Edge> edges = vector<Edge>();
	//Edge edge = Edge(0, firstStateId, 0);
	//edges.push_back(edge);
	this->sourceState = shared_ptr<State>(new State(0,edges,false));
	this->finalState = shared_ptr<State>(new State(-1, vector<Edge>(), true));
	this->states = vector<shared_ptr<State>>();
}

void LayerGraph::addState(shared_ptr<State> state)
{
	this->states.push_back(state);
}

void LayerGraph::removeState(shared_ptr<State> state)
{
	vector<shared_ptr<State>>::iterator it;
	for (it = this->states.begin(); it != this->states.end(); ++it) {
		if (*it == state) {
			break;
		}
	}
	this->states.erase(it);
}


LayerGraph::~LayerGraph()
{
}
