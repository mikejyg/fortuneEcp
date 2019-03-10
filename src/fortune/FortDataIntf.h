/*
 * FortDataIntf.h
 *
 *  Created on: Mar 10, 2019
 *      Author: mikejyg
 */

#ifndef FORTUNE_FORTDATAINTF_H_
#define FORTUNE_FORTDATAINTF_H_

#include <iostream>

namespace fortune {

/**
 * an interface for a fortune data set
 */
class FortDataIntf {
public:
	typedef std::pair<unsigned, unsigned> StringPositionType;		// a pair of position determines the string

public:
	virtual ~FortDataIntf() {}

	virtual StringPositionType getStringPosition(int stringIdx) = 0;

	virtual std::string getString(const StringPositionType & pos) = 0;

	virtual unsigned fortlen(const StringPositionType & pos) = 0;

	virtual unsigned getNumStr() const = 0;

	virtual const std::string & getFilename() const = 0;

	virtual void print(std::ostream & strm) const=0;

};

} /* namespace fortune */

#endif /* FORTUNE_FORTDATAINTF_H_ */
