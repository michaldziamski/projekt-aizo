//
// Created by Michał Dzik on 14.04.2024.
//

#ifndef UNTITLED_SORTALGORITHM_H
#define UNTITLED_SORTALGORITHM_H

template<typename T>
class SortAlgorithm {

public:
    virtual void sort(T* array, int size) = 0;

    virtual ~SortAlgorithm() {}
};


#endif //UNTITLED_SORTALGORITHM_H
