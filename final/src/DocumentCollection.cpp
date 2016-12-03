#include "DocumentCollection.hpp"
#include <iostream>
#include <fstream>

/* read a list of names from a file, add each document to the model */
void DocumentCollection :: readFileList(std::string fname) {
  std::vector<std::string> nameList = readNames(fname);
  for (std::string &name : nameList) {
    addTextFromFile(name);
  }
}


/* read a list of names from a file */
std::vector<std::string> DocumentCollection :: readNames(std::string listFile) {
  std::vector<std::string> names;
  std::ifstream fin(listFile); // try to open file
  if (!fin.is_open()) { // see if it worked
    std::cerr << "Error: failed to open listfile '" << listFile << "'\n"; 
    exit(-1);
  }

  std::string name;
  while (fin >> name) { 
    names.push_back(name); // read names until we run out of file
  }
  fin.close(); // close the file
  return names;
}


/* add text from the given document file to the model */
void DocumentCollection :: addTextFromFile(std::string fname) {
  std::ifstream fin(fname);
  if (!fin.is_open()) { // make sure it opened
    std::cerr << "Error: could not open file '" << fname << "', file will be skipped...\n";
    return;
  }

  std::string word;
  std::vector<std::string> text; // the document will be stored here
  while (fin >> word) {
    std::transform(word.begin(), word.end(), word.begin(), std::tolower);//convert to lower case
	word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());//remove punctuation
    text.push_back(word); // read words from the file and add them to the document 
  }
  fin.close(); // close the file

  buildNgrams(text); // add ngrams from the document to the model
}


/* takes a document (as a vector of words, including start/end tags), and
 * adds each n-gram to the model */
void DocumentCollection :: buildNgrams(const std::vector<std::string> &text) {
  auto first = text.begin(); // first element
  auto last = text.begin() + (docVector.at(docVector.getSize()-1)).getN(); // n-1th element

  while (last-1 != text.end()) {
    (docVector.at(docVector.getSize()-1)).increment(first, last); // add ngrams until we run out
    ++first;
    ++last;
  }
}

/* toString just returns whatever the NgramCollection toString() gives us */
std::string DocumentCollection :: toString(char order) const {
   return ngrams.toString(order);
}


/* generate a new document based on the current model;
 * returns the new document as a single string
 */
std::string DocumentCollection :: generateText() const {
  std::string doc;
  
  std::list<std::string> curr; // context (i.e. current (n-1)gram)
  for (unsigned i=1; i<ngrams.getN(); ++i) {
    curr.push_back("<START_" + std::to_string(i) + ">"); // prime the pump with start tags
    doc += " " + curr.back();
  }

  std::string next;
  std::string end = "<END_" + std::to_string(ngrams.getN()-1) + ">"; // what we're looking for
  do { // add words to the document until we see the final end tag
    next = ngrams.pickWord(curr.begin(), curr.end());
    doc += next + " ";
    curr.pop_front();
    curr.push_back(next);
  } while (next != end);

  return doc;
}
