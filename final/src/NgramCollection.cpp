#include "NgramCollection.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cassert>

/* take iterators to the start/end of an Ngram, increment the appropriate
 * element of the map */
void NgramCollection :: increment(std::vector<std::string>::const_iterator begin,
                   std::vector<std::string>::const_iterator end) {
  assert(end - begin == n); // make sure we've got the right number of words
  std::vector<std::string> words; // make a vector containing the first n-1 words
  for (auto i = begin; i != end; ++i) {
    words.push_back(*i);
  }
  counts[words]++; // increment the corresponding count
}
