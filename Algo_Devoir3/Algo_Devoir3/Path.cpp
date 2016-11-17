#include "stdafx.h"
#include "Path.h"
#include "InvalidEdgeException.h"


Path::Path()
{
	this->weight = 0;
	this->path = vector<const State*>();
}


Path::~Path()
{
}

void Path::pushState(const State * newState)
{
	bool isLegal = false;
	if (this->path.empty()) {
		isLegal = true;
	}
	if (!isLegal) {
		for (Edge edge : this->path[this->path.size() - 1]->getEdges()) {
			if (edge.getOutState()->compareIds(*newState)) {
				isLegal = true;
				this->weight += edge.getWeight();
			}
		}
	}
	if (isLegal) {
		this->path.push_back(newState);
	}
	else {
		throw InvalidEdgeException();
	}
}

void Path::pushState(shared_ptr<State> state)
{
	this->path.insert(path.begin(), state.get());
}

int Path::getWeight()
{
	return this->weight;
}

int Path::getLength()
{
	return this->path.size();
}

bool Path::operator==(const Path & p) const
{
	return this->weight == p.weight;
}

bool Path::operator<=(const Path & p) const
{
	return this->weight <= p.weight;
}

bool Path::operator>=(const Path & p) const
{
	return this->weight >= p.weight;
}

bool Path::operator<(const Path & p) const
{
	return this->weight < p.weight;
}

bool Path::operator>(const Path & p) const
{
	return this->weight > p.weight;
}
