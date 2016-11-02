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
	const State &getState(int index) const;
	State &getState(int id);
	const State &getState(const State &state) const;
	virtual ~AFDGraph();
};

