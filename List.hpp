#pragma once


template <typename T>
class List
{

private:

	size_t _size;

public:

	virtual size_t      size() = 0;
	virtual bool  isEmpty() = 0;
	virtual T     atIndex(size_t index) = 0;
	virtual size_t    search(T elem) = 0;
	virtual void      add(T elem, size_t index) = 0;
	virtual void addFront(T elem) = 0;
	virtual void  addBack(T elem) = 0;

};

