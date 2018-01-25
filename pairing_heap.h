#pragma once

#include "heap.h"
#include <queue>
#include <vector>
#include <iostream>
#include <functional>

template<typename TYPE, typename COMPARATOR = std::less<TYPE>>
class pairing_heap : public heap<TYPE, COMPARATOR> {
public:
	typedef unsigned size_type;

	template<typename InputIterator>
	pairing_heap(InputIterator start, InputIterator end, COMPARATOR comp = COMPARATOR());
	pairing_heap(COMPARATOR comp = COMPARATOR());
	pairing_heap(const pairing_heap& other);

	pairing_heap& operator=(const pairing_heap& rhs);

	~pairing_heap();

	virtual void push(const TYPE& val);
	virtual void pop();
	virtual const TYPE& peek() const;

	virtual size_type size() const { return length;	}
	virtual bool empty() const { return length == 0; }

	class Node {
	public:
		Node(const TYPE & val)
			: elt(val), sibling(nullptrptr), child(nullptrptr)
		{}
	public:
		const TYPE& operator*() const { return elt; }
		const Node* sibling_ptr() const { return sibling; }
		const Node* child_ptr() const { return child; }

		friend pairing_heap;
	private:
		TYPE elt;
		Node* sibling;
		Node* child;
	};

	const Node* root_ptr() const { return root; }

private:
	Node* root;
	int length;

	Node* meld(Node* A, Node* B) {
		if (A == nullptr)
			return B;
		else if (B == nullptr)
			return A;

		if (this->compare(B->elt, A->elt)) {
			if (A->child == nullptr)
				A->child = B;
			else {
				B->sibling = A->child;
				A->child = B;
			}
			return A;
		}
		else {
			if (B->child == nullptr)
				B->child = A;
			else {
				A->sibling = B->child;
				B->child = A;
			}
			return B;
		}
	}

	Node* merge(Node* start) {
		std::queue<Node* > q;
		while (start != nullptr) {
			q.push(start);
			start = start->sibling;
		}

		while (q.size() > 1) {
			Node* a = q.front();
			q.pop();
			Node* b = q.front();
			q.pop();

			Node* c = meld(a, b);
			q.push(c);
		}
		return q.front();
	}

	void destroy(Node* A) {
		if (A != nullptr)
		{
			destroy(A->child);
			destroy(A->sibling);
			delete A;
		}
	}

};


//ITERATOR CONSTRUCTOR
template<typename TYPE, typename COMPARATOR>
template<typename InputIterator>
pairing_heap<TYPE, COMPARATOR>::pairing_heap(
	InputIterator start, InputIterator end, COMPARATOR comp) {

	root = new Node(*start);
	this->compare = comp;
	length = 0;
	start++;
	while (start != end) {
		length++;
		meld(root, new Node(*start));
	}

}


//CONSTRUCTOR
template<typename TYPE, typename COMPARATOR>
pairing_heap<TYPE, COMPARATOR>::pairing_heap(COMPARATOR comp) {
	root = nullptr;
	this->compare = comp;
	length = 0;
}


//COPY CONSTRUCTOR
template<typename TYPE, typename COMPARATOR>
pairing_heap<TYPE, COMPARATOR>::pairing_heap(const pairing_heap& other) {
	root = other.root;
	length = other.length;
	this->compare = other.compare;
}


//COPY ASSIGNMENT
template<typename TYPE, typename COMPARATOR>
pairing_heap<TYPE, COMPARATOR>&
pairing_heap<TYPE, COMPARATOR>::operator=(const pairing_heap& rhs) {
	//TODO
	return *this;
}


//DELETE
template<typename TYPE, typename COMPARATOR>
pairing_heap<TYPE, COMPARATOR>::~pairing_heap() {
	destroy(root);
	root = nullptr;
}


//POP
template<typename TYPE, typename COMPARATOR>
void pairing_heap<TYPE, COMPARATOR>::pop() {

	Node *oldRoot = root;

	if (root->child == nullptr)
		root = nullptr;
	else {
		root = merge(root->child);
	}

	delete oldRoot;

	length--;
}


//TOP
template<typename TYPE, typename COMPARATOR>
const TYPE& pairing_heap<TYPE, COMPARATOR>::peek() const {
	return root->elt;
}


//PUSH
template<typename TYPE, typename COMPARATOR>
void pairing_heap<TYPE, COMPARATOR>::push(const TYPE& val) {
	length++;

	Node* node = new Node(val);
	if (root == nullptr)
		root = node;
	else root = meld(root, node);

	//TODO
	//2nd highest value in heap is lost

}

