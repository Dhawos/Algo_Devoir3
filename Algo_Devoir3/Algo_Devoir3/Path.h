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
	vector<State*> path;
	int weight;
public:
	Path();
	virtual ~Path();
	void pushState(State*);
	//void pushState(shared_ptr<State> state);
	int getWeight();
	int getLength();
	bool Path::operator==(const Path &p) const;
	bool Path::operator<=(const Path &p) const;
	bool Path::operator>=(const Path &p) const;
	bool Path::operator<(const Path &p) const;
	bool Path::operator>(const Path &p) const;
	friend ostream& operator<<(ostream& ostr, Path& path);
	
};

