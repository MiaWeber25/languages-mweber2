#include <utility.h>

std::vector<std::string> vec(std::size_t n, std::function<std::string (std::size_t i)> f) {
  std::vector<std::string> ans(n,std::string());
  for (size_t i = 0; i<n; ++i) {
    ans[i]=f(i);
  }
  return ans;
}

std::vector<std::string> vec() { return std::vector<std::string>(); }

std::vector<std::string> vec(const std::string &a) { return std::vector<std::string>((&a)+0,(&a)+1); }

std::vector<std::string> vec(const std::vector<std::string> &a) { return a; }

std::vector<std::string> vec(const std::string &a, const std::string &b) {
  return vec(vec(a),vec(b));
}

std::vector<std::string> vec(const std::string &a, const std::vector<std::string> &b) {
  return vec(vec(a),b);
}

std::vector<std::string> vec(const std::vector<std::string> &a, const std::string &b) {
  return vec(a,vec(b));
}

std::vector<std::string> vec(const std::vector<std::string> &a, const std::vector<std::string> &b) {
  std::vector < std::string> ans;
  ans.reserve(a.size()+b.size());
  ans.insert(ans.end(),a.begin(),a.end());
  ans.insert(ans.end(),b.begin(),b.end());
  return ans;
}

std::vector<std::string> slice(const std::vector < std::string > &a, size_t begin, size_t end) {
  return std::vector<std::string>(a.begin()+begin,a.begin()+end);
}

std::vector <std::string> swap(const std::vector < std::string > &a, size_t i, size_t j) {
  std::vector < std::string > ans(a);
  ans.at(i)=a.at(j);
  ans.at(j)=a.at(i);
  return ans;
}

size_t minIndex(const std::vector < std::string > &a, size_t begin, size_t end) {
  size_t i = -1;
  for (size_t j = begin; j < end; ++j) {
    if (i == -1 || a[j] < a[i]) { i = j; }
  }
  return i;
}


