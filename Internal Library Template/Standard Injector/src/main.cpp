#include <Windows.h>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "utils\memory\memory.h"
#include "utils\functions\functions.h"

int main()
{
	std::wstring targetProcess = L"ac_client.exe";

	std::unique_ptr<Memory> memory = std::make_unique<Memory>(targetProcess);
	if (!memory->Init())
	{
		// while you can use a function to clean up its not quite recommended, 
		// I read that on https://learncpp.com I couldn't find which page

		std::cerr << "Couldn't initialize Memory class.\n";
		system("pause");
		return 1;
	}

	// At this point we have found the process id and opened a handle
	// So we can just do the rest of the functions from a standard dll injector

	std::string dllName = "Internal Library Template.dll";
	std::string fullPath = (std::filesystem::current_path() / dllName).string();
	size_t pathLength = fullPath.length();

	std::fstream x(fullPath);
	if (!x.good())
	{
		std::cerr << "Failed to locate dll. Last thread error: " << utilsFuncs::GetLastErrorStr() << "\n";
		system("pause");
		return 1;
	}

	x.close();

	void* allocatedMem = memory->AllocateMemory(pathLength);
	if (allocatedMem == nullptr)
	{
		std::cerr << "Failed to allocate memory. Last thread error: " << utilsFuncs::GetLastErrorStr() << "\n";
		system("pause");
		return 1;
	}
	if (!memory->WriteMemory(reinterpret_cast<uintptr_t>(allocatedMem), fullPath.c_str(), pathLength))
	{
		std::cerr << "Failed to write memory. Last thread error: " << utilsFuncs::GetLastErrorStr() << "\n";
		system("pause");
		return 1;
	}

	HANDLE remoteThread = CreateRemoteThread(memory->ProcHandle, NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(LoadLibraryA), allocatedMem, 0, NULL);
	if (remoteThread == INVALID_HANDLE_VALUE) {
		std::cerr << "Failed to get create remote thread.\n";
		system("pause");
		return 1;
	}

	WaitForSingleObject(remoteThread, INFINITE);
	
	DWORD threadExitCode;
	GetExitCodeThread(remoteThread, &threadExitCode);
	if (threadExitCode == NULL) 
	{
		std::wcerr << "Failed to inject '" << dllName.c_str() << "' to target process: " << targetProcess.c_str() << ".\n";
		system("pause");
		return 1;
	}

	std::wcout << "Injected '" << dllName.c_str() << "' to target process: " << targetProcess.c_str() << ".\n";
	system("pause");
}