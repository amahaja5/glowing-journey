//This will be the driver file which contains main

#include "NgramCollection.hpp"
#include "DocumentCollection.hpp"

int main(int argc, char** argv) {
	if (argc < 2 ) {
		std::cerr << "Error: please provide a file name\n";
		return 1;
	}

	std::string fileName = argv[1];
	char sChoice = 'm';
	if (argc == 3) {
		sChoice = std::string(argv[2]).at(0);
	}

	//Construct DocumentCollection type
	DocumentCollection collection(2);

	//read file names from a list
	collection.readFileList(fileName);

	if (sChoice == 'h') {
		collection.examineAllDocs(0.05);
	} else if (sChoice == 'm') {
		collection.examineAllDocs(0.10);
	} else if (sChoice == 'l') {
		collection.examineAllDocs(0.15);
	} else {
		std::cerr << "Unknown command line argument\n";
	}
	
	collection.printListOfPairs();

	return 0;
}
