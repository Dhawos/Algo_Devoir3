#pragma once
#include <vector>
#include <memory>
#include "Edge.h"

using std::shared_ptr;
using std::vector;

class State
{
private:
	int id;
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
	void addEdge(const State* outState, string transition, int weight);
	Edge getEdge(int i);
	const vector<Edge> & getEdges();
	bool isFinal();
};

bool const operator==(State const &s1,State const &s2);
