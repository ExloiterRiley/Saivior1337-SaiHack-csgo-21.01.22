#include "ProcessMemory.h"

ProcessMemory * mem;

DWORD ProcessMemory::getProcessId()
{
	G.gameWindow = FindWindowA(0, XOR("Counter-Strike: Global Offensive - Direct3D 9"));
	if (!G.gameWindow)
		con->error_message(1);

	GetWindowThreadProcessId(G.gameWindow, &G.gameProcessId);

	if (!G.gameProcessId)
		con->error_message(2);

	return G.gameProcessId;
}


void ProcessMemory::attachProcess()
{
	G.gameHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, getProcessId());
	if (!G.gameHandle)
		con->error_message(3);
}

DWORD ProcessMemory::getGameModule(const char* moduleName)
{
	HANDLE module = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, getProcessId());
	MODULEENTRY32 moduleEntry; 
	moduleEntry.dwSize = sizeof(moduleEntry); 

	do
	{
		if (!strcmp(moduleEntry.szModule, moduleName))
		{
			CloseHandle(module); 

			if (moduleName == "client.dll")
			{
				return G.client_dll = (DWORD)moduleEntry.modBaseAddr, G.client_dll_size = (DWORD)moduleEntry.dwSize;
			}

			if (moduleName == "engine.dll")
			{
				return G.engine_dll = (DWORD)moduleEntry.modBaseAddr, G.engine_dll_size = (DWORD)moduleEntry.modBaseSize; 
			}

			if (moduleName == "vstdlib.dll")
			{
				return G.vstdlib_dll = (DWORD)moduleEntry.modBaseAddr, G.vstdlib_dll_size = (DWORD)moduleEntry.modBaseSize; 
			}
		}
	} while (Module32Next(module, &moduleEntry));

	CloseHandle(module); 
	moduleEntry.modBaseAddr = 0; 
	return (DWORD)moduleEntry.modBaseAddr;
}

DWORD ProcessMemory::FindSignature(DWORD start, DWORD size, const char* sig, const char* mask)
{
	BYTE* data = new BYTE[size]; 
	SIZE_T bytesRead; 

	ReadProcessMemory(G.gameHandle, (LPVOID)start, data, size, &bytesRead); 

	for (DWORD i = 0; i < size; i++)
	{
		if (mem->MemoryCompare((const BYTE*)(data + i), (const BYTE*)sig, mask))
		{
			delete[] data; 
			return start + i; 
		}
	}
	delete[] data; 


	return NULL; 
}

bool ProcessMemory::MemoryCompare(const BYTE* bData, const BYTE* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++bData, ++bMask)
	{
		if (*szMask == 'x' && *bData != *bMask)
		{
			return false; 
		}
	}
	return (*szMask == NULL); 
}


void ProcessMemory::printDebugInfo()
{
	con->printColoredText(0xF, XOR("[SaiHack]: ")); std::cout << XOR("Successfully injected!") << std::endl;
	con->printColoredText(0xF, XOR("[SaiHack]: ")); std::cout << XOR("Window: "); con->printColoredText(0xA, XOR("Counter-Strike: Global Offensive - Direct3D 9")); std::cout << std::endl;
	con->printColoredText(0xF, XOR("[SaiHack]: ")); std::cout << XOR("ProcessId: "); SetConsoleTextAttribute(G.consoleHandle, 0xA); std::cout << G.gameProcessId << std::endl;  SetConsoleTextAttribute(G.consoleHandle, 0x7);
	con->printColoredText(0xF, XOR("[SaiHack]: ")); std::cout << XOR("Game handle: "); SetConsoleTextAttribute(G.consoleHandle, 0xA); std::cout << std::hex << G.gameHandle << std::endl;  SetConsoleTextAttribute(G.consoleHandle, 0x7);
	con->printColoredText(0xF, XOR("[SaiHack]: ")); std::cout << XOR("Client: "); SetConsoleTextAttribute(G.consoleHandle, 0xA); std::cout << std::hex << G.client_dll << std::endl;  SetConsoleTextAttribute(G.consoleHandle, 0x7);
	con->printColoredText(0xF, XOR("[SaiHack]: ")); std::cout << XOR("Engine: "); SetConsoleTextAttribute(G.consoleHandle, 0xA); std::cout << std::hex << G.engine_dll << std::endl;  SetConsoleTextAttribute(G.consoleHandle, 0x7);
	con->printColoredText(0xF, XOR("[SaiHack]: ")); std::cout << XOR("Vstdlib: "); SetConsoleTextAttribute(G.consoleHandle, 0xA); std::cout << std::hex << G.vstdlib_dll << std::endl;  SetConsoleTextAttribute(G.consoleHandle, 0x7);
	con->printColoredText(0xF, XOR("[SaiHack]: ")); std::cout << XOR("LocalPlayer: "); SetConsoleTextAttribute(G.consoleHandle, 0xA); std::cout << std::hex << mem->read<DWORD>(G.client_dll + OFF.dwLocalPlayer) << std::endl;  SetConsoleTextAttribute(G.consoleHandle, 0x7);

}

void ProcessMemory::startMemory()
{
	attachProcess();
	getGameModule("client.dll");
	getGameModule("engine.dll");
	getGameModule("vstdlib.dll");
	printDebugInfo();
}
