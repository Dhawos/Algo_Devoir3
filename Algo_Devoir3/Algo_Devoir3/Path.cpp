#include "stdafx.h"
#include "Path.h"
#include "InvalidEdgeException.h"
using std::stoi;

Path::Path(int size)
{
	this->weight = 0;
	this->path = vector<State*>();
	this->occurences = vector<int>(size, 0);
}

Path::Path(const Path & path)
{
	this->weight = path.weight;
	this->path = path.path;
	this->occurences = path.occurences;
}

Path::~Path()
{
}

void Path::pushState(State * newState)
{
	this->path.push_back(newState);
	if (path.size() > 1) {
		for (Edge edge : newState->getEdges()) {
			if (edge.getOutState()->getId() == path[path.size()-2]->getId()) {
				weight += edge.getWeight();
				if (edge.getTransition() != "") {
					int index = stoi(edge.getTransition()) - 1;
					occurences[index]++;
				}
			}
		}
	}
}

void Path::push_frontState(State * newState)
{
	this->path.insert(this->path.begin(),newState);
	if(path.size() > 1){
		for (Edge edge : path[1]->getEdges()) {
			if (edge.getOutState()->getId() == newState->getId()) {
				weight += edge.getWeight();
				if (edge.getTransition() != "") {
					int index = stoi(edge.getTransition()) - 1;
					occurences[index]++;
				}
			}
		}
	}
}

int Path::getWeight()
{
	return this->weight;
}

int Path::getLength()
{
	return this->path.size();
}

/*
vector<State*> Path::getPath()
{
	return this->getPath;
}
*/

void Path::operator=(const Path & p)
{
	this->weight = p.weight;
	this->path = p.path;
	this->occurences = p.occurences;
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
		for (int i = pathToPrint.path.size()-2; i > 1; i--) {
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
