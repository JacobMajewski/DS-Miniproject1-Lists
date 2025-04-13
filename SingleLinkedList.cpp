#include "SingleLinkedList.hpp"
#include "List.hpp"

template <typename T>
SingleLinkedList<T>::SingleLinkedList() : head(nullptr) {
    this->_size = 0;
}

template <typename T>
SingleLinkedList<T>::~SingleLinkedList() {
    clear();
}

template <typename T>
void SingleLinkedList<T>::clear() {
    while (head != nullptr) {
        Node* tym = head;
        head = head->next;
        delete tym;
    } this->_size = 0;
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
    Node* node = getNode(index);
    if (!node) return T(); //zwraca domyslna wartosc
    return node->data;
}

template <typename T>
void SingleLinkedList<T>::add(T elem, size_t index) {
    if (index > this->_size) return;

    if (index == 0) {
        addFront(elem);
    } else {
        Node* previous_node = getNode(index - 1);
        if (!previous_node) return;
        previous_node->next = new Node(elem, previous_node->next);
        this->_size++;
    }
}

template <typename T>
void SingleLinkedList<T>::addFront(T elem) {
    head = new Node(elem, head);
    this->_size++;
}

template <typename T>
void SingleLinkedList<T>::addBack(T elem) {
    if (!head) {
        head = new Node(elem);
    } else {
        Node* tail = getNode(this->_size - 1);
        if (!tail) return;
        tail->next = new Node(elem);
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

    Node* previous_node = getNode(this->_size - 2);
    if (!previous_node || !previous_node->next) return T();
    T val = previous_node->next->data;
    delete previous_node->next;
    previous_node->next = nullptr;
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
    return popBack();  
}
