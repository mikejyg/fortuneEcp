/*
 * TimeUtils.h
 *
 *  Created on: Mar 11, 2019
 *      Author: jgu
 */

#ifndef FORTUNE_TIMEUTILS_H_
#define FORTUNE_TIMEUTILS_H_

#include <sys/time.h>

namespace fortune {

class TimeUtils {
public:
	// get current time in seconds
	static double time() {
		struct timeval tv;
		gettimeofday(&tv, nullptr);

		double t = tv.tv_usec;
		t/=1000000.;
		t += tv.tv_sec;

		return t;
	}

};

} /* namespace fortune */

#endif /* FORTUNE_TIMEUTILS_H_ */
