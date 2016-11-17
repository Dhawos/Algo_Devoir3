#pragma once
#include <vector>
#include "State.h"
#include <memory>
using std::vector;
using std::shared_ptr;
class AFDGraph
{
private:
	vector<State> states;
	int startStateId;
public:
	AFDGraph();
	void createAndInsertState(int id, bool final, bool start);
	State &getState(int index);
	State &getStartState();
	//State &getState(const State &state);
	const vector<State> &getStates() const;
	virtual ~AFDGraph();
};

