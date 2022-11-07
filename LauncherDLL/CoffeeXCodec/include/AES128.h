#pragma once
#include "IXCodec.h"



class CAES128 : public IXCodec {
public:
    CAES128();
    virtual ~CAES128();


    bool GetEncryptBuffer(const unsigned char*& pDest, int& nLenDest) override;
    bool GetDecryptBuffer(const unsigned char*& pDest, int& nLenDest) override;
    bool SetSource(unsigned char* pSource, int nLenSource) override;

protected:
    bool CheckRule();



};