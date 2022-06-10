#include "HashFunction.h"
namespace HashFunction
{
	// implementation of a basic addition hash
	unsigned int badHash(const char* data, unsigned int length)
	{
		unsigned int hash = 0;
		for (unsigned int i = 0; i < length; ++i)
		{
			hash += data[i];
		}
		return hash;
	}
	//	Robert Sedwicks Hash with some simple optimizations
	unsigned int RSHash(const char* data, unsigned int length)
	{
		unsigned int b = 378551;
		unsigned int a = 63689;
		unsigned int hash = 0;
		unsigned int i = 0;
		for (i = 0; i < length; ++data, ++i)
		{
			hash = hash * a + (*data);
			a = a * b;
		}
		return hash;
	}
	//	Justin Sobel Hash. A bitwise Has function
	unsigned int JSHash(const char* data, unsigned int length)
	{
		unsigned int hash = 1315423911;
		unsigned int i = 0;
		for (i = 0; i < length; ++data, ++i)
		{
			hash ^= ((hash << 5) + (*data) + (hash >> 2));
		}
		return hash;
	}
	// This hash algorithm is based on work by Peter J. Weinberger of Renaissance Technologies.
	unsigned int PJWHash(const char* data, unsigned int length)
	{
		const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
		const unsigned int ThreeQuarters = (unsigned int)((BitsInUnsignedInt * 3) / 4);
		const unsigned int OneEigth = (unsigned int)(BitsInUnsignedInt / 8);
		const unsigned int HighBits = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEigth);
		unsigned int hash = 0;
		unsigned int test = 0;
		unsigned int i = 0;

		for (i = 0; i < length; ++data, ++i)
		{
			hash = (hash << OneEigth) + (*data);
			if ((test = hash & HighBits) != 0)
			{
				hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
			}
		}
		return hash;
	}
	// Similar to the PJW Hash function, but tweaked for 32-bit processors. It is a widley used hash function on UNIX based systems.
	unsigned int ELFHash(const char* data, unsigned int length)
	{
		unsigned int hash = 0;
		unsigned int x = 0;
		unsigned int i = 0;
		for (i = 0; i < length; ++data, ++i)
		{
			hash = (hash << 4) + (*data);
			if ((x = hash & 0xF0000000L) != 0)
			{
				hash ^= (x >> 24);
			}
			hash &= ~x;
		}
		return hash;
	}
	// This hash function comes from Brian Kernighanand Dennis Ritchie's book "The C Programming Language". 
	// It is a simple hash function using a strange set of possible seeds which all constitute a pattern of 
	// 31....31...31 etc, it seems to be very similar to the DJB hash function.
	unsigned int BKDRHash(const char* data, unsigned int length)
	{
		unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
		unsigned int hash = 0;
		unsigned int i = 0;

		for (i = 0; i < length; ++data, ++i)
		{
			hash = (hash * seed) + (*data);
		}

		return hash;
	}
	// This is the algorithm of choice which is used in the open source SDBM project.
	// The hash function seems to have a good over - all distribution for many different data sets.
	// It seems to work well in situations where there is a high variance in the MSBs of the elements in a data set.
	unsigned int SDBMHash(const char* data, unsigned int length)
	{
		unsigned int hash = 0;
		unsigned int i = 0;

		for (i = 0; i < length; ++data, ++i)
		{
			hash = (*data) + (hash << 6) + (hash << 16) - hash;
		}

		return hash;
	}
	// An algorithm produced by Professor Daniel J.Bernstein and shown first to the world on the
	// usenet newsgroup comp.lang.c.It is one of the most efficient hash functions ever published.
	unsigned int DJBHash(const char* data, unsigned int length)
	{
		unsigned int hash = 5381;
		unsigned int i = 0;

		for (i = 0; i < length; ++data, ++i)
		{
			hash = ((hash << 5) + hash) + (*data);
		}

		return hash;
	}
	// An algorithm proposed by Donald E.Knuth in The Art Of Computer Programming Volume 3, under the topic of sortingand search chapter 6.4.
	unsigned int DEKHash(const char* data, unsigned int length)
	{
		unsigned int hash = length;
		unsigned int i = 0;

		for (i = 0; i < length; ++data, ++i)
		{
			hash = ((hash << 5) ^ (hash >> 27)) ^ (*data);
		}

		return hash;
	}
	// An algorithm produced by me Arash Partow. I took ideas from all of the above hash functions making a 
	// hybrid rotative and additive hash function algorithm.There isn't any real mathematical analysis
	// explaining why one should use this hash function instead of the others described above other than
	// the fact that I tired to resemble the design as close as possible to a simple LFSR. An empirical
	// result which demonstrated the distributive abilities of the hash algorithm was obtained using a hash-table
	// with 100003 buckets, hashing The Project Gutenberg Etext of Webster's Unabridged Dictionary, the longest
	// encountered chain length was 7, the average chain length was 2, the number of empty buckets was 4579.
	unsigned int APHash(const char* data, unsigned int length)
	{
		unsigned int hash = 0xAAAAAAAA;
		unsigned int i = 0;

		for (i = 0; i < length; ++data, ++i)
		{
			hash ^= ((i & 1) == 0) ? ((hash << 7) ^ (*data) * (hash >> 3)) :
									(~((hash << 11) + ((*data) ^ (hash >> 5))));
		}
		return hash;
	}
}