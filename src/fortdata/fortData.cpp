/*
 * fortData.cpp
 *
 *  Created on: Mar 11, 2019
 *      Author: jgu
 */

#include "fortData.h"
#include "../fortune/FortDataStatic.h"

extern unsigned char computers[], computers_dat[];
extern unsigned computers_len, computers_dat_len;

extern unsigned char bofh_excuses[], bofh_excuses_dat[];
extern unsigned bofh_excuses_len, bofh_excuses_dat_len;

namespace fortune {

void addStaticFortData(Fortune & fort) {

	fort.add(new FortDataStatic(computers, computers_len, computers_dat, computers_dat_len, "computers"));

	fort.add(new FortDataStatic(bofh_excuses, bofh_excuses_len, bofh_excuses_dat, bofh_excuses_dat_len, "computers"));

}

} // namespace
