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
    void sortData(structures::ArrayList<int> &arrList, int n);
    void printArray(structures::ArrayList<int> &array, int size);

};

inline ShellSort::ShellSort() {
    structures::ArrayList<int> *data = new structures::ArrayList<int>;
    for (int i = 9; i > 0; --i) {
        data->add(i);
    }
    //int size = sizeof(data) / sizeof(data[0]);
    int size = data->size();
    sortData(*data, size);
    cout << "Sorted array: \n";
    printArray(*data, size);
    delete data;
}


inline void ShellSort::sortData(structures::ArrayList<int> &arrList, int n) {
    // Rearrange elements at each n/2, n/4, n/8, ... intervals
    for (int interval = n / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < n; i += 1) {
            int temp = arrList.at(i);
            int j;
            for (j = i; j >= interval && arrList.at(j - interval) > temp; j -= interval) {
                arrList.at(j) = arrList.at(j - interval);
            }
            arrList.at(j) = temp;
        }
    }

}

inline void ShellSort::printArray(structures::ArrayList<int> &array, int size) {
    int i;
    for (i = 0; i < size; i++)
        cout << array.at(i) << " ";
    cout << endl;
}
