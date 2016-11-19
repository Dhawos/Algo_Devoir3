#pragma once
#include <memory>

using std::shared_ptr;
class State;
class DijkstraNodeState
{
private:
	bool set;
	int cost;
	bool closed;
	State* pred;
public:
	DijkstraNodeState();
	DijkstraNodeState(int cost, bool closed, State* pred);
	//Getters
	int getCost() const;
	bool isClosed() const;
	State* getPredecessor() const;
	//Setters
	
	void setCost(int cost);
	void setClosed(bool closed);
	void setPredecessor(State* pred);
	
	void setNodeState(int cost, bool closed, State* pred);
	void reset();
	//Others
	bool isSet();
};

