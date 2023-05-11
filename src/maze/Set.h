#pragma once

#include "Container.h"

template <typename T>
class Set : public virtual Container<T>{
protected:
	unsigned int count = 0;
	int universeSize;
public:
	Set(int n) : universeSize(n) {}
	int UniverseSize() const { return universeSize; }
	unsigned int Count() const { return count; };
	virtual void Insert(T element) = 0;
	virtual bool IsMember(T element) const = 0;
	virtual void Withdraw(T element) = 0;
};