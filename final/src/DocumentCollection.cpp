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
  	std::cout << "Reading: " << name + "\n";
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
    
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);//convert to lower case
	
	word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());//remove punctuation
	
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

double DocumentCollection :: similarity(NgramCollection q, NgramCollection d) {
	double sumTerm = 0;
	//add whatever additional variables we need
	// size of collection
	// number of terms in q
	// number of terms in d
	for (auto itq = q.counts.begin(); itq != q.counts.end(); ++itq) {
		for (auto itd = d.counts.begin(); itd != d.counts.end(); ++itd) {
			if (itq->first == itd->first) {//check if common pair of n-grams
				double h = (double) docFrequency(itq->first);
				double occQ = (double) q.counts[itq->first];
				double occD = (double) d.counts[itd->first];
				sumTerm += (getSize()/h)/(1 + std::abs(occD - occQ));
			}
		}
	}
	double numTermsD = (double) d.counts.size();
	double numTermsQ = (double) q.counts.size();
	double outerTerm = 1/(1 + std::log(1 + std::abs(numTermsD - numTermsQ)));
	return (outerTerm*sumTerm);
}

int DocumentCollection :: docFrequency(std::vector<std::string> term) {
	int count = 0;
	bool seen = false;
	for (const auto& itp : docVector) {
		for (const auto& itNGrams : itp.second.counts) {
			if (itNGrams.first == term) {
				seen = true;
			}
		}
		if (seen) {
			count++;
		}
	}
	//std::cout << std::to_string(count) + "\n";//for testing purposes
	return count;
}

void DocumentCollection :: examineAllDocs(double sensitivity) {
	//call existing similarity function to find plagiarism of all docs and store in vector of string pairs
	for (auto outerIter = docVector.begin(); outerIter != docVector.end(); ++outerIter) {//change this cant use for each
		for (auto innerIter = outerIter + 1; innerIter != docVector.end(); ++innerIter) {
			//add a cout for comparing
			std::cout << "Comparing: " + outerIter->first << " to " + innerIter->first + "\n";

			double docScore = similarity(outerIter->second, innerIter->second)/similarity(outerIter->second, outerIter->second);
			//print out document similarity scores to check
			std::cout << std::to_string(docScore) + "\n";
			if (docScore >= sensitivity) {
		    	std::pair<std::string, std::string> tempStrPair(outerIter->first, innerIter->first);
				plPairs.push_back(tempStrPair);			
			}
		}
	}
}

void DocumentCollection :: printListOfPairs() {
	for (auto it = plPairs.begin(); it != plPairs.end(); ++it) {
		std::cout << "Similar Pair: " + it->first + " and " + it->second + "\n";
	}
}
