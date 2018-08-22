// GetMainWndByExeName.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <string>

typedef struct {
  DWORD dwProcessId;
  HWND hWnd;
} WNDINFO, *LPWNDINFO;

BOOL CALLBACK FlEnumProc(HWND hWnd, LPARAM lParam) {
  DWORD dwProcId;
  GetWindowThreadProcessId(hWnd, &dwProcId);
  LPWNDINFO pInfo = (LPWNDINFO)lParam;
  if (dwProcId == pInfo->dwProcessId) {
    HWND p = GetParent(hWnd);
    HWND ph = GetParent(p);
    if (ph) {
      pInfo->hWnd = ph;
      return FALSE;
    }
  }
  return TRUE;
}

HWND GetProcessMainWnd(DWORD dwProcessId) {
  WNDINFO wi;
  wi.dwProcessId = dwProcessId;
  wi.hWnd = NULL;
  EnumWindows(FlEnumProc, (LPARAM)&wi);
  return wi.hWnd;
}

HWND GetMainWndByExeName(const char *exe_name) {
  wchar_t w_buffer[512];
  mbstowcs(w_buffer, exe_name, strlen(exe_name) + 1);
  std::wstring w_exe_name(w_buffer);

  PROCESSENTRY32 pe32;
  pe32.dwSize = sizeof(pe32);
  HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (hProcessSnap == INVALID_HANDLE_VALUE) {
    return NULL;
  }
  DWORD dwProcID = 0;
  BOOL bMore = ::Process32First(hProcessSnap, &pe32);
  while (bMore) {
    std::wstring proc_name(pe32.szExeFile);
    if (w_exe_name == proc_name) {
      dwProcID = pe32.th32ProcessID;
      break;
    }
    bMore = ::Process32Next(hProcessSnap, &pe32);
  }
  ::CloseHandle(hProcessSnap);
  if (dwProcID == 0) {
    return NULL;
  } else {
    return GetProcessMainWnd(dwProcID);
  }
}

int _tmain(int argc, _TCHAR* argv[])
{
  HWND hWnd = GetMainWndByExeName("OneCutd.exe");
  if (hWnd) {
    ShowWindow(hWnd, SW_MINIMIZE);
    ShowWindow(hWnd, SW_SHOWMAXIMIZED);
  }
	return 0;
}