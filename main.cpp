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
    ArrayList<int> Array();
    SingleLinkedList<int> Single();
    DoubleLinkedList<int> Double();
    for (auto &e : Sizes)

    std::cout << "Hello World!\n";
}
