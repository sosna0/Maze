#pragma once

#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <memory>
#include <GLFW/glfw3.h>

#include "GraphAsMatrix.h"
#include "SetAsArray.h"

using GLfPair = std::pair<GLfloat, GLfloat>;


std::vector<std::unique_ptr<SetAsArray>> MakeSetsFromVerticies(GraphAsMatrix& graph){

	std::vector<std::unique_ptr<SetAsArray>> SetsOfVert(graph.NumberOfVertices());	//Wektor zbiorów z wierzcho³ków

	auto& vertIter = graph.VerticesIter();

	while (!vertIter.IsDone()) {
		auto& vert = *vertIter;

		int vertNum = vert.Number();

		SetsOfVert[vertNum] = std::make_unique<SetAsArray>(graph.NumberOfVertices());
		SetsOfVert[vertNum]->Insert(vertNum);
		++vertIter;
	}
	delete& vertIter;

	return SetsOfVert;	//Zwrócenie wektora zbiorów
}


std::vector<std::unique_ptr<Edge>> AddWeightsAndSortEdges(GraphAsMatrix &graph) {
	
	std::vector<int> EdgesWeights;
	std::vector<std::unique_ptr<Edge>> EdgesList;

	std::random_device rd;
	std::mt19937 g(rd());

	auto& edgeIt = graph.EdgesIter();
	int num = 0;

	while (!edgeIt.IsDone()) {	//Stworzenie wektora wag
		EdgesWeights.push_back(num);
		num++;
		++edgeIt;
	}
	delete& edgeIt;


	std::shuffle(EdgesWeights.begin(), EdgesWeights.end(), g);	//Losowe ustawienie wektora wag
	
	int VectorSize = EdgesWeights.size();
	EdgesList.resize(VectorSize);	//Ustawienie rozmiaru wektora krawêdzi do wektora zawieraj¹cego wagi

	auto& edgeIter = graph.EdgesIter();
	
	while (!edgeIter.IsDone()) {
		auto edge = *edgeIter;

		edge.weight = EdgesWeights[VectorSize - 1];	//Ustawienie losowych wag dla krawêdzi (od 0 do SIZE-1)
		EdgesList[edge.weight] = std::make_unique<Edge>(edge);	//Wrzucenie krawêdzi na odpowiednie miejsce w wektorze tak, aby wektor by³ posortowany wg wag

		EdgesWeights.pop_back();
		EdgesWeights.resize(VectorSize - 1);

		VectorSize--; ++edgeIter;
	}
	delete& edgeIter;

	return EdgesList;	//Zwrócenie wektora krawêdzi
}


std::vector<std::pair<GLfloat, GLfloat>> kruskal_maze(GraphAsMatrix &graph, int rows, int cols) {

	auto VertSets = MakeSetsFromVerticies(graph);
	auto EdgesList = AddWeightsAndSortEdges(graph);
	
	std::vector<Edge> SpanningTree;

	for (int i = 0; i < EdgesList.size(); i++) {

		auto& edge = EdgesList[i];

		int edge_V0 = edge->V0()->Number();
		int edge_V1 = edge->V1()->Number();

		auto& set0 = *VertSets[edge_V0];
		auto& set1 = *VertSets[edge_V1];

		if (IsDisjoint(set0, set1)) {

			SpanningTree.push_back(*edge);

			auto setUnion = set0 + set1;
			for (int i = 0; i < VertSets.size(); i++) {
				if ((VertSets[i]->IsMember(edge_V0))
					|| (VertSets[i]->IsMember(edge_V1))) {
					*VertSets[i] = setUnion;
				}

			}
			

		}
		else {

			auto& graph_label = graph.SelectEdge(edge_V0, edge_V1)->label;
			if (graph_label == "v") {
				graph.SelectEdge(edge_V0, edge_V1)->label = "V";
			}
			else if (graph_label == "h") {
				graph.SelectEdge(edge_V0, edge_V1)->label = "H";
			}

		}

	}

	/*std::cout << std::endl;

	for (auto& s : SpanningTree) {
		std::cout << "Edge(" << s.V0()->Number() << ", " << s.V1()->Number() << ") ";
		std::cout << "Edge weight: " << s.weight << std::endl;
	}
	std::cout << "\nNumber of edges in SpanningTree: " << SpanningTree.size() << std::endl;*/


	std::vector<std::pair<GLfloat, GLfloat>> vert;
	GLfloat width = 0.025f;
	GLfloat start_x = -0.97f;
	GLfloat start_y = 0.97f;

	for (int i = 0; i < rows*cols; i = i+cols) {

		for (int j = i; j < cols - 1 +i; j++) {
			if (graph.SelectEdge(j, j + 1)->label == "V") {

				GLfPair p1(start_x + width, start_y);
				GLfPair p2(start_x + width, start_y - width);

				vert.push_back(p1);
				vert.push_back(p2);
			}
			start_x = start_x + width;
		}

		start_x = -0.97f;

		if ( i >= (rows*cols) - cols) { break; }
		for (int k = i; k < cols + i; k++) {
			if (graph.SelectEdge(k, k + cols)->label == "H") {
				GLfPair p1(start_x, start_y - width);
				GLfPair p2(start_x + width, start_y - width);

				vert.push_back(p1);
				vert.push_back(p2);
			}
			start_x = start_x + width;
		}
		start_x = -0.97f;
		start_y = start_y - width;

	}
	return vert;

}