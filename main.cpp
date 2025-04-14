#include "ArrayList.hpp"
#include "SingleLinkedList.hpp"
#include "DoubleLinkedList.hpp"
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <string>
#include <stdlib.h>

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

    //menu wyboru
int wyborGlowny = 0;
while (true) {
    std::cout << "\n==== STRUKTURY DANYCH ====\n";
    std::cout << "1. Opcja jeden\n";
    std::cout << "2. Opcja dwa\n";
    std::cout << "3. Opcja trzy\n";
    std::cout << "4. Wyjscie\n";
    std::cout << "Wybierz opcje: ";
    std::cin >> wyborGlowny;
    system("CLS");

    if (wyborGlowny == 4) {
        break;
    }

    if (wyborGlowny == 1) {
        int wybor1 = 0;
        while (true) {
            // Menu opcji jeden
            std::cout << "\n-- MENU OPCJI JEDEN --\n";
            std::cout << "1. Podopcja 1\n";
            std::cout << "2. Podopcja 2\n";
            std::cout << "3. Podopcja 3\n";
            std::cout << "4. Podopcja 4\n";
            std::cout << "5. Podopcja 5\n";
            std::cout << "6. Powrot do menu glownego\n";
            std::cout << "Wybierz podopcje: ";
            std::cin >> wybor1;
            system("CLS");

            if (wybor1 == 6) {
                break;
            }

            if (wybor1 == 1) {
                std::cout << "Wykonuje sie kod dla opcji 1 w menu jeden\n";
            }
            else if (wybor1 == 2) {
                std::cout << "Wykonuje sie kod dla opcji 2 w menu jeden\n";
            }
            else if (wybor1 == 3) {
                std::cout << "Wykonuje sie kod dla opcji 3 w menu jeden\n";
            }
            else if (wybor1 == 4) {
                std::cout << "Wykonuje sie kod dla opcji 4 w menu jeden\n";
            }
            else if (wybor1 == 5) {
                std::cout << "Wykonuje sie kod dla opcji 5 w menu jeden\n";
            }
        }
    }
    else if (wyborGlowny == 2) {
        int wybor2 = 0;
        while (true) {
            // Menu opcji dwa
            std::cout << "\n-- MENU OPCJI DWA --\n";
            std::cout << "1. Podopcja 1\n";
            std::cout << "2. Podopcja 2\n";
            std::cout << "3. Podopcja 3\n";
            std::cout << "4. Podopcja 4\n";
            std::cout << "5. Podopcja 5\n";
            std::cout << "6. Powrot do menu glownego\n";
            std::cout << "Wybierz podopcje: ";
            std::cin >> wybor2;
            system("CLS");

            if (wybor2 == 6) {
                break;
            }

            if (wybor2 == 1) {
                std::cout << "Wykonuje sie kod dla opcji 1 w menu dwa\n";
            }
            else if (wybor2 == 2) {
                std::cout << "Wykonuje sie kod dla opcji 2 w menu dwa\n";
            }
            else if (wybor2 == 3) {
                std::cout << "Wykonuje sie kod dla opcji 3 w menu dwa\n";
            }
            else if (wybor2 == 4) {
                std::cout << "Wykonuje sie kod dla opcji 4 w menu dwa\n";
            }
            else if (wybor2 == 5) {
                std::cout << "Wykonuje sie kod dla opcji 5 w menu dwa\n";
            }
        }
    }
    else if (wyborGlowny == 3) {
        int wybor3 = 0;
        while (true) {
            // Menu opcji dwa
            std::cout << "\n-- MENU OPCJI DWA --\n";
            std::cout << "1. Podopcja 1\n";
            std::cout << "2. Podopcja 2\n";
            std::cout << "3. Podopcja 3\n";
            std::cout << "4. Podopcja 4\n";
            std::cout << "5. Podopcja 5\n";
            std::cout << "6. Powrot do menu glownego\n";
            std::cout << "Wybierz podopcje: ";
            std::cin >> wybor3;
            system("CLS");

            if (wybor3 == 6) {
                break;
            }

            if (wybor3 == 1) {
                std::cout << "Wykonuje sie kod dla opcji 1 w menu dwa\n";
            }
            else if (wybor3 == 2) {
                std::cout << "Wykonuje sie kod dla opcji 2 w menu dwa\n";
            }
            else if (wybor3 == 3) {
                std::cout << "Wykonuje sie kod dla opcji 3 w menu dwa\n";
            }
            else if (wybor3 == 4) {
                std::cout << "Wykonuje sie kod dla opcji 4 w menu dwa\n";
            }
            else if (wybor3 == 5) {
                std::cout << "Wykonuje sie kod dla opcji 5 w menu dwa\n";
            }
        }
    }
}

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
