#pragma once

template<typename T>
class Iterator {
public:
	virtual ~Iterator(){}
	virtual bool IsDone() const = 0;
	virtual const T& operator*() const = 0;
	virtual void operator++() = 0;
};