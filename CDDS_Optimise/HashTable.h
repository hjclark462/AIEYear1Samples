#pragma once
#include <utility>
#include <vector>
#include <string>
using namespace std;


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

template<typename Value>
class HashTable
{
public:
	HashTable(unsigned int size) : m_size(size) {}
	~HashTable() { delete m_data; }

	Value& operator[] (string key)
	{
		auto hashedKey = APHash(key) % m_size;
		return m_data[hashedKey];
	}
	const Value& operator [](string key) const
	{
		auto hashedKey = APHash(key) % m_size;
		return m_data[hashedKey];
	}

	void Add(string* key, Value* val)
	{
		m_filler++;
		if (m_filler <= m_size * 0.7f)
		{
			auto hashedKey = APHash(*key) % m_size;
			if (m_data[hashedKey] == nullptr)
			{
				m_data[hashedKey] = pair<key, val>;
			}
			else
			{
				m_data[hashedKey] = pair<m_data[hashedKey], pair<key, val>>;
			}
		}
		else
		{
			Upsize(key,  val);
		}
	}

	bool Find(const char key)
	{
		
	}

	void Upsize(const char key, Value val)
	{

	}

private:
	vector<pair<string*, Value*>> m_data;
	unsigned int m_size;
	unsigned int m_filler;
};