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

public:
	ArrayList();
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
};

