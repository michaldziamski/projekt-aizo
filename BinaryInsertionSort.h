//
// Created by Michał Dzik on 16.04.2024.
//

#include "SortAlgorithm.h"

#ifndef UNTITLED_BINARYINSERTIONSORT_H
#define UNTITLED_BINARYINSERTIONSORT_H

#endif //UNTITLED_BINARYINSERTIONSORT_H


template <typename T>
class BinaryInsertionSort : public SortAlgorithm<T> {
public:
    void sort(T* array, int size) override {
        for (int i = 1; i < size; ++i) {
            T key = array[i];
            int left = 0;
            int right = i - 1;

            // Wyszukiwanie binarne miejsca do wstawienia
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (array[mid] < key) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }

            // Przesuwanie elementów większych od key
            for (int j = i - 1; j >= left; --j) {
                array[j + 1] = array[j];
            }
            array[left] = key;
        }
    }
};