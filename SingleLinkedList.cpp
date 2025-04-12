#include "SingleLinkedList.hpp"

template <typename T>
SingleLinkedList<T>::Node::Node(const T& node_data) : dane(node_data), next(nullptr) {}

template <typename T>
SingleLinkedList<T>::SingleLinkedList() : head(nullptr), tail(nullptr), _size(0) {}

template <typename T>
SingleLinkedList<T>::~SingleLinkedList() 
{
	clear();
}
template <typename T>
void SingleLinkedList<T>::push_end(const T& value)
{
	Node* newN = new Node(node_data);
	if (!head) {
		head = newN;
		tail = newN;
	}
	else {
		tail->next = newN;
		tail = newN;

	} ++_size;
}

template<typename T>
void SingleLinkedList<T>::push_front(const T& value)
{
	Node* newN = new Node(node_data);
	newN->next = head;
	head = newN;
	if (!tail) {
		tail = head;
	} ++_size;
}

template<typename T>
bool SingleLinkedList<T>::pop_front()
{
	if (!head) return false;
	Node* temp_pointer = head;
	head = head->next;
	delete temp_pointer;
	--_size;
	if (!head) tail = nullptr;
	return true;
}