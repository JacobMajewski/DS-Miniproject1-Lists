#pragma once

#include "List.hpp"

template <typename T>
class ArrayList : public List<T>
{
private:
	*T content;
	size_t _capacity;
	size_t _start;
	size_t last();
public:
	ArrayList<T>() : _capacity(4), _start(1), List<T>() {}
	size_t size() override;
	bool isEmpty() override;
	T atIndex(size_t index) override;
	size_t search(T elem) override;
	void add(T elem, size_t index) override;
	void addFront(T elem) override;
	void addBack(T elem) override;
};

