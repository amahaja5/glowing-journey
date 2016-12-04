#include "DocumentCollection.hpp"
#include <iostream>
#include <fstream>


void DocumentCollection :: pushBackDoc(std::pair<std::string,NgramCollection> docNgram) {
	docVector.push_back(docNgram);
}

NgramCollection DocumentCollection :: getNgram(unsigned index) {
	return docVector.at(index).second;
}

std::string DocumentCollection :: getDocName(unsigned index) {
	return docVector.at(index).first;
}

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
    /*
	 * fix this later 
    std::transform(word.begin(), word.end(), word.begin(), std::tolower);//convert to lower case
	word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());//remove punctuation
	*/
    text.push_back(word); // read words from the file and add them to the document 
  }
  fin.close(); // close the file

  buildNgrams(text, fname); // add ngrams from the document to the model
}


/* takes a document (as a vector of words, including start/end tags), and
 * adds each n-gram to the model */
void DocumentCollection :: buildNgrams(const std::vector<std::string> &text, std::string fname) {
  auto first = text.begin(); // first element
  auto last = text.begin() + get_N(); // nth element
  
  NgramCollection tempNgrams(get_N());
  while (last != text.end()) {
    tempNgrams.increment(first, last); // add ngrams until we run out
    ++first;
    ++last;
  }
  std::pair <std::string, NgramCollection> tempPair (fname, tempNgrams);
  pushBackDoc(tempPair);

}


/* toString just returns whatever the NgramCollection toString() gives us */
/*
std::string DocumentCollection :: toString(char order) const {
   return ngrams.toString(order);
}
*///probably not needed

double similarity(NgramCollection q, NgramCollection d) {
	for (auto


}
