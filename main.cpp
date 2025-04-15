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
        lists[i] = new ListType(size);
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
        lists[i] = new ListType(size);
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

// ------- Benchmark: popFront -------
template <typename ListType>
void benchmarkPopFront(int* baseData, int size, std::ofstream& out) {
    ListType* lists[10];
    for (int i = 0; i < 10; ++i) {
        lists[i] = new ListType(size);
        prepareList(lists[i], baseData, size);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; ++i)
        lists[i]->popFront();  // Usuwanie pierwszego elementy
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
        lists[i] = new ListType(size);
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
        lists[i] = new ListType(size);
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

// ------- Benchmark: pop(index) -------
template <typename ListType>
void benchmarkPopAtIndex(int* baseData, int size, int index, std::ofstream& out) {
    ListType* lists[10];
    for (int i = 0; i < 10; ++i) {
        lists[i] = new ListType(size);
        prepareList(lists[i], baseData, size);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10; ++i)
        lists[i]->pop(index);
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
    OutputFile files[7][3]; // Tablica przechowująca pliki
    openFiles(files); // Otwieranie plików przed rozpoczęciem benchmarków

    std::mt19937 gen(777);
    std::uniform_int_distribution<int> dist(0, 1000000);
    const int Sizes[]{ 5000, 10000, 25000, 50000, 100000, 250000, 500000, 1000000 };

    //menu wyboru
    int wyborGlowny = 0;
    while (true) {
        std::cout << "\n==== STRUKTURY DANYCH ====\n";
        std::cout << "1. SinlgeLinkedList\n";
        std::cout << "2. DoubleLinkedList\n";
        std::cout << "3. ArrayList\n";
        std::cout << "4. Uruchom badania\n";
        std::cout << "5. Wyjscie\n";
        std::cout << "Wybierz opcje: ";
        std::cin >> wyborGlowny;
        system("CLS");

        if (wyborGlowny == 5) break;

        if (wyborGlowny == 1) {
            SingleLinkedList<int> sll;
            int wybor1 = 0;
            while (true) {
                // Menu opcji jeden
                std::cout << "\n-- SINGLE LINKED LIST --\n";
                std::cout << "1. Random \n";
                std::cout << "2. Print All\n";
                std::cout << "3. Pop \n";
                std::cout << "4. Add \n";
                std::cout << "5. Search \n";
                std::cout << "6. Powrot do menu glownego\n";
                std::cout << "Wybierz podopcje: ";
                std::cin >> wybor1;

                if (wybor1 == 6) {
                    break;
                }

                if (wybor1 == 1) {
                    int rozmiar;
                    std::cout << "Wybierz rozmiar: ";
                    std::cin >> rozmiar;

                    std::mt19937 gen(std::random_device{}());
                    std::uniform_int_distribution<int> dist(0, 1000000);
                    int* dane = generateRandomArray(rozmiar, gen, dist);
                    prepareList(&sll, dane, rozmiar);
                }
                else if (wybor1 == 2) {
                    sll.print();
                }
                else if (wybor1 == 3) {
                    size_t index_delete;
                    std::cout << "Wybierz indeks do usunięcia: ";

                    std::cin >> index_delete;
                    sll.pop(index_delete);
                }
                else if (wybor1 == 4) {
                    size_t index_delete;
                    int new_element;                std::cout << "Wybierz indeks do dodania: ";

                    std::cin >> index_delete;
                    std::cout << "Podaj wartość do dodania: ";

                    std::cin >> new_element;
                    sll.add(new_element, index_delete);
                }
                else if (wybor1 == 5) {
                    int user_input_value;
                    std::cout << "Wybierz indeks do wyszukania: ";

                    std::cin >> user_input_value;

                    size_t found_index = sll.search(user_input_value);
                    std::cout << found_index;
                }
            }
        }
        else if (wyborGlowny == 2) {
            DoubleLinkedList<int> dll;
            int wybor2 = 0;
            while (true) {
                // Menu opcji dwa
                std::cout << "\n-- DOUBLE LINKED LIST --\n";
                std::cout << "1. Random \n";
                std::cout << "2. Print All\n";
                std::cout << "3. Pop \n";
                std::cout << "4. Add \n";
                std::cout << "5. Search \n";
                std::cout << "6. Powrot do menu glownego\n";
                std::cout << "Wybierz podopcje: ";
                std::cin >> wybor2;


                if (wybor2 == 6) {
                    break;
                }

                if (wybor2 == 1) {
                    int rozmiar;
                    std::cout << "Wybierz rozmiar: ";

                    std::cin >> rozmiar;

                    std::mt19937 gen(std::random_device{}());
                    std::uniform_int_distribution<int> dist(0, 1000000);
                    int* dane = generateRandomArray(rozmiar, gen, dist);
                    prepareList(&dll, dane, rozmiar);
                }
                else if (wybor2 == 2) {
                    dll.print();
                }
                else if (wybor2 == 3) {
                    size_t index_delete;
                    std::cout << "Wybierz indeks do usunięcia: ";

                    std::cin >> index_delete;
                    dll.pop(index_delete);
                }
                else if (wybor2 == 4) {
                    size_t index_delete;
                    int new_element;
                    std::cout << "Wybierz indeks do dodania: ";

                    std::cin >> index_delete;
                    std::cout << "Podaj wartość do dodania: ";

                    std::cin >> new_element;
                    dll.add(new_element, index_delete);
                }
                else if (wybor2 == 5) {
                    int user_input_value;
                    std::cout << "Wybierz indeks do wyszukania: ";

                    std::cin >> user_input_value;

                    size_t found_index = dll.search(user_input_value);
                    std::cout << found_index;
                }
            }
        }
        else if (wyborGlowny == 3) {
            ArrayList<int> arl;
            int wybor3 = 0;
            while (true) {
                // Menu opcji dwa
                std::cout << "\n-- ARRAY LIST --\n";
                std::cout << "1. Random \n";
                std::cout << "2. Print All\n";
                std::cout << "3. Pop \n";
                std::cout << "4. Add \n";
                std::cout << "5. Search \n";
                std::cout << "6. Powrot do menu glownego\n";
                std::cout << "Wybierz podopcje: ";
                std::cin >> wybor3;

                if (wybor3 == 6) {
                    break;
                }

                if (wybor3 == 1) {
                    int rozmiar;
                    std::cout << "Wybierz rozmiar: ";

                    std::cin >> rozmiar;

                    std::mt19937 gen(std::random_device{}());
                    std::uniform_int_distribution<int> dist(0, 1000000);
                    int* dane = generateRandomArray(rozmiar, gen, dist);
                    prepareList(&arl, dane, rozmiar);
                }
                else if (wybor3 == 2) {
                    arl.print();
                }
                else if (wybor3 == 3) {
                    size_t index_delete;
                    std::cout << "Wybierz indeks do usunięcia: ";
                    std::cin >> index_delete;
                    arl.pop(index_delete);
                }
                else if (wybor3 == 4) {
                    size_t index_delete;
                    int new_element;
                    std::cout << "Wybierz indeks do dodania: ";
                    std::cin >> index_delete;
                    std::cout << "Podaj wartość do dodania: ";
                    std::cin >> new_element;
                    arl.add(new_element, index_delete);
                }
                else if (wybor3 == 5) {
                    int user_input_value;
                    std::cout << "Wybierz indeks do wyszukania: ";
                    std::cin >> user_input_value;

                    size_t found_index = arl.search(user_input_value);
                    std::cout << found_index;
                }
            }
            system("CLS");
        }
        else if (wyborGlowny == 4) {
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

                // --- pop(index) ---
                benchmarkPopAtIndex<ArrayList<int>>(baseData, size, randIndex, files[5][0].file);
                benchmarkPopAtIndex<SingleLinkedList<int>>(baseData, size, randIndex, files[5][1].file);
                benchmarkPopAtIndex<DoubleLinkedList<int>>(baseData, size, randIndex, files[5][2].file);

                // --- popFront ---
                benchmarkPopFront<ArrayList<int>>(baseData, size, files[6][0].file);
                benchmarkPopFront<SingleLinkedList<int>>(baseData, size, files[6][1].file);
                benchmarkPopFront<DoubleLinkedList<int>>(baseData, size, files[6][2].file);

                delete[] baseData; // Zwolnienie pamięci
                std::cout << "Zakończono pomiary dla rozmiaru: " << size << "\n";
            }

            closeFiles(files); // Zamknięcie plików po zakończeniu benchmarków

            std::cout << "Wyniki zapisano w plikach CSV.\n";
        }
    }

    
    return 0;
}
