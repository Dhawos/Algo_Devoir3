#include "stdafx.h"
#include "Path.h"
#include "InvalidEdgeException.h"


Path::Path()
{
	this->weight = 0;
	this->path = vector<State*>();
}

Path::~Path()
{
}

void Path::pushState(State * newState)
{
	this->path.push_back(newState);
	weight = this->path[0]->getNodeState().getCost();
	
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

ostream & operator<<(ostream & ostr, Path & pathToPrint)
{
	{
		vector<State *>::reverse_iterator it;
		for (it = pathToPrint.path.rbegin(); it != pathToPrint.path.rend(); ++it) {
			if ((*it)->getId() == -1) {
				ostr << "Debut" << " - ";
			}
			else if ((*it)->getId() == -2) {
				ostr << "Fin";
			}
			else {
				ostr << (*it)->getId() << " - ";
			}
		}
		ostr << " | Cout total : " << pathToPrint.weight << std::endl;
		ostr << "Mot trouve : ";
		for (int i = pathToPrint.path.size()-2; i >= 1; i--) {
			string letter;
			State* currentState = pathToPrint.path[i];
			State* nextState = pathToPrint.path[i - 1];
			for (Edge edge : currentState->getEdges()) {
				if (edge.getOutState() == nextState) {
					letter = edge.getTransition();
				}
			}
			ostr << letter;
		}
		return (ostr);
	}
}
