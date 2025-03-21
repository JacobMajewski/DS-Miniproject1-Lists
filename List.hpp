#pragma once


template <typename T>
class List
{

private:

	int size;

public:

	List() : size(0) {}
	List(int size) : size(size) {}

	virtual int      size() = 0;
	virtual bool  isEmpty() = 0;
	virtual T     atIndex() = 0;
	virtual int    search() = 0;
	virtual void      add() = 0;
	virtual void addFront() = 0;
	virtual void  addBack() = 0;

};

