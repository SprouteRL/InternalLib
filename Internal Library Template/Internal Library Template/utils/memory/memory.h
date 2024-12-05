#pragma once
#include <Windows.h>
#include <string>
#include <TlHelp32.h>

#include "../storage/storage.h"

struct Memory {
public: // Variables
	DWORD procId;
	uintptr_t baseAddr;

public: // Functions
	Memory(std::string moduleName = "") {
		procId = GetCurrentProcessId();
		baseAddr = reinterpret_cast<uintptr_t>(GetModuleHandleA(moduleName.empty() ? nullptr : moduleName.c_str()));
	}

	bool IsValidAddress(const uintptr_t& address) {
		MEMORY_BASIC_INFORMATION mbi;
		if (VirtualQuery(reinterpret_cast<void*>(address), &mbi, sizeof(mbi))) 
		{
			if ((mbi.State == MEM_COMMIT) && !(mbi.Protect & PAGE_NOACCESS) && !(mbi.Protect & PAGE_GUARD) ) return true;
		}
		return false;
	}

	// https://www.learncpp.com/cpp-tutorial/basic-exception-handling/
	// chatgpt reminded i can use expection handling, and thanks to the link above I did this kinda..
	template <typename Ty>
	Ty ReadMemory(const uintptr_t& address) {
		if (!IsValidAddress(address)) return Ty{};
		
		__try {
			return *reinterpret_cast<Ty*>(address);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return Ty{}; 
		}
	}

	template <typename Ty>
	bool WriteMemory(const uintptr_t& address, const Ty& value) {
		if (!IsValidAddress(address)) return false;

		__try {
			*reinterpret_cast<Ty*>(address) = value;
			return true; 
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return false;
		}
	}

	DWORD GetProcIdFromName(std::wstring name);
	void KillProcess(std::wstring procName);
};
