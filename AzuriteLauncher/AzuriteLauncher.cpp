#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <shlobj.h>
#include <process.h>
#include <windows.h>
#include <signal.h>
#include <string>

int wmain(int argc, wchar_t *argv[])
{
    signal(SIGINT, SIG_IGN);

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

    std::wstring strCmdLine(L"/C azurite");

    int i;
    for (i = 1; i < argc; i++)
    {
        strCmdLine.append(L" ");
        strCmdLine.append(argv[i]);
    }

    LPTSTR cmdLine = &strCmdLine[0];

    if (!CreateProcess(cmdExe, cmdLine, NULL, NULL, FALSE, 0, NULL, my_documents, &si, &pi))
    {
        wprintf(L"Error starting %s: %d", cmdExe, GetLastError());
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    wprintf(L"Exiting AzuriteLauncher...\n");

    return 0;
}