#pragma once

#include <string>

class Vertex{
private:
	int number;
public:
	int weight;
	std::string label;
	Vertex(int n);
	int Number() const;
};

Vertex::Vertex(int n):number(n), weight(0) {}

int Vertex::Number() const { return number; }

