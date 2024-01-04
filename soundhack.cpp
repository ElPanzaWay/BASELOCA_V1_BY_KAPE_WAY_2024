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

/*
PVOID PreS_DynamicSound()// hpp v6
{
	auto ptr = Absolute(FindPush((PCHAR)"CL_Parse_Sound: ent = %i, cl.max_edicts %i", Module[HW].base, Module[HW].end) - 0x10);

	if (AddressNotInSpace(ptr, Module[HW].base, Module[HW].end))
	{
		ptr = Absolute(FindPush((PCHAR)"CL_Parse_Sound: ent = %i, cl.max_edicts %i", Module[HW].base, Module[HW].end) - 0x11);

		if (AddressNotInSpace(ptr, Module[HW].base, Module[HW].end))
		{
			Utils::TraceLog(V("%s: not found.\n"), V(__FUNCTION__));
			return NULL;
		}
	}

	return (PVOID)ptr;
}*/

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

/*
PEngineMsg EngineMsgByName( char* szMsgName )
{
	PEngineMsg Ptr = nullptr;
	Ptr = pEngineMsgBase;

	while ( lstrcmpA( Ptr->name , "End of List" ) )
	{
		if ( !lstrcmpA( Ptr->name , szMsgName ) )
			return Ptr;

		Ptr++;
	}

	Ptr->pfn = 0;
	return Ptr;
}

pfnEngineMessage HookEngineMsg( char *szMsgName , pfnEngineMessage pfn )
{
	PEngineMsg Ptr = nullptr;
	pfnEngineMessage Original = nullptr;

	Ptr = EngineMsgByName( szMsgName );

	if ( Ptr->pfn != 0 )
	{
		Original = Ptr->pfn;
		Ptr->pfn = pfn;
	}
	else
	{
		MessageBoxA( 0 , szMsgName , 0 , MB_OK | MB_ICONERROR );
	}

	return Original;
}

deque < Vector > d_vSoundOrigin;
deque < DWORD > d_dwSoundTime;

void MSG_SaveReadCount()
{
	MSG_SavedReadCount = *MSG_ReadCount;
}

void MSG_RestoreReadCount()
{
	*MSG_ReadCount = MSG_SavedReadCount;
}

void SVC_Sound()
{
	MSG_SaveReadCount();

	int field_mask , volume;
	float attenuation;
	int channel , ent , sound_num;
	float origin[3] = { 0 };
	int pitch;

	MSG_StartBitReading( MSG_Buffer );

	field_mask = MSG_ReadBits( 9 );

	if ( field_mask & SND_FL_VOLUME )
		volume = MSG_ReadBits( 8 ) / 255;
	else
		volume = DEFAULT_SOUND_PACKET_VOLUME;

	if ( field_mask & SND_FL_ATTENUATION )
		attenuation = MSG_ReadBits( 8 ) / 64.0f;

	channel = MSG_ReadBits( 3 );
	ent = MSG_ReadBits( 11 );

	if ( field_mask & SND_FL_LARGE_INDEX )
		sound_num = MSG_ReadBits( 16 );
	else
		sound_num = MSG_ReadBits( 8 );

	MSG_ReadBitVec3Coord( origin );

	if ( field_mask & SND_FL_PITCH )
		pitch = MSG_ReadBits( 8 );

	MSG_EndBitReading( MSG_Buffer );

	// add_log( "SVC_Sound: %i , %i [%0.2f , %0.2f %0.2f]\n" , ent , sound_num , origin[0] , origin[1] , origin[2] );

	if ( g_AntiScreen.DrawVisuals && g_Settings.esp.sound && AIM_VERSION == 0 )
	{
		if ( !g_Cheat.VisibleTrace( g_Local.vOrigin , origin ) )
		{
			d_vSoundOrigin.push_back( origin );
			d_dwSoundTime.push_back( GetTickCount() );
		}
	}

	MSG_RestoreReadCount();
	pSVC_sound();
}


void HookEngineMessages()
{
	pEngineMsgBase = (PEngineMsg)c_Offset.FindSVCMessages();
	pSVC_sound = HookEngineMsg( "svc_sound" , SVC_Sound );
}*/

//-------------------------------------------------------------------//


