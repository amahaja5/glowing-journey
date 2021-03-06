/** Document Collection class implementation
 *
 * Our Documentcolllection class has most of the
 * functions that handle input/output, it also 
 * creates 3-grams, and feeds the 3-grams for different
 * files into the similiarity algorithm.
 *
 * author: Avi Mahajan (amahaja5) and Nick Skacel (nskacel1)
 * last modified: 12/7/16
 */
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
  for (auto it = tempNgrams.counts.begin(); it != tempNgrams.counts.end(); ++it) {
	freq[it->first]++;
  }
  std::pair <std::string, NgramCollection> tempPair (fname, tempNgrams);
  pushBackDoc(tempPair);

}

/** Similiarity score measure, as mentioned in README */
double DocumentCollection :: similarity(NgramCollection q, NgramCollection d) {
	double sumTerm = 0;
	for (auto itq = q.counts.begin(); itq != q.counts.end(); ++itq) {
		for (auto itd = d.counts.begin(); itd != d.counts.end(); ++itd) {
			if (itq->first == itd->first) {//check if common pair of n-grams
				double h = (double) freq[itq->first];
				double occQ = (double) itq->second;
				double occD = (double) itd->second;
				sumTerm += (1/h)/(1 + std::abs(occD - occQ));
			}
		}
	}
	double numTermsD = (double) d.counts.size();
	double numTermsQ = (double) q.counts.size();
	double outerTerm = getSize()/(1 + std::log(1 + std::abs(numTermsD - numTermsQ)));
	return (outerTerm*sumTerm);
}

/** Examine all of the documents at a specified similarity to print it out */
void DocumentCollection :: examineAllDocs(double sensitivity) {
	//call existing similarity function to find plagiarism of all docs and store in vector of string pairs
	for (auto outerIter = docVector.begin(); outerIter != docVector.end(); ++outerIter) { 
		for (auto innerIter = outerIter + 1; innerIter != docVector.end(); ++innerIter) {
			//add a cout for comparing, this can be removed if unnecessary
			std::cout << "Comparing: " + outerIter->first << " to " + innerIter->first + "\n";

			double docScore = similarity(outerIter->second, innerIter->second);
			if (docScore >= sensitivity) {
		    	std::pair<std::string, std::string> tempStrPair(outerIter->first, innerIter->first);
				plPairs.push_back(tempStrPair);			
			}
		}
	}
    std::cout << "\n\n";
}

/** print out pairs that are found to be plagarized */
void DocumentCollection :: printListOfPairs() {
    for (auto iter = plPairs.begin(); iter != plPairs.end(); ++iter) {
	    std::cout << "Similar Pair: " + iter->first + " and " + iter->second + "\n\n";
	}
}
