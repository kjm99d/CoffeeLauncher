#include <Windows.h>
#include <WinHttpComm/include/Request.h>
#pragma comment(lib, "WinHttpComm.lib")

int main()
{
//	POST();

	CRequest& request = CRequest::GetInst();
	request.SetMethod(kGET);
	request.Request();
	

	return 0;
}