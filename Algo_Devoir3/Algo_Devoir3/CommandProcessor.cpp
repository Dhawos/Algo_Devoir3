#include "stdafx.h"
#include "CommandProcessor.h"
#include <iostream>

CommandProcessor::CommandProcessor(shared_ptr<LayerGraph> layerGraph, bool& shouldExit) : shouldExit(shouldExit)
{
	this->layerGraph = layerGraph;
}


CommandProcessor::~CommandProcessor()
{
}

void CommandProcessor::printHelp()
{
	std::cout << "---------------Help----------------" << std::endl;
	std::cout << "Voici les commandes disponibles" << std::endl;
	std::cout << "computePaths : Computes paths that satisfies constraint (must be called befor other commands)" << std::endl;
	std::cout << "findMin : Trouve le mot de poids le plus faible" << std::endl;
	std::cout << "quit : Quitte l'application" << std::endl;
}

void CommandProcessor::quit()
{
	this->shouldExit = true;
}

void CommandProcessor::processCommand(string command)
{
	if (command == "computePaths") {
		std::cout << "Computing paths.... (This can take a while)" << std::endl;
		layerGraph->getLegalPaths();
		std::cout << "Paths have been computed." << std::endl;
	}
	else if (command == "findMin") {
		findMinimumPath();
	}
	else if (command == "quit") {
		quit();
	}
	else {
		std::cout << "Commande invalide" << std::endl;
		printHelp();
	}
}

void CommandProcessor::findMinimumPath()
{
	std::cout << "Voici le chemin de poids minimum dans le graphe :" << std::endl;
	//std::cout << this->layerGraph->getMinimumPath() << std::endl;
	Path path = this->layerGraph->Dijkstra();
	if (path.path.size() == 0) {
		std::cout << "Aucun chemin valide trouve" << std::endl;
	}
	else {
		std::cout << path << std::endl;
	}
}
