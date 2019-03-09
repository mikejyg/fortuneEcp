/*
 * main.cpp
 *
 *  Created on: Mar 9, 2019
 *      Author: mikejyg
 */

#include "fortune/DatFileTest.h"
#include "fortune/Fortune.h"

using namespace fortune;

/**
 * test generation of any, short and long types
 */
void testAllTypes(Fortune & fort, int rounds) {
	int seed=1;
	int type = 0;

	while (rounds--) {
		Fortune::FortPositionType pos;

		switch (type) {
		case 0:
			std::cout << "any: " << std::endl;
			fort.getFort(&seed);
			seed++;
			break;

		case 1:
			std::cout << "short: " << std::endl;
			do {
				pos = fort.getFort(&seed);
				seed++;
			} while ( fort.getFortLen(pos) > fort.getSLen() );
			break;

		case 2:
			std::cout << "long: " << std::endl;
			do {
				pos = fort.getFort(&seed);
				seed++;
			} while ( fort.getFortLen(pos) <= fort.getSLen() );
			break;
		}

		fort.display(pos);

		type++;
		type %= 3;

	}

}

void printHelp() {
	printf("usage: fortune_file ...\n");
}

int main(int argc, char * argv[]) {

//	DatFileTest::test();

	if (argc<2) {
		printHelp();
		return 1;
	}

	Fortune fort;

	for (auto i=1; i<argc; i++) {
		fort.addFile(argv[i]);
	}

//	testAllTypes(fort, 1000000000);

	auto pos = fort.getFort();
	fort.display(pos);

}
