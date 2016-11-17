#include "stdafx.h"
#include "DijkstraNodeState.h"
#include "State.h"
#include <exception>
DijkstraNodeState::DijkstraNodeState()
{
	this->set = false;
}

DijkstraNodeState::DijkstraNodeState(int cost, bool closed, shared_ptr<State> pred)
{
	this->cost = cost;
	this->closed = closed;
	this->pred = pred;
}

DijkstraNodeState::~DijkstraNodeState()
{
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

shared_ptr<State> DijkstraNodeState::getPredecessor() const
{
	if (set) {
		return pred;
	}
	else {
		throw std::exception();
	}
}
void DijkstraNodeState::setNodeState(int cost, bool closed, shared_ptr<State> pred)
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

void DijkstraNodeState::setPredecessor(shared_ptr<State> pred)
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

