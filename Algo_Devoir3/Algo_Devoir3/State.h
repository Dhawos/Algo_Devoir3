#pragma once
#include <vector>
#include <memory>
#include "Edge.h"
#include "DijkstraNodeState.h"
using std::shared_ptr;
using std::vector;

class State
{
private:
	int id;
	DijkstraNodeState nodeState;
	vector<Edge> outEdges;
	bool final;
public:
	State();
	State(int id,vector<Edge> outEdges, bool final);
	State(int id, bool final);
	virtual ~State();
	int getId() const;
	int getNbOutEdges();
	void addEdge(Edge edge);
	void addEdge(State* outState, string transition, int weight);
	void removeEdge(Edge& edge);
	Edge getEdge(int i);
	DijkstraNodeState& getNodeState();
	vector<Edge> & getEdges();
	bool isFinal() const;
	bool compareIds(State const &s1) const;
	bool const operator==(State &s1);
	bool const operator>(State &s1);
	bool const operator<(State &s1);
	bool const operator>=(State &s1);
};


