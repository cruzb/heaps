#pragma once
#include "heap.h"

template<typename TYPE, typename COMPARATOR = std::less<TYPE>>
class binary_heap : public heap<TYPE, COMPARATOR> {
public:
	template<typename InputIterator>
	binary_heap(InputIterator start, InputIterator end, COMPARATOR comp = COMPARATOR());
	binary_heap(COMPARATOR comp = COMPARATOR());

	virtual void push(const TYPE& val);
	virtual void pop();
	virtual const TYPE& peek() const;
	virtual std::size_t size() const { return data.size(); }
	virtual bool empty() const { return data.empty(); }

	virtual void updatePriorities();

private:
	std::vector<TYPE> data;

	void heapify(unsigned int i) {
		unsigned int l, r, h;
		TYPE temp;

		l = i * 2 + 1; // get the left child
		r = i * 2 + 2; // get the right child
		h = i;

		if ((l <= data.size()) && this->compare(data[h], data[l]))
			h = l;
		if ((r <= data.size()) && this->compare(data[h], data[r]))
			h = r;
		if (h != i) {
			temp = data[i];
			data[i] = data[h];
			data[h] = temp;

			heapify(h);
		}
	}


	void heapifyUp(size_t i) {
		size_t p;
		TYPE temp;

		p = (i - 1) / 2;

		if (this->compare(data[p], data[i])) {
			temp = data[i];
			data[i] = data[p];
			data[p] = temp;
			heapifyUp(p);
		}
	}
};


template<typename TYPE, typename COMPARATOR>
template<typename InputIterator>
binary_heap<TYPE, COMPARATOR>::binary_heap(
	InputIterator start, InputIterator end, COMPARATOR comp) : data(start, end) {

	this->compare = comp;

	for (unsigned i = data.size() / 2; i < data.size(); i++)
		heapify(i);
}

template<typename TYPE, typename COMPARATOR>
binary_heap<TYPE, COMPARATOR>::binary_heap(COMPARATOR comp) {
	this->compare = comp;
}

template<typename TYPE, typename COMPARATOR>
void binary_heap<TYPE, COMPARATOR>::push(const TYPE & val) {
	data.push_back(val);

	heapifyUp(data.size() - 1);
}

template<typename TYPE, typename COMPARATOR>
void binary_heap<TYPE, COMPARATOR>::pop() {
	data.front() = data.back();//something wrong here
	data.pop_back();

	heapify(0);
}



template<typename TYPE, typename COMPARATOR>
const TYPE& binary_heap<TYPE, COMPARATOR>::peek() const {
	return data.front();
}

template<typename TYPE, typename COMPARATOR>
void binary_heap<TYPE, COMPARATOR>::updatePriorities() {
	heapify(0);
}

