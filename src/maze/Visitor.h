#pragma once

template<typename T>
class Visitor {
public:
	virtual void Visit(T& element) = 0;
	virtual bool IsDone() const { return false; }
	virtual void SetAll() = 0;
};