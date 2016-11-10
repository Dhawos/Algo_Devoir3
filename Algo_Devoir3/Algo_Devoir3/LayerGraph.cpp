#include "stdafx.h"
#include "LayerGraph.h"
#include "Edge.h"
#include <vector>
using std::vector;


LayerGraph::LayerGraph(AFDGraph graph, int wordLength)
{
	this->layers = vector<vector<State>>();
	//Initializing firstState
	vector<Edge> edges = vector<Edge>();
	Edge edge = Edge(&graph.getStartState(), "", 0);
	edges.push_back(edge);
	this->sourceState = State(-1, edges, false);
	//Initialiazing first layer
	this->layers.push_back(vector<State>());
	for (State state : graph.getStates()) {
		State newState = State(state.getId(),state.isFinal());
		this->layers[0].push_back(newState);
	}
	//Initializing middle layers
	for (int i = 1; i < wordLength; i++) {
		this->layers.push_back(vector<State>());
		for (State state : graph.getStates()) {
			State newState = State(state.getId(), state.isFinal());
			this->layers[i].push_back(newState);
		}
		//Now linking i-1 layer states to their outStates in layer i
		for (State state : this->layers[i-1]) {
			//Retrieving corresponding state in AFDGraph
			State stateInAFDGraph = graph.getState(state.getId());
			for (Edge edge : stateInAFDGraph.getEdges()) {
				int idToLink = edge.getOutState()->getId();
				state.addEdge(edge.getOutState(), edge.getTransition(), edge.getWeight());
			}
		}
	}
	//Initializing finalState
	this->finalState = State(-2,true);
	//Linking all final states in the AFDGraph to the final State of the layer Graph
	for (State state : this->layers[this->layers.size()-1]) {
		if (state.isFinal()) {
			Edge newEdge = Edge(&this->finalState, "", 0);
		}
	}
}

LayerGraph::~LayerGraph()
{
}
