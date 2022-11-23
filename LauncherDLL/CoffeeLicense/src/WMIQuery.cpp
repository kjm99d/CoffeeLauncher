#include "WMIQuery.h"
#include <iostream>
#include <string>
#include <vector>

#include <comdef.h>
#include <Wbemidl.h>
#include <ntddscsi.h>
#include <algorithm>

#pragma comment(lib, "wbemuuid.lib")

std::wstring StringProcessorId();

template <typename T = const wchar_t*>
void QueryWMI(std::wstring WMIClass, std::wstring Field, std::vector <T>& Value, const wchar_t* ServerName = L"ROOT\\CIMV2") {
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

        if (typeid(T) == typeid(long) || typeid(T) == typeid(int)) {
            Value.push_back((T)Variant.intVal);
        }
        else if (typeid(T) == typeid(bool)) {
            Value.push_back((T)Variant.boolVal);
        }
        else if (typeid(T) == typeid(unsigned int)) {
            Value.push_back((T)Variant.uintVal);
        }
        else if (typeid(T) == typeid(unsigned short)) {
            Value.push_back((T)Variant.uiVal);
        }
        else if (typeid(T) == typeid(long long)) {
            Value.push_back((T)Variant.llVal);
        }
        else if (typeid(T) == typeid(unsigned long long)) {
            Value.push_back((T)Variant.ullVal);
        }
        else {
            Value.push_back((T)((bstr_t)Variant.bstrVal).copy());
        }

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
    QueryWMI(L"Win32_BaseBoard", L"SerialNumber", SerialNumber);


    return SerialNumber.at(0);
}


const char* StringLicense()
{
    static char license[4096] = { 0x00, };
    memset(license, 0x00, sizeof(license) * sizeof(char));

    std::wstring Processor = StringProcessorId();
    std::string strProcessorId(Processor.begin(), Processor.end());
    sprintf_s(license, 4096, "%s", strProcessorId.c_str());
    
    
    return license;
}
