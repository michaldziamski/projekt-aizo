//
// Created by Michał Dzik on 14.04.2024.
//

#include "SortAlgorithm.h"

#ifndef UNTITLED_MERGESORT_H
#define UNTITLED_MERGESORT_H

#endif //UNTITLED_MERGESORT_H

template <typename T>
class MergeSort : public SortAlgorithm<T> {
public:
    void sort(T* array, int size) override {
        mergeSort(array, 0, size - 1);
    }

private:
    void mergeSort(T* array, int low, int high) {
        if (low < high) {
            int mid = low + (high - low) / 2;
            mergeSort(array, low, mid);
            mergeSort(array, mid + 1, high);
            merge(array, low, mid, high);
        }
    }

    void merge(T* array, int low, int mid, int high) {
        int n1 = mid - low + 1;
        int n2 = high - mid;
        T* L = new T[n1];
        T* R = new T[n2];
        for (int i = 0; i < n1; i++) {
            L[i] = array[low + i];
        }
        for (int j = 0; j < n2; j++) {
            R[j] = array[mid + 1 + j];
        }
        int i = 0;
        int j = 0;
        int k = low;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                array[k] = L[i];
                i++;
            } else {
                array[k] = R[j];
                j++;
            }
            k++;
        }
        while (i < n1) {
            array[k] = L[i];
            i++;
            k++;
        }
        while (j < n2) {
            array[k] = R[j];
            j++;
            k++;
        }
        delete[] L;
        delete[] R;
    }
};