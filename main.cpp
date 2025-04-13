#include "ArrayList.hpp"
#include "SingleLinkedList.hpp"
#include "DoubleLinkedList.hpp"
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <string>

// Struktura przechowująca pliki do zapisu
struct OutputFile {
    std::ofstream file;
    std::string operation;
    std::string listType;
};

// Funkcja do zamknięcia plików
void closeFiles(OutputFile files[4][3]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3; ++j) {
            files[i][j].file.close();
        }
    }
}

// Funkcja przygotowująca pliki
void openFiles(OutputFile files[4][3]) {
    const std::string operations[] = { "addBack", "addFront", "addAtIndex", "search" };
    const std::string listNames[] = { "ArrayList", "SingleLinkedList", "DoubleLinkedList" };

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3; ++j) {
            files[i][j].operation = operations[i];
            files[i][j].listType = listNames[j];
            files[i][j].file.open(operations[i] + "_" + listNames[j] + ".csv");
            files[i][j].file << "Size,Time[ns]\n";
        }
    }
}

// Funkcja generująca losową tablicę
int* generateRandomArray(int size, std::mt19937& gen, std::uniform_int_distribution<int>& dist) {
    int* arr = new int[size];
    for (int i = 0; i < size; ++i)
        arr[i] = dist(gen);
    return arr;
}

// Funkcja przygotowująca listę
template <typename ListType>
void prepareList(ListType* list, int* data, int size) {
    for (int i = 0; i < size; ++i)
        list->addBack(data[i]);
}

// Funkcja resetująca listę po operacji (przywrócenie jej do stanu początkowego)
template <typename ListType>
void resetList(ListType* list, int* baseData, int size) {
    list->clear(); // Czyści listę
    for (int i = 0; i < size; ++i)
        list->addBack(baseData[i]); // Ponownie dodaje dane
}

// ------- Benchmark: addBack -------
template <typename ListType>
void benchmarkAddBack(int* baseData, int size, int value, std::ofstream& out) {
    ListType* lists[10];
    for (int i = 0; i < 10; ++i) {
        lists[i] = new ListType();
        prepareList(lists[i], baseData, size);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; ++i)
        lists[i]->addBack(value);
    auto end = std::chrono::high_resolution_clock::now();

    long long duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    out << size << "," << duration << "\n";

    // Resetowanie po badaniu
    for (int i = 0; i < 10; ++i) {
        resetList(lists[i], baseData, size);
        delete lists[i];
    }
}

// ------- Benchmark: popBack -------
template <typename ListType>
void benchmarkPopBack(int* baseData, int size, std::ofstream& out) {
    ListType* lists[10];
    for (int i = 0; i < 10; ++i) {
        lists[i] = new ListType();
        prepareList(lists[i], baseData, size);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; ++i)
        lists[i]->popBack();  // Usuwanie ostatniego elementu
    auto end = std::chrono::high_resolution_clock::now();

    long long duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    out << size << "," << duration << "\n";

    // Resetowanie po badaniu
    for (int i = 0; i < 10; ++i) {
        lists[i]->addBack(baseData[size - 1]);  // Dodanie losowego elementu z powrotem
        resetList(lists[i], baseData, size - 1);  // Przypisanie pierwotnej wersji
        delete lists[i];
    }
}

// ------- Benchmark: addFront -------
template <typename ListType>
void benchmarkAddFront(int* baseData, int size, int value, std::ofstream& out) {
    ListType* lists[10];
    for (int i = 0; i < 10; ++i) {
        lists[i] = new ListType();
        prepareList(lists[i], baseData, size);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; ++i)
        lists[i]->addFront(value);
    auto end = std::chrono::high_resolution_clock::now();

    long long duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    out << size << "," << duration << "\n";

    // Resetowanie po badaniu
    for (int i = 0; i < 10; ++i) {
        resetList(lists[i], baseData, size);
        delete lists[i];
    }
}

