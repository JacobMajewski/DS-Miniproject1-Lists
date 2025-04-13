#include "DoubleLinkedList.hpp"
#include "List.hpp"
#include <stdexcept>

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList() : head(nullptr), tail(nullptr) {
    this->_size = 0;
}

template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {
    clear();
}

template <typename T>
void DoubleLinkedList<T>::clear() {
    Node* current = head;
    while (current) {
        Node* tym = current;
        current = current->next;
        delete tym;
    }
    head = tail = nullptr;
    this->_size = 0;
}

template <typename T>
size_t DoubleLinkedList<T>::size() {
    return this->_size;
}

template <typename T>
bool DoubleLinkedList<T>::isEmpty() {
    return this->_size == 0;
}

template <typename T>
typename DoubleLinkedList<T>::Node* DoubleLinkedList<T>::getNode(size_t index) {
    if (index >= this->_size) return nullptr;

    Node* current;
    if (index < this->_size / 2) {
        current = head;
        for (size_t i = 0; i < index; ++i)
            current = current->next;
    }
    else {
        current = tail;
        for (size_t i = this->_size - 1; i > index; --i)
            current = current->prev;
    }
    return current;
}

template <typename T>
int DoubleLinkedList<T>::search(T elem) {
    Node* current = head;
    size_t index = 0;
    while (current) {
        if (current->data == elem)
            return index;
        current = current->next;
        ++index;
    }
    return -1;
}

template <typename T>
T DoubleLinkedList<T>::atIndex(size_t index) {
    if (index >= this->_size)
        throw std::out_of_range("Invalid index");

    Node* node = getNode(index);
    return node ? node->data : T();
}

template <typename T>
void DoubleLinkedList<T>::addFront(T elem) {
    Node* newNode = new Node(elem, nullptr, head);
    if (head) head->prev = newNode;
    head = newNode;
    if (!tail) tail = head;
    this->_size++;
}

template <typename T>
void DoubleLinkedList<T>::addBack(T elem) {
    Node* newNode = new Node(elem, tail, nullptr);
    if (tail) tail->next = newNode;
    tail = newNode;
    if (!head) head = tail;
    this->_size++;
}

template <typename T>
void DoubleLinkedList<T>::add(T elem, size_t index) {
    if (index > this->_size)
        throw std::out_of_range("Invalid index");

    if (index == 0) addFront(elem);
    else if (index == this->_size) addBack(elem);
    else {
        Node* nextN = getNode(index);
        Node* prevN = nextN->prev;
        Node* newN = new Node(elem, prevN, nextN);
        if (prevN)
            prevN->next = newN;
        nextN->prev = newN;
        this->_size++;
    }
}

template <typename T>
T DoubleLinkedList<T>::popFront() {
    if (isEmpty()) return T();

    Node* node = head;
    T val = node->data;
    head = head->next;
    if (head)
        head->prev = nullptr;
    else
        tail = nullptr;
    delete node;
    this->_size--;
    return val;
}

template <typename T>
T DoubleLinkedList<T>::popBack() {
    if (isEmpty()) return T();

    Node* node = tail;
    T val = node->data;
    tail = tail->prev;
    if (tail)
        tail->next = nullptr;
    else
        head = nullptr;

    delete node;
    this->_size--;
    return val;
}

template <typename T>
T DoubleLinkedList<T>::pop(size_t index) {
    if (index >= this->_size || isEmpty()) return T();

    if (index == 0) return popFront();
    if (index == this->_size - 1) return popBack();

    Node* node_delete = getNode(index);
    T value = node_delete->data;

    Node* prevN = node_delete->prev;
    Node* nextN = node_delete->next;

    if (prevN) prevN->next = nextN;
    if (nextN) nextN->prev = prevN;

    delete node_delete;
    this->_size--;

    return value;
}
