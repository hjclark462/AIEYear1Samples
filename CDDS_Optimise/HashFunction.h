#pragma once
#include <functional>
#include <string>
using namespace std;
namespace HashFunction
{
    typedef std::function< unsigned int(const char*, unsigned int)> HashFunc;

    // implementation of a basic addition hash 
    unsigned int badHash(const char* data, unsigned int length);
    unsigned int RSHash(const char* data, unsigned int length);
    unsigned int JSHash(const char* data, unsigned int length);
    unsigned int PJWHash(const char* data, unsigned int length);
    unsigned int ELFHash(const char* data, unsigned int length);
    unsigned int BKDRHash(const char* data, unsigned int length);
    unsigned int SDBMHash(const char* data, unsigned int length);
    unsigned int DJBHash(const char* data, unsigned int length);
    unsigned int DEKHash(const char* data, unsigned int length);
    unsigned int APHash(const char* data, unsigned int length);

    // a helper to access a default hash function 
    static HashFunc defult = APHash;
}
