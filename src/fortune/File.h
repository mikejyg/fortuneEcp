/*
 * File.h
 *
 *  Created on: Mar 9, 2019
 *      Author: mikejyg
 */

#ifndef FORTUNE_FILE_H_
#define FORTUNE_FILE_H_

#include <cstdio>
#include <string>
#include "Utils.h"

namespace fortune {

/**
 * a wrapper class for FILE *
 */
class File {
protected:
	std::string filename;
	FILE * fp;

public:
	File(const std::string & filename="") : filename(filename)
		, fp(nullptr)
	{}

	// auto close on destruction
	~File() {
		fclose();
	}

	File(const File & )=delete;	// no copy

	// move constructor
	File(File && f2) : filename(std::move(f2.filename))
		, fp(f2.fp) {
		f2.fp=nullptr;
	}

	// move assignment
	File & operator = (File && f2) {
		this->filename=std::move(f2.filename);
		this->fp = f2.fp;
		f2.fp=nullptr;
		return *this;
	}

	void fopen(const char * mode = "r" ) {
		fp = Utils::fopen(filename.c_str(), mode);
	}

	void fclose() {
		if (fp)
			Utils::fclose(fp);
	}

	FILE * getFp() {
		return fp;
	}

	const std::string & getFilename() const {
		return filename;
	}

};

} /* namespace fortune */

#endif /* FORTUNE_FILE_H_ */
