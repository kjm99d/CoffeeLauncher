#include <Windows.h>
#include <WinHttpComm/include/Request.h>
#pragma comment(lib, "WinHttpComm.lib")


#include <CoffeeFileDownloader/include/DownloaderURL.h>
#pragma comment(lib, "CoffeeFileDownloader.lib")



#include <windows.h>
#include <iostream>


#include <vector>
#include <CoffeeXCodec/include/AES128.h>
#pragma comment(lib, "CoffeeXCodec.lib")
using namespace std;


#include <CoffeeUtil/include/include.h>
#pragma comment(lib, "CoffeeUtil.lib")

namespace EXAMPLE {
	void WinHttpRequest()
	{
		CRequest client;

		client.Open(RequestMethod::kGET, L"http://127.0.0.1:5000/form");
		client.SetHeader(L"user-agent", L"Hello");
		client.Send();

		DWORD dwStatusCode = client.GetStatusCode();

		PBYTE responseBuffer = NULL;
		DWORD dwReadDataSize = 0;

		if (dwStatusCode != 200)
		{
			return void();
		}

		while (client.GetBuffer(responseBuffer, dwReadDataSize))
		{
			printf("%s", responseBuffer);
		}
	};


	void FileDownload()
	{
		CURLDownload loader;
		loader.Download("http://10.20.10.73/635f78d1b22de.jpg", "D:\\test.jpg");
	}

    int fAES128()
    {
        //Random key
        unsigned char key[] = { 0xEC, 0xFD, 0x08, 0xB0, 0x5D, 0x51, 0x3B, 0x81, 0x48, 0x69, 0x80, 0x1F, 0x23, 0xE7, 0x0B, 0xC7 };
        AES128 aes;
        aes.SetKey(key);

        //message example
        unsigned char message[] = "00hellohellohellohellohellohellohellohellohello";

        cout << "Original message in hex:" << endl;
        for (int i = 0; i < sizeof(message); i++) {
            cout << hex << (int)message[i];
            cout << " ";
        }
        cout << endl;
        cout << endl;

        unsigned char encryptedMessage[sizeof(message)];

        //Encrypt the message 
        aes.Encrypt(message, encryptedMessage, sizeof(message) / 16);


        cout << "Encrypted message in hex:" << endl;
        for (int i = 0; i < sizeof(message); i++) {
            cout << hex << (int)encryptedMessage[i];
            cout << " ";
        }
        cout << endl;
        cout << endl;


        unsigned char DencryptedMessage[sizeof(message)]; //should be equal to original one :)

        //Decrypt the message
        aes.Decrypt(encryptedMessage, DencryptedMessage, sizeof(message) / 16);

        cout << "Final message in hex:" << endl;
        for (int i = 0; i < sizeof(message); i++) {
            cout << hex << (int)DencryptedMessage[i];
            cout << " ";
        }
        cout << endl;
        cout << endl;

        return 0;
    }


    bool ReadRegistry()
    {
        bool ret;
        char szValue[128] = { 0, };
        DWORD nLenValue = 0;

        if (ret = RegKeyRead(HKEY_LOCAL_MACHINE,
            "SOFTWARE\\Microsoft\\Windows\\CurrentVersion", "ProgramFilesDir",
            szValue, &nLenValue))
        {
            printf("SUCC \n");

        }
        else
        {
            printf("FAIL \n");
        }
        
        return ret;
    }
}

void ExampleWinHttp()
{


	return void();
}

int main()
{
	/*
	CURLDownload * downloader = new CURLDownload("http://192.168.0.4:8085/windbg.exe");
	downloader->DownloadMemory();
	downloader->Write("D:\\test.exe");
	*/

	//ExampleWinHttp();
	
    //EXAMPLE::fAES128();
	//EXAMPLE::FileDownload();
    //EXAMPLE::ReadRegistry();

    BOOL bit = OS::Is64Bit();
    OS::eType typeOS = OS::CurrentWindowVersion();
    printf("%d", bit);

}