#pragma once
#include <utility>
#include <vector>
#include <string>
using namespace std;

struct Bucket
{
	string* key;
	Texture2D* value;
};

struct Node
{
	Bucket data;
	Node* next;
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
	ResourceManager(unsigned int size) : m_size(size), m_data(new Node[size]) {}
	~ResourceManager() { delete m_data; }

	Node& operator[] (string key)
	{
		auto hashedKey = APHash(key) % m_size;
		return m_data[hashedKey];
	}
	const Node& operator [](string key) const
	{
		auto hashedKey = APHash(key) % m_size;
		return m_data[hashedKey];
	}

	void Add(string* key)
	{
		Texture2D texture = LoadTexture(key->c_str());
		/*m_filler++;
		if (m_filler <= m_size * 0.7f)
		{*/
			auto hashedKey = APHash(*key) % m_size;
			if (&m_data[hashedKey] == nullptr)
			{
				m_data[hashedKey].data.key = key;
				m_data[hashedKey].data.value = &texture;
			}
			else
			{
				m_data[hashedKey].next->data.key = key;
				m_data[hashedKey].next->data.value = &texture;
			}
		/*}
		else
		{
			Upsize(key);
		}*/
	}

	Texture2D Find(string key)
	{
		auto hashedKey = APHash(key) % m_size;
		return *m_data[hashedKey].data.value;

	}

	void Remove(string key)
	{
		
	}

	void Upsize(string key)
	{

	}

private:
	Node* m_data;
	unsigned int m_size;
	unsigned int m_filler;
};