#include "stdafx.h"
#include "GraphParser.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using std::ifstream;
using std::stringstream;
using std::string;
using std::vector;
using std::getline;
using std::find;
using std::stoi;

std::vector<std::string> split(const std::string &s, char delim) {
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
		// elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
	}
	return elems;

}
GraphParser::GraphParser(string filename)
{
	this->filename = filename;
}

std::shared_ptr<AFDGraph> GraphParser::parseFile()
{
	ifstream file(this->filename);
	string line;
	if (file) {
		//First line is alphabet size
		getline(file, line);
		int alphabetSize = stoi(line);
		//Second line is number of states
		getline(file, line);
		int nbStates = stoi(line);
		//Third line is initial node id
		getline(file, line);
		int initialNodeId = stoi(line);
		//Fourth line is number of final states
		getline(file, line);
		int nbFinalStates = stoi(line);
		//Fifth line is IDs of final states
		getline(file, line);
		vector<string> finalStatesID = split(line,' ');
		vector<int> finalStatesIDint = vector<int>();
		for (int i = 0; i < finalStatesID.size(); i++) {
			finalStatesIDint.push_back(stoi(finalStatesID[i]));
		}
		//Sixth line is number of transitions
		getline(file, line);
		int nbEdges = stoi(line);
		//From here we can generate the graph and populate all its edges later on.
		shared_ptr<AFDGraph> newGraph = shared_ptr<AFDGraph>(new AFDGraph());
		for (int i = 1; i <= nbStates; i++) {
			if(i == initialNodeId) {
				if (find(finalStatesIDint.begin(), finalStatesIDint.end(), i) != finalStatesIDint.end()) {
					newGraph->createAndInsertState(i, true, true);
				}
				else {
					newGraph->createAndInsertState(i, false, true);
				}

			}
			else if (find(finalStatesIDint.begin(),finalStatesIDint.end(),i) != finalStatesIDint.end() ) {
				newGraph->createAndInsertState(i, true, false);
			}
			else {
				newGraph->createAndInsertState(i, false, false);
			}
		}
		//Next lines describe transitions
		int i = 1;
		while (i <= nbEdges) {
			getline(file, line);
			vector<string> splittedLine = split(line, ' ');
			string transition = splittedLine[0];
			int firstNodeId = stoi(splittedLine[1]);
			int outNodeId = stoi(splittedLine[2]);
			int weight = stoi(splittedLine[3]);
			newGraph->getState(firstNodeId).addEdge(&(newGraph->getState(outNodeId)), transition, weight);
			i++;
		}
		return newGraph;
	}
}


GraphParser::~GraphParser()
{
}
