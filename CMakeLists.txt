cmake_minimum_required(VERSION 3.28)
project(untitled)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

set(SOURCE_FILES main.cpp)
add_executable(untitled main.cpp
        SortAlgorithm.cpp
        InsertionSort.cpp
        InsertionSort.h
        HeapSort.h
        HeapSort.cpp
        QuickSort.h
        QuickSort.cpp
        MergeSort.h
        MergeSort.cpp
        BubbleSort.h
        BubbleSort.cpp
        BinaryInsertionSort.h
        BinaryInsertionSort.cpp
)
