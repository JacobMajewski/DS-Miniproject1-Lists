#pragma once

#include "List.hpp"

template <typename T>
class SingleLinkedList : public List<T> {
private:
	struct Node
	{
		T dane;
		Node* next;

		Node(const T& node_data);
	};

	Node* head;
	Node* tail;
	size_t size_t;

public:
	SingleLinkedList();

	~SingleLinkedList();

	void push_end(const T& value);

	void push_front(const T& value);

	bool pop_front();
};

