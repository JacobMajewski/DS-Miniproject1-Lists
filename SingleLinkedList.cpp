#include "SingleLinkedList.hpp"
#include "List.hpp"
#include <stdexcept>



template <typename T>
void SingleLinkedList<T>::clear() {
    while (head != nullptr) {
        Node* tym = head;
        head = head->next;
        delete tym;
    } this->_size = 0;
    tail = nullptr;
}


template <typename T>
size_t SingleLinkedList<T>::size() {
    return this->_size;
}

template <typename T>
bool SingleLinkedList<T>::isEmpty() {
    return this->_size == 0;
}

template <typename T>
typename SingleLinkedList<T>::Node* SingleLinkedList<T>::getNode(size_t index) {
    if (index >= this->_size)
        return nullptr;

    Node* current_node = head;
    for (size_t i = 0; i < index; ++i)
        current_node = current_node->next;

    return current_node;
}

template <typename T>
int SingleLinkedList<T>::search(T elem) {
    Node* current_node = head;
    size_t index = 0;
    while (current_node) {
        if (current_node->data == elem) return index;
        current_node = current_node->next;
        ++index;
    }
    return -1; // not found
}

template <typename T>
T SingleLinkedList<T>::atIndex(size_t index) {
    if (index >= this->_size) throw std::out_of_range("Invalid index");

    Node* node = head;
    for (size_t i = 0; i < index; ++i) node = node->next;

    return node->data;
}

template <typename T>
void SingleLinkedList<T>::add(T elem, size_t index) {
    if (index > this->_size) throw std::out_of_range("Invalid index");

    if (index == 0) addFront(elem);
    else if (index == this->_size) addBack(elem);
    else {
        Node* previous_node = head;
        for (size_t i = 0; i < index-1; i++) previous_node = previous_node->next;
        
        previous_node->next = new Node(elem, previous_node->next);
        this->_size++;
    }
}

template <typename T>
void SingleLinkedList<T>::addFront(T elem) {
    head = new Node(elem, head);
    if (this->_size == 0) tail = head;
    this->_size++;
}

template <typename T>
void SingleLinkedList<T>::addBack(T elem) {
    if (!head) {
        head = new Node(elem);
        tail = head;
    } else {
        tail->next = new Node(elem);
        tail = tail->next;
    }
    this->_size++;
}

template <typename T>
T SingleLinkedList<T>::popBack() {
    if (isEmpty())
        return T();

    if (this->_size == 1) {
        T val = head->data;
        delete head;
        head = nullptr;
        this->_size = 0;
        return val;
    }

    Node* previous_node = head;
    while (previous_node->next != tail) previous_node = previous_node->next;
    T val = tail ->data;
    delete previous_node->next;
    previous_node->next = nullptr;
    tail = previous_node;
    this->_size--;
    return val;
}

template <typename T>
T SingleLinkedList<T>::popFront() {
    if (isEmpty())
        return T();

    Node* tmp = head;
    T val = tmp->data;
    head = head->next;
    delete tmp;
    this->_size--;
    return val;
}
template <typename T>
T SingleLinkedList<T>::pop(size_t index) {
    if (index >= this->_size || isEmpty()) return T();

    if (index == 0) return popFront();

    Node* prev = head;
    for (size_t i = 0; i < index - 1; ++i) {
        prev = prev->next;
    }

    Node* node_delete = prev->next;
    T value = node_delete->data;

    prev->next = node_delete->next;
    if (node_delete == tail) tail = prev;

    delete node_delete;
    this->_size--;

    return value;
}
template class SingleLinkedList<int>;