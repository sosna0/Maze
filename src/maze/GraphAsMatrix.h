#pragma once

#include <vector>
#include "Vertex.h"
#include "Edge.h"
#include "Iterator.h"

class GraphAsMatrix{
private:
	std::vector<Vertex*> vertices;
	std::vector< std::vector<Edge*> > adjacencyMatrix;
	bool isDirected;
	int numberOfVertices;
	int numberOfEdges;

public:
	GraphAsMatrix(int n, bool b);
	~GraphAsMatrix(){}
	int NumberOfVertices();
	bool IsDirected();
	int NumberOfEdges();
	bool IsEdge(int u, int v);
	void MakeNull();
	void AddEdge(int u, int v);
	Edge* SelectEdge(int u, int v);
	Vertex* SelectVertex(int v);


	class AllVerticesIter: public Iterator<Vertex>{
	private:
		GraphAsMatrix& owner;
		int current;
	public:
		AllVerticesIter(GraphAsMatrix& _owner):owner(_owner), current(-1) {
			this->operator++();
		}
		
		bool IsDone() const{
			if (current > owner.NumberOfVertices() - 1) { return true; }
			else { return false; }
		}

		const Vertex& operator*() const{ return *owner.SelectVertex(current); }
		
		void operator++() {	current++; }
	};

	class AllEdgesIter: public Iterator<Edge> {
	private:
		GraphAsMatrix& owner;
		int row;
		int col;
	public:
		void next() {
			
			if (col < owner.NumberOfVertices()) { col++; }

			for (int i = row; i < owner.NumberOfVertices(); i++) {
				for (int j = col; j < owner.NumberOfVertices(); j++) {
					if (owner.IsEdge(i, j) == true) { row = i; col = j; return; }
				}
				col = 0;
			}
			row = col = owner.NumberOfVertices();

		}

		AllEdgesIter(GraphAsMatrix& _owner):owner(_owner), row(0), col(-1) {
			this->operator++();
		}

		bool IsDone() const{
			if ( (row >= owner.NumberOfVertices()) && (col >= owner.NumberOfVertices()) ) { return true; }
			else { return false; }
		}

		const Edge& operator*() const {	return *owner.SelectEdge(row, col); }

		void operator++() { next(); }

	};

	class EmanEdgesIter: public Iterator<Edge>{
		GraphAsMatrix& owner;
		int row;
		int col;

	public:
		void next() {
			for (int i = 0; i < owner.NumberOfVertices(); i++) {
				col++;
				if (IsDone()) { return; }
				if (owner.IsEdge(row, col) != NULL) { return; }
			}
		}

		EmanEdgesIter(GraphAsMatrix& _owner, int v):owner(_owner), col(-1), row(v) {
			this->operator++();
		}

		bool IsDone() const {
			if (col >= owner.NumberOfVertices()) { return true; }
			else { return false; }
		}
		
		const Edge& operator*() const{ return *owner.SelectEdge(row, col); }
		
		void operator++() { next(); }
	};

	class InciEdgesIter: public Iterator<Edge> {
		GraphAsMatrix& owner;
		int row;
		int col;
	public:
		void next(){
			for (int i = 0; i < owner.NumberOfVertices(); i++) {
				row++;
				if (IsDone()) { return; }
				if (owner.IsEdge(row, col)) { return; }
			}
		}

		InciEdgesIter(GraphAsMatrix& _owner, int v) :owner(_owner), row(-1), col(v) {
			this->operator++();
		}

		bool IsDone() const {
			if (row >= owner.NumberOfVertices()) { return true; }
			else { return false; }
		}

		const Edge& operator*() const{ return *owner.SelectEdge(row, col); }

		void operator++(){ next(); }
	};

	Iterator<Vertex>& VerticesIter() { return *new AllVerticesIter(*this); }
	Iterator<Edge>& EdgesIter(){ return *new AllEdgesIter(*this); }
	Iterator<Edge>& EmanatingEdgesIter(int v){ return *new EmanEdgesIter(*this, v); }
	Iterator<Edge>& IncidentEdgesIter(int v){ return *new InciEdgesIter(*this, v); }
};


GraphAsMatrix::GraphAsMatrix(int n, bool b)
	:isDirected(b), numberOfVertices(n), vertices(n), adjacencyMatrix(n), numberOfEdges(0) {

	for (int i = 0; i < n; i++) {
		vertices[i] = new Vertex(i);
		adjacencyMatrix[i].resize(n);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			adjacencyMatrix[i][j] = NULL;
		}
	}

}

int GraphAsMatrix::NumberOfVertices() { return numberOfVertices; }

bool GraphAsMatrix::IsDirected(){ return isDirected; }

int GraphAsMatrix::NumberOfEdges() { return numberOfEdges; }


bool GraphAsMatrix::IsEdge(int u, int v){
	if (adjacencyMatrix[u][v] == NULL) { return false; }
	else { return true; }
}

void GraphAsMatrix::MakeNull(){
	for (int i = 0; i < numberOfVertices; i++) {
		for (int j = 0; j < numberOfVertices; j++) {
			adjacencyMatrix[i][j] = NULL;
		}
	}
}

void GraphAsMatrix::AddEdge(int u, int v){
	if ( ((u>= 0) && (u < numberOfVertices)) && ((v >= 0) && (v < numberOfVertices)) ) {
		if (IsDirected()) {
			if (adjacencyMatrix[u][v] == NULL) {
				numberOfEdges++;
				adjacencyMatrix[u][v] = new Edge(vertices[u], vertices[v]);
			}
		}
		else {
			if (adjacencyMatrix[u][v] == NULL) {
				numberOfEdges += 2;
				adjacencyMatrix[u][v] = new Edge(vertices[u], vertices[v]);
				adjacencyMatrix[v][u] = new Edge(vertices[v], vertices[u]);
			}
		}
	}
}

Edge* GraphAsMatrix::SelectEdge(int u, int v){
	if (((u >= 0) && (u < numberOfVertices)) && ((v >= 0) && (v < numberOfVertices))) {
		return adjacencyMatrix[u][v];
	}
}

Vertex* GraphAsMatrix::SelectVertex(int v){
	if ((v >= 0) && (v < numberOfVertices)) {
		return vertices[v];
	}
}
