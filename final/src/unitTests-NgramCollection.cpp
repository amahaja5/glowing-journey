/*
 * Unit test cases for NgramCollection class.
 *
 * Since there's only one real function, there's only one 
 * method to test
 *
 * Author: Avi Mahajan (amahaja5) and Nick Skacel (nskacel1) 
 * (adapted from old scaffolding code)
 * Date last modified: 12/7/2016
 */

#include "../include/catch.hpp" // simple unit-testing framework
#include "../include/NgramCollection.hpp" // header declaring the functions we want to test

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <algorithm>
using std::string;
using std::vector;
using std::list;

/* test getN, should be pretty easy
 */
TEST_CASE("getN", "[getN]") {
  NgramCollection g3(3);
  NgramCollection g4(4);
  REQUIRE(g3.getN() == 3);
  REQUIRE(g4.getN() == 4);
}

TEST_CASE("increment vector", "[increment]") {
  NgramCollection g3(3);
  vector<string> v {"four", "score", "and", "seven", "years", "ago"};
  for (auto it = v.begin(); it+3 != v.end(); ++it) {
    g3.increment(it, it+3);
  }
  auto it3 = v.begin();
  vector<vector<string>> Ngrams;
  for (int i = 0; i < 4; i++) {
    vector<string> v (it3 + i, it3 + 3 + i);
    Ngrams.push_back(v);
  }
  std::sort(Ngrams.begin(), Ngrams.end());
  auto it = Ngrams.begin();
  for (auto it2 = g3.counts.begin(); it2 != g3.counts.end(); ++it2) {
    REQUIRE(it2->first == *it);
    REQUIRE(it2->second == 1);
    it++;
  }
}
