///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// BASELOCA V1 By WAY TEAM
//
// By Kape Way , (2024)
//
// Credits: Russian bases, OGC and Kyros Base code and ideas, gamedeception guys, unknowncheats.me, and VALVE!
//
// Tested on latest Steam CS version (Jan2024), beta versions, non-steam v43, maybe others
// https://way-team-cs.blogspot.com/
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "client_headers.h"

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
// Credits 101XD src, TKZ HACK src

void RandomizeSTEAMID(int op)// mi putita querida, junior, ripeador serial de codes rusos, y no es el único.. desde 2016 rip y rip
{

	if(op == 1)
	{

	srand ( GetTickCount ( ) );
 
	DWORD NoSteamId = (DWORD) GetModuleHandle ( "steamclient.dll\0" ) + 0x5AC60;

	*(DWORD*) NoSteamId = 0;
	NoSteamId += 4; *(DWORD*) NoSteamId = 0;
	NoSteamId += 4; *(DWORD*) NoSteamId = 0;
	NoSteamId += 4; *(DWORD*) NoSteamId = 0;
 
	char HID[16] = "\0";
	sprintf ( HID, "%X%X%X%X%X%X%X%X\0", rand()%15, rand()%15, rand()%15, rand()%15, rand()%15, rand()%15, rand()%15, rand()%15 );
	pEngfuncs->PlayerInfo_SetValueForKey ( "*HID\0", HID );

	pEngfuncs->Con_Printf ( "Validated as random Non-Steam Enabled.\n\0" );

	}

	if(op == 2)
	{

	srand ( GetTickCount ( ) );
	DWORD NoSteamId = (DWORD) GetModuleHandle ( "steamclient.dll\0" ) + 0x5AC60;
	*(DWORD*) NoSteamId = 0x69726573;
	NoSteamId += 4; *(DWORD*) NoSteamId = 0x6F676C61;
	NoSteamId += 4; *(DWORD*) NoSteamId = 0x65687365;
	NoSteamId += 4; *(DWORD*) NoSteamId = 0x00006572;
 
	DWORD UnLock = (DWORD) GetModuleHandle ( "steamclient.dll\0" ) + 0x5B4D4;
	*(DWORD*) UnLock = 0;
 
	DWORD SteamId =  (DWORD) GetModuleHandle ( "steamclient.dll\0" ) + 0x5A44A;
	*(DWORD*) SteamId = rand ( ) % 99999999;

	pEngfuncs->Con_Printf ( "Validated as random Steam Enabled.\n\0" );

	}
 
	
}

//-------------------------------------------------------------------//