// ------- Benchmark: add(index) -------
template <typename ListType>
void benchmarkAddAtIndex(int* baseData, int size, int value, int index, std::ofstream& out) {
    ListType* lists[10];
    for (int i = 0; i < 10; ++i) {
        lists[i] = new ListType();
        prepareList(lists[i], baseData, size);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; ++i)
        lists[i]->add(value, index);
    auto end = std::chrono::high_resolution_clock::now();

    long long duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    out << size << "," << duration << "\n";

    // Resetowanie po badaniu
    for (int i = 0; i < 10; ++i) {
        resetList(lists[i], baseData, size);
        delete lists[i];
    }
}

// ------- Benchmark: Search -------
template <typename ListType>
void benchmarkSearch(int* baseData, int size, int value, int index, std::ofstream& out) {
    ListType* lists[10];
    for (int i = 0; i < 10; ++i) {
        lists[i] = new ListType();
        prepareList(lists[i], baseData, size);
    }
    std::mt19937 gen(100);
    std::uniform_int_distribution<int> dist(0, 1000000);
    int* numbers_to_search = generateRandomArray(10, gen, dist);
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; ++i)
        lists[i]->search(numbers_to_search[i]);
    auto end = std::chrono::high_resolution_clock::now();

    long long duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    out << size << "," << duration << "\n";

    // Resetowanie po badaniu
    for (int i = 0; i < 10; ++i) {
        resetList(lists[i], baseData, size);
        delete lists[i];
    }
}

// Funkcja do przeprowadzenia benchmarków
int main() {
    OutputFile files[4][3]; // Tablica przechowująca pliki
    openFiles(files); // Otwieranie plików przed rozpoczęciem benchmarków

    std::mt19937 gen(777);
    std::uniform_int_distribution<int> dist(0, 1'000'000);
    const int Sizes[]{ 5000, 10000, 25000, 50000, 100000, 250000, 500000, 1000000 };

    for (int size : Sizes) {
        int* baseData = generateRandomArray(size, gen, dist);
        int newValue = dist(gen);
        std::uniform_int_distribution<int> indexDist(0, size - 1);
        int randIndex = indexDist(gen);

        // Wywołanie benchmarków dla różnych operacji
        // --- addBack ---
        benchmarkAddBack<ArrayList<int>>(baseData, size, newValue, files[0][0].file);
        benchmarkAddBack<SingleLinkedList<int>>(baseData, size, newValue, files[0][1].file);
        benchmarkAddBack<DoubleLinkedList<int>>(baseData, size, newValue, files[0][2].file);

        // --- popBack ---
        benchmarkPopBack<ArrayList<int>>(baseData, size, files[1][0].file);
        benchmarkPopBack<SingleLinkedList<int>>(baseData, size, files[1][1].file);
        benchmarkPopBack<DoubleLinkedList<int>>(baseData, size, files[1][2].file);

        // --- addFront ---
        benchmarkAddFront<ArrayList<int>>(baseData, size, newValue, files[2][0].file);
        benchmarkAddFront<SingleLinkedList<int>>(baseData, size, newValue, files[2][1].file);
        benchmarkAddFront<DoubleLinkedList<int>>(baseData, size, newValue, files[2][2].file);

        // --- add(index) ---
        benchmarkAddAtIndex<ArrayList<int>>(baseData, size, newValue, randIndex, files[3][0].file);
        benchmarkAddAtIndex<SingleLinkedList<int>>(baseData, size, newValue, randIndex, files[3][1].file);
        benchmarkAddAtIndex<DoubleLinkedList<int>>(baseData, size, newValue, randIndex, files[3][2].file);

        // --- search ---
        benchmarkSearch<ArrayList<int>>(baseData, size, newValue, randIndex, files[4][0].file);
        benchmarkSearch<SingleLinkedList<int>>(baseData, size, newValue, randIndex, files[4][1].file);
        benchmarkSearch<DoubleLinkedList<int>>(baseData, size, newValue, randIndex, files[4][2].file);

        delete[] baseData; // Zwolnienie pamięci
        std::cout << "Zakończono pomiary dla rozmiaru: " << size << "\n";
    }

    closeFiles(files); // Zamknięcie plików po zakończeniu benchmarków

    std::cout << "Wyniki zapisano w plikach CSV.\n";
    return 0;
}