#include <iostream>
#include <iterator>
#include <string>
#include <regex>

#include "gtest/gtest.h"


TEST(RegEx,JsonStrings) {
  //
  // TODO: change your-ad-here to a regular expression that passes this test
  //
  //std::basic_regex re(R"=(your-ad-here)=",std::regex::extended);  

  // below is the simple regex that passes here: https://regexr.com/7ca8u   
  //std::basic_regex re(R"=(^"\(\(?=\)\("|/|\\|b|"|f|n|r|t|u[0-9a-f]{4}\)|[^\\"]*\)*"$)=",std::regex::extended); 
  // once you combine or statements and correct the escaping issues for c++ you get the following:

  std::basic_regex re(R"=("([^\"\\]|\\([\"\\/fnrtb]|u([1-9]|[A-F]){4}))*")=",std::regex::extended);
   
  
    std::vector<std::string> pass = {
    R"=("")=",
    R"=("x")=",
    R"=("'")=",
    R"=(" ")=",
    R"=("\"")=",
    R"=("\\")=",
    R"=("\/")=",
    R"=("\b")=",
    R"=("\n")=",
    R"=("\r")=",
    R"=("\t")=",
    R"=("\uAD7F")=",
    R"=("\\x")=",
    R"=("\"'")=",
    R"=(" \/")=",
    R"=("\"\"")=",
    R"=("\b\\")=",
    R"=("\/")=",
    R"=("\uAD7F\b")=",
    R"=("\nx")=",
    R"=("x\r")="
  };

  std::vector<std::string> fail = {
    R"=(")=",
    R"=('x')=",
    R"=(""")=",
    R"=(" )=",
    R"=("""")=",
    R"=("\z")=",
    R"=("\1")="
  };

  std::vector<std::pair<std::string,bool>> incorrect;

  for (auto ok : pass) {
     std::match_results<std::string::iterator> results;
     bool ans = std::regex_search(ok.begin(),ok.end(),results,re);
     if (ans != true || results[0] != ok) {
       incorrect.push_back(std::make_pair(ok,ans));
     }
  }

  for (auto bad : fail) {
     std::match_results<std::string::iterator> results;
     bool ans = std::regex_search(bad.begin(),bad.end(),results,re);
     if (ans == true && results[0] == bad) {
       incorrect.push_back(std::make_pair(bad,ans));
     }
  }

  for (auto err : incorrect) {
    if (err.second == true) {
      std::cout << "Incorrectly matched: " ;
    } else {
      std::cout << "Incorrectly failed: ";
    }
    std::cout << err.first << std::endl;
  }

  ASSERT_TRUE(incorrect.empty());
}
