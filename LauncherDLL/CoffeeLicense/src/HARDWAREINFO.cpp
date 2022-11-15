#include "HARDWAREINFO.h"

const CHardwareInfo* CHardwareInfo::GetInstance()
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
    return m_hwid.CPU.ProcessorId;
}
