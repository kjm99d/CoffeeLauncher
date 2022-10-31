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

/*
* @brief 에러정보를 저장하는 열거형.
*/
typedef enum {
	ERROR_NONE = 0,
} RequestError;

/*
* @brief 에러값을 문자열로 반환 해주는 함수.
* 
* @param err - CRequest의 Public Object 호출을 통해 반환받은 정보
*/
const char* GetRequestErrorString(RequestError err);

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

	CRequest(const wchar_t* url);
	CRequest(const RequestMethod method, wchar_t *url);
	~CRequest();

public:
	RequestError GetLastError();

	/**
	 * @brief 세션을 열고 동작에 필요한 URL 정보를 파싱하는 함수.
	 * 
	 * 
	 * \param method - RequestMethod Enum 값으로 설정된 열거 타입으로 지정되어 있음.
	 * \param url - 요청하고자 하는 웹서버의 주소정보.
	 */
	void Open(RequestMethod method, const wchar_t* url);

	/**
	 * \brief 요청헤더를 설정합니다.
	 *
	 * \param key - 헤더의 키값
	 * \param value - 헤더의 밸류값
	 */
	void SetHeader(const wchar_t* key, const wchar_t* value);
	
	/**
	 * 실질적인 요청을 진행한다.
	 * 
	 * \param form - 폼 정보를 의미한다.
	 * \param Example : 
	 */
	void Send(const wchar_t* form);


	/**
	 * ResponseBody Byte 정보를 전달받는 함수..
	 * 
	 * \param pbBufferStorage - PBYTE 형태로 정의된 변수를 입력으로 받아 포인터를 전달 받는다.
	 * \param dwReadDataSize - DWORD 형태로 정의된 변수를 입력 받아, 서버를 통해 전달 받은 데이터의 크기를 가져온다.
	 * \return 
	 */
	BOOL GetBuffer(PBYTE& pbBufferStorage, DWORD& dwReadDataSize);

	/**
	 * Send(...) 함수 호출 이후, 응답상태 코드를 반환한다..
	 * 
	 * \return Response Header Status Code
	 */
	DWORD GetStatusCode();
	/*
	* // ================================================ //
	*/




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
	 * \brief std::pair 타입으로된 배열을 입력으로 받아 헤더를 구성합니다.
	 * 
	 * \param headers header key와 value로 구성된 배열
	 */
	void SetHeader(request_header headers);



	/**
	 * \brief 요청 파라미터에 들어갈 페이로드를 설정한다.
	 * \brief 만약 GET 방식의 요청인 경우 페이로드를 설정하지 않는다.
	 * 
	 * \param payload - 페이로드
	 */
	void SetPayload(const wchar_t* payload);




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
	HINTERNET hSession;			// 요청 세션

	
	//std::string m_responseBody;


private:
	void CreateSession(const wchar_t * session = NULL);
	void SetComponent(const wchar_t* url);


	void Close();


private:
	BYTE           m_ResponseBuffer[4096];
	URL_COMPONENTS m_urlComponents;
	WCHAR          m_szHostName[256], m_szUrlPath[2048];
	HINTERNET      m_hConnect, m_hRequest;
	DWORD m_dwStatusCode;


};