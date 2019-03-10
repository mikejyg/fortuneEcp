/*
 * DatFileTest.h
 *
 *  Created on: Mar 9, 2019
 *      Author: mikejyg
 */

#ifndef FORTUNE_DATFILETEST_H_
#define FORTUNE_DATFILETEST_H_

#include "DatFile.h"

namespace fortune {

/**
 * unit test for DatFile
 */
class DatFileTest {
public:

	static void test(const std::string & fortFilename) {
		// print all messages from the file
		DatFile datFile(fortFilename);

		datFile.print(std::cout);
		std::cout << std::endl;

		datFile.printAllStrings(std::cout);

	}

};

} /* namespace fortune */

#endif /* FORTUNE_DATFILETEST_H_ */
