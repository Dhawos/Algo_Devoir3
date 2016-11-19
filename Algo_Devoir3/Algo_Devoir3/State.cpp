#include "stdafx.h"
#include "State.h"


State::State()
{
	this->nodeState = DijkstraNodeState();
}

State::State(int id, vector<Edge> outEdges, bool final)
{
	this->nodeState = DijkstraNodeState();
	this->id = id;
	this->outEdges = outEdges;
	this->final = final;
}

State::State(int id, bool final)
{
	this->nodeState = DijkstraNodeState();
	this->id = id;
	this->outEdges = vector<Edge>();
	this->final = final;
}

int State::getId() const
{
	return this->id;
}

int State::getNbOutEdges()
{
	return this->outEdges.size();
}

void State::addEdge(Edge edge)
{
	this->outEdges.push_back(Edge(edge));
}

void State::addEdge(State* outState, string transition, int weight)
{
	Edge newEdge = Edge(outState, transition, weight);
	this->outEdges.push_back(newEdge);
}

Edge State::getEdge(int i)
{
	return this->outEdges[i];
}

DijkstraNodeState & State::getNodeState()
{
	return this->nodeState;
}

const vector<Edge>& State::getEdges() const
{
	return this->outEdges;
}

bool State::isFinal() const
{
	return this->final;
}

bool State::compareIds(State const & s1) const
{
	return this->getId() == s1.getId();
}

State::~State()
{
}

bool const State::operator==(State & s1)
{
	return this->getNodeState().getCost() == s1.getNodeState().getCost();
}

bool const State::operator<(State & s1)
{
	return this->getNodeState().getCost() < s1.getNodeState().getCost();
}

bool const State::operator>(State & s1)
{
	return this->getNodeState().getCost() > s1.getNodeState().getCost();
}

bool const State::operator>=(State & s1)
{
	return this->getNodeState().getCost() >= s1.getNodeState().getCost();
}