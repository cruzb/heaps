#pragma once

#include <functional>
#include <iterator>
#include <vector>

template<typename TYPE, typename COMPARATOR = std::less<TYPE>>
class heap {
public:
	virtual ~heap() {}
	virtual void push(const TYPE& val) = 0;
	virtual void pop() = 0;
	virtual const TYPE& peek() const = 0;
	virtual std::size_t size() const = 0;
	virtual bool empty() const = 0;
	virtual void updatePriorities() = 0;

protected:
	COMPARATOR compare;
};

