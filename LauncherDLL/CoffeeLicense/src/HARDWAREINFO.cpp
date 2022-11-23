// 아래 관련 기능 들중 일부 함수가 XP에서 지원하지 않으므로,
// 윈도우XP 빌드 시, 위 매크로를 전처리기에 등록해주어야함.
#ifndef USE_V141_WIN_XP

#include "HARDWAREINFO.h"



CHardwareInfo* CHardwareInfo::GetInstance()
{
    static CHardwareInfo* inst = NULL;

    if (NULL == inst)
    {
        inst = new CHardwareInfo();
    }

    return inst;
}

std::wstring CHardwareInfo::GetBiosSerial()
{
    return m_hwid.SMBIOS.SerialNumber;
}

std::wstring CHardwareInfo::GetCpuProcessorId()
{
    return m_hwid.SMBIOS.SerialNumber;
}

CHardwareInfo::CHardwareInfo()
{ 
};

char buffer1[4096] = { 0, };
char buffer2[4096] = { 0, };

char * GetBiosSerial()
{
    std::wstring wstr = CHardwareInfo::GetInstance()->GetBiosSerial();
    std::string message_a;

    message_a.assign(wstr.begin(), wstr.end());

    memset(buffer1, 0x00, 4096);
    memcpy_s(buffer1, 4096, message_a.c_str(), message_a.size());

    return buffer1;
}


char * GetCpuProcessorId()
{
    std::wstring wstr = CHardwareInfo::GetInstance()->GetCpuProcessorId();
    std::string message_a;

    message_a.assign(wstr.begin(), wstr.end());

    memset(buffer2, 0x00, 4096);
    memcpy_s(buffer2, 4096, message_a.c_str(), message_a.size());

    return buffer2;
}


#endif