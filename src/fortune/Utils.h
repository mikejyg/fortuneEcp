/*
 * Utils.h
 *
 *  Created on: Mar 9, 2019
 *      Author: mikejyg
 */

#ifndef FORTUNE_UTILS_H_
#define FORTUNE_UTILS_H_

#include <cstdio>
#include <stdexcept>
#include <cstdlib>
#include <cmath>

namespace fortune {

class Utils {
public:
	static FILE * fopen(const char *path, const char *mode) {
		FILE * file = ::fopen(path, mode);
		if (file==NULL)
			throw std::runtime_error("fopen() error");
		return file;
	}

	static size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
		size_t k = ::fread(ptr, size, nmemb, stream);
		if (k!=nmemb)
			throw std::runtime_error("fread() returned " + std::to_string(k) + " vs " + std::to_string(nmemb) + " expected.");
		return k;
	}

	static size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
		size_t k = ::fwrite(ptr, size, nmemb, stream);
		if (k!=nmemb)
			throw std::runtime_error("fwrite() returned " + std::to_string(k) + " vs " + std::to_string(nmemb) + " expected.");
		return k;
	}

	static int fclose(FILE *fp) {
		int k = ::fclose(fp);
		if (k!=0)
			throw std::runtime_error("fclose() error");
		return k;
	}

	static void fseek(FILE *stream, long offset, int whence = SEEK_SET) {
		auto k = ::fseek(stream, offset, whence);
		if (k!=0)
			throw std::runtime_error("fseek() error");
	}

	/**
	 * generate a random number within [0..end)
	 */
	static unsigned rand(unsigned end) {
		unsigned long long r = ::rand();
		r *= end;
		r /= (unsigned long long)RAND_MAX + 1;
		return r;
	}

#define swap32(x)                                        \
  ((((x) & 0xff000000u) >> 24) | (((x) & 0x00ff0000u) >> 8)        \
   | (((x) & 0x0000ff00u) << 8) | (((x) & 0x000000ffu) << 24))

	static uint32_t ntohl(uint32_t x) {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		return swap32(x);
#else
		return x;
#endif
	}

};

} /* namespace fortune */

#endif /* FORTUNE_UTILS_H_ */
