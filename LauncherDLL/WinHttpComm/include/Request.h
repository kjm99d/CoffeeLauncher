#pragma once

#ifdef WINHTTPCOMM_EXPORTS
#define WINHTTPCOMM_EXPORT __declspec(dllexport)
#else
#define WINHTTPCOMM_EXPORT __declspec(dllexport)
#endif

#include <tchar.h>

typedef enum {
	None,
	kGET,
	kPOST,
	kPUT,
	kDELETE,
	kPATCH,
} RequestMethod;

class WINHTTPCOMM_EXPORT CRequest
{

public:
	static CRequest& GetInst();
	CRequest();
	~CRequest();

public:
	void Request();
	void SetMethod(RequestMethod method);
	void SetURL(const TCHAR * url);


private:
	bool POST();
	bool GET();

private:
	RequestMethod m_method;
	const TCHAR* m_url;

};




#if __cplusplus
extern "C" {
#endif

	WINHTTPCOMM_EXPORT int POST();
	WINHTTPCOMM_EXPORT int GET();
	


#if __cplusplus
}
#endif