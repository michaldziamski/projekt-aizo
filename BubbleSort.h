//
// Created by Michał Dzik on 14.04.2024.
//

#include <algorithm>
#include "SortAlgorithm.h"

#ifndef UNTITLED_BUBBLESORT_H
#define UNTITLED_BUBBLESORT_H

#endif //UNTITLED_BUBBLESORT_H


template <typename T>
class BubbleSort : public SortAlgorithm<T> {
public:
    void sort(T* array, int size) override {
        // Kod sortowania bąbelkowego
        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < size - i - 1; ++j) {
                if (array[j] > array[j + 1]) {
                    std::swap(array[j], array[j + 1]);
                }
            }
        }
    }
};