#pragma once
#include <memory>
#include <string>
using std::string;
using std::shared_ptr;
class State;

class Edge
{
private:
	State* outState;
	string transition;
	int weight;
public:
	Edge(State* outState, string transition, int weight);
	Edge(const Edge &edge);
	virtual ~Edge();
	State* getOutState() const;
	string getTransition() const;
	int getWeight() const;
};

