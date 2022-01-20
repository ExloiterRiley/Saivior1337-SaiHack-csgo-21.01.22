#include "Utils.h"

#pragma warning(disable: 4018)

Utils * iUtils;

#define NT_SUCCESS(x) ((x) >= 0)
typedef NTSTATUS(NTAPI* _NtWriteVirtualMemory)(HANDLE ProcessHandle, PVOID BaseAddress, LPCVOID Buffer, ULONG NumberOfBytesToWrite, PULONG NumberOfBytesWritten);
_NtWriteVirtualMemory NtWriteVirtualMemory = (_NtWriteVirtualMemory)GetProcAddress(GetModuleHandleA(XOR("ntdll.dll")), XOR("NtWriteVirtualMemory"));
typedef NTSTATUS(NTAPI* _NtReadVirtualMemory)(HANDLE ProcessHandle, PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToRead, PULONG NumberOfBytesRead);
_NtReadVirtualMemory NtReadVirtualMemory = (_NtReadVirtualMemory)GetProcAddress(GetModuleHandleA(XOR("ntdll.dll")), XOR("NtReadVirtualMemory"));


UINT Utils::GetModelIndexByName(const char* modelName)
{
	DWORD cstate = mem->read<DWORD>(G.engine_dll + OFF.dwClientState); 
	DWORD nst = mem->read<DWORD>(cstate + 0x52a4); 
	DWORD nsd = mem->read<DWORD>(nst + 0x40); 
	DWORD nsdi = mem->read<DWORD>(nsd + 0xC); 

	for (UINT i = 0; i < 1024; i++)
	{
		DWORD nsdi_i = mem->read<DWORD>(nsdi + 0xC + i * 0x34); 
		char str[128] = { 0 }; 
		mem->rvm(nsdi_i, &str); 
		if (str)
		{
			if (_stricmp(str, modelName) == 0)
			{
				return i; 
			}
		}
	}
	return 0; 
}
