#include "ArrayList.hpp"
#include <stdexcept>
#include <iostream>
//instead of _size there is this->_size, why? if both classes are templates, compiler doest not see member variable


template<typename T>
size_t ArrayList<T>::last() //helper to calc last index with value
{
	return this->_size + _start - 1;
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
	 if (index >= this->_size) throw std::out_of_range("Invalid index");
	 return content[_start + index];
 }
 template <typename T>
 int ArrayList<T>::search(T elem)
 {
	 for (size_t i = 0; i < this->_size; ++i)
		 if (content[_start + i] == elem) return i;
	 return -1;
 }
 template <typename T>
 void ArrayList<T>::add(T elem, size_t index) // ah, mate negative indexes
 {
	 if (index > this->_size)
		 throw std::out_of_range("Invalid index");
	 if (last() + 1 == _capacity) resize();
	 size_t realIndex = this->_start + index; // offset

	 for (size_t idx = last() + 1; idx > realIndex; --idx)
		 content[idx] = content[idx - 1];

	 content[realIndex] = elem;
	 this->_size++;
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
 void ArrayList<T>::addBack(T elem)
 {
	 if (_start + this->_size >= _capacity) {
		 resize();
	 }

	 size_t insertIndex = _start + this->_size;
	 content[insertIndex] = elem;
	 this->_size++;
 }
 template<typename T>
 T ArrayList<T>::popBack()
 {
	 if (isEmpty()) throw std::length_error("List is empty");
	 T removed = content[last()];
	 this->_size--;
	 shrink();
	 return removed;
 }
 template<typename T>
 T ArrayList<T>::popFront()
 {
	 if (isEmpty()) throw std::length_error("List is empty");
	 T removed = content[_start];
	 _start++;
	 this->_size--;
	 shrink();
	 return removed;
 }
 template<typename T>
 T ArrayList<T>::pop(size_t index)
 {
	 {
		 if (index >= this->_size) {
			 throw std::out_of_range("Index out of bounds");
		 }

		 T removed = content[_start + index];

		 for (size_t i = _start + index; i <= last(); ++i) {
			 content[i] = content[i + 1];
		 }

		 this->_size--;
		 shrink();
		 return removed;
	 }
 }
 template <typename T>
 void ArrayList<T>::print()
 {
	 if (this->_size == 0) return;
	 for (size_t i = 0; i < this->_size; i++)
		 std::cout << content[_start + i] << " ";
	 std::cout << std::endl;
 }
 template <typename T>
 void ArrayList<T>::resize() {
	 size_t oldCapacity = _capacity;
	 T* oldContent = content;

	 _capacity *= 2;
	 content = new T[_capacity];

	 size_t newStart = _capacity / 2 - this->_size / 2;

	 for (size_t i = 0; i < this->_size; ++i) {
		 content[newStart + i] = oldContent[_start + i];
	 }

	 delete[] oldContent;
	 _start = newStart;
 }
 template <typename T>
 void ArrayList<T>::shrink() {
	 if (this->_size < _capacity / 4 && _capacity > 4) { // zmniejsz tylko jeœli du¿o wolnego miejsca
		 size_t newCapacity = _capacity / 2;
		 size_t newStart = _capacity / 4;
		 T* newContent = new T[newCapacity];

		 for (size_t i = 0; i < this->_size; ++i) {
			 newContent[newStart + i] = content[_start + i];
		 }

		 delete[] content;
		 content = newContent;
		 _capacity = newCapacity;
		 _start = newStart;
	 }
 }

 template <typename T>
 void ArrayList<T>::clear() {
	 delete[] content;
	 size_t startSize = 4;
	 _capacity = 4;
	 _start = 1;
	 content = new T[4];
	 this->_size = 0;
	 
 }

 template class ArrayList<int>;