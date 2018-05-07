#pragma once
#include <string> // string
#include <cstddef> // size_t

/*!
\brief   MurmurHashNeutral2, by Austin Appleby
\detail  Produces a hash of a byte array. Same as MurmurHash2, but endian- and alignment-neutral.
         Site: https://sites.google.com/site/murmurhash/
\param   key Pointer to an array of bytes
\param   len Length of the array
\param   seed Seed for hashing algorithm
\see     pretty_index::hash_code
*/
inline unsigned int MurmurHashNeutral2(const void * key, int len, unsigned int seed) {
	const unsigned int m = 0x5bd1e995;
	const int r = 24;

	unsigned int h = seed ^ len;

	const unsigned char * data = (const unsigned char *)key;

	while (len >= 4) {
		unsigned int k;

		k = data[0];
		k |= data[1] << 8;
		k |= data[2] << 16;
		k |= data[3] << 24;

		k *= m;
		k ^= k >> r;
		k *= m;

		h *= m;
		h ^= k;

		data += 4;
		len -= 4;
	}

	switch (len) {
		case 3: h ^= data[2] << 16;
		case 2: h ^= data[1] << 8;
		case 1: h ^= data[0];
			h *= m;
	};

	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
}

inline std::size_t hash(const std::string& str) {
	return static_cast<std::size_t>(MurmurHashNeutral2(
		str.data(),
		static_cast<int>(str.size()),
		0));
}