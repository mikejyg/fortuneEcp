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

		for (auto i=0u; i<datFile.getNumStr(); i++) {
			std::cout << i << ": ";

			auto pos = datFile.getStringPosition(i);
			//			std::cout << pos.first << ", " << pos.second << std::endl;
			datFile.displayString(pos);
		}

	}

};

} /* namespace fortune */

#endif /* FORTUNE_DATFILETEST_H_ */
