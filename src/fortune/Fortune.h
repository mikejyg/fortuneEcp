/*
 * Fortune.h
 *
 *  Created on: Mar 9, 2019
 *      Author: mikejyg
 */

#ifndef FORTUNE_FORTUNE_H_
#define FORTUNE_FORTUNE_H_

#include "DatFile.h"
#include <vector>

namespace fortune {

class Fortune {
public:
	static const unsigned DEFAULT_SLEN = 160;

	// index of the fortune file, and the string position, determines where the fortune is.
	typedef std::pair< unsigned, DatFile::StringPositionType > FortPositionType;

protected:
	// max length of short quotes
	unsigned sLen;

	std::vector<DatFile> fortFiles;

	unsigned totalStrs;

	bool showFilenameFlag;

	////////////////////////////////////////////

	/**
	 * get fort, with the rand seed already set.
	 */
	FortPositionType getFortSeedSet() {
		auto idx = Utils::rand(totalStrs);

		FortPositionType pos;
		auto & fortFileIdx = pos.first;

		for (fortFileIdx=0; fortFileIdx<fortFiles.size(); fortFileIdx++) {
			auto & fortFile = fortFiles[fortFileIdx];

			if ( idx < fortFile.getNumStr() ) {
				pos.second = fortFile.getStringPosition(idx);
				return pos;

			} else {
				idx -= fortFile.getNumStr();
			}
		}

		throw std::runtime_error("random string index out of range, remaining: " + std::to_string(idx));
	}

public:
	Fortune() : sLen(DEFAULT_SLEN)
		, totalStrs(0), showFilenameFlag(false)
	{}

	void addFile(const std::string & filename) {
		fortFiles.emplace_back(filename);
		totalStrs += fortFiles.back().getNumStr();
	}

	FortPositionType getFort(const int * seedPtr=nullptr) {
		if (seedPtr) {
			srand(*seedPtr);
		} else {
			srand(time(nullptr));
		}

		return getFortSeedSet();
	}

	void display(FortPositionType & pos) {
		if (showFilenameFlag) {
			printf ("(%s)\n%%\n", fortFiles[pos.first].getFilename().c_str());
		}
		fortFiles[pos.first].displayString(pos.second);
	}

	unsigned getFortLen(FortPositionType & pos) {
		return fortFiles[pos.first].fortlen(pos.second);
	}

	unsigned getSLen() const {
		return sLen;
	}

	void setShowFilenameFlag(bool showFilenameFlag) {
		this->showFilenameFlag = showFilenameFlag;
	}

	void printFileList() const {
		for (auto & fort : fortFiles) {
			printf("%5.2f%% %s\n", (double)fort.getNumStr()/totalStrs*100, fort.getFilename().c_str());
		}
	}

};

} /* namespace fortune */

#endif /* FORTUNE_FORTUNE_H_ */
