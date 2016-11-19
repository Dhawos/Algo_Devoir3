#pragma once
#include "State.h"
#include "AFDGraph.h"
#include <memory>
#include "Path.h"
using std::shared_ptr;

class LayerGraph
{
private:
	vector<int> maximums;
	vector<int> minimums;
	State sourceState;
	vector<vector<State>> layers;
	State finalState;
public:
	LayerGraph(AFDGraph graph, int wordLength, vector<int> maximums, vector<int> minimums);
	virtual ~LayerGraph();
	Path Dijkstra();
	bool propagateStates(State& start, State& goal);
	Path getOptimalPath();
	//Path getMinimumPath();
	//Path recursiveGetMinimumPath(const State* state,Path currentPath,Path& bestPath);
	bool isStateFinal(const State& state);
};

