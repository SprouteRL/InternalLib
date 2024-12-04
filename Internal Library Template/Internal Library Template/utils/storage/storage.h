#pragma once
#include <Windows.h>

namespace storage // In case you are wondering why I use inline so much, it always give compiler errors idk
{
	inline long c = MB_OK | MB_ICONINFORMATION; // for messagebox info
	inline long e = MB_OK | MB_ICONERROR; // for messagebox error

	namespace your_game
	{
#define AddBase(x) ((uintptr_t)(GetModuleHandleA(nullptr)) + (x))

		namespace address
		{

		}
		namespace offset
		{

		}
		namespace definitios
		{

		}
	}
}