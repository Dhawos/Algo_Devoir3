#include "stdafx.h"
#include "Edge.h"
#include "State.h"

Edge::Edge(State* outState, string transition, int weight) : outState(outState)
{
	this->outState = outState;
	this->transition = transition;
	this->weight = weight;
}

Edge::Edge(const Edge & edge) : outState(edge.outState)
{
	this->outState = edge.getOutState();
	this->transition = edge.getTransition();
	this->weight = edge.getWeight();
}

State* Edge::getOutState() const
{
	return this->outState;
}

string Edge::getTransition() const
{
	return this->transition;
}

int Edge::getWeight() const
{
	return this->weight;
}


Edge::~Edge()
{
}