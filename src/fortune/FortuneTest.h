/*
 * FortuneTest.h
 *
 *  Created on: Mar 9, 2019
 *      Author: mikejyg
 */

#ifndef FORTUNE_FORTUNETEST_H_
#define FORTUNE_FORTUNETEST_H_

#include "Fortune.h"

namespace fortune {

/**
 * test for the Furtune class
 */
class FortuneTest {
public:
	/**
	 * test generation of any, short and long types
	 */
	static void testAllTypes(Fortune & fort, int rounds) {
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

};

} /* namespace fortune */

#endif /* FORTUNE_FORTUNETEST_H_ */
