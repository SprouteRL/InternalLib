#include <Windows.h>
#include "exploit.h"

int WINAPI DllMain(HINSTANCE instance, DWORD reasonForAttach, LPVOID reserved)
{
	DisableThreadLibraryCalls(instance);

	if (reasonForAttach == DLL_PROCESS_ATTACH)
	{
		HANDLE thread = CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Exploit), instance, 0, 0);
		if (thread) CloseHandle(thread);

		return TRUE;
	}
	return TRUE;
}