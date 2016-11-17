#include "stdafx.h"
#include "LayerGraph.h"
#include "Edge.h"
#include <vector>
#include <algorithm>
using std::vector;
using std::find;


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
	bool goalReached = propagateStates(this->sourceState,this->finalState);
	if (goalReached) {
		return getOptimalPath();
	}
	else {
		//Handle error
	}
}

bool LayerGraph::propagateStates(State& start, State& goal)
{
	vector<shared_ptr<State>> heap = vector<shared_ptr<State>>();
	make_heap(heap.begin(), heap.end());
	shared_ptr<State> currentState = shared_ptr<State>(&start);
	int trialCost = 0;
	do {
		currentState->getNodeState().setClosed(true);
		for (Edge edge : currentState->getEdges()) {
			trialCost = currentState->getNodeState().getCost() + edge.getWeight();
			State* outState = edge.getOutState();
			if (outState->getNodeState().isSet()) {
				if (!edge.getOutState()->getNodeState().isClosed() && trialCost < edge.getOutState()->getNodeState().getCost()) {
					vector<shared_ptr<State>>::iterator it;
					for (it = heap.begin(); it != heap.end(); ++it) {
						if (it->get()->getId() == outState->getId()) {
							break;
						}
					}
					it->get()->getNodeState().setCost(trialCost);
					outState->getNodeState().setPredecessor(currentState);
					outState->getNodeState().setCost(trialCost);
				}
			}
			else {
				outState->getNodeState().setNodeState(trialCost, false, currentState);
				heap.push_back(shared_ptr<State>(outState));
				push_heap(heap.begin(), heap.end());
				sort_heap(heap.begin(), heap.end());
			}

		}

		pop_heap(heap.begin(), heap.end());
		currentState = heap.back();
		heap.pop_back();
		sort_heap(heap.begin(), heap.end());
	} while (!heap.empty() && currentState->getId() != goal.getId());
	return *currentState == goal;
}

Path LayerGraph::getOptimalPath()
{
	shared_ptr<State> currentState = shared_ptr<State>(&this->finalState);
	Path path = Path();
	while (currentState->getId() != sourceState.getId()) {
		path.pushState(currentState);
	}
	path.pushState(shared_ptr<State>(&sourceState));
	return path;
}


Path LayerGraph::getMinimumPath()
{
	Path currentPath = Path();
	Path bestPath = Path();
	int bestWeight = -1;
	for (Edge edge : this->sourceState.getEdges()) {
		recursiveGetMinimumPath(edge.getOutState(),currentPath, bestPath);
	}
	return bestPath;
}

Path LayerGraph::recursiveGetMinimumPath(const State* state, Path currentPath, Path& bestPath)
{
	if (isStateFinal(*state)) {
		currentPath.pushState(state);
		bestPath = currentPath;
		return currentPath;
	}
	for (Edge edge : state->getEdges()) {
		if (bestPath.getLength() == 0 || currentPath.getWeight() + edge.getWeight() < bestPath.getWeight()) {
			recursiveGetMinimumPath(edge.getOutState(), currentPath, bestPath);
		}
	}
	return bestPath;
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
