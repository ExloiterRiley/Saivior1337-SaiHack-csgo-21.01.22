#pragma once
#include "m_headers.h"

class ProcessMemory
{
public:
	DWORD getProcessId();
	DWORD getGameModule(const char*	moduleName);
	DWORD FindSignature(DWORD start, DWORD size, const char* sig, const char* mask);
	void attachProcess();
	void startMemory();
	void printDebugInfo();
	bool MemoryCompare(const BYTE* bData, const BYTE* bMask, const char* szMask);


	template<class T>
	BOOL write(uint32_t address, T buffer)
	{
		return WriteProcessMemory(G.gameHandle, (LPVOID)address, &buffer, sizeof(T), NULL);
	}

	template <class dataType>
	dataType read(uint32_t addressToRead)
	{
		dataType rpmBuffer;
		ReadProcessMemory(G.gameHandle, (PVOID)addressToRead, &rpmBuffer, sizeof(dataType), 0);
		return rpmBuffer;
	}

	template <class dataType>
	void rvm(DWORD addressToRead, dataType* valToRead)
	{
		DWORD oldProtect = 0; NTSTATUS status = 0;
		VirtualProtectEx(G.gameHandle, (PVOID)addressToRead, sizeof(dataType), PAGE_EXECUTE_READWRITE, &oldProtect);
		status = NtReadVirtualMemory(G.gameHandle, PVOID(addressToRead), valToRead, sizeof(dataType), 0);
		VirtualProtectEx(G.gameHandle, (PVOID)addressToRead, sizeof(dataType), oldProtect, NULL);
	}
};

extern ProcessMemory * mem;