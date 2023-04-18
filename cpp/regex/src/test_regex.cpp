#include <iostream>
#include <iterator>
#include <string>
#include <regex>

#include "gtest/gtest.h"

TEST(RegEx,AOk) {
  std::basic_regex re("a");
  std::string candidate = "a";
  bool ans = std::regex_match(candidate.begin(),candidate.end(),re);

  ASSERT_TRUE(ans);
}

TEST(RegEx,BNotOk) {
  std::basic_regex re("a",std::regex::extended);
  std::string candidate = "b";
  bool ans = std::regex_match(candidate.begin(),candidate.end(),re);

  ASSERT_FALSE(ans);
}

TEST(RegEx,Apple) {
  std::basic_regex re("a",std::regex::extended);
  std::string candidate = "apple";
  bool ans = std::regex_match(candidate.begin(),candidate.end(),re);

  ASSERT_FALSE(ans);
}

TEST(RegEx,NyanCatKing) {
  std::basic_regex re(".*cat.*",std::regex::extended);
  std::string candidate = "nyan cat is king";
  bool ans = std::regex_match(candidate.begin(),candidate.end(),re);

  ASSERT_TRUE(ans);
}


TEST(RegEx,CatsAndDogs) {
  std::basic_regex re("(cat|dog)(|s)",std::regex::extended);
  std::match_results<std::string::iterator> results;
  std::string candidate = "the cats is dog dogs cat dog";
  bool ans = std::regex_search(candidate.begin(),candidate.end(),results,re);
  ASSERT_TRUE(ans);

  std::string prefix = results.prefix();
  ASSERT_EQ(prefix,"the ");

  for (size_t i = 0; i < results.size(); ++i) 
    std::cout << "match " << i << ": " << results[i] << std::endl;
}

TEST(RegEx,PhoneNum) {
  // std::basic_regex re("([0-9]{10}|[0-9]{3}-[0-9]{3}-[0-9]{4}|\\([0-9]{3}\\) [0-9]{3}-[0-9]{4})",std::regex::extended);
  //    std::basic_regex re("([0-9]{10}|[0-9]{3}-[0-9]{3}-[0-9]{4}|\\([0-9]{3}\\) [0-9]{3}-[0-9]{4})",std::regex::extended);
  //  std::basic_regex re(R"=(([0-9]{3})|\(([0-9]{3})\))[- .]?([0-9]{3})[- .]?([0-9]{4})=",std::regex::extended);
  //std::basic_regex re(R"=()[- .]?([0-9]{3})[- .]?([0-9]{4})=",std::regex::extended);
  std::basic_regex re(R"=(([0-9]{3}|\(([0-9]{3})\))[- .]?([0-9]{3})[- .]?([0-9]{4}))=",std::regex::extended);    

  std::vector<std::string> pass = {
    "9072551234", 
    "907-255-1234",
    "(907) 255-1234",
  };

  std::vector<std::string> fail = {
    "90725512345",
    "07-255-1234",
    "(907 255-1234",
  };

  for (auto ok : pass) {
     std::match_results<std::string::iterator> results;
     bool ans = std::regex_search(ok.begin(),ok.end(),results,re);
     std::string area_code = (results[2] != "") ? results[2] : results[1];
     std::string prefix = results[3];
     std::string line_number = results[4];
     std::cout << area_code << "," << prefix << "," << line_number << std::endl;     
     ASSERT_TRUE(ans);
  }

  for (auto bad : fail) {
    ASSERT_FALSE(std::regex_match(bad.begin(),bad.end(),re)) << " for " << bad;
  }
}
