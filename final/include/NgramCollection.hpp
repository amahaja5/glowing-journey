#ifndef _CS120_NGRAM_COLLECTION_HPP
#define _CS120_NGRAM_COLLECTION_HPP
#include <vector>
#include <list>
#include <map>
#include <string>
#include <cstdlib> // for srand
#include <ctime> // for time(NULL)

class NgramCollection {

public:

  //Generate an NgramCollection object with N equal to argument num
  //Also seeds the RNG (there are better ways of ensuring this only happens once, but this will probably be good enough)
  //Note that you may want to change this to a fixed seed
  //for testing purposes.
  NgramCollection(unsigned num) : n(num) { }

  //Increase count for NgramCollection representing values from begin up to end
  //begin is an iterator to the first word in the Ngram,
  //end is an iterator to the end of the Ngram
  // (so (end - begin) == N)
  void increment(std::vector<std::string>::const_iterator begin,
		 std::vector<std::string>::const_iterator end);

  //Retrieve the value for N
  unsigned getN() const { return n; }

  //the collection of entries in this NgramCollection
  std::map<std::vector<std::string>, unsigned> counts;

  //the number of items in our NgramCollection
  unsigned n;
};

#endif
