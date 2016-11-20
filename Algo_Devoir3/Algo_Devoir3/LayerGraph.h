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
	vector<Path> legalpaths;
public:
	LayerGraph(AFDGraph graph, int wordLength, vector<int> maximums, vector<int> minimums);
	virtual ~LayerGraph();
	State* getState(int id, int layer);
	Edge* getEdge(State* s1,State* s2);
	Path Dijkstra();
	bool propagateStates(State& start, State& goal);
	bool propagateStates(State& start, State* goal);
	Path getOptimalPath();
	Path getOptimalPath(State* state);
	bool checkConstraints(Path& Path);
	bool isStateFinal(State& state);
	bool canPathBeLegal(Path path);
	Path firstLegalPath(Path path);
	Path isEdgeOnLegalPath(Edge* edge);
	vector<Path> getLegalPaths();
	void recGetLegalPaths(State* state, Path path, vector<Path>& paths);
	void removeIllegalEdges();
};

