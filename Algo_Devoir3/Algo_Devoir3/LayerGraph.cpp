#include "stdafx.h"
#include "LayerGraph.h"
#include "Edge.h"
#include <vector>
#include <algorithm>
#include <set>
using std::vector;
using std::find;
using std::push_heap;
using std::pop_heap;
using std::make_heap;
using std::stoi;
using std::set;
using std::pair;

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
			return Path(maximums.size());
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
		State* outState = NULL;
		for (Edge edge : currentState->getEdges()) {
			if(!edge.isDeleted()){
				trialCost = currentState->getNodeState().getCost() + edge.getWeight();
				outState = edge.getOutState();
				if (outState->getNodeState().isSet()) {
					if (!edge.getOutState()->getNodeState().isClosed() && trialCost < edge.getOutState()->getNodeState().getCost()) {
						vector<State *>::iterator it;
						for (it = heap.begin(); it != heap.end(); ++it) {
							if ((*it)->getId() == outState->getId()) {
								break;							}
							}
						(*it)->getNodeState().setCost(trialCost);
						outState->getNodeState().setPredecessor(currentState);
						outState->getNodeState().setCost(trialCost);
						make_heap(heap.begin(), heap.end(), compare);
					}
				}
				else {
					if (outState != NULL) {
						Path path = Path(maximums.size());
						State* cState = currentState;
						path.pushState(outState);
						while (cState->getId() != sourceState.getId()) {
							path.pushState(cState);
							cState = cState->getNodeState().getPredecessor();
						}
						path.pushState(&sourceState);
						if (canPathBeLegal(path)) {
							outState->getNodeState().setNodeState(trialCost, false, currentState);
							heap.push_back(outState);
							push_heap(heap.begin(), heap.end(), compare);
						}
					}
				}
			}
		}
	}
	return currentState->getId() == goal.getId();
}

Path LayerGraph::getOptimalPath()
{
	State* currentState = &this->finalState;
	Path path = Path(maximums.size());
	while (currentState->getId() != sourceState.getId()) {
		path.pushState(currentState);
		currentState = currentState->getNodeState().getPredecessor();
	}
	path.pushState(&sourceState);
	return path;
}

bool LayerGraph::checkConstraints(Path& path)
{
	for (int i = 0; i < path.occurences.size(); i++) {
		if (path.occurences[i] < minimums[i] || path.occurences[i] > maximums[i]) {
			return false;
		}
	}
	return true;
}

bool LayerGraph::isStateFinal(State & state)
{
	for (Edge edge : state.getEdges()) {
		if (!edge.isDeleted()) {
			if (edge.getOutState()->isFinal()) {
				return true;
			}
		}
	}
	return false;
}

bool LayerGraph::canPathBeLegal(Path path)
{
	State* lastState = path.path[0];
	if (lastState->isFinal()) {
		return checkConstraints(path);
	}
	else {
		for (int i = 0; i < path.occurences.size(); i++) {
			if (path.occurences[i] > maximums[i]) {
				return false;
			}
		}
		bool legality = false;
		for (Edge edge : lastState->getEdges()) {
			Path newPath = Path(path);
			newPath.push_frontState(edge.getOutState());
			if (canPathBeLegal(newPath)) {
				legality = true;
				break;
			}
		}
		return legality;
	}
}

vector<Path> LayerGraph::getLegalPaths()
{
	Path path = Path(maximums.size());
	path.push_frontState(&sourceState);
	vector<Path> paths = vector<Path>();
	recGetLegalPaths(&sourceState,path,paths);
	this->legalpaths = paths;
	return paths;
}

void LayerGraph::recGetLegalPaths(State* currentState, Path path, vector<Path>& paths)
{
	if (currentState->isFinal()) {
		if (checkConstraints(path)) {
			paths.push_back(path);
		}
	}
	else {
		for (Edge edge : currentState->getEdges()) {
			if (!edge.isDeleted()) {
				Path newPath = path;
				newPath.push_frontState(edge.getOutState());
				bool isStillValid = true;
				for (int i = 0; i < newPath.occurences.size(); i++) {//Enforcing maximums to avoid spending time on useless paths
					if (newPath.occurences[i] > maximums[i]) {
						isStillValid = false;
					}
				}
				if (isStillValid) {
					recGetLegalPaths(edge.getOutState(), newPath, paths);
				}
			}
		}
	}
}

void LayerGraph::removeIllegalEdges()
{
	vector<Path> paths = getLegalPaths();
	set<Edge*> legalEdges;
	for (Path currentPath : paths) {
		for (int i = currentPath.path.size() - 2; i > 0; i--) {
			State* currentState = currentPath.path[i];
			State* nextState = currentPath.path[i - 1];
			Edge* edge = NULL;
			for (int j = 0; j < currentState->getEdges().size(); j++) {
				edge = &(currentState->getEdges()[j]);
				if (!edge->isDeleted()) {
					if (edge->getOutState() == nextState) {
						legalEdges.insert(edge);
					}
				}
			}
		}
	}
	Edge* edge = NULL;
	//Removing all illegal edges from layers
	for (vector<State>& layer : layers) {
		for (State& currentState : layer) {
			for (int j = 0; j < currentState.getEdges().size(); j++) {
				edge = &(currentState.getEdges()[j]);
				if (!edge->isDeleted()){
					if (legalEdges.find(edge) == legalEdges.end()) {
						currentState.removeEdge(*edge);
					}
				}
			}
		}
	}
}

