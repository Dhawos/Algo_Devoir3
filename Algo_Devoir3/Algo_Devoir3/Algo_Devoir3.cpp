// Algo_Devoir3.cpp : Defines the entry point for the console application.
//
//
#include "stdafx.h"
#include <iostream>
#include "GraphParser.h"
#include "LimitParser.h"
#include "CommandProcessor.h"
using std::getline;
using std::cin;
using std::string;

int main()
{
	string input;
	shared_ptr<AFDGraph> graph = NULL;
	while (graph == NULL) {
		std::cout << "Entrez le nom du fichier decrivant l'automate" << std::endl;
		getline(std::cin, input);
		GraphParser parser = GraphParser(input);
		graph = parser.parseFile();
		if (graph == NULL) {
			std::cout << "Fichier non existant" << std::endl;
		}
	}
	shared_ptr<LayerGraph> layerGraph = NULL;
	while (layerGraph == NULL) {
		std::cout << "Entrez le nom du fichier decrivant les limites" << std::endl;
		std::getline(std::cin, input);
		LimitParser limitParser = LimitParser(input, *graph);
		layerGraph = limitParser.parseFile();
		if (layerGraph == NULL) {
			std::cout << "Fichier non existant" << std::endl;
		}
	}
	bool shouldExit = false;
	CommandProcessor cmdProcessor = CommandProcessor(layerGraph,shouldExit);
	cmdProcessor.printHelp();
	while (!shouldExit) {
		std::cout << "Commande : ";
		getline(std::cin, input);
		cmdProcessor.processCommand(input);
	}
    return 0;
}

