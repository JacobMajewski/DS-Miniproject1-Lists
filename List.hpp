#pragma once


template <typename T>
class List
{

protected:

	size_t _size;

public:
	List() : _size(0) {}           
	virtual ~List() = default;     

	virtual size_t size() = 0;
	virtual bool  isEmpty() = 0;
	virtual T atIndex(size_t index) = 0;
	virtual int search(T elem) = 0;
	virtual void add(T elem, size_t index) = 0;
	virtual void addFront(T elem) = 0;
	virtual void addBack(T elem) = 0;
	virtual T popBack() = 0;
	virtual T popFront() = 0;
	virtual T pop(size_t index) = 0;
	virtual void print()=0;

};

