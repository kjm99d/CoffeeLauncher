#pragma once
#include "Request.h"

class WINHTTPCOMM_EXPORT CRequestFile : public CRequest
{
public:
	CRequestFile(FILE* fd);
	~CRequestFile();

	int Write();

protected:
	FILE* m_fd;
};

