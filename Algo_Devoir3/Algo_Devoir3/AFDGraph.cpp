#include "stdafx.h"
#include "AFDGraph.h"
#include "NotFoundException.h"

AFDGraph::AFDGraph()
{
	this->startStateId = -1;
	this->states = vector<State>();
}

void AFDGraph::createAndInsertState(int id, bool final, bool start)
{
	State newState = State(id, final);
	this->states.push_back(newState);
	if (start) {
		this->startStateId = id;
	}
}

State & AFDGraph::getState(int id)
{
	vector<State>::iterator it;
	for (it = this->states.begin(); it != this->states.end(); ++it) {
		if (it->getId() == id) {
			break;
		}
	}
	return *it; 
}

State & AFDGraph::getStartState()
{
	vector<State>::iterator it;
	for (it = this->states.begin(); it != this->states.end(); ++it) {
		if (it->getId() == this->startStateId) {
			return *it;
		}
	}
	throw NotFoundException();
}

State & AFDGraph::getState(const State & state)
{
	vector<State>::iterator it;
	for (it = this->states.begin(); it != this->states.end(); ++it) {
		if (*it == state) {
			break;
		}
	}
	throw NotFoundException();
}

const vector<State>& AFDGraph::getStates() const
{
	return this->states;
}


AFDGraph::~AFDGraph()
{
}
