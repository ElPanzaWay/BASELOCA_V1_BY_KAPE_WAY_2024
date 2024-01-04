//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

#include "xxx.h"

//-------------------------------------------------------------------//

PBYTE Z20GetModuleNamePointerPcm(const wchar_t* a1, DWORD th32ProcessID)
{
	PBYTE result=0;   // eax@2
	MODULEENTRY32 me; // [sp+14h] [bp-234h]@1
	HANDLE hSnapshot=0; // [sp+238h] [bp-10h]@1
  
	int i=0; // [sp+23Ch] [bp-Ch]@3

	//
	memset(&me, 0, sizeof(me));
	hSnapshot = CreateToolhelp32Snapshot(/*8u*/TH32CS_SNAPMODULE, th32ProcessID);
	if(hSnapshot)
	{
		me.dwSize = 548;
		for(i = Module32First(hSnapshot, &me); i; i = Module32Next(hSnapshot, &me) )
		{
			if ( !wcscmp(me.szModule, a1) )
			{
				CloseHandle(hSnapshot);
				return me.modBaseAddr;
			}
		}
    
		CloseHandle(hSnapshot);
		result = 0;
	}
	else
	{
		result = 0;
	}
	return result;
}

//-------------------------------------------------------------------//

void TTT()
{
	DWORD Buffer = 0;

	DWORD dwOffs = 0x61B82C;
	DWORD dwIndex = 0x617A78;

	DWORD dwON = 1;
    DWORD dwOFF = 0;

	HANDLE hProcess = GetCurrentProcess();
	DWORD hlBase = (DWORD)GetModuleHandle(L"hl.exe\0");

	if(hProcess && hlBase)
	{
		ReadProcessMemory(hProcess, (LPCVOID)(hlBase + dwOffs), &Buffer, 4, 0);

		if(!Buffer)
		{
			WriteProcessMemory(hProcess, (LPVOID)(hlBase+dwIndex), &dwOFF, 4, 0);
		//	WriteProcessMemory(hProcess, &hlBase[dwIndex], &dwOFF, 4, 0);
		}

		if(Buffer == 1)
		{
			WriteProcessMemory(hProcess, (LPVOID)(hlBase+dwIndex), &dwOFF, 4, 0);
		//	WriteProcessMemory(hProcess, &hlBase[dwIndex], &dwOFF, 4, 0);
		}

		if(Buffer == 2)
		{
			WriteProcessMemory(hProcess, (LPVOID)(hlBase+dwIndex), &dwON, 4, 0);
		//	WriteProcessMemory(hProcess, &hlBase[dwIndex], &dwON, 4, 0);
			DrawConStringCenter(calcscreen.displayCenterX - 45, calcscreen.displayCenterY+30, 255, 0, 255,
				/*[FUCKING-TRAITOR]\0*/XorStr<0x68,19,0xB9F5B6FC>("\x33\x2F\x3F\x28\x27\x24\x20\x28\x5D\x25\x20\x32\x3D\x21\x39\x25\x25\x79"+0xB9F5B6FC).s
			);
		}
	}
}

//-------------------------------------------------------------------//

void TTT1()
{
	DWORD Buffer = 0;

	DWORD dwOffs = 0x61B82C;
	DWORD dwIndex = 0x617A78;

	DWORD dwON = 1;
    DWORD dwOFF = 0;

	DWORD dwProcessId = GetCurrentProcessId();
	HANDLE hProcess = OpenProcess(0x1F0FFFu, 1, dwProcessId);//GetCurrentProcess()

	DWORD hlBase = (DWORD)Z20GetModuleNamePointerPcm(L"cstrike.exe\0", dwProcessId);
	if(!hlBase)
		hlBase = (DWORD)Z20GetModuleNamePointerPcm(L"hl.exe\0", dwProcessId);
	if(hProcess && hlBase)
	{
		ReadProcessMemory(hProcess, (LPCVOID)(hlBase + dwOffs), &Buffer, 4, 0);

		if(!Buffer)
		{
			WriteProcessMemory(hProcess, (LPVOID)(hlBase+dwIndex), &dwOFF, 4, 0);
		//	WriteProcessMemory(hProcess, &hlBase[dwIndex], &dwOFF, 4, 0);
		}

		if(Buffer == 1)
		{
			WriteProcessMemory(hProcess, (LPVOID)(hlBase+dwIndex), &dwOFF, 4, 0);
		//	WriteProcessMemory(hProcess, &hlBase[dwIndex], &dwOFF, 4, 0);
		}

		if(Buffer == 2)
		{
			WriteProcessMemory(hProcess, (LPVOID)(hlBase+dwIndex), &dwON, 4, 0);
		//	WriteProcessMemory(hProcess, &hlBase[dwIndex], &dwON, 4, 0);
			DrawConStringCenter(calcscreen.displayCenterX - 45, calcscreen.displayCenterY+30, 255, 0, 255,
				/*[FUCKING-TRAITOR]\0*/XorStr<0x68,19,0xB9F5B6FC>("\x33\x2F\x3F\x28\x27\x24\x20\x28\x5D\x25\x20\x32\x3D\x21\x39\x25\x25\x79"+0xB9F5B6FC).s
			);
		}

		CloseHandle(hProcess);
	}
	CloseHandle(hProcess);
}

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//















