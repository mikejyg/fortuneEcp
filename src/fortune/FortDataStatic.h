/*
 * FortDataStatic.h
 *
 *  Created on: Mar 10, 2019
 *      Author: mikejyg
 */

#ifndef FORTUNE_FORTDATASTATIC_H_
#define FORTUNE_FORTDATASTATIC_H_

#include "FortDataIntf.h"
#include <cstring>
#include "Utils.h"

namespace fortune {

/**
 * A Fort Data class backed by statically allocated arrays
 */
class FortDataStatic: public FortDataIntf {
protected:
	const unsigned char * fortData;
	unsigned dataLen;

	const unsigned char * fortIdx;
	unsigned idxLen;

	std::string filename;

public:
	FortDataStatic(const unsigned char * fortData, unsigned dataLen, const unsigned char * fortIdx, unsigned idxLen
			, const std::string & filename)
		: fortData(fortData), dataLen(dataLen), fortIdx(fortIdx), idxLen(idxLen)
		, filename(filename)
	{
		auto * p = (uint32_t *)fortIdx;
		str_version = Utils::ntohl(*p++);
		str_numstr = Utils::ntohl(*p++);
		str_longlen = Utils::ntohl(*p++);
		str_shortlen = Utils::ntohl(*p++);
		str_flags = Utils::ntohl(*p++);

		memcpy(stuff, p, 4);
	}

	virtual ~FortDataStatic() {}

	virtual StringPositionType getStringPosition(int stringIdx) override {
		StringPositionType pos;

		auto offset = strSize() + stringIdx * sizeof(uint32_t);
		auto * p = (uint32_t *)(fortIdx + offset);
		pos.first = *p++;
		pos.second = *p++;

	    pos.first = Utils::ntohl( pos.first );
	    pos.second = Utils::ntohl( pos.second );

	    return pos;
	}

	virtual unsigned fortlen(const StringPositionType & pos) const override {
		return pos.second - pos.first - 2;
	}

	virtual std::string getString(const StringPositionType & pos) override {
	    std::string str;
	    auto len = fortlen(pos);
	    str.resize(len);

	    memcpy( (char *)str.data(), fortData + pos.first, len);

	    if ( getFlags() & STR_ROTATED )
	    	rotate(str);

	    return str;
	}

	virtual const std::string & getFilename() const override {
		return filename;
	}


};

} /* namespace fortune */

#endif /* FORTUNE_FORTDATASTATIC_H_ */
