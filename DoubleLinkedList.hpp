#pragma once
#include "List.hpp"

template <typename T>
class DoubleLinkedList : public List<T> {
private:
	struct Node {
		T dane;
		Node* prev;
		Node* next;
	};
};
