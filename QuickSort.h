//
// Created by Michał Dzik on 14.04.2024.
//

#include <algorithm>
#include "SortAlgorithm.h"

#ifndef UNTITLED_QUICKSORT_H
#define UNTITLED_QUICKSORT_H

#endif //UNTITLED_QUICKSORT_H


template <typename T>
class QuickSort : public SortAlgorithm<T> {
public:
    void sort(T* array, int size) override {
        quickSort(array, 0, size - 1);
    }

private:
    void quickSort(T* array, int low, int high) {
        if (low < high) {
            int pi = partition(array, low, high);
            quickSort(array, low, pi - 1);
            quickSort(array, pi + 1, high);
        }
    }

    int partition(T* array, int low, int high) {
        T pivot = array[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++) {
            if (array[j] < pivot) {
                i++;
                std::swap(array[i], array[j]);
            }
        }
        std::swap(array[i + 1], array[high]);
        return i + 1;
    }
};