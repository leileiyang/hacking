#include <windows.h>
#include <tchar.h>

/********************************************
 *  The function is used to execute a command without showing the
 *  console window in windows. The function is blocking.
 *
 */

int WindowsSystem(const char *cmd) {
  PROCESS_INFORMATION pi;
  STARTUPINFO si;
  wchar_t w_cmd[100];
  mbstowcs(w_cmd, cmd, strlen(cmd) + 1);
  LPWSTR cmdline = w_cmd;
  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  si.wShowWindow = SW_HIDE;
  si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
  ZeroMemory(&pi, sizeof(pi));

  if (CreateProcess(NULL, cmdline, NULL, NULL, TRUE, NULL, NULL, NULL,
        &si, &pi)) {

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
  }
  return -1;
}
