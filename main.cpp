#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include "ArrayList.hpp"
#include "SingleLinkedList.hpp"
#include "DoubleLinkedList.hpp"
const int Sizes[]{ 5000, 10000, 25000, 50000, 100000, 250000, 500000, 1000000 };
int main()
{
    
    for (auto& e : Sizes)
    {
        ArrayList<int> Array[10];
        SingleLinkedList<int> Single[10];
        DoubleLinkedList<int> Double[10];
    }
    std::cout << "Hello World!\n";
}
