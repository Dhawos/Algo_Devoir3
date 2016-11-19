#include "stdafx.h"
#include "DijkstraNodeState.h"
#include "State.h"
#include <exception>
DijkstraNodeState::DijkstraNodeState()
{
	this->set = false;
	this->cost = -1;
	this->closed = false;
	this->pred = NULL;
}

DijkstraNodeState::DijkstraNodeState(int cost, bool closed, State* pred)
{
	this->cost = cost;
	this->closed = closed;
	this->pred = pred;
}

int DijkstraNodeState::getCost() const
{
	if (set) {
		return this->cost;
	}
	else {
		throw std::exception();
	}
}

bool DijkstraNodeState::isClosed() const
{
	if (set) {
		return closed;
	}
	else {
		throw std::exception();
	}
}

State* DijkstraNodeState::getPredecessor() const
{
	if (set) {
		return pred;
	}
	else {
		throw std::exception();
	}
}
void DijkstraNodeState::setNodeState(int cost, bool closed, State* pred)
{
	set = true;
	this->cost = cost;
	this->closed = closed;
	this->pred = pred;
}

void DijkstraNodeState::setCost(int cost)
{
	this->set = true;
	this->cost = cost;
}

void DijkstraNodeState::setClosed(bool closed)
{
	this->set = true;
	this->closed = closed;
}

void DijkstraNodeState::setPredecessor(State* pred)
{
	this->set = true;
	this->pred = pred;
}

void DijkstraNodeState::reset()
{
	set = false;
}

bool DijkstraNodeState::isSet()
{
	return set;
}

