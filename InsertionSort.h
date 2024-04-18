//
// Created by Michał Dzik on 14.04.2024.
//

#include "SortAlgorithm.h"

#ifndef UNTITLED_INSERTIONSORT_H
#define UNTITLED_INSERTIONSORT_H

#endif //UNTITLED_INSERTIONSORT_H


template <typename T>
class InsertionSort : public SortAlgorithm<T> {

public:
    void sort(T* array, int size) override {
        // Kod sortowania przez wstawianie
        for (int i = 1; i < size; ++i) {
            T key = array[i];
            int j = i - 1;
            while (j >= 0 && array[j] > key) {
                array[j + 1] = array[j];
                j = j - 1;
            }
            array[j + 1] = key;
        }
    }
};