// Implementation of Quick Sort in order to sort the given vector "items" (divide and conquer algorithm)
// This is a procedural example because it simply manipulates the given input data rather than copying the input data into another structure
// Mia Weber 
// 02/23/2023
//https://mathworld.wolfram.com/Quicksort.html https://algs4.cs.princeton.edu/23quicksort/ 

#include "sort_proc.h"
 

int partition(std::vector<std::string> &items, int start, int end) { // function to put the pivot in the correct location, then sort to the right of the pivot and to the left of the pivot
  auto p = items[start]; // the first element is always the pivot 
  int count = 0;
  for (int i = start +1; i<= end; i++) { // loop over the vector and find the correct location where the pivot belongs
    if (items[i] <= p) {
      count++;
    }
  }
  
    int pIndex = start + count; // pIndex is the index of p's correct location
    swap(items[pIndex], items[start]); // place p (the pivot) into its correct location

    int i = start;
    int j = end;

  // sort the elements to the right of the pivot and to the left of the pivot (right subfile and left subfile)
  while(i<pIndex && j> pIndex) {
    while (items[i] <= p) {
      i++;
    }
    while (items[j] > p) {
      j--;
    }
    if (i < pIndex && j > pIndex) {
      swap(items[i++], items[j--]);
    }
  }
  return pIndex;
}


void quickSort(std::vector<std::string> &items, int start, int end) { // this is the recursive function that continues to partition smaller and smaller subarrays until the entire vector is sorted
  if (start >= end) { // this is the base case, nothing more to do
    return;
  }

  int p = partition(items, start, end); // partition the vector (p is the pivotIndex)
  quickSort(items, start, p-1); // sort the left side of the partition (everything to the left of the pivotIndex)
  quickSort(items, p+1, end); // sort the right side of the partition (everythign to the right of the pivotIndex)
}

void sort_proc(std::vector<std::string> &items) {
  quickSort(items, 0 , items.size()-1);
}