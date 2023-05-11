#pragma once

#include <iostream>
#include "Set.h"
#include "Visitor.h"
#include "Iterator.h"
#include <vector>

class SetAsArray : public Set<int>{
private:
	std::vector<bool> array;
public:
	SetAsArray(unsigned int n);
	void MakeNull();//metody z containera 
	bool IsFull() const { return (Count() == UniverseSize()); };
	void Insert(int element);
	bool IsMember(int element) const;
	void Withdraw(int element);
	void Show();
	void Accept(Visitor<int> &visitor);

	//friend- funkcja uzyska prawo dostepu do prywatnych elementów danej klasy. 
	friend SetAsArray operator + (SetAsArray const& a, SetAsArray const& b);
	friend SetAsArray operator - (SetAsArray const& a, SetAsArray const& b);
	friend SetAsArray operator * (SetAsArray const& a, SetAsArray const& b);
	friend bool operator == (SetAsArray const& a, SetAsArray const& b);
	friend bool operator <= (SetAsArray const& a, SetAsArray const& b);
	friend bool IsDisjoint(SetAsArray const& a, SetAsArray const& b);

	class Iter :public Iterator<int> {
	private:	
		std::vector<bool> it_arr;
		int uSize;
		int current;
	public:
		Iter(std::vector<bool> array, int universeSize) {
			it_arr = array;
			uSize = universeSize;
			current = -1;
			this->operator++(); //ustawia iterator na pierwszy element o wartoœci true
		}

		bool IsDone() const{
			if (current > uSize - 1) { return true; }
			else { return false; }
		}

		const int& operator*() const { return current; }

		void operator++() {
			while (!IsDone()) {
				current++;
				if (current > uSize - 1) { break; }	//zabezpieczenie przed wyjœciem poza wektor
				if (it_arr[current] == true) { break; }
			}
		}
	};

	Iterator<int>& NewIterator() { return *new Iter(array, UniverseSize()); }

};

SetAsArray::SetAsArray(unsigned int n = 10) : Set(n) {
	array.resize(n);
	MakeNull();
}

void SetAsArray::MakeNull() {
	for (int i = 0; i < UniverseSize(); i++) {
		array[i] = false;
	}
	count = 0;
}


void SetAsArray::Accept(Visitor<int> &visitor){

	visitor.SetAll();
	int i = 0;

	for (i = 0; i < UniverseSize() && !visitor.IsDone(); i++) {
		if (IsMember(i)) {
			visitor.Visit(i);
		}
	}
	std::cout << "--- Accept() ends after element on position: " << i - 1 << " ---\n";
}

void SetAsArray::Insert(int element) {
	if (element > UniverseSize() || IsMember(element)) {
		return;
	}
	array[element] = true;
	count++;
}


inline bool SetAsArray::IsMember(int element) const {
	return array[element];
}

void SetAsArray::Withdraw(int element) {	//usuniêcie elementu ze zbioru
	if (element > UniverseSize() || !IsMember(element)) {
		return;
	}
	array[element] = false;
	count--;
}

void SetAsArray::Show() {
	//std::cout << "size: " << Count() << " | elements: ";
	/*for (int i = 0; i < UniverseSize(); i++) {
		if (IsMember(i)) {
			std::cout << i << " ";
		}
	}
	std::cout << std::endl;*/

	auto& it = NewIterator();
	while (!it.IsDone()) {
		std::cout << *it << " ";
		++it;
	}
	delete &it;
	std::cout << std::endl;
}



SetAsArray operator + (SetAsArray const& a, SetAsArray const& b) {	//suma zbiorów
	SetAsArray new_set(a.UniverseSize());
	for (int i = 0; i < a.UniverseSize(); i++) {
		if (a.array[i] || b.array[i]) {	// 1 or 0 lub 0 or 1 lub 1 or 1
			new_set.array[i] = true;	//new_set.insert(i);
			new_set.count++;
		}
		else {
			new_set.array[i] = false;
		}
	}
	return new_set;
}

SetAsArray operator - (SetAsArray const& a, SetAsArray const& b) {	//ró¿nica zbiorów
	SetAsArray new_set(a.UniverseSize());
	for (int i = 0; i < a.UniverseSize(); i++) {
		if ( a.array[i] && !b.array[i] ) {	// 1 and ~0 czyli 1 and 1
			new_set.array[i] = true;	//new_set.insert(i);
			new_set.count++;
		}
		else {
			new_set.array[i] = false;
		}
	}
	return new_set;
}

SetAsArray operator * (SetAsArray const& a, SetAsArray const& b) {	//czêœæ wspólna zbiorów
	SetAsArray new_set(a.UniverseSize());
	for (int i = 0; i < a.UniverseSize(); i++) {
		if ( (a.array[i] && b.array[i]) == true ) {
			new_set.array[i] = true;	//new_set.insert(i);
			new_set.count++;
		}
		else {
			new_set.array[i] = false;
		}
	}
	return new_set;
}

bool operator == (SetAsArray const& a, SetAsArray const& b) {	//równoœæ zbiorów
	for (int i = 0; i < a.UniverseSize(); i++) {
		if (a.array[i] != b.array[i]) {
			return false;
		}
	}
	return true;
}

bool operator <= (SetAsArray const& a, SetAsArray const& b) {	//zawieranie siê w zbiorze
	for (int i = 0; i < a.UniverseSize(); i++) {
		if (a.IsMember(i)) {
			if (!b.IsMember(i)) {
				return false;
			}
		}
	}
	return true;
}

bool IsDisjoint(SetAsArray const& a, SetAsArray const& b){
	for (int i = 0; i < a.UniverseSize(); i++) {
		if ((a.array[i] && b.array[i]) == true) { return false; }
	}
	return true;
}
