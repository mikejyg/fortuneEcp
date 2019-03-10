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
	typedef std::pair<uint32_t, uint32_t> StringPositionType;		// a pair of position determines the string

	static const int STRFILE_VERSION = 2;

	static const int STR_RANDOM = 0x1;         /* randomized pointers */
	static const int STR_ORDERED = 0x2;         /* ordered pointers */
	static const int STR_ROTATED = 0x4;         /* rot-13'd text */

protected:
	uint32_t   str_version;        /* version number */
	uint32_t   str_numstr;     /* # of strings in the file */
	uint32_t   str_longlen;        /* length of longest string */
	uint32_t   str_shortlen;       /* length of shortest string */
	uint32_t   str_flags;      /* bit field for flags */
	uint8_t    stuff[4];       /* long aligned space */

	/////////////////////////////////////////

	uint8_t getDelim() const {
		return stuff[0];	// delimiting character
	}

	/**
	 * the size of the STR (header)
	 */
	static unsigned strSize() {
		return 6 * sizeof(uint32_t);
	}

	unsigned getFlags() const {
		return str_flags;
	}

	void rotate(std::string & str) {
		for (auto & ch : str) {
			if (isupper(ch) && isascii(ch))
				ch = 'A' + (ch - 'A' + 13) % 26;
			else if (islower(ch) && isascii (ch))
				ch = 'a' + (ch - 'a' + 13) % 26;
		}
	}

public:
	virtual ~FortDataIntf() {}

	unsigned getNumStr() const {
		return str_numstr;
	}

	virtual StringPositionType getStringPosition(int stringIdx) = 0;

	virtual unsigned fortlen(const StringPositionType & pos) const = 0;

	virtual std::string getString(const StringPositionType & pos) = 0;

	virtual const std::string & getFilename() const = 0;

	/////////////////////////////////////////////////////////////////////

	virtual void print(std::ostream & strm) const {
		strm << "version: " << str_version;
		strm << ", number of quotes: " << str_numstr;     /* # of strings in the file */
		strm << ", longest length: " << str_longlen;        /* length of longest string */
		strm << ", shortest length: " << str_shortlen;       /* length of shortest string */
		strm << ", flags: 0x" << std::hex << str_flags << std::dec << " (";      /* bit field for flags */
		if (str_flags & STR_RANDOM)
			strm << " random";
		if (str_flags & STR_ORDERED)
			strm << " ordered";
		if (str_flags & STR_ROTATED)
			strm << " rotated";
		strm << ")";

		strm << ", delim: " << getDelim();
	}

	virtual void printAllStrings(std::ostream & strm) {
		for (auto i=0u; i<getNumStr(); i++) {
			std::cout << i << ": ";

			auto pos = getStringPosition(i);
			//			std::cout << pos.first << ", " << pos.second << std::endl;
			strm << getString(pos);

			strm << std::endl;
		}
	}

};

} /* namespace fortune */

#endif /* FORTUNE_FORTDATAINTF_H_ */
