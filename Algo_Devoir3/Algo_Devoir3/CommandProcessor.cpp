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
	std::cout << "dijkstra : Trouve le mot de poids le plus faible (en utilisant l'algorithme de Dijkstra)" << std::endl;
	//std::cout << "chemins valides : Calcule tout les chemins valides au sein du graphe" << std::endl;
	std::cout << "recherche : Recherche une arrete dans le graphe et determine elle appartient a un chemin valide" << std::endl;
	std::cout << "aide,? : Affiche la liste des commandes" << std::endl;
	std::cout << "quitter : Quitte l'application" << std::endl;
}

void CommandProcessor::quit()
{
	this->shouldExit = true;
}

void CommandProcessor::processCommand(string command)
{
	if (command == "dijkstra") {
		findMinimumPath();
	}
	/*
	else if (command == "chemins valides") {
		std::cout << "Calculs des chemins en cours (Peut prendre du temps)..." << std::endl;
		this->layerGraph->getLegalPaths();
		std::cout << "Les chemins ont ete calcules" << std::endl;
	}*/
	else if (command == "recherche") {
		string input;
		std::cout << "Premier noeud de l'arete?" << std::endl;
		getline(std::cin, input);
		int id1 = stoi(input);
		std::cout << "Sur quel niveau du graphe en couche?" << std::endl;
		getline(std::cin, input);
		int layer1 = stoi(input);
		State* state1 = this->layerGraph->getState(id1, layer1);
		std::cout << "Second noeud de l'arete?" << std::endl;
		getline(std::cin, input);
		int id2 = stoi(input);
		std::cout << "Sur quel niveau du graphe en couche?" << std::endl;
		getline(std::cin, input);
		int layer2 = stoi(input);
		State* state2 = this->layerGraph->getState(id2, layer2);
		Edge* edge = this->layerGraph->getEdge(state1, state2);
		if (edge == NULL) {
			std::cout << "L'arrete n'a pas pu etre localisee" << std::endl;
		}
		else {
			std::cout << "Borne superieure ? Laisser vide pour une recherche sans borne" << std::endl;
			getline(std::cin, input);
			if (input != "") {
				int bound;
				bound = stoi(input);
				Path path = this->layerGraph->isEdgeOnLegalPath(edge,bound);
				if (path.path.empty()) {
					std::cout << "Cette arrete n'apparait sur aucun chemin realisable de cout inferieur ou egal a " << bound << std::endl;
				}
				else {
					std::cout << "Voici le chemin sur lequel cette arrete apparait de cout inferieur a " << bound << std::endl;
					std::cout << path << std::endl;
				}
			}
			else {
				Path path = this->layerGraph->isEdgeOnLegalPath(edge);
				if (path.path.empty()) {
					std::cout << "Cette arrete n'apparait sur aucun chemin realisable" << std::endl;
				}
				else {
					std::cout << "Voici le chemin sur lequel cette arrete apparait" << std::endl;
					std::cout << path << std::endl;
				}
			}
		}
	}
	else if (command == "aide" || command == "?") {
		printHelp();
	}
	else if (command == "quitter") {
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
	Path path = this->layerGraph->Dijkstra();
	if (path.path.size() == 0) {
		std::cout << "Aucun chemin valide trouve" << std::endl;
	}
	else {
		std::cout << path << std::endl;
	}
}
