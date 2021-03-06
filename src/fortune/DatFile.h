/*
 * DatFile.h
 *
 *  Created on: Mar 9, 2019
 *      Author: mikejyg
 */

/*  $NetBSD: strfile.h,v 1.3 1995/03/23 08:28:49 cgd Exp $  */

/*-
 * Copyright (c) 1991, 1993
 *  The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Ken Arnold.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *  This product includes software developed by the University of
 *  California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *  @(#)strfile.h   8.1 (Berkeley) 5/31/93
 */

/* Modified September, 1995, Amy A. Lewis
 * 1: removed all file-locking dreck.  Unnecessary
 * 2: Fixed bug that made fortune -f report a different list than
 *    fortune with any other parameters, or none, and which forced
 *    the program to read only one file (named 'fortunes')
 * 3: removed the unnecessary print_file_list()
 * 4: Added "OFFDIR" to pathnames.h as the directory in which offensive
 *    fortunes are kept.  This considerably simplifies our life by
 *    permitting us to dispense with a lot of silly tests for the string
 *    "-o" at the end of a filename.
 * 5: I think the problems with trying to find filenames were fixed by
 *    the change in the way that offensive files are defined.  Two birds,
 *    one stone!
 * 6: Calculated probabilities for all files, so that -f will print them.
 */

/* Changes Copyright (c) 1997 Dennis L. Clark.  All rights reserved.
 *
 *    The changes in this file may be freely redistributed, modified or
 *    included in other software, as long as both the above copyright
 *    notice and these conditions appear intact.
 */

#ifndef DATFILE_H_
#define DATFILE_H_

#include "FortDataIntf.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include "Utils.h"
#include <iostream>
#include "Utils.h"
#include <utility>
#include <cstring>
#include "File.h"

namespace fortune {

/**
 * information table
 */
class DatFile : public FortDataIntf {
protected:
	File datFile;

	File fortFile;

	////////////////////////////////

	/*
	 * get_tbl:
	 *      Get the tbl data file the datfile.
	 */
	void readFromFile() {
		Utils::fread(&str_version, sizeof str_version, 1, datFile.getFp());

		Utils::fread(&str_numstr, sizeof str_numstr, 1, datFile.getFp());
		Utils::fread(&str_longlen, sizeof str_longlen, 1, datFile.getFp());
		Utils::fread(&str_shortlen, sizeof str_shortlen, 1, datFile.getFp());
		Utils::fread(&str_flags, sizeof str_flags, 1, datFile.getFp());
		Utils::fread(&stuff, sizeof stuff, 1, datFile.getFp());

		str_version = Utils::ntohl(str_version);
		str_numstr = Utils::ntohl(str_numstr);
		str_longlen = Utils::ntohl(str_longlen);
		str_shortlen = Utils::ntohl(str_shortlen);
		str_flags = Utils::ntohl(str_flags);
	}

public:
	virtual ~DatFile() {}

	DatFile(const std::string & fortFilename) : datFile(fortFilename+".dat")
		, fortFile(fortFilename)
	{
		datFile.fopen();
		readFromFile();
	}

	/**
	 * return the begin and end position of the string, of the furtune file
	 */
	virtual StringPositionType getStringPosition(int stringIdx) override {
		StringPositionType pos;

		auto offset = strSize() + stringIdx * sizeof(uint32_t);
		Utils::fseek(datFile.getFp(), offset);
	    Utils::fread(& pos.first, sizeof(uint32_t), 1, datFile.getFp());
	    Utils::fread(& pos.second, sizeof(uint32_t), 1, datFile.getFp());

	    pos.first = Utils::ntohl( pos.first );
	    pos.second = Utils::ntohl( pos.second );

	    return pos;
	}

	/**
	 * get the length of the string
	 */
	virtual unsigned fortlen(const StringPositionType & pos) const override
	{
	    int nchar;
//	    char line[BUFSIZ];

	    if ( ! ( getFlags() & (STR_RANDOM | STR_ORDERED) ) )
	        nchar = ( pos.second - pos.first ) - 2;  /* for %^J delimiter */
	    else
	    {
	    	// the following is not logically sound, deprecated

	    	throw std::runtime_error("The STR (.dat) file should be re-generated so that the indexes are accurate.");

//	        Utils::fseek( fortFile.getFp(), pos.first);
//	        nchar = 0;
//	        while ( fgets(line, sizeof line, fortFile.getFp() ) != NULL &&
//	               ! isEndString(line) ) {
//	            nchar += strlen(line);
//	        }
	    }
	    return nchar;
	}

	virtual std::string getString(const StringPositionType & pos) override
	{
		if (!fortFile.getFp()) {
			fortFile.fopen();
		}
	    Utils::fseek(fortFile.getFp(), pos.first);

	    std::string str;
	    auto len = fortlen(pos);
	    str.resize(len);

	    Utils::fread( (char *) str.data(), sizeof(char), len, fortFile.getFp() );

	    if ( getFlags() & STR_ROTATED )
	    	rotate(str);

	    return str;
	}

	////////////////////////////////////////////////

	virtual const std::string & getFilename() const override {
		return fortFile.getFilename();
	}

};

} /* namespace fortune */

#endif /* DATFILE_H_ */
