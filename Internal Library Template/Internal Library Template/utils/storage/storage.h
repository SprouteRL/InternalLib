#pragma once
#include <Windows.h>

namespace storage // In case you are wondering why I use inline so much, it always give compiler errors idk
{
	inline long c = MB_OK | MB_ICONINFORMATION; // for messagebox info
	inline long e = MB_OK | MB_ICONERROR; // for messagebox error


	// i made this just for testing in assault cube, but you can use it aswell
	namespace your_game
	{
#define AddBase(x) ((uintptr_t)(GetModuleHandleA(nullptr)) + (x))

		namespace address
		{

		}
		namespace offset
		{
			inline uintptr_t localPlayerOffset = 0x17E0A8;

			inline uintptr_t healthOffset = 0xEC;
		}
		namespace definitios
		{

		}
	}
}