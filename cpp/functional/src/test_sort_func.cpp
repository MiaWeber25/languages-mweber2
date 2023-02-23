#include <cmath>
#include "sort_func.h"
#include "gtest/gtest.h"
using namespace std;

// print out vectors in [a,b,c,...] format:
template <typename T>
std::ostream& operator<<(std::ostream &out, const std::vector < T > &a) { // Override << 
  out << "[";
  bool first = true;
  for (auto x : a) { // Loop over the vector of type T
    if (first) {
      first = false;
    } else {
      out << ",";
    }
    out << x;
  }
  out << "]";
  return out;
}

// sample items to test on
const std::vector < std::string> samples = { 
      "", " ", "1", "11", "2", "a", "apple", "cart"
};

// number of arrangements of length m from items (duplication ok)
template <typename T>
int arrangements(const std::vector<T> &items, int len) {
    return (int) pow(items.size(),len);
}

// i'th arrangment
template <typename T>
std::vector < T > arrangement(const std::vector< T > &items, int len, int i) {
  std::vector < std::string > ans(len,"");
  for (int k=0; k<len; ++k) {
    ans[k] = items[i % items.size()];
    i = i / items.size();
  }
  return ans;
}

// Test that arrangements are correct
TEST(Sort,Arrangements) {
  std::vector < std::string > s1 = {"x"};
  std::vector < std::string > s3 = {"x","y","z"};

  ASSERT_EQ(1,arrangements(s1,4));
  ASSERT_EQ(81,arrangements(s3,4));
  
  std::vector < std::string > s3_0 = {"x","x","x","x"};
  std::vector < std::string > s3_1 = {"y","x","x","x"};
  std::vector < std::string > s3_2 = {"z","x","x","x"};
  std::vector < std::string > s3_3 = {"x","y","x","x"};
  std::vector < std::string > s3_9 = {"x","x","y","x"};
  std::vector < std::string > s3_80 = {"z","z","z","z"};

  ASSERT_EQ(s3_0,arrangement(s3,4,0));
  ASSERT_EQ(s3_1,arrangement(s3,4,1));
  ASSERT_EQ(s3_2,arrangement(s3,4,2));
  ASSERT_EQ(s3_3,arrangement(s3,4,3));
  ASSERT_EQ(s3_9,arrangement(s3,4,9));
  ASSERT_EQ(s3_80,arrangement(s3,4,80));
}

// test functional style; all arrangments of samples, len < 4
TEST(Sort, Func) {
  std::vector < std::string> duplicate = {};
  std::vector < std::string > expect = {};
  std::vector < std::string> result;

  for (int len = 0; len < 4; ++len) {
    int n = arrangements(samples,len);
    for (int i = 0; i < n; ++i) {
      auto items = arrangement(samples,len,i);
      auto dup = items;

      std::vector < std::string > expect(items);
      std::sort(expect.begin(),expect.end()); // STD sort will sort a vector of strings alphabeticaclly 

      std::vector < std::string > result = sort_func(items); 
      ASSERT_EQ(dup, items) << " for items = " << items;
     

      ASSERT_EQ(expect,result) << " for items = " << items;
    }
  }
}
