#pragma once
#include "hwid.h"
#include "Common.h"

class COFFEELICENSE_EXPORT CHardwareInfo {
public:
    static CHardwareInfo* GetInstance();

public:
    std::wstring GetBiosSerial();
    std::wstring GetCpuProcessorId();

private:
    CHardwareInfo();


private:
    HardwareId m_hwid;

};

extern "C" {


}
