#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <memory>
#include <iostream>

struct Memory
{
public: // Variables
	std::wstring ProcName;
	DWORD ProcId;
	HANDLE ProcHandle;

public: // Functions
	bool Init();

	Memory(const std::wstring& procName = L"") // constructor
	{
		ProcName = procName;
	}
	~Memory()
	{
		if (ProcHandle) CloseHandle(ProcHandle);
	}

	template <typename Ty>
	Ty ReadMemory(const uintptr_t& address)
	{
		Ty value;

		ReadProcessMemory(ProcHandle, reinterpret_cast<LPCVOID>(address), &value, sizeof(Ty), 0);
		return value;
	}

	template <typename Ty>
	bool WriteMemory(const uintptr_t& address, const Ty& value)
	{
		SIZE_T bytesWritten;
		return WriteProcessMemory(ProcHandle, reinterpret_cast<LPVOID>(address), value, sizeof(Ty), &bytesWritten) && bytesWritten == sizeof(Ty);
	}

	template <typename Ty>
	bool WriteMemory(const uintptr_t& address, const Ty& value, const size_t& size)
	{
		SIZE_T bytesWritten;
		return WriteProcessMemory(ProcHandle, reinterpret_cast<LPVOID>(address), value, size, &bytesWritten) && bytesWritten == size;
	}

	LPVOID AllocateMemory(const size_t& size, DWORD allocationType = MEM_COMMIT | MEM_RESERVE, DWORD protect = PAGE_READWRITE);
};