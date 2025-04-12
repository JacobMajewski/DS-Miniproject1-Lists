#include "ArrayList.hpp"
#include "List.hpp"
template <typename T>
ArrayList<T>::ArrayList<T>() : _capacity(4), _start(1), List<T>() { content = new T[4]; }
template<typename T>
size_t ArrayList<T>::last() //helper to calc last index
{
	return _size + _start;
}
template <typename T>
size_t ArrayList<T>::size() 
{
	return _size;
}
template <typename T>
 bool  ArrayList<T>::isEmpty()
 {
	 return _size == 0;
 }
 template <typename T>
 T atIndex(size_t index)
 {

 }
 template <typename T>
 size_t ArrayList<T>::search(T elem)
 {
	 for(size_t inx = _start; i < size_
	 return idx;
 }
 template <typename T>
 void ArrayList<T>::add(T elem, size_t index)
 {
	 if (index >= start && index < _capacity-1)
	 {
		 for (size_t idx = size_; idx>index; idx++)
			 content
	 }
 }
 template <typename T>
 void ArrayList<T>::addFront(T elem)
 {

 }
 template <typename T>
 void  ArrayList<T>::addBack(T elem)
 {
	 last();
 }