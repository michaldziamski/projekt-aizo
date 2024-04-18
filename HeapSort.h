//
// Created by Michał Dzik on 14.04.2024.
//

#include <algorithm>
#include "SortAlgorithm.h"

#ifndef UNTITLED_HEAPSORT_H
#define UNTITLED_HEAPSORT_H

#endif //UNTITLED_HEAPSORT_H


template <typename T>
class HeapSort : public SortAlgorithm<T> {
public:
    void sort(T* array, int size) override {
        // Kod sortowania przez kopcowanie
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(array, size, i);
        }
        for (int i = size - 1; i >= 0; i--) {
            std::swap(array[0], array[i]);
            heapify(array, i, 0);
        }
    }

private:
    void heapify(T* array, int size, int index) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        if (left < size && array[left] > array[largest]) {
            largest = left;
        }
        if (right < size && array[right] > array[largest]) {
            largest = right;
        }
        if (largest != index) {
            std::swap(array[index], array[largest]);
            heapify(array, size, largest);
        }
    }
};