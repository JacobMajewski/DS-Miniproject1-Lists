#pragma once
#include "List.hpp"

template <typename T>
class SingleLinkedList : public List<T>
{
private:
    struct Node {
        T data;
        Node* next;
        Node(T val, Node* nxt = nullptr) : data(val), next(nxt) {}
    };

    Node* head;

public:
    SingleLinkedList();
    ~SingleLinkedList();

    size_t size() override;
    bool isEmpty() override;
    int search(T elem) override;
    T atIndex(size_t index) override;

    void add(T elem, size_t index) override;
    void addFront(T elem) override;
    void addBack(T elem) override;

    T popBack() override;
    T popFront() override;
    T pop(size_t index) override;

private:
    Node* getNode(size_t index);
    void clear();
};
