// Algo_Devoir3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GraphParser.h"
#include "LimitParser.h"


int main()
{
	GraphParser parser = GraphParser("exemple11comment.afdC");
	shared_ptr<AFDGraph> graph = parser.parseFile();
	LimitParser limitParser = LimitParser("exemple11limitecomment.afdC", *graph);
	shared_ptr<LayerGraph> layerGraph = limitParser.parseFile();
    return 0;
}

