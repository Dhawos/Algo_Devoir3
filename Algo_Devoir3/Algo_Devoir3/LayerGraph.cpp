#include "stdafx.h"
#include "LayerGraph.h"
#include "Edge.h"
#include <vector>
#include <algorithm>
#include <queue>
using std::vector;
using std::find;
using std::push_heap;
using std::pop_heap;
using std::make_heap;
using std::stoi;

bool compare(State* a, State* b)
{
	return (*a>*b);
}

LayerGraph::LayerGraph(AFDGraph graph, int wordLength, vector<int> maximums, vector<int> minimums)
{
	this->maximums = maximums;
	this->minimums = minimums;
	this->layers = vector<vector<State>>();
	//Initialiazing first layer
	this->layers.push_back(vector<State>());
	for (State state : graph.getStates()) {
		State newState = State(state.getId(),false);
		this->layers[0].push_back(newState);
	}
	vector<State>::iterator it;
	for (it = this->layers[0].begin(); it != this->layers[0].end(); ++it) {
		if (it->getId() == graph.getStartState().getId()) {
			break;
		}
	}
	//Initializing firstState
	vector<Edge> edges = vector<Edge>();
	Edge edge = Edge(&*it, "", 0);
	edges.push_back(edge);
	this->sourceState = State(-1, edges, false);
	//Initializing middle layers
	for (int i = 1; i <= wordLength; i++) {
		this->layers.push_back(vector<State>());
		for (State state : graph.getStates()) {
			State newState = State(state.getId(), false);
			this->layers[i].push_back(newState);
		}
		//Now linking i-1 layer states to their outStates in layer i
		for (State& state : this->layers[i-1]) {
			//Retrieving corresponding state in AFDGraph
			State stateInAFDGraph = graph.getState(state.getId());
			for (Edge edge : stateInAFDGraph.getEdges()) {
				int idToLink = edge.getOutState()->getId();
				for (it = this->layers[i].begin(); it != this->layers[i].end(); ++it) {
					if (it->getId() == edge.getOutState()->getId()) {
						break;
					}
				}
				state.addEdge(&*it , edge.getTransition(), edge.getWeight());
			}
		}
	}
	//Initializing finalState
	this->finalState = State(-2,true);
	//Linking all final states in the AFDGraph to the final State of the layer Graph
	for (State& state : this->layers[this->layers.size()-1]) {
		if (graph.getState(state.getId()).isFinal()) {
			Edge newEdge = Edge(&this->finalState, "", 0);
			state.addEdge(newEdge);
		}
	}
}

LayerGraph::~LayerGraph()
{
}

Path LayerGraph::Dijkstra()
{
	if (this->finalState.getNodeState().isSet()) {
		return getOptimalPath();
	}
	else {
		bool goalReached = propagateStates(this->sourceState, this->finalState);
		if (goalReached) {
			return getOptimalPath();
		}
		else {
			return Path();
		}
	}
}

bool LayerGraph::propagateStates(State& start, State& goal)
{
	vector<State *> heap = vector<State *>();
	make_heap(heap.begin(), heap.end(),compare);
	State* currentState = NULL;
	heap.push_back(&start);
	push_heap(heap.begin(), heap.end(),compare);
	int trialCost = 0;
	while (!heap.empty() && (currentState == NULL || currentState->getId() != goal.getId())) {
		pop_heap(heap.begin(), heap.end(),compare);
		currentState = heap.back();
		heap.pop_back();
		currentState->getNodeState().setClosed(true);
		for (Edge edge : currentState->getEdges()) {
			trialCost = currentState->getNodeState().getCost() + edge.getWeight();
			State* outState = edge.getOutState();
			if (outState->getNodeState().isSet()) {
				if (!edge.getOutState()->getNodeState().isClosed() && trialCost < edge.getOutState()->getNodeState().getCost()) {
					vector<State *>::iterator it;
					for (it = heap.begin(); it != heap.end(); ++it) {
						if ((*it)->getId() == outState->getId()) {
							break;
						}
					}
					(*it)->getNodeState().setCost(trialCost);
					outState->getNodeState().setPredecessor(currentState);
					outState->getNodeState().setCost(trialCost);
					make_heap(heap.begin(), heap.end(), compare);
				}
			}
			else {
				outState->getNodeState().setNodeState(trialCost, false, currentState);
				if (checkConstraints(outState)) {
					heap.push_back(outState);
					push_heap(heap.begin(), heap.end(), compare);
				}
			}
		}
	}
	return currentState->getId() == goal.getId();
}

Path LayerGraph::getOptimalPath()
{
	State* currentState = &this->finalState;
	Path path = Path();
	while (currentState->getId() != sourceState.getId()) {
		path.pushState(currentState);
		currentState = currentState->getNodeState().getPredecessor();
	}
	path.pushState(&sourceState);
	return path;
}

bool LayerGraph::checkConstraints(State * state)
{
	vector<int> occurences = vector<int>(maximums.size(),0);
	State* currentState = state;
	while (!(*currentState == sourceState)) {
		State* previousState = currentState->getNodeState().getPredecessor();
		for (Edge edge : previousState->getEdges()) {
			if (edge.getOutState() == currentState && edge.getTransition() != "") {
				int index = stoi(edge.getTransition()) - 1;
				occurences[index]++;
			}
		}
		currentState = previousState;
	}
	for (int i = 0; i < occurences.size(); i++) {
		if (/*occurences[i] < minimums[i] || */occurences[i] > maximums[i]) {
			return false;
		}
	}
	return true;
}

bool LayerGraph::isStateFinal(const State & state)
{
	for (Edge edge : state.getEdges()) {
		if (edge.getOutState()->isFinal()) {
			return true;
		}
	}
	return false;
}
