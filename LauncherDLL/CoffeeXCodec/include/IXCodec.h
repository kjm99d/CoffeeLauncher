#pragma once
#include <string>

#ifdef COFFEEXCODEC_EXPORTS
    #define COFFEEXCODEC_EXPORT __declspec(dllexport)
#else
    #define COFFEEXCODEC_EXPORT __declspec(dllimport)
#endif


class COFFEEXCODEC_EXPORT IXCodec
{
public:
    virtual ~IXCodec() = 0;
    
    virtual bool GetEncryptBuffer(const unsigned char*& pDest, int& nLenDest) = 0;
    virtual bool GetDecryptBuffer(const unsigned char*& pDest, int& nLenDest) = 0;
    virtual bool SetSource(unsigned char* pSource, int nLenSource) = 0;

protected:
    virtual bool CheckRule() = 0;
    unsigned char* buffer, *dest;
    int m_nLenBuffer, m_nLenDest;
};
