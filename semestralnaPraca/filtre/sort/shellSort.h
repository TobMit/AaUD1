//
// Created by Tobias on 28/05/2022.
//
#include <iostream>
#include "unsorted_sequence_table.h"
#include "array_list.h"

class ShellSort {
public:
    ShellSort();

private:
    void sortData(structures::ArrayList<int> &arrList, int nSize, bool zozstupne);
    void printArray(structures::ArrayList<int> &array, int size);

};

inline ShellSort::ShellSort() {
    structures::ArrayList<int> *data = new structures::ArrayList<int>;
    for (int i = 1; i <= 99; i++) {
        data->add(i);
    }
    int size = data->size();
    sortData(*data, size, true);
    cout << "Sorted array: \n";
    printArray(*data, size);
    delete data;
}


inline void ShellSort::sortData(structures::ArrayList<int> &arrList, int nSize, bool zozstupne) {
    for (int krok = nSize / 2; krok > 0; krok /= 2) {
        for (int delta = 0; delta < krok ; delta++) {
            for (int i = delta; i < nSize; i += krok) {
                int j = i;
                if (!zozstupne) {
                    while (j - krok >= delta && arrList.at(j) < arrList[j - krok]) {
                        structures::Utils::swap(arrList.at(j), arrList.at(j - krok));
                        j -= krok;
                    }
                } else {
                    while (j - krok >= delta && arrList.at(j) > arrList[j - krok]) {
                        structures::Utils::swap(arrList.at(j), arrList.at(j - krok));
                        j -= krok;
                    }
                }
            }

        }

    }

}

inline void ShellSort::printArray(structures::ArrayList<int> &array, int size) {
    int i;
    for (i = 0; i < size; i++)
        cout << array.at(i) << " ";
    cout << endl;
}
