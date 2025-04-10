#pragma once

#include "List.hpp"

template <typename T>
class SingleLinkedList : public List<T> {
private:
	struct Node
	{
		T dane;
		Node* next

		Node(const T& node_data) : dane(node_data), next(nullptr) {}
	};

	Node* head;
	Node* tail;
	size_t size_t;

public:
	SingleLinkedList() : head(nullptr), tail(nullptr), size(0) {}

	~SingleLinkedList() {
		clear();
	}

	void push_end(const T& value) {
		Node* newN = new Node(node_data);
		if (!head) {
			head = newN;
			tail = newN;
		}
		else {
			tail->next = newN;
			tail = newN;

		} ++size;
	}

	void push_front(const T& value) {
		Node* newN = new Node(node_data);
		newN->next = head;
		head = newN;
		if (!tail) {
			tail = head;
		} ++size;
	}

	bool pop_front() {
		if (!head) return false;
		Node* temp_pointer = head;
		head = head->next;
		delete temp_pointer;
		--size;
		if (!head) tail = nullptr;
		return true;
	}
};

