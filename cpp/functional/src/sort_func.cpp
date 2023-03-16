// Functional Style Sort 
// Mia Weber
// 03/14/2023
// CSCI330 Programming Languages

#include <iostream>
#include "sort_func.h"
#include "utility.h"
#include "merger.h"

bool greaterThan(std::vector<std::string> &vec, size_t comp1, size_t comp2) {
    int min = minIndex(vec,comp1,comp2+1);

    if (min == comp2) { 
        return true; // yes! first value is greater than second value!
    }

    return false; // no! first value is NOT greater than second value!
}

std::vector<std::string> doSwap(const std::vector<std::string> &sorted, size_t j) {
    std::vector<std::string> result = vec(sorted);
   
    result = swap(result, j, j+1); // swap the smaller element with the element to it's right

    if (j+1 < result.size()-1) { // if there is an element to the right of j
        if (greaterThan(result, j+1, j+2)) { 
            result = doSwap(result, j+1);
        }
    }
    return result;
}

std::vector<std::string> insertion(std::vector<std::string> &progress, size_t n) {
    std::vector<std::string> sorted = vec(progress); // make a copy of the input vector progress
    size_t m = sorted.size(); 

    if (sorted.size() <= 1 || n < 1) { // base case: if the vector is 0 or 1 or you have been through it all then you're done
        return sorted;
    }

    if (greaterThan(sorted, n-1, n)) { 
        sorted = doSwap(sorted, n-1); 
    }

    return insertion(sorted, n-1);
}

std::vector<std::string> sort_func(const std::vector<std::string> &items) {
    if (items.size() <= 1) { return items; }

    std::vector<std::string> progress = vec(items);
    size_t n = progress.size();

    return (insertion(progress,n-1));
}