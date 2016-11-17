#pragma once
#include "State.h"
#include <vector>
#include <iostream>
#include <memory>
using std::ostream;
using std::vector;
using std::shared_ptr;
class Path
{
private:
	vector<const State*> path;
	int weight;
public:
	Path();
	virtual ~Path();
	void pushState(const State*);
	void pushState(shared_ptr<State> state);
	int getWeight();
	int getLength();
	bool Path::operator==(const Path &p) const;
	bool Path::operator<=(const Path &p) const;
	bool Path::operator>=(const Path &p) const;
	bool Path::operator<(const Path &p) const;
	bool Path::operator>(const Path &p) const;
	friend ostream& operator<<(ostream& ostr, const Path& obj)
	{
		for (const State* state : obj.path) {
			ostr << state->getId() << " - ";
		}
		ostr << std::endl;
		return (ostr);
	}
};

