#pragma once

#include "List.hpp"

template <typename T>
class ArrayList : public List<T>
{
protected:
	T* content;
	size_t _capacity;
	size_t _start;
	size_t last();
	void resize();
	void shrink();

public:
	ArrayList();
	ArrayList(size_t size);
	~ArrayList();
	size_t size() override;
	bool isEmpty() override;
	T atIndex(size_t index) override;
	int search(T elem) override;
	void add(T elem, size_t index) override;
	void addFront(T elem) override;
	void addBack(T elem) override;
	T popBack();
	T popFront();
	T pop(size_t index);
	void print() override;

	void clear();
};
template <typename T>
ArrayList<T>::ArrayList() : List<T>(), _capacity(4), _start(1) {
	this->_size = 0;
	content = new T[4];
}
template <typename T>
ArrayList<T>::ArrayList(size_t size) : List<T>(), _capacity(size) {
	this->_size = 0;
	_start = size / 4;
	content = new T[size];
}
template <typename T>
ArrayList<T>::~ArrayList() { delete[] content; }
