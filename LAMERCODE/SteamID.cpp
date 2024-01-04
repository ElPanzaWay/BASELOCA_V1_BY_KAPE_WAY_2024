///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "inclusions.h"

/////////////////////////////////////////////////////////////////////////////////////////////////

#include "MultiEmulator/MultiEmulator/Source/Emulators/RevEmu2013.h"
//#pragma comment(lib, "MultiEmulator.lib")

/////////////////////////////////////////////////////////////////////////////////////////////////

CSteamIDChanger g_SteamID;

class ISteamUser;

//using TInitiateGameConnection = int(__fastcall*)(ISteamUser * self, int, void* pData, int cbMaxData, long long steamID, int unIPServer, short usPortServer, int bSecure);
//using TSteamUser = ISteamUser * (*)();

typedef int(__fastcall* TInitiateGameConnection)(ISteamUser * self, int, void* pData, int cbMaxData, /*long*/ long steamID, int unIPServer, short usPortServer, int bSecure);
typedef ISteamUser* (*TSteamUser)();

TInitiateGameConnection pfnInitiateGameConnection = 0;

static int newSteamID = 0;
static bool RandomSteamID = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////

BOOL WINAPI hVirtualProtect(LPVOID lpAddress,DWORD dwSize,DWORD flNewProtect,PDWORD lpflOldProtect);

/////////////////////////////////////////////////////////////////////////////////////////////////

int __fastcall hkInitiateGameConnection(ISteamUser* self, int, void* pData, int cbMaxData, /*long*/ long steamID, int unIPServer, short usPortServer, int bSecure)
{
	static int iSID;

	if (RandomSteamID)
	{
		srand(time(NULL));

		iSID = rand() % 99999999 + 10000000;
	}
	else
		iSID = newSteamID;
	
	return GenerateRevEmu2013(pData, iSID);

	// return pfnInitiateGameConnection(self, 0, pData, cbMaxData, steamID, unIPServer, usPortServer, bSecure);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

bool ChangeSID()
{
	HMODULE hSteamAPI;

	while (true)
	{
		hSteamAPI = GetModuleHandleA("steam_api.dll\0");

		if (hSteamAPI)
			break;

		Sleep(500);
	}

	TSteamUser pfnSteamUser = (TSteamUser)GetProcAddress(hSteamAPI, "SteamUser\0");

	if (!pfnSteamUser)
		return FALSE;

	TSteamUser pSteamUser = (TSteamUser)pfnSteamUser();
	if (!pSteamUser)
		return FALSE;

	/* Get pointer to InitiateGameConnection method address in virtual table of ISteamUser interface. */
	DWORD pfn = (DWORD)&((void**)(*(void**)pSteamUser))[3];

	/* Save original InitiateGameConnection method code address. */
	pfnInitiateGameConnection = (TInitiateGameConnection)*(DWORD*)pfn;

	/* Write own InitiateGameConnection function address to virtual table. */
	DWORD oldProtect=0;

	////////////////////////////////////////////////////////////////////////////
	hVirtualProtect((void*)pfn, sizeof(void*), PAGE_READWRITE, &oldProtect);
	////////////////////////////////////////////////////////////////////////////

	*(DWORD*)pfn = (DWORD)hkInitiateGameConnection;

	////////////////////////////////////////////////////////////////////////////
	hVirtualProtect((void*)pfn, sizeof(void*), oldProtect, NULL);
	////////////////////////////////////////////////////////////////////////////

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void CSteamIDChanger::Apply(int newSID)
{
	if (newSID == NULL)
		RandomSteamID = true;
	else
	{
		RandomSteamID = false;
		newSteamID = newSID;
	}

	Change();
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void CSteamIDChanger::Change()
{
//	cvar.debug ? (ChangeSID() ? g_pConsole->DPrintf("SteamID changed successfully.\n\0") : g_pConsole->DPrintf("Failed to change SteamID.\n\0")) : ChangeSID() ? EXIT_SUCCESS : EXIT_FAILURE;

	if(ChangeSID())
	{
		Con_Echo("SteamID changed successfully.\n\0");
	//	g_pConsole->DPrintf("SteamID changed successfully.\n\0");
	//	EXIT_SUCCESS
	}
	else
	{
		Con_Echo("Failed to change SteamID.\n\0");
	//	g_pConsole->DPrintf("Failed to change SteamID.\n\0");
	//	EXIT_FAILURE
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////
