#pragma once
#include "State.h"
#include <vector>
#include <iostream>
using std::ostream;
using std::vector;
using std::shared_ptr;
class Path
{
private:
	int weight;
public:
	vector<int> occurences;
	vector<State*> path;
	Path(int size);
	Path(const Path& path);
	virtual ~Path();
	void pushState(State*);
	void push_frontState(State * newState);
	int getWeight();
	int getLength();
	//vector<State*>& getPath();
	void Path::operator=(const Path &p);
	bool Path::operator==(const Path &p) const;
	bool Path::operator<=(const Path &p) const;
	bool Path::operator>=(const Path &p) const;
	bool Path::operator<(const Path &p) const;
	bool Path::operator>(const Path &p) const;
	friend ostream& operator<<(ostream& ostr, Path& path);
	
};

