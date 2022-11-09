

#include "Registry.h"
#include <winerror.h>
#include <winreg.h>

BOOL RegKeyRead(HKEY RootKey, const char* csSubKey, const char *csValue, char * szValue, DWORD * dwSize)
{
    BOOL ret = false;
    HKEY hKey;
    LONG lResult;

   
    lResult = RegOpenKeyExA(HKEY_LOCAL_MACHINE, csSubKey, 0, KEY_READ, &hKey);
    if (ERROR_SUCCESS == lResult)
    {
        if (ERROR_SUCCESS == RegQueryValueExA(hKey, csValue, NULL, NULL, NULL, dwSize))
            // 실제 값을 읽어온다.
            if (ERROR_SUCCESS == RegQueryValueExA(hKey, csValue, NULL, NULL, (LPBYTE)szValue, dwSize))
            { 

                RegCloseKey(hKey);
                ret = true;
            }
        
    }



    return ret;
}