#pragma once

#include "GraphAsMatrix.h"


GraphAsMatrix generateGraph(int row, int col) {
	GraphAsMatrix graph(row * col, true);
	
	for (int i = 0; i < row * col; i++) {
		if ( (i+1) % col != 0) {
			graph.AddEdge(i, i + 1); 
			graph.SelectEdge(i, i + 1)->label = "v";
		}
	}
	
	for (int i = 0; i < (row * col) - col; i++) {
		graph.AddEdge(i, i + col);
		graph.SelectEdge(i, i + col)->label = "h";
	}
	
	return graph;
}