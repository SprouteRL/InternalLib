#include "memory.h"

bool Memory::Init()
{
	// Find Proccess Id
	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (!processesSnapshot) return false;

	PROCESSENTRY32W processInfo = { sizeof(PROCESSENTRY32W) };

	if (Process32FirstW(processesSnapshot, &processInfo))
	{
		do
		{
			if (lstrcmpW(processInfo.szExeFile, ProcName.c_str()) == 0)
			{
				ProcId = processInfo.th32ProcessID;
				break;
			}

		} while (Process32NextW(processesSnapshot, &processInfo));
	}

	if (ProcId == 0)
	{
		std::wcerr << L"Failed to find target process: " << ProcName.c_str() << L".\n";
		return false;
	}

	// Find Window
	if (!ProcWindowName.empty())
	{
		ProcWindow = FindWindowA(0, ProcWindowName.c_str());
		if (ProcWindow == INVALID_HANDLE_VALUE)
		{
			std::wcerr << L"Failed to find target window: " << ProcWindowName.c_str() << L".\n";
			return false;
		}
	}

	// Find Handle
	ProcHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, ProcId);
	if (ProcHandle == INVALID_HANDLE_VALUE)
	{
		std::wcerr << L"Failed to open handle to target process: " << ProcName.c_str() << L".\n";
		return false;
	}
	return true;
}

LPVOID Memory::AllocateMemory(const size_t& size, DWORD allocationType, DWORD protect)
{
	return VirtualAllocEx(ProcHandle, nullptr, size, allocationType, protect);
}