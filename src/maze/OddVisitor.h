#pragma once

#include <iostream>
#include "Visitor.h"


class OddVisitor : public Visitor<int> {
private:
	bool IsOdd = false;
public:
	void Visit(int &element);
	bool IsDone() const;
	void GetOdd();
	void SetAll();
};


void OddVisitor::Visit(int &element) {
	if (element % 2 != 0) {
		IsOdd = true;
	}
	else { IsOdd = false; }
}

bool OddVisitor::IsDone() const{
	if (IsOdd == true) { return true; }
	else { return false; }
}

void OddVisitor::SetAll() {
	IsOdd = false;
}

void OddVisitor::GetOdd() {
	if (IsOdd == true) { std::cout << "There IS an odd element in the set "; }
	else { std::cout << "There IS NO odd element in the set "; }
}