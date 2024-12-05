#include "memory.h"

DWORD Memory::GetProcIdFromName(std::wstring name)
{
	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (!processesSnapshot) return false;

	PROCESSENTRY32W processInfo = { sizeof(PROCESSENTRY32W) };

	if (Process32FirstW(processesSnapshot, &processInfo))
	{
		do
		{
			if (lstrcmpW(processInfo.szExeFile, name.c_str()) == 0)
			{
				return processInfo.th32ProcessID;
			}

		} while (Process32NextW(processesSnapshot, &processInfo));
	}
}

void Memory::KillProcess(std::wstring procName)
{
	DWORD ProcId = GetProcIdFromName(procName);
	HANDLE ProcHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, ProcId);
	if (ProcHandle == INVALID_HANDLE_VALUE) return;

	if (TerminateProcess(ProcHandle, 0)) CloseHandle(ProcHandle);
}
