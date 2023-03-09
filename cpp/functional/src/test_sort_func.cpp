#include <cmath>
#include <vector>
#include "gtest/gtest.h"

#include "utility.h"
#include "sort_func.h"


// sample items to test on
const std::vector < std::string> samples = { 
      "", " ", "1", "11", "2", "a", "apple", "cart"
};

// test functional style; all arrangments of samples, len < 4
TEST(Sort, Func) {
  std::vector < std::string > duplicate = {};
  std::vector < std::string > expect = {};
  std::vector < std::string> result;

  for (int len = 0; len < 4; ++len) {
    int n = arrangements(samples,len);
    for (int i = 0; i < n; ++i) {
      std::vector < std::string > items = arrangement(samples,len,i);
      std::vector < std::string > dup = items;

      std::vector < std::string > expect(items);
      std::sort(expect.begin(),expect.end());

      std::vector < std::string > result = sort_func(items);
      ASSERT_EQ(dup,items) << " for items = " << STRING(items);

      ASSERT_EQ(expect,result) << " for items = " << STRING(items);
    }
  }
}
