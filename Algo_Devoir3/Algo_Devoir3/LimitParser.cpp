#include "stdafx.h"
#include <fstream>
#include <sstream>
#include "LimitParser.h"
#include "Utility.h"
using std::getline;
using std::string;
using std::ifstream;
using std::stoi;

LimitParser::LimitParser(string filename, const AFDGraph & graph): graph(graph)
{
	this->filename = filename;
}

shared_ptr<LayerGraph> LimitParser::parseFile()
{
	ifstream file(this->filename);
	string line;
	if (file) {
		//First line is alphabet size
		getline(file, line);
		int alphabetSize = stoi(line);
		//Second line is the length of the word
		getline(file, line);
		int wordLength = stoi(line);
		//Third line is the minimum number of times we have to read each letter
		getline(file, line);
		vector<string> minForEachLetterString = Utility::split(line, ' ');
		vector<int> minForEachLetter = vector<int>();
		for (int i = 0; i < minForEachLetterString.size(); i++) {
			minForEachLetter.push_back(stoi(minForEachLetterString[i]));
		}
		//Fourth line is the minimum number of times we have to read each letter
		getline(file, line);
		vector<string> maxForEachLetterString = Utility::split(line, ' ');
		vector<int> maxForEachLetter = vector<int>();
		for (int i = 0; i < maxForEachLetterString.size(); i++) {
			maxForEachLetter.push_back(stoi(maxForEachLetterString[i]));
		}
		//We now have all information needed so we build the layer Graph
		return shared_ptr<LayerGraph>(new LayerGraph(this->graph,wordLength));
	}
	return shared_ptr<LayerGraph>(NULL);
}


LimitParser::~LimitParser()
{
}
