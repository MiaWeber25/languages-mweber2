#include <cmath>
#include "lists.h"
#include "gtest/gtest.h"

#include <list>


TEST(Replace, IntList) {
    std::list <int> items = {1, 9, 7, 8, 9};

    int search = 9;
    int with = 2;
    std::list <int> expect = {1, 2, 7, 8, 2};
    std::list <int> result = items;

    int count = lists::replace(result.begin(), result.end(), search, with);

    ASSERT_EQ(expect, result);
    ASSERT_EQ(2, count);
}
