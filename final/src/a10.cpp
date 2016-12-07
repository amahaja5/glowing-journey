/** Driver class for a10. This handles input and
 * calls the functions that create output.
 *
 * Authors: Avi Mahajan (amahaja5) and Nick Skacel (nsckacel1)
 * Date Last Modified: 12/7/16
 */

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
		collection.examineAllDocs(100);
		collection.printListOfPairs();
	} else if (sChoice == 'm') {
		collection.examineAllDocs(200);
		collection.printListOfPairs();
	} else if (sChoice == 'l') {
		collection.examineAllDocs(300);
		collection.printListOfPairs();
	} else {
		std::cerr << "Unknown command line argument\n";
	}
	
	return 0;
}
