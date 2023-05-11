#pragma once

#include <iostream>
#include "Visitor.h"


class VisitorSum : public Visitor<int> {
private:
	int sum_of_elements = 0;
public:
	void Visit(int &element);
	int GetSum() { return sum_of_elements; }
	bool IsDone() const { return false; }
	void SetAll();

};


void VisitorSum::Visit(int& element) {
	sum_of_elements += element;
}

void VisitorSum::SetAll() {
	sum_of_elements = 0;
}