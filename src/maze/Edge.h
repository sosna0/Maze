#pragma once

#include "Vertex.h"

class Edge{
protected:
	Vertex* v0;
	Vertex* v1;
public:
	int weight;
	std::string label;
	Edge(Vertex* V0, Vertex* V1);
	Edge(const Edge &edge);
	Vertex* Mate(Vertex* v);
	Vertex* V0() const { return v0; };
	Vertex* V1() const { return v1; };
};

Edge::Edge(Vertex* V0, Vertex* V1):v0(V0), v1(V1), weight(0) {}
Edge::Edge(const Edge& e):v0(e.V0()), v1(e.V1()), weight(e.weight), label(e.label) {}

Vertex* Edge::Mate(Vertex* v) {
	if (v->Number() == v0->Number()) { return v1; }
	else if(v->Number() == v1->Number()) { return v0; }
}