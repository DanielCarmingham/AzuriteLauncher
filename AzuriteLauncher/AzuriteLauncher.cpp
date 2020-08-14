#include <stdio.h>
#include <shlobj.h>
#include <process.h>
#include <windows.h>

int main()
{
    printf("AzuriteLauncher - Launch Azurite as AzureStorageEmulator.exe so you can debug Azure Functions in Visual Studio\n");

    TCHAR my_documents[MAX_PATH];
    SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);

    TCHAR cmdExe[MAX_PATH];
    GetEnvironmentVariable(L"COMSPEC", cmdExe, MAX_PATH);

    PROCESS_INFORMATION pi;
    STARTUPINFO si;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    LPTSTR cmdLine = _wcsdup(L"/C azurite");

    if (!CreateProcess(cmdExe, cmdLine, NULL, NULL, FALSE, 0, NULL, my_documents, &si, &pi))
    {
        wprintf(L"Error starting %s: %d", cmdExe, GetLastError());
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}