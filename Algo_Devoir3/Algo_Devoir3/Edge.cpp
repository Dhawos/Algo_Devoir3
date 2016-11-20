#include "stdafx.h"
#include "Edge.h"
#include "State.h"

Edge::Edge(State* outState, string transition, int weight)
{
	this->outState = outState;
	this->transition = transition;
	this->weight = weight;
	this->deleted = false;
}

Edge::Edge(const Edge & edge)
{
	this->outState = edge.getOutState();
	this->transition = edge.getTransition();
	this->weight = edge.getWeight();
	this->deleted = edge.deleted;
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

bool Edge::isDeleted()
{
	return deleted;
}

void Edge::markDeleted()
{
	deleted = true;
}

bool const Edge::operator==(Edge & e1)
{
	return this->outState == e1.outState && this->transition == e1.transition && this->weight == e1.weight;
}


Edge::~Edge()
{
}