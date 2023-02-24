#include "sort_func.h"
// MERGE SORT!!
// staple sort -> doesn't modify the position of elements if they are equal (not out of order, don't change anything)

std::vector<std::string> merge(const std::vector<std::string> &first, const std::vector<std::string> &second, std::vector<std::string>) {
  auto i = first.begin();
  auto j = second.begin(); 

  if (j == second.end()) {
    return first;
  }
  if (i == first.end()) {
    return second;
  }
  

  std::vector<std::string> ans;

  if ()

  // This loop is still very procedural
  while (i != first.end() && j!= second.end()) { // While theres something in both lists
    if (*j < *i) { // Want to move something from j
      ans.push_back(*j);
      ++j;
    } else {
      ans.push_back(*i);
      ++i;
    }
  }

 return ans;
}

// sort first half, sort second half, merge two sorted lists together and return
std::vector<std::string> sort_func(std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end) {
  size_t size = end - begin; // Get the distance between the two iterators = size of the vector
  if (size <=1) {
      return std::vector<std::string> (begin, end); // Can't return items, create a new vector to return
    }

  // sort(a,b) = [a,b)
  auto firstBegin = begin; // Beginning of the list
  auto firstEnd = firstBegin + size/2; // Halfway through the list
  auto secondBegin = firstEnd; 
  auto secondEnd = end; // End of the list

  auto firstSorted = sort_func(firstBegin, firstEnd);
  auto secondSorted = sort_func(secondBegin, secondEnd);

  return merge(firstSorted, secondSorted);
}


// const & so that you can't modify the original data and can't be void because it needs to hand back a new list of things
std::vector <std::string> sort_func(const std::vector<std::string> &items) {
  // TODO sort the items using a functional programming style.
  return sort_func(items.begin(), items.end());

}
