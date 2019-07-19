#define WIN32_LEAN_AND_MEAN         // Exclude APIs such as Cryptography, DDE, RPC, Shell, and Windows Sockets
#define NOSERVICE                   // Additional NOservice definitions: NOMCX, NOIME, NOSOUND, NOCOMM, NOKANJI, NORPC, ...
#define _WINSOCKAPI_                // Prevent windows.h from including winsock.h
#define _WIN32_DCOM                 // Include all DCOM (Distributed Component Object Model) centric definitions
#include <windows.h>                // ... pull in Windows headers!

#include <iso646.h>                 // not, and, or, xor

/* From Windows 8.1 onwards GetVersion() and GetVersionEx()
   have been deprecated! */
#ifndef _NTDEF_
typedef __success(return >= 0) LONG NTSTATUS, *PNTSTATUS;
#endif

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS      ((NTSTATUS)0x00000000L)
#endif

typedef NTSTATUS (WINAPI * PFN_RTLGETVERSIONEX) (LPOSVERSIONINFOEX lpVersionInformation);

#if !defined(PACKVERSION)
  #define PACKVERSION(major,minor)    MAKELONG(minor,major)
#endif

extern LONG GetWindowsVer (void)
{ LONG
    os_version = -1L;

  { PFN_RTLGETVERSIONEX
      RtlGetVersionPtr;

    HMODULE hNtdll = LoadLibrary (TEXT("ntdll.dll"));

    if (not hNtdll)
      goto LoadLibraryFailed;

    RtlGetVersionPtr = (PFN_RTLGETVERSIONEX)GetProcAddress (hNtdll, "RtlGetVersion");

    if (RtlGetVersionPtr == NULL)
      goto GetProcFailed;

    { OSVERSIONINFOEX
        os_info;

      os_info.dwOSVersionInfoSize = sizeof(os_info);
      if ((*RtlGetVersionPtr) (&os_info) != STATUS_SUCCESS)
        goto GetVersionFailed;

      os_version = PACKVERSION(os_info.dwMajorVersion, os_info.dwMinorVersion);
    }

GetVersionFailed:
GetProcFailed:
    FreeLibrary (hNtdll);
  }

LoadLibraryFailed:
  return (os_version);
}
