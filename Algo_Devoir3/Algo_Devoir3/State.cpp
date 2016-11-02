#include "stdafx.h"
#include "State.h"


State::State(int id, vector<Edge> outEdges, bool final)
{
	this->id = id;
	this->outEdges = outEdges;
	this->final = final;
}

State::State(int id, bool final)
{
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

bool State::isFinal()
{
	return this->final;
}

State::~State()
{
	this->outEdges.clear();
}

bool const operator==(State const & s1, State const & s2)
{
	return s1.getId() == s2.getId();
}
