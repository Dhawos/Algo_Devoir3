// Algo_Devoir3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GraphParser.h"


int main()
{
	//GraphParser parser = GraphParser("test8.afdC");
	GraphParser parser = GraphParser("exemple11comment.afdC");
	shared_ptr<AFDGraph> graph = parser.parseFile();
    return 0;
}

