#pragma once
#include <utility>
#include <vector>
#include <string>
using namespace std;

struct Bucket
{
	string key;
	Texture2D value;
};

unsigned int APHash(string key)
{
	unsigned int hash = 0xAAAAAAAA;
	unsigned int i = 0;
	const char* data = key.c_str();

	for (i = 0; i < key.length(); ++data, ++i)
	{
		hash ^= ((i & 1) == 0) ? ((hash << 7) ^ (*data) * (hash >> 3)) :
			(~((hash << 11) + ((*data) ^ (hash >> 5))));
	}
	return hash;
}

class ResourceManager
{
public:
	ResourceManager(unsigned int size) : m_size(size), m_data(new Bucket[size]) {}

	Texture2D& operator[] (string key)
	{
		auto hashedKey = APHash(key) % m_size;
		return m_data[hashedKey].value;
	}
	const Texture2D& operator [](string key) const
	{
		auto hashedKey = APHash(key) % m_size;
		return m_data[hashedKey].value;
	}

	void Add(string key, Texture2D texture)
	{
		auto hashedKey = APHash(key) % m_size;
		bool added = false;
			while (!added)
			{
				if (m_data[hashedKey].key.empty())
				{
					m_data[hashedKey].key = key;
					m_data[hashedKey].value = texture;
					added = true;
				}
				else
				{
					hashedKey++;
					if (hashedKey == m_size)
						hashedKey = 0;
				}

			}
	}

	Texture2D Find(string key)
	{
		auto hashedKey = APHash(key) % m_size;
		return m_data[hashedKey].value;
	}

private:
	Bucket* m_data;
	unsigned int m_size;
};