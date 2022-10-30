#pragma once

#ifdef WINHTTPCOMM_EXPORTS
#define WINHTTPCOMM_EXPORT __declspec(dllexport)
#else
#define WINHTTPCOMM_EXPORT __declspec(dllexport)
#endif

#include <vector>
#include <map>
#include <utility>
#include <string>
#include <iostream>
#include <Windows.h>
#include <winhttp.h>
#include <string>

/**
 * Single Vector 형태로 Key와 Value를 저장하는 리스트
 */
typedef std::vector<std::pair<const wchar_t*, const wchar_t*>> request_header;

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
	CRequest() = delete;
	CRequest(const CRequest&) = delete;

	CRequest(const wchar_t *url);
	~CRequest();

public:
	// 

	/**
	 * \brief Set[...] 기반의 함수로 설정된 다양한 파라미터 옵션을 기반으로 웹서버에 데이터를 요청합니다.
	 * 
	 * \return 에러코드
	 */
	int Request();

	
	/**
	 * \brief 요청할 URL을 설정합니다.
	 * 
	 * \param url - 요청 URL을 입력합니다.
	 */
	void SetURL(const wchar_t* url);

	/**
	 * \brief 요청 메소드를 설정합니다.
	 * 
	 * \param method - RequestMethod Enum 참조
	 */
	void SetMethod(const RequestMethod method);

	/**
	 * \brief 요청헤더를 설정합니다. 
	 * 
	 * \param key - 헤더의 키값
	 * \param value - 헤더의 밸류값
	 */
	void SetHeader(const wchar_t* key, const wchar_t* value);

	/**
	 * \brief std::pair 타입으로된 배열을 입력으로 받아 헤더를 구성합니다.
	 * 
	 * \param headers header key와 value로 구성된 배열
	 */
	void SetHeader(request_header headers);

	/**
	 * UserAgent 헤더를 설정한다.
	 * 
	 * \param value - 설정될 UserAgent
	 */
	void SetUserAgent(const wchar_t* value);


	/**
	 * \brief 요청 파라미터에 들어갈 페이로드를 설정한다.
	 * \brief 만약 GET 방식의 요청인 경우 페이로드를 설정하지 않는다.
	 * 
	 * \param payload - 페이로드
	 */
	void SetPayload(const wchar_t* payload);


	BOOL GetBuffer(PBYTE& pbBufferStorage, DWORD& dwReadDataSize);


protected:
	/**
	 * 현재 설정된 요청 메소드를 기반으로 문자열화된 요청 메소드를 전달합니다.
	 * 
	 * \return 
	 */
	const wchar_t* StrRequestMethodW();
	

protected:
	request_header m_headers;
	RequestMethod m_method;		// 요청 메소드 타입
	wchar_t m_url[4096];			// 요청 URL
	const wchar_t* m_query;		// QueryString
	const wchar_t* m_useragent;	// useragent
	HINTERNET hSession;			// 요청 세션

	
	//std::string m_responseBody;


private:
	void Open();
	void SetComponent();


	void Close();


private:
	BYTE           m_ResponseBuffer[4096];
	URL_COMPONENTS m_urlComponents;
	WCHAR          m_szHostName[256], m_szUrlPath[2048];
	HINTERNET      m_hConnect, m_hRequest;
	DWORD m_dwStatusCode;


};