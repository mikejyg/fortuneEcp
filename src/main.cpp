/*
 * main.cpp
 *
 *  Created on: Mar 9, 2019
 *      Author: mikejyg
 */

#include "fortune/DatFileTest.h"
#include "fortune/Fortune.h"
#include "fortune/FortuneTest.h"
#include <unistd.h>

using namespace fortune;

void printHelp() {
	printf("usage: options fortune_file ...\n");
	printf("options:\n");
	printf("\t-t\tPerform self tests.\n");
	printf("\t-c\tShow the cookie file from which the fortune came.\n");
	printf("\t-f\tPrint out the list of files which would be searched, but don't print a fortune.\n");
//	printf("\t-l file_name_list\tUse filenames in the list file.\n");
//	printf("\t-i\tread filenames from stdin.\n");
	printf("\t-m file_name\tprint out all messages from the specified file.\n");
}

bool selfTest=false;
bool printFileList = false;
std::string fileList;
bool readFilenames=false;
std::string fortFilename;

void parseArgs(int argc, char * argv[], Fortune & fort) {
	int c;
	while ( (c = getopt (argc, argv, "tcfl:im:")) != -1 )
		switch (c)
		{
		case 't':
			selfTest = true;
			break;

		case 'c':
			fort.setShowFilenameFlag(true);
			break;

		case 'f':
			printFileList = true;
			break;

		case 'l':
			fileList = optarg;
			break;

		case 'i':
			readFilenames = true;
			break;

		case 'm':
			fortFilename = optarg;
			break;

		case '?':
			if (optopt == 'c')
				fprintf (stderr, "Option -%c requires an argument.\n", optopt);
			else if (isprint (optopt))
				fprintf (stderr, "Unknown option `-%c'.\n", optopt);
			else
				fprintf (stderr,
						"Unknown option character `\\x%x'.\n",
						optopt);
			throw std::exception();

		default:
			abort ();
		}
}

void test(Fortune & fort) {
	FortuneTest::testAllTypes(fort, 30);

}

int main(int argc, char * argv[]) {
	if (argc<2) {
		printHelp();
		exit(1);
	}

	Fortune fort;

	parseArgs(argc, argv, fort);

	// add files on the command line
	for (auto i = optind; i < argc; i++) {
		fort.addFile(argv[i]);
	}

	if (!fileList.empty()) {
		// TODO read filenames from the list file

	}

	if (readFilenames) {
		// TODO read filenames from stdin

	}

	if (!fortFilename.empty()) {
		DatFileTest::test(fortFilename);
		return 0;
	}

	if (printFileList) {
		fort.printFileList();
		return 0;
	}

	if (selfTest) {
		test(fort);
		return 0;
	}

	auto pos = fort.getFort();
	fort.display(pos);

}
