#pragma once
#include "HashFunction.h"
using namespace HashFunction;
template<typename string, typename Value>
class HashTable
{
public:
	HashTable(unsigned int size) : m_size(size), m_data(new Value[size]) {}
	~HashTable() { delete[] m_data; }

	Value& operator[] (const string& key)
	{
		auto hashedKey = HashFunc(key) % m_size;
		return m_data[hashedKey]
	}
	const Value& operator [](const string& key) const
	{
		auto hashedKey = HashFunc(key) % m_size;
		return m_data[hashedKey];
	}

	void Add(string key, Value val)
	{
		m_filler++;
		if (m_filler <= m_size * 0.7f)
		{
			auto hashedKey = HashFunc(key) % m_size;
			if (m_data[hashedKey] == nullptr)
			{
				m_data[hashedKey] = val;
			}
			else
			{
				for (int i = hashedKey++; i < m_size; i++)
				{
					if (m_data[i] == nullptr)
					{
						m_data[hashedKey] = val;
						break;
					}
				}
			}
		}
		else
		{
			Upsize(key,  val);
		}
	}

	bool Find(string key)
	{

	}

	Upsize(string key, Value val)
	{

	}

private:
	Value* m_data;
	unsigned int m_size;
	unsigned int m_filler;
};