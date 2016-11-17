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
	shared_ptr<State> pred;
public:
	DijkstraNodeState();
	DijkstraNodeState(int cost, bool closed, shared_ptr<State> pred);
	virtual ~DijkstraNodeState();
	//Getters
	int getCost() const;
	bool isClosed() const;
	shared_ptr<State> getPredecessor() const;
	//Setters
	
	void setCost(int cost);
	void setClosed(bool closed);
	void setPredecessor(shared_ptr<State> pred);
	
	void setNodeState(int cost, bool closed, shared_ptr<State> pred);
	void reset();
	//Others
	bool isSet();
};

