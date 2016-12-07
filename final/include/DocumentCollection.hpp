#ifndef CS120_DOCUMENT_COLLECTION_HPP
#define CS120_DOCUMENT_COLLECTION_HPP
/** Header file for DocumentCollection.
 *
 * Author: Avi Mahajan (amahaja5) and Nick Skacel (nskacel1)
 * modified: 12/7/16
 */
#include <vector>
#include <string>
#include <cassert>
#include "NgramCollection.hpp"
#include <algorithm>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <utility>
#include <cmath>
#include <map>

class DocumentCollection {

public:

  // constructor; need to specify N
  DocumentCollection(int num) : n(num) { assert(n > 1); }

  void pushBackDoc(std::pair<std::string,NgramCollection> docNgram);

  NgramCollection getNgram(unsigned index);

  std::string getDocName(unsigned index);

  void buildNgrams(const std::vector<std::string> &text, std::string fname);

  // takes name of a file that contains paths to the documents
  void readFileList(std::string fname);

  // add text from the given filename to the model
  void addTextFromFile(std::string fname);
 
  int get_N() {
    return n;
  }

  unsigned getSize() {
    return docVector.size();
  }
  
  double similarity(NgramCollection q, NgramCollection d);

//  int docFrequency(std::vector<std::string> term);

  void examineAllDocs(double); 

  void printListOfPairs();

private:
  // read a list of paths from a file
  std::vector<std::string> readNames(std::string listFile);

  // add ngrams to the model from a vector of words
  void buildNgrams(const std::vector<std::string> &text);
  
  // stores actual ngram-count information
  std::vector<std::pair<std::string,NgramCollection> > docVector;
  
  std::vector<std::pair<std::string, std::string> > plPairs;
  
//  std::map<std::pair<std::string, std::string>, double> pairsWithScore;

  int n;
};

#endif
