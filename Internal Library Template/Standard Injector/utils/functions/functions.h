#pragma once
#include <Windows.h>
#include <string>

namespace utilsFuncs
{
	std::string GetLastErrorStr(); // From https://stackoverflow.com/questions/1387064/how-to-get-the-error-message-from-the-error-code-returned-by-getlasterror
}