#include "ArrayList.hpp"
#include "List.hpp"

//instead of _size there is this->_size, why? if both classes are templates, compiler doest not see member variable

template <typename T>
ArrayList<T>::ArrayList() : _capacity(4), _start(1), List() { content = new T[4]; }
template <typename T>
ArrayList<T>::~ArrayList() { delete[] content; }
template<typename T>
size_t ArrayList<T>::last() //helper to calc last index
{
	return this->_size + _start;
}
template <typename T>
size_t ArrayList<T>::size() 
{
	return this->_size;
}
template <typename T>
 bool ArrayList<T>::isEmpty()
 {
	 return this->_size == 0;
 }
 template <typename T>
 T ArrayList<T>::atIndex(size_t index)
 {
	 if (index >= _start && index < _capacity - 1)
		 return content[index];
 }
 template <typename T>
 size_t ArrayList<T>::search(T elem)
 {
	 for(size_t idx = _start; idx < this->_size; idx++)
		if(content[idx] == elem) return idx;
	 return -1;
 }
 template <typename T>
 void ArrayList<T>::add(T elem, size_t index)
 {
	 if (index >= 0 && index < _capacity-1)
	 {
		 for (size_t idx = this->_size; idx>index; idx++)
			 content[index] = content[index-1];
	 }
 }
 template <typename T>
 void ArrayList<T>::addFront(T elem)
 {
	 if (_start == 0) resize();
	 _start--;
	 this->_size++;
	 content[_start] = elem;
 }
 template <typename T>
 void  ArrayList<T>::addBack(T elem)
 {

	 if (last() == _capacity - 1) resize();

 }
 template<typename T>
 T ArrayList<T>::popBack()
 {
	 return T();
 }
 template<typename T>
 T ArrayList<T>::popFront()
 {
	 return T();
 }
 template<typename T>
 T ArrayList<T>::pop()
 {
	 return T();
 }
 template <typename T>
 void  ArrayList<T>::resize()
 {								   // therefore i made that even if mass emplacement on either side happens, both end are at least in amortized analysis O(1) time complexity and memory usage is also O(n). Perchance
	 size_t newStart = _capacity; // n "negative indexes"
	 _capacity *= 3;			 // also n back indexes
	 T* newContent = new T[_capacity];
		 for (size_t idx = _start, i = newStart; idx < last(); idx++)
			 newContent[idx + newStart] = content[idx];
		 delete[] content;
		 content = newContent;
		 _start = newStart;
 }