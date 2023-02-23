#include "sort_func.h"


// const & so that you can't modify the original data and can't be void because it needs to hand back a new list of things
std::vector <std::string> sort_func(const std::vector<std::string> &items) {
  // TODO sort the items using a functional programming style.
  auto ans = items;
  std::sort(ans.begin(), ans.end());
  return ans;
}
