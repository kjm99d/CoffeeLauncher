#include "QueryWMI.h"

#include <string>
#include <vector>

#include <comdef.h>
#include <Wbemidl.h>
#include <ntddscsi.h>
#include <algorithm>

#pragma comment(lib, "wbemuuid.lib")

std::wstring StringProcessorId();
std::wstring StringBaseBoardSerial();   // XP Not Supported !
std::wstring StringDiskDriveSerial();   // XP Not Supported !
std::wstring StringNetworkMacAddress();
std::wstring StringSystemDriveSerial();
std::wstring StringSystemInfomation();  // XP Not Supported !



const char* GetStringLicense()
{
    static char strLicense[4096] = { 0, };
    memset(strLicense, 0x00, sizeof(strLicense));
    std::string bucket, response;

    /*
    bucket.append("[ ");
    std::wstring SysInfo = StringSystemInfomation();
    response.assign(SysInfo.begin(), SysInfo.end());
    bucket.append(response);
    bucket.append(" ]");
    */


    // BaseBoardSerial
    std::wstring BaseBoardSerial = StringBaseBoardSerial();
    response.assign(BaseBoardSerial.begin(), BaseBoardSerial.end());
    bucket.append(response);

    // 프로세서 ID
    std::wstring ProcessorID = StringProcessorId();
    response.assign(ProcessorID.begin(), ProcessorID.end());
    bucket.append(response);

    /*
    // 네트워크 MAC 주소
    std::wstring MacAddress = StringNetworkMacAddress();
    response.assign(MacAddress.begin(), MacAddress.end());
    bucket.append(response);
    */


    

    // 시스템 디스크 시리얼 넘버
    std::wstring DriveSerialNumber = StringSystemDriveSerial();
    response.assign(DriveSerialNumber.begin(), DriveSerialNumber.end());
    bucket.append(response);
    

    sprintf_s(strLicense, 4096, "%s", bucket.c_str());

    return strLicense;
}


// ================================================================================ //

//template <typename T = const wchar_t*>
void QueryWMI(std::wstring WMIClass, std::wstring Field, std::vector <const wchar_t*>& Value, const wchar_t* ServerName = L"ROOT\\CIMV2") {
    std::wstring Query(L"SELECT ");
    Query.append(Field.c_str()).append(L" FROM ").append(WMIClass.c_str());

    IWbemLocator* Locator{};
    IWbemServices* Services{};
    IEnumWbemClassObject* Enumerator{};
    IWbemClassObject* ClassObject{};
    VARIANT Variant{};
    DWORD Returned{};


    HRESULT hResult{ CoInitializeEx(nullptr, COINIT_MULTITHREADED) };


    if (FAILED(hResult)) {
        return;
    }


    hResult = CoInitializeSecurity(nullptr,
        -1,
        nullptr,
        nullptr,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        nullptr,
        EOAC_NONE,
        nullptr);



    if (FAILED(hResult)) {
        CoUninitialize();
        return;
    }


    hResult = CoCreateInstance(CLSID_WbemLocator,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator,
        reinterpret_cast<PVOID*>(&Locator));


    if (FAILED(hResult)) {
        CoUninitialize();
        return;
    }


    hResult = Locator->ConnectServer(_bstr_t(ServerName),
        nullptr,
        nullptr,
        nullptr,
        NULL,
        nullptr,
        nullptr,
        &Services);


    if (FAILED(hResult)) {
        Locator->Release();
        CoUninitialize();
        return;
    }


    hResult = CoSetProxyBlanket(Services,
        RPC_C_AUTHN_WINNT,
        RPC_C_AUTHZ_NONE,
        nullptr,
        RPC_C_AUTHN_LEVEL_CALL,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        nullptr,
        EOAC_NONE);


    if (FAILED(hResult)) {
        Services->Release();
        Locator->Release();
        CoUninitialize();
        return;
    }


    hResult = Services->ExecQuery(bstr_t(L"WQL"),
        bstr_t(Query.c_str()),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        nullptr,
        &Enumerator);


    if (FAILED(hResult)) {
        Services->Release();
        Locator->Release();
        CoUninitialize();
        return;
    }

    while (Enumerator) {

        HRESULT Res = Enumerator->Next(WBEM_INFINITE,
            1,
            &ClassObject,
            &Returned);

        if (!Returned) {
            break;
        }

        Res = ClassObject->Get(Field.c_str(),
            0,
            &Variant,
            nullptr,
            nullptr);


            Value.push_back((const wchar_t*)((bstr_t)Variant.bstrVal).copy());
        

        VariantClear(&Variant);
        ClassObject->Release();
    }

    if (!Value.size()) {
        Value.resize(1);
    }

    Services->Release();
    Locator->Release();
    Enumerator->Release();
    CoUninitialize();
}


std::wstring StringProcessorId() {
    std::vector <const wchar_t*> SerialNumber{};
    QueryWMI(L"Win32_Processor", L"ProcessorId", SerialNumber);
    return SerialNumber.at(0);
}


std::wstring StringBaseBoardSerial() {
    std::vector <const wchar_t*> SerialNumber{};
    QueryWMI(L"Win32_BaseBoard", L"SerialNumber", SerialNumber);
    return SerialNumber.at(0);
}


std::wstring StringDiskDriveSerial() {
    std::vector <const wchar_t*> SerialNumber{};
    QueryWMI(L"Win32_DiskDrive", L"SerialNumber", SerialNumber);
    return SerialNumber.at(0);
}

std::wstring StringNetworkMacAddress() {
    std::vector <const wchar_t*> Name;
    std::vector <const wchar_t*> MAC;
    QueryWMI(L"Win32_NetworkAdapter", L"Name", Name);
    QueryWMI(L"Win32_NetworkAdapter", L"MACAddress", MAC);

    wprintf(L"%s | MAC [%s]\n", Name.at(0), MAC.at(0));

    std::wstring wstr = L"";

    return wstr;
}

std::wstring StringSystemDriveSerial()
{
    WCHAR szSysPath[MAX_PATH] = { 0, };
    UINT nLenSysPath = 0;

    nLenSysPath = GetSystemDirectory(szSysPath, MAX_PATH);
    WCHAR SystemDrive = szSysPath[0];

    WCHAR szRootPathName[5] = { 0, };
    swprintf_s(szRootPathName, 5, L"%C:\\", SystemDrive);


    DWORD SerialNumber = 0;
    GetVolumeInformation(szRootPathName, nullptr, 0, &SerialNumber, nullptr, nullptr, nullptr, 0);

    std::wstring StrSerialNumber = std::to_wstring(SerialNumber);
    


    return StrSerialNumber;
}

std::wstring StringSystemInfomation()
{
    std::vector <const wchar_t*> OSName;
    std::vector <const wchar_t*> OSArchitecture;
    std::vector <const wchar_t*> OSSerialNumber;

    QueryWMI(L"Win32_OperatingSystem", L"Name", OSName);
    QueryWMI(L"Win32_OperatingSystem", L"OSArchitecture", OSArchitecture);
    QueryWMI(L"Win32_OperatingSystem", L"SerialNumber", OSSerialNumber);

    std::wstring response;
    response.append(OSName.at(0)) + L"|";
    response.append(OSArchitecture.at(0)) + L"|";
    response.append(OSSerialNumber.at(0));

    return response;
}


// ================================================================================ //