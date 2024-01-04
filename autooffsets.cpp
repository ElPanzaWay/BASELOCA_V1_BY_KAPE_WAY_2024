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

cl_clientfunc_t *g_pClient=0;
cl_clientfunc_t g_Client;
//ClientDll_t gClientDll;

cl_enginefuncs_s * pEngfuncs = (cl_enginefuncs_s *)0;
struct cl_enginefuncs_s gEngfuncs;

engine_studio_api_s * pstudio = (engine_studio_api_s*)0;
struct engine_studio_api_s IEngineStudio;

struct r_studio_interface_s** ppinterface = 0;

struct playermove_s* g_ppmove = 0;

DWORD dwPDS = 0;

double* globalTime = 0;

//-------------------------------------------------------------------//

DWORD HL_EXE_HANDLE = 0;
DWORD HL_EXE_BASE = 0;
DWORD HL_EXE_SIZE = 0;
DWORD HL_EXE_END = 0;

DWORD SW_MODULE_HANDLE = 0;
DWORD SW_MODULE_BASE = 0;
DWORD SW_MODULE_SIZE = 0;

DWORD HW_MODULE_HANDLE = 0;
DWORD HW_MODULE_BASE = 0;
DWORD HW_MODULE_SIZE = 0;
DWORD HW_MODULE_END = 0;

DWORD CLIENT_MODULE_HANDLE = 0;
DWORD CLIENT_MODULE_BASE = 0;
DWORD CLIENT_MODULE_SIZE = 0;
DWORD CLIENT_MODULE_END = 0;

DWORD VgBase = 0;
DWORD VgSize = 0;
DWORD VgEnd = 0;

//-------------------------------------------------------------------//

#define OFF_ENGINE_PATTERN	"\xFF\x15\xFF\xFF\xFF\xFF\x68\xFF\xFF\xFF\xFF\x89\x86\xFF\xFF\xFF\xFF\xFF\x15\xFF\xFF\xFF\xFF\x68\xFF\xFF\xFF\xFF\x89\x86\xFF\xFF\xFF\xFF\xFF\x15\xFF\xFF\xFF\xFF\x68\xFF\xFF\xFF\xFF\x89\x86\xFF\xFF\xFF\xFF\xFF\x15\xFF\xFF\xFF\xFF\x68\xFF\xFF\xFF\xFF\x89\x86\xFF\xFF\xFF\xFF\xFF\x15\xFF\xFF\xFF\xFF\x68\xFF\xFF\xFF\xFF\x89\x86\xFF\xFF\xFF\xFF\xFF\x15\xFF\xFF\xFF\xFF\x68\xFF\xFF\xFF\xFF\x89\x86\xFF\xFF\xFF\xFF\xFF\x15\xFF\xFF\xFF\xFF\x68\xFF\xFF\xFF\xFF\x89\x86\xFF\xFF\xFF\xFF\xFF\x15\xFF\xFF\xFF\xFF"
#define OFF_SVC_MSG_PATTERN	"\xBF\xFF\xFF\xFF\xFF\x8B\x04\xB5\xFF\xFF\xFF\xFF\x85\xC0\x74\xFF\x81\xFF\xFF\xFF\xFF\xFF\x7F\x04\x8B\x0F\xEB\x05"

DWORD FindPattern( PCHAR pattern , PCHAR mask , DWORD start , DWORD end , DWORD offset );
DWORD FindPattern( PCHAR pattern , DWORD start , DWORD end , DWORD offset );
DWORD FindReferenceX( DWORD start , DWORD end , DWORD Address );

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

DWORD FarProc( DWORD Address , DWORD LB , DWORD HB )
{
	return ( ( Address < LB ) || ( Address > HB ) );
}

//-------------------------------------------------------------------//
/*
typedef unsigned Cardinal;
typedef unsigned* PCardinal;
typedef unsigned** PPCardinal;
unsigned Absolute(DWORD Addr)
{
	return Cardinal(Addr) + *(PCardinal)(Addr)+4;
}*/

DWORD Absolute( DWORD Address )
{
	return Address + *(PDWORD)Address + 4;
}

//-------------------------------------------------------------------//

DWORD GetModuleSize( DWORD Address )
{
	return PIMAGE_NT_HEADERS( Address + (DWORD)PIMAGE_DOS_HEADER( Address )->e_lfanew )->OptionalHeader.SizeOfImage;
}

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

bool CheckByte(DWORD Address, BYTE Value, int Offset)
{
	if (*(PBYTE)((DWORD)Address + Offset) == Value)
		return true;
	else
		return false;
}

#define CompareMemory(Buff1, Buff2, Size) __comparemem((const UCHAR *)Buff1, (const UCHAR *)Buff2, (UINT)Size)
#define FindMemoryClone(Start, End, Clone, Size) __findmemoryclone((const ULONG)Start, (const ULONG)End, (const ULONG)Clone, (UINT)Size)
#define FindReference(Start, End, Address) __findreference((const ULONG)Start, (const ULONG)End, (const ULONG)Address)

BOOL __comparemem(const UCHAR *buff1, const UCHAR *buff2, UINT size)
{
	for (UINT i = 0; i < size; i++, buff1++, buff2++)
	{
		if ((*buff1 != *buff2) && (*buff2 != 0xFF))
			return FALSE;
	}
	return TRUE;
}

ULONG __findmemoryclone(const ULONG start, const ULONG end, const ULONG clone, UINT size)
{
	for (ULONG ul = start; (ul + size) < end; ul++)
	{
		if (CompareMemory(ul, clone, size))
			return ul;
	}
	return NULL;
}

ULONG __findreference(const ULONG start, const ULONG end, const ULONG address)
{
	UCHAR Pattern[5];
	Pattern[0] = 0x68;
	*(ULONG*)&Pattern[1] = address;
	return FindMemoryClone(start, end, Pattern, sizeof(Pattern)-1);
}

DWORD MessagePtr(char Message[], BYTE size)
{
	BYTE bPushAddrPattern[5] = { 0x68, 0x90, 0x90, 0x90, 0x90 };
	char* String = new char[size];
	strcpy(String, Message);
	DWORD Address = FindMemoryClone(HW_MODULE_BASE, HW_MODULE_BASE + HW_MODULE_SIZE, 
		(PBYTE)String, size - 1);
	*(PDWORD)(bPushAddrPattern + 1) = Address;
	Address = FindMemoryClone(HW_MODULE_BASE, HW_MODULE_BASE + HW_MODULE_SIZE, 
		(PBYTE)bPushAddrPattern, 5);
	return Address;
}

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

void GetRenderType()
{
	char hw_dll[] = { 'h','w','.','d','l','l',0 };
	char sw_dll[] = { 's','w','.','d','l','l',0 };
	
	HW_MODULE_HANDLE = (DWORD)GetModuleHandleA( hw_dll );
	SW_MODULE_HANDLE = (DWORD)GetModuleHandleA( sw_dll );
	HL_EXE_HANDLE = (DWORD)GetModuleHandleA( NULL );
}

//-------------------------------------------------------------------//

bool GetModuleInfo()// INITIALIZE INFORMATION
{
	char client_dll[] = { 'c','l','i','e','n','t','.','d','l','l',0 };
	char gameui_dll[] = { 'G','a','m','e','U','I','.','d','l','l',0 };

	GetRenderType();

	if ( HW_MODULE_HANDLE )
		HW_MODULE_BASE = HW_MODULE_HANDLE;
	else if ( SW_MODULE_HANDLE )
		HW_MODULE_BASE = SW_MODULE_HANDLE;
	else
		HW_MODULE_BASE = HL_EXE_HANDLE;

	HW_MODULE_SIZE = GetModuleSize( HW_MODULE_BASE );
	HW_MODULE_END = HW_MODULE_BASE + HW_MODULE_SIZE - 1;

	HL_EXE_BASE = HL_EXE_HANDLE;
	HL_EXE_SIZE = (DWORD)GetModuleSize( HL_EXE_BASE );
	HL_EXE_END = HL_EXE_BASE + HL_EXE_SIZE - 1;

	CLIENT_MODULE_BASE = (DWORD)GetModuleHandleA( client_dll );

	if ( CLIENT_MODULE_BASE )
	{
		CLIENT_MODULE_SIZE = GetModuleSize( CLIENT_MODULE_BASE );
		CLIENT_MODULE_END = CLIENT_MODULE_BASE + CLIENT_MODULE_SIZE - 1;
	}
	else
	{
		CLIENT_MODULE_BASE = HW_MODULE_BASE;
		CLIENT_MODULE_END = HW_MODULE_END;
		CLIENT_MODULE_SIZE = HW_MODULE_SIZE;
	}
		
	VgBase = (DWORD)GetModuleHandleA( gameui_dll );
	
	if ( VgBase )
	{
		VgSize = (DWORD)GetModuleSize( VgBase );
		VgEnd = VgBase + VgSize - 1;
	}

	return ( HW_MODULE_BASE && CLIENT_MODULE_BASE && HL_EXE_BASE && VgBase );
}

//-------------------------------------------------------------------//

DWORD FindClientTable()
{
	char off_client_pattern[] = { 'S','c','r','e','e','n','F','a','d','e',0 };
	
	BYTE ClientOffset[2] = { 0x10, 0x13 };

	DWORD PatternAddress = FindPattern( off_client_pattern , HW_MODULE_BASE , HW_MODULE_END , 0 );

	if ( PatternAddress )
	{
		for ( byte i = 0; i < sizeof( ClientOffset ); i++ )
		{
			DWORD ClientTablePtr = *(PDWORD)( 
				
				FindReferenceX( HW_MODULE_BASE , HW_MODULE_END , PatternAddress ) + ClientOffset[i] );

			if ( !FarProc( (DWORD)ClientTablePtr , HW_MODULE_BASE , HW_MODULE_END ) &&
				 !IsBadReadPtr( (PVOID)ClientTablePtr , sizeof( cl_clientfunc_t ) ) )
			{
				return ClientTablePtr;
			}
		}
	}

	return 0;
}

void* ClientFuncs(void)
{
	bool bMustLeave = false;

	PCHAR String = "ScreenFade\0";
//	PCHAR String = (char*)/*ScreenFade\0*/XorStr<0x71,12,0xC92AD028>("\x22\x11\x01\x11\x10\x18\x31\x19\x1D\x1F\x7B"+0xC92AD028).s;
	DWORD Address = (DWORD)FindMemoryClone(HW_MODULE_BASE, HW_MODULE_BASE+HW_MODULE_SIZE, String, strlen(String));
	PVOID ClientPtr = (PVOID)*(PDWORD)(FindReference(HW_MODULE_BASE, HW_MODULE_BASE+HW_MODULE_SIZE, Address) + 0x13);
	
	if ( FarProc((DWORD)ClientPtr,HW_MODULE_BASE,HW_MODULE_END) )
	{
//		Error((char*)"Couldn't find ClientPtr pointer.\0");
		bMustLeave = true;
	}
	
	if(!bMustLeave)
	{
		return ClientPtr;
	}

	return 0;
}

//-------------------------------------------------------------------//

DWORD FindEngineTable()
{
	char off_engine_mask[] = 
	{ 
		'x','x','?','?','?','?','x','?','?','?','?','x','x','?','?','?','?','x',
		'x','?','?','?','?','x','?','?','?','?','x','x','?','?','?','?','x','x',
		'?','?','?','?','x','?','?','?','?','x','x','?','?','?','?','x','x','?',
		'?','?','?','x','?','?','?','?','x','x','?','?','?','?','x','x','?','?',
		'?','?','x','?','?','?','?','x','x','?','?','?','?','x','x','?','?','?',
		'?','x','?','?','?','?','x','x','?','?','?','?','x','x','?','?','?','?',
		'x','?','?','?','?','x','x','?','?','?','?','x','x','?','?','?','?',0
	};

	DWORD PatternAddress = FindPattern( OFF_ENGINE_PATTERN , off_engine_mask , 
		
		CLIENT_MODULE_BASE , CLIENT_MODULE_END , 0x02 );
	
	if ( PatternAddress )
	{
		if ( !FarProc( (DWORD)PatternAddress , CLIENT_MODULE_BASE , CLIENT_MODULE_END ) )
		{
			return *(PDWORD)PatternAddress;
		}
	}
	else
	{
		PatternAddress = FindPattern( OFF_ENGINE_PATTERN , off_engine_mask , 
			HL_EXE_BASE , HL_EXE_END , 0x02 );

		if ( PatternAddress )
		{
			if ( !FarProc( (DWORD)PatternAddress , HL_EXE_BASE , HL_EXE_END ) )
			{
				return *(PDWORD)PatternAddress;
			}
		}
	}

	return 0;
}

void* EngineFuncs(void)
{
	bool bMustLeave = false;

	PCHAR String = "ScreenFade\0";
//	PCHAR String = (char*)/*ScreenFade\0*/XorStr<0x71,12,0xC92AD028>("\x22\x11\x01\x11\x10\x18\x31\x19\x1D\x1F\x7B"+0xC92AD028).s;
	DWORD Address = FindMemoryClone(HW_MODULE_BASE, HW_MODULE_BASE+HW_MODULE_SIZE, String, strlen(String));
	PVOID EnginePtr = (PVOID)*(PDWORD)(FindReference(HW_MODULE_BASE, HW_MODULE_BASE+HW_MODULE_SIZE, Address) + 0x0D);
	
	if ( FarProc((DWORD)EnginePtr,HW_MODULE_BASE,HW_MODULE_END) )
	{
//		Error((char*)"Couldn't find EnginePtr pointer.\0");
		bMustLeave = true;
	}

	if(!bMustLeave)
	{
		return EnginePtr;
	}

	return 0;
}

/*
DWORD GetExportsPtr()
{
	DWORD dwExportTable=0;

	dwExportTable = dwFindPattern( (DWORD)GetModuleHandle( "hw.dll\0" ), 0x0122A000, 
		(BYTE*)"\x68\x00\x00\x00\x00\x68\x00\x00\x00\x00\x50\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00", "x????x????xxx????????xx????????\0" );
	
	if( dwExportTable != NULL )
	{
		dwExportTable = *(DWORD*)(dwExportTable + 0x1);
	}
	return dwExportTable;
}*/


//-------------------------------------------------------------------//

DWORD FindStudioTable()// FALLA EN EL ÚLTIMO STEAM
{
	DWORD StudioTablePtr = *(DWORD*)( (DWORD)g_pClient->HUD_GetStudioModelInterface + 0x30 ); // old patch, dod

	if ( FarProc( (DWORD)StudioTablePtr , HW_MODULE_BASE , HW_MODULE_END ) && 
		
		FarProc( (DWORD)StudioTablePtr , HL_EXE_BASE , HL_EXE_END ) &&

		FarProc( (DWORD)StudioTablePtr , CLIENT_MODULE_BASE , CLIENT_MODULE_END ) /*FOR DOD*/ )
	{
		StudioTablePtr = *(DWORD*)( (DWORD)g_pClient->HUD_GetStudioModelInterface + 0x1A ); // new patch / steam	

		if ( FarProc( (DWORD)StudioTablePtr , CLIENT_MODULE_BASE , CLIENT_MODULE_END ) )
			return 0;
	}

	return StudioTablePtr;
}

/*
PVOID Studio()// hpp v6
{
	auto ptr = *(PDWORD)((uintptr_t)g_pClient->HUD_GetStudioModelInterface + 0x30);

	if (AddressNotInSpace(ptr, Module[CLIENT].base, Module[CLIENT].end))
	{
		ptr = *(PDWORD)((uintptr_t)g_pClient->HUD_GetStudioModelInterface + 0x1A);

		if (AddressNotInSpace(ptr, Module[CLIENT].base, Module[CLIENT].end))
		{
			Utils::TraceLog(V("%s: not found.\n"), V(__FUNCTION__));
			return NULL;
		}
	}

	return (PVOID)ptr;
}*/


DWORD EngineStudio(void)
{
	bool bMustLeave = false;

//start_ptr:
	bool badptr = false;
	DWORD OLD = 0;
	DWORD dwStudioone = 0;
	PCHAR String = "Couldn't get client .dll studio model rendering interface.\0";
//	PCHAR String = (char*)/*Couldn't get client .dll studio model rendering interface.\0*/XorStr<0x75,60,0x116A3BA5>("\x36\x19\x02\x14\x1D\x14\x5C\x08\x5D\x19\x1A\xF4\xA1\xE1\xEF\xED\xE0\xE8\xF3\xA8\xA7\xEE\xE7\xE0\xAD\xFD\xFB\xE5\xF5\xFB\xFC\xB4\xF8\xF9\xF3\xFD\xF5\xBA\xE9\xF9\xF3\xFA\xFA\xD2\xC8\xCC\xC4\x84\xCC\xC8\xD3\xCD\xDB\xCC\xCA\xCF\xC8\x80\xAF"+0x116A3BA5).s;
	DWORD Address = FindMemoryClone(HW_MODULE_BASE, HW_MODULE_BASE+HW_MODULE_SIZE, String, strlen(String));
	PVOID EngineStudioPtr = (PVOID)*(PDWORD)(FindReference(HW_MODULE_BASE, HW_MODULE_BASE+HW_MODULE_SIZE, Address) - 0x14);

	if ( FarProc((DWORD)EngineStudioPtr,HW_MODULE_BASE,HW_MODULE_END) )
	{
//		Error((char*)"Couldn't find EngineStudioPtr #1 pointer.\0");
		bMustLeave = true;
	}

	if(!bMustLeave)
	{

		if(!g_pClient)
		{
			return  0;
		}

	for(DWORD i = 0;i <= 60;i++)
	{


		dwStudioone = (DWORD)g_pClient->HUD_GetStudioModelInterface + i;


		if ( CheckByte(dwStudioone,0xB8,0) || CheckByte(dwStudioone,0xBF,0) )
		{
			dwStudioone++;

			if ( IsBadReadPtr((PDWORD)(*(PDWORD)dwStudioone),sizeof(engine_studio_api_s)) )
				badptr = true;
			else
				badptr = false;

			if ( badptr == false ) 
			{
				if ( *(PWORD)(PDWORD)EngineStudioPtr == *(PWORD)(PDWORD)(*(PDWORD)dwStudioone) )
				{
					return *(PDWORD)dwStudioone;
				}
			}
		}
	}

	}

//	goto start_ptr;
	return  0;
}

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
// OTROS OFFSETS
//-------------------------------------------------------------------//

/*
#define OFF_SVC_MSG_PATTERN "\xBF\xFF\xFF\xFF\xFF\x8B\x04\xB5\xFF\xFF\xFF\xFF\x85\xC0\x74\xFF\x81\xFF\xFF\xFF\xFF\xFF\x7F\x04\x8B\x0F\xEB\x05"
#define OFF_SVC_MSG_MASK	"x????xxx????xxx?xx????xxxxxx"

//

typedef unsigned __int16 uint16;

typedef void( *pfnEngineMessage )( );

typedef struct sizebuf_s
{
	const char *buffername;
	uint16 flags;
	byte *data;
	int maxsize;
	int cursize;
} sizebuf_t;

typedef struct EngineMsg
{
	int number;
	char* name;
	pfnEngineMessage pfn;
} *PEngineMsg;

#define BIT(n) (1<<(n))

#define DEFAULT_SOUND_PACKET_VOLUME			255

// Sound flags
#define SND_FL_VOLUME			BIT(0)	// send volume
#define SND_FL_ATTENUATION		BIT(1)	// send attenuation
#define SND_FL_LARGE_INDEX		BIT(2)	// send sound number as short instead of byte
#define SND_FL_PITCH			BIT(3)	// send pitch

//

typedef byte( *HL_MSG_ReadByte )( );
typedef void( *HL_MSG_ReadBitVec3Coord )( float* fa );
typedef int( *HL_MSG_ReadBits )( int Count );
typedef void( *HL_MSG_StartBitReading )( sizebuf_t* buffer );
typedef void( *HL_MSG_EndBitReading )( sizebuf_t* buffer );

int* MSG_ReadCount = 0;
int MSG_SavedReadCount = 0;
sizebuf_t* MSG_Buffer = 0;

HL_MSG_ReadByte MSG_ReadByte = 0;
HL_MSG_ReadBitVec3Coord MSG_ReadBitVec3Coord = 0;
HL_MSG_ReadBits MSG_ReadBits = 0;
HL_MSG_StartBitReading MSG_StartBitReading = 0;
HL_MSG_EndBitReading MSG_EndBitReading = 0;

pfnEngineMessage pSVC_sound = 0;
PEngineMsg pEngineMsgBase = 0;

//

DWORD FindSVCMessages()
{
	DWORD EngineMsgBase = FindPattern( OFF_SVC_MSG_PATTERN , OFF_SVC_MSG_MASK , 
		HW_MODULE_BASE , HW_MODULE_END , 1 );

	PEngineMsg pEngineMsgBase = (PEngineMsg)( *(PDWORD)EngineMsgBase - sizeof( DWORD ) );

	if ( pEngineMsgBase )
	{
		MSG_ReadByte = (HL_MSG_ReadByte)Absolute( ( (DWORD)pEngineMsgBase[32].pfn ) + 1 );
		MSG_ReadCount = *(PINT*)( (INT)(MSG_ReadByte)+1 );

		DWORD SVC_SoundBase = (DWORD)pEngineMsgBase[6].pfn;

		if ( *(PBYTE)( SVC_SoundBase + 0x0E ) == 0xE8 )
		{
			MSG_Buffer = (sizebuf_t *)( *(PDWORD)( SVC_SoundBase + 0x0A ) );
			MSG_StartBitReading = (HL_MSG_StartBitReading)Absolute( SVC_SoundBase + 0x0F );
			MSG_ReadBits = (HL_MSG_ReadBits)Absolute( SVC_SoundBase + 0x16 );
		}
		else if ( *(PBYTE)( SVC_SoundBase + 0x0C ) == 0xE8 )
		{
			MSG_Buffer = (sizebuf_t *)( *(PDWORD)( SVC_SoundBase + 0x08 ) );
			MSG_StartBitReading = (HL_MSG_StartBitReading)Absolute( SVC_SoundBase + 0x0D );
			MSG_ReadBits = (HL_MSG_ReadBits)Absolute( SVC_SoundBase + 0x14 );
		}

		if ( *(PBYTE)( SVC_SoundBase + 0xD6 ) == 0xE8 )
		{
			MSG_EndBitReading = (HL_MSG_EndBitReading)Absolute( SVC_SoundBase + 0xD7 );
			MSG_ReadBitVec3Coord = (HL_MSG_ReadBitVec3Coord)Absolute( SVC_SoundBase + 0xAF );
		}
		else if ( *(PBYTE)( SVC_SoundBase + 0xE2 ) == 0xE8 )
		{
			MSG_EndBitReading = (HL_MSG_EndBitReading)Absolute( SVC_SoundBase + 0xE3 );
			MSG_ReadBitVec3Coord = (HL_MSG_ReadBitVec3Coord)Absolute( SVC_SoundBase + 0xBE );
		}
	}

	return (DWORD)pEngineMsgBase;
}*/

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

/*
#define OFF_CLIENT_PATTERN "ScreenFade"

#define OFF_ENGINE_PATTERN	"\xFF\x15\xFF\xFF\xFF\xFF\x68\xFF\xFF\xFF\xFF\x89\x86\xFF\xFF\xFF\xFF\xFF\x15\xFF\xFF\xFF\xFF\x68\xFF\xFF\xFF\xFF\x89\x86\xFF\xFF\xFF\xFF\xFF\x15\xFF\xFF\xFF\xFF\x68\xFF\xFF\xFF\xFF\x89\x86\xFF\xFF\xFF\xFF\xFF\x15\xFF\xFF\xFF\xFF\x68\xFF\xFF\xFF\xFF\x89\x86\xFF\xFF\xFF\xFF\xFF\x15\xFF\xFF\xFF\xFF\x68\xFF\xFF\xFF\xFF\x89\x86\xFF\xFF\xFF\xFF\xFF\x15\xFF\xFF\xFF\xFF\x68\xFF\xFF\xFF\xFF\x89\x86\xFF\xFF\xFF\xFF\xFF\x15\xFF\xFF\xFF\xFF\x68\xFF\xFF\xFF\xFF\x89\x86\xFF\xFF\xFF\xFF\xFF\x15\xFF\xFF\xFF\xFF"
#define OFF_ENGINE_MASK "xx????x????xx????xx????x????xx????xx????x????xx????xx????x????xx????xx????x????xx????xx????x????xx????xx????x????xx????xx????"

#define OFF_SVC_MSG_PATTERN "\xBF\xFF\xFF\xFF\xFF\x8B\x04\xB5\xFF\xFF\xFF\xFF\x85\xC0\x74\xFF\x81\xFF\xFF\xFF\xFF\xFF\x7F\x04\x8B\x0F\xEB\x05"
#define OFF_SVC_MSG_MASK "x????xxx????xxx?xx????xxxxxx"

#define OFF_MSG_USER_MASK1 "xxx????x"
#define OFF_MSG_USER_MASK2 "???xxxx????x"

#define OFF_MSG_READ_CORD "MSG_ReadCoord"
#define OFF_MSG_STR_READING "MSG_StartBitReading"
#define OFF_MSG_END_READING "MSG_EndBitReading"
#define OFF_ENGINE_MSG_BASE "EngineMsgBase"
#define OFF_SVC_MESSAGES_P "End of List"

typedef void( *pfnEngineMessage )( );

typedef struct EngineMsg
{
	int number;
	char* name;
	pfnEngineMessage pfn;
} *PEngineMsg;

PEngineMsg pEngineMsgBase;
*/

/*
PEngineMsg EngineMsgByName( char* szMsgName )
{
	PEngineMsg Ptr = nullptr;
	Ptr = pEngineMsgBase;

	while ( native_strcmp( Ptr->name , OFF_SVC_MESSAGES_P ) )
	{
		if ( !native_strcmp( Ptr->name , szMsgName ) )
			return Ptr;

		Ptr++;
	}

	Ptr->pfn = 0;
	return Ptr;
}*/

/*
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
}*/

/*
void HookEngineMessages()
{
	pEngineMsgBase = (PEngineMsg)offset.FindSVCMessages();

	pSVC_sound = HookEngineMsg( SVC_SOUND_MSG , SVC_Sound );
	pSVC_SpawnStaticSound = HookEngineMsg( SVC_SPAWNSTATIC_SOUND_MSG , SVC_SpawnStaticSound );
}*/

/*
typedef struct sizebuf_s
{
	const char *buffername;
	uint16 flags;
	byte *data;
	int maxsize;
	int cursize;
} sizebuf_t;

typedef struct c_sizebuf_s
{
	qboolean		bOverflow;	// overflow reading or writing
	const char	*pDebugName;	// buffer name (pointer to const name)

	byte		*pData;
	int		iCurBit;
	int		nDataBits;
} c_sizebuf_t;

#define	SVC_BAD                   0
#define	SVC_NOP                   1
#define	SVC_DISCONNECT            2
#define	SVC_EVENT                 3
#define	SVC_VERSION               4
#define	SVC_SETVIEW               5
#define	SVC_SOUND                 6
#define	SVC_TIME                  7
#define	SVC_PRINT                 8
#define	SVC_STUFFTEXT             9
#define	SVC_SETANGLE              10
#define	SVC_SERVERINFO            11
#define	SVC_LIGHTSTYLE            12
#define	SVC_UPDATEUSERINFO        13
#define	SVC_DELTADESCRIPTION      14
#define	SVC_CLIENTDATA            15
#define	SVC_STOPSOUND             16
#define	SVC_PINGS                 17
#define	SVC_PARTICLE              18
#define	SVC_DAMAGE                19
#define	SVC_SPAWNSTATIC           20
#define	SVC_EVENT_RELIABLE        21
#define	SVC_SPAWNBASELINE         22
#define	SVC_TEMPENTITY            23
#define	SVC_SETPAUSE              24
#define	SVC_SIGNONNUM             25
#define	SVC_CENTERPRINT           26
#define	SVC_KILLEDMONSTER         27
#define	SVC_FOUNDSECRET           28
#define	SVC_SPAWNSTATICSOUND      29
#define	SVC_INTERMISSION          30
#define	SVC_FINALE                31
#define	SVC_CDTRACK               32
#define	SVC_RESTORE               33
#define	SVC_CUTSCENE              34
#define	SVC_WEAPONANIM            35
#define	SVC_DECALNAME             36
#define	SVC_ROOMTYPE              37
#define	SVC_ADDANGLE              38
#define	SVC_NEWUSERMSG            39
#define	SVC_PACKETENTITIES        40
#define	SVC_DELTAPACKETENTITIES   41
#define	SVC_CHOKE                 42
#define	SVC_RESOURCELIST          43
#define	SVC_NEWMOVEVARS           44
#define	SVC_RESOURCEREQUEST       45
#define	SVC_CUSTOMIZATION         46
#define	SVC_CROSSHAIRANGLE        47
#define	SVC_SOUNDFADE             48
#define	SVC_FILETXFERFAILED       49
#define	SVC_HLTV                  50
#define	SVC_DIRECTOR              51
#define	SVC_VOICEINIT             52
#define	SVC_VOICEDATA             53
#define	SVC_SENDEXTRAINFO         54
#define	SVC_TIMESCALE             55
#define	SVC_RESOURCELOCATION      56
#define	SVC_SENDCVARVALUE         57
#define	SVC_SENDCVARVALUE2        58

//

#define BIT(n) (1<<(n))

#define DEFAULT_SOUND_PACKET_VOLUME			255
#define DEFAULT_SOUND_PACKET_ATTENUATION	1.0f
#define DEFAULT_SOUND_PACKET_PITCH			100

// Sound flags
#define SND_FL_VOLUME			BIT(0)	// send volume
#define SND_FL_ATTENUATION		BIT(1)	// send attenuation
#define SND_FL_LARGE_INDEX		BIT(2)	// send sound number as short instead of byte
#define SND_FL_PITCH			BIT(3)	// send pitch
#define SND_FL_SENTENCE			BIT(4)	// set if sound num is actually a sentence num
#define SND_FL_STOP				BIT(5)	// stop the sound
#define SND_FL_CHANGE_VOL		BIT(6)	// change sound vol
#define SND_FL_CHANGE_PITCH		BIT(7)	// change sound pitch
#define SND_FL_SPAWNING			BIT(8)	// we're spawning, used in some cases for ambients (not sent across network)

// director command types:
#define DRC_CMD_NONE				0	// NULL director command
#define DRC_CMD_START				1	// start director mode
#define DRC_CMD_EVENT				2	// informs about director command
#define DRC_CMD_MODE				3	// switches camera modes
#define DRC_CMD_CAMERA				4	// set fixed camera
#define DRC_CMD_TIMESCALE			5	// sets time scale
#define DRC_CMD_MESSAGE				6	// send HUD centerprint
#define DRC_CMD_SOUND				7	// plays a particular sound
#define DRC_CMD_STATUS				8	// HLTV broadcast status
#define DRC_CMD_BANNER				9	// set GUI banner
#define DRC_CMD_STUFFTEXT			10	// like the normal svc_stufftext but as director command
#define DRC_CMD_CHASE				11	// chase a certain player
#define DRC_CMD_INEYE				12	// view player through own eyes
#define DRC_CMD_MAP					13	// show overview map
#define DRC_CMD_CAMPATH				14	// define camera waypoint
#define DRC_CMD_WAYPOINTS			15	// start moving camera, inetranl message
#define DRC_CMD_LAST				15


typedef byte( *HL_MSG_ReadByte )( );
typedef short( *HL_MSG_ReadShort )( );
typedef int( *HL_MSG_ReadLong )( );
typedef float( *HL_MSG_ReadFloat )( );
typedef char* ( *HL_MSG_ReadString )( );
typedef float( *HL_MSG_ReadCoord )( );
typedef void( *HL_MSG_ReadBitVec3Coord )( float* fa );
typedef int( *HL_MSG_ReadBits )( int Count );
typedef void( *HL_MSG_StartBitReading )( sizebuf_t* buffer );
typedef void( *HL_MSG_EndBitReading )( sizebuf_t* buffer );


int* MSG_ReadCount = 0;
int* MSG_CurrentSize = 0;
int* MSG_BadRead = 0;
int MSG_SavedReadCount = 0;
sizebuf_t* MSG_Buffer = 0;

HL_MSG_ReadByte MSG_ReadByte = 0;
HL_MSG_ReadShort MSG_ReadShort = 0;
HL_MSG_ReadLong MSG_ReadLong = 0;
HL_MSG_ReadFloat MSG_ReadFloat = 0;
HL_MSG_ReadString MSG_ReadString = 0;
HL_MSG_ReadCoord MSG_ReadCoord = 0;
HL_MSG_ReadBitVec3Coord MSG_ReadBitVec3Coord = 0;
HL_MSG_ReadBits MSG_ReadBits = 0;
HL_MSG_StartBitReading MSG_StartBitReading = 0;
HL_MSG_EndBitReading MSG_EndBitReading = 0;

void MSG_SaveReadCount()
{
	MSG_SavedReadCount = *MSG_ReadCount;
}

void MSG_RestoreReadCount()
{
	*MSG_ReadCount = MSG_SavedReadCount;
}

pfnEngineMessage pSVC_sound;
pfnEngineMessage pSVC_SpawnStaticSound;

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
		volume = MSG_ReadBits( 8 ) / 255.0;
	else
		volume = DEFAULT_SOUND_PACKET_VOLUME;

	if ( field_mask & SND_FL_ATTENUATION )
		attenuation = MSG_ReadBits( 8 ) / 64.0;

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

	///////////////////////////////////////////////////////

//	if ( !PathFree( origin ) )
//	{
//		g_Sound.AddSound( GetTickCount() , origin );
//	}

	///////////////////////////////////////////////////////

	MSG_RestoreReadCount();
	pSVC_sound();
}

void SVC_SpawnStaticSound()
{
	MSG_SaveReadCount();

	float pos[3] = { 0 };

	int soundnum;
	float vol , attenuation;
	int ent , pitch , fFlags;

	MSG_StartBitReading( MSG_Buffer );

	pos[0] = MSG_ReadCoord();
	pos[1] = MSG_ReadCoord();
	pos[2] = MSG_ReadCoord();

	soundnum = MSG_ReadShort();
	vol = MSG_ReadByte() / 255.0;
	attenuation = MSG_ReadByte() / 64.0;
	ent = MSG_ReadShort();
	pitch = MSG_ReadByte();
	fFlags = MSG_ReadByte();

	//////////////////////////////////////////////////////

//	if ( !PathFree( pos ) )
//	{
//		g_Sound.AddSound( GetTickCount() , pos );
//	}

	//////////////////////////////////////////////////////

	MSG_EndBitReading( MSG_Buffer );

	MSG_RestoreReadCount();
	pSVC_SpawnStaticSound();
}

//

#define OFF_ERROR "Error Find"
void Error( PCHAR Msg )
{
	MessageBoxA( 0 , Msg , OFF_ERROR , MB_OK | MB_ICONERROR );
	TerminateProcess( GetCurrentProcess() , 0 );
}

DWORD FindSVCMessages2()
{
	DWORD EngineMsgBase = FindPattern( OFF_SVC_MSG_PATTERN , OFF_SVC_MSG_MASK , 
		HW_MODULE_BASE , HW_MODULE_END , 1 );

	PEngineMsg pEngineMsgBase = (PEngineMsg)( *(PDWORD)EngineMsgBase - sizeof( DWORD ) );

	if ( pEngineMsgBase )
	{
		MSG_ReadByte = (HL_MSG_ReadByte)Absolute( ( (DWORD)pEngineMsgBase[SVC_CDTRACK].pfn ) + 1 );
		MSG_ReadShort = (HL_MSG_ReadShort)Absolute( ( (DWORD)pEngineMsgBase[SVC_STOPSOUND].pfn ) + 1 );
		MSG_ReadLong = (HL_MSG_ReadLong)Absolute( ( (DWORD)pEngineMsgBase[SVC_VERSION].pfn ) + 1 );
		MSG_ReadFloat = (HL_MSG_ReadFloat)Absolute( ( (DWORD)pEngineMsgBase[SVC_TIMESCALE].pfn ) + 1 );
		MSG_ReadString = (HL_MSG_ReadString)Absolute( ( (DWORD)pEngineMsgBase[SVC_PRINT].pfn ) + 1 );

		DWORD CallMSG_ReadCoord = Absolute( (DWORD)( pEngineMsgBase[SVC_PARTICLE].pfn ) + 1 );

		if ( *(PBYTE)( CallMSG_ReadCoord + 0x13 ) == 0xE8 )	// STEAM
			MSG_ReadCoord = (HL_MSG_ReadCoord)Absolute( ( CallMSG_ReadCoord + 0x14 ) );
		else if ( *(PBYTE)( CallMSG_ReadCoord + 0x15 ) == 0xE8 )	// OLD PATCH (SOFTWARE)
			MSG_ReadCoord = (HL_MSG_ReadCoord)Absolute( ( CallMSG_ReadCoord + 0x16 ) );
		else if ( *(PBYTE)( CallMSG_ReadCoord + 0x0E ) == 0xE8 )	// OLD PATCH
			MSG_ReadCoord = (HL_MSG_ReadCoord)Absolute( ( CallMSG_ReadCoord + 0x0F ) );
		else if ( *(PBYTE)( CallMSG_ReadCoord + 0x0B ) == 0xE8 )	// OLD OLD PATCH
			MSG_ReadCoord = (HL_MSG_ReadCoord)Absolute( ( CallMSG_ReadCoord + 0x0C ) );
		else
		{
		//	Error( OFF_MSG_READ_CORD );
		}

		MSG_ReadCount = *(PINT*)( (INT)(MSG_ReadByte)+1 );
		MSG_CurrentSize = *(PINT*)( (INT)(MSG_ReadByte)+7 );
		MSG_BadRead = *(PINT*)( (INT)(MSG_ReadByte)+20 );

		DWORD SVC_SoundBase = (DWORD)pEngineMsgBase[SVC_SOUND].pfn;

		if ( *(PBYTE)( SVC_SoundBase + 0x0E ) == 0xE8 )
		{
			MSG_Buffer = (sizebuf_t *)( *(PDWORD)( SVC_SoundBase + 0x0A ) );
			MSG_StartBitReading = (HL_MSG_StartBitReading)Absolute( SVC_SoundBase + 0x0F );
			MSG_ReadBits = (HL_MSG_ReadBits)Absolute( SVC_SoundBase + 0x16 );
		}
		else if ( *(PBYTE)( SVC_SoundBase + 0x0C ) == 0xE8 )
		{
			MSG_Buffer = (sizebuf_t *)( *(PDWORD)( SVC_SoundBase + 0x08 ) );
			MSG_StartBitReading = (HL_MSG_StartBitReading)Absolute( SVC_SoundBase + 0x0D );
			MSG_ReadBits = (HL_MSG_ReadBits)Absolute( SVC_SoundBase + 0x14 );
		}
		else
		{
		//	Error( OFF_MSG_STR_READING );
		}

		if ( *(PBYTE)( SVC_SoundBase + 0xD6 ) == 0xE8 )
		{
			MSG_EndBitReading = (HL_MSG_EndBitReading)Absolute( SVC_SoundBase + 0xD7 );
			MSG_ReadBitVec3Coord = (HL_MSG_ReadBitVec3Coord)Absolute( SVC_SoundBase + 0xAF );
		}
		else if ( *(PBYTE)( SVC_SoundBase + 0xE2 ) == 0xE8 )
		{
			MSG_EndBitReading = (HL_MSG_EndBitReading)Absolute( SVC_SoundBase + 0xE3 );
			MSG_ReadBitVec3Coord = (HL_MSG_ReadBitVec3Coord)Absolute( SVC_SoundBase + 0xBE );
		}
		else
		{
		//	Error( OFF_MSG_END_READING );
		}
	}
	else
	{
	//	Error( OFF_ENGINE_MSG_BASE );
	}

	return (DWORD)pEngineMsgBase;
}*/

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

/*
PVOID EngineMsgs()// hpp v6
{
	auto ptr = FindPush((PCHAR)"-------- Message Load ---------\n", Module[HW].base, Module[HW].end); // .text:01D1CFB7                 push    offset aMessageLoad ; "-------- Message Load ---------\n"
	
	ptr = FindDownPattern((PCHAR)V("\xBF"), ptr, Module[HW].end, 0x1); // hw.dll+1CFC8 - BF A4B39703           - mov edi,hw.dll+13B3A4 { [0397AFC0] }

	auto ptr_enginemsgbase = (svc_func_t*)(*(PDWORD)ptr - sizeof(DWORD));

	if (ptr_enginemsgbase)
	{
		MSG_ReadByte = (HL_MSG_ReadByte)Absolute(((uintptr_t)ptr_enginemsgbase[svc_cdtrack].pfnParse) + 1);
		MSG_ReadShort = (HL_MSG_ReadShort)Absolute(((uintptr_t)ptr_enginemsgbase[svc_stopsound].pfnParse) + 1);
		MSG_ReadLong = (HL_MSG_ReadLong)Absolute(((uintptr_t)ptr_enginemsgbase[svc_version].pfnParse) + 1);
		MSG_ReadFloat = (HL_MSG_ReadFloat)Absolute(((uintptr_t)ptr_enginemsgbase[svc_timescale].pfnParse) + 1);
		MSG_ReadString = (HL_MSG_ReadString)Absolute(((uintptr_t)ptr_enginemsgbase[svc_print].pfnParse) + 1);

		auto CallMSG_ReadCoord = Absolute((uintptr_t)(ptr_enginemsgbase[svc_particle].pfnParse) + 1);

		if (*(PBYTE)(CallMSG_ReadCoord + 0x13) == 0xE8)	// STEAM
			MSG_ReadCoord = (HL_MSG_ReadCoord)Absolute((CallMSG_ReadCoord + 0x14));
		else if (*(PBYTE)(CallMSG_ReadCoord + 0x15) == 0xE8)	// OLD PATCH (SOFTWARE)
			MSG_ReadCoord = (HL_MSG_ReadCoord)Absolute((CallMSG_ReadCoord + 0x16));
		else if (*(PBYTE)(CallMSG_ReadCoord + 0x0E) == 0xE8)	// OLD PATCH
			MSG_ReadCoord = (HL_MSG_ReadCoord)Absolute((CallMSG_ReadCoord + 0x0F));
		else if (*(PBYTE)(CallMSG_ReadCoord + 0x0B) == 0xE8)	// OLD OLD PATCH
			MSG_ReadCoord = (HL_MSG_ReadCoord)Absolute((CallMSG_ReadCoord + 0x0C));
		else
		{
			Utils::TraceLog(V("%s: MSG_ReadCoord not found.\n"), V(__FUNCTION__));
			return NULL;
		}

		MSG_ReadCount = *(PINT*)((INT)(MSG_ReadByte)+1);
		MSG_CurrentSize = *(PINT*)((INT)(MSG_ReadByte)+7);
		MSG_BadRead = *(PINT*)((INT)(MSG_ReadByte)+20);

		auto SVC_SoundBase = (uintptr_t)ptr_enginemsgbase[svc_sound].pfnParse;

		if (*(PBYTE)(SVC_SoundBase + 0x0E) == 0xE8)
		{
			MSG_Buffer = (sizebuf_t*)(*(PDWORD)(SVC_SoundBase + 0x0A));
			MSG_StartBitReading = (HL_MSG_StartBitReading)Absolute(SVC_SoundBase + 0x0F);
			MSG_ReadBits = (HL_MSG_ReadBits)Absolute(SVC_SoundBase + 0x16);
		}
		else if (*(PBYTE)(SVC_SoundBase + 0x0C) == 0xE8)
		{
			MSG_Buffer = (sizebuf_t*)(*(PDWORD)(SVC_SoundBase + 0x08));
			MSG_StartBitReading = (HL_MSG_StartBitReading)Absolute(SVC_SoundBase + 0x0D);
			MSG_ReadBits = (HL_MSG_ReadBits)Absolute(SVC_SoundBase + 0x14);
		}
		else
		{
			Utils::TraceLog(V("%s: MSG_StartBitReading not found.\n"), V(__FUNCTION__));
			return NULL;
		}

		if (*(PBYTE)(SVC_SoundBase + 0xD6) == 0xE8)
		{
			MSG_EndBitReading = (HL_MSG_EndBitReading)Absolute(SVC_SoundBase + 0xD7);
			MSG_ReadBitVec3Coord = (HL_MSG_ReadBitVec3Coord)Absolute(SVC_SoundBase + 0xAF);
		}
		else if (*(PBYTE)(SVC_SoundBase + 0xE2) == 0xE8)
		{
			MSG_EndBitReading = (HL_MSG_EndBitReading)Absolute(SVC_SoundBase + 0xE3);
			MSG_ReadBitVec3Coord = (HL_MSG_ReadBitVec3Coord)Absolute(SVC_SoundBase + 0xBE);
		}
		else
		{
			Utils::TraceLog(V("%s: MSG_EndBitReading not found.\n"), V(__FUNCTION__));
			return NULL;
		}
	}
	else
	{
		Utils::TraceLog(V("%s: not found.\n"), V(__FUNCTION__));
		return NULL;
	}

	return (PVOID)ptr_enginemsgbase;
}*/

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

void* Sound()// no anda con el nuevo STEAM
{
	DWORD Addres = MessagePtr("S_StartDynamicSound: %s volume > 255\0", 37);

	for (unsigned int i = 1; i < 200; i++)
	{
		Addres--;
		if (CheckByte(Addres, 0x90, 0))
		{
			Addres++;
			if (CheckByte(Addres, 0x55, 0) || CheckByte(Addres, 0x83, 0))
			{
				return (void*)Addres;
			}
			else
			{
				return 0;
			}
		}
	}
	return 0;
}

//-------------------------------------------------------------------//

void* Sound1(void)
{
	bool bMustLeave = false;

	DWORD Addres = MessagePtr("S_StartDynamicSound: %s volume > 255\0",37);
//	DWORD Addres = MessagePtr((char*)"S_StartDynamicSound: %s volume > 255",37);
	
	for(unsigned int i = 1;i < 200;i++)
	{

		if(bMustLeave)
		{
			break;
		}

		Addres--;
		if( CheckByte(Addres,0x90,0) )
		{
			Addres++;
			if ( CheckByte(Addres,0x55,0) || CheckByte(Addres,0x83,0) )
			{
				return (void*)Addres;
			}
			else
			{
			//	Error((char*)"Couldn't find PreS_DynamicSound #1 pointer.\0");
				bMustLeave = true;
			}
		}
	}

	if(!bMustLeave)
	{
	//	Error((char*)"Couldn't find PreS_DynamicSound #2 pointer.\0");
		bMustLeave = true;
	}

	return 0;
}

//-------------------------------------------------------------------//

/*
inline static bool datacompare(const BYTE* data1, const BYTE* data2, const char* mask){

	for(;*mask;++mask,++data1,++data2){
		if(*mask=='x' && *data1!=*data2 ) return false;
	}

	return (*mask)==0;
}

enum{ PATCH_MAX=64 };
BYTE*  patchloc;
DWORD  patchsize;
BYTE   backup   [PATCH_MAX];
BYTE   patchdata  [PATCH_MAX];
bool find_location(BYTE* hint,const BYTE* sig_bytes,const char* sig_mask){

	assert(sig_mask&&strlen(sig_mask)&&sig_bytes&&hint);
	assert(!patchloc&&!patchsize);
	DWORD len = strlen(sig_mask);
	assert(len<PATCH_MAX);
	if( !datacompare(hint,sig_bytes,sig_mask) ) { return false; }
	patchloc  = hint;
	patchsize = len;
	assert(patchsize<PATCH_MAX);
	memcpy(backup ,patchloc,patchsize);
	memcpy(patchdata,patchloc,patchsize);
	return true;
}

DWORD PatchSound()
{
	BYTE* offs = (BYTE*)dwPDS;
	BYTE* sig   = (BYTE*)"\x83\xEC\x48\xA1\x00\x00\x00\x00";
	char* mask  = "xxxx????\0";
	if(!find_location(offs,sig,mask)){
	}
}*/

//-------------------------------------------------------------------//

#define REFERENCE_ABSOLUTE_PUSH 1
#define REFERENCE_RELATICE_CALL 2

#define CompareMemoryXYZ(Buff1, Buff2, Size) __comparememGG((const unsigned char*) Buff1, (const unsigned char*) Buff2, (unsigned int) Size)
#define CompareMemoryValueXYZ(Buff, Value) __comparememGG((const unsigned char*) Buff, (const unsigned char*) &Value, (unsigned int) sizeof(Value))
#define FindMemoryCloneXYZ(start, end, clone, clonesize) __findmemorycloneGG((const unsigned long) start, (const unsigned long) end, (const unsigned long) clone, (unsigned int) clonesize)
#define FindReferenceXYZ(start, end, address, type) __findreferenceGG((const unsigned long) start, (const unsigned long) end, (const unsigned long) address, (const unsigned char) type)
//#define FindReferenceXYZ(start, end, address, type) __findreferenceGG((const unsigned long) start, (const unsigned long) end, (const unsigned long) address, (const unsigned char) type)

bool __comparememGG(const unsigned char* Buff1, const unsigned char* Buff2, unsigned int Size)
{
	for( unsigned int i=0; i < Size; i++, Buff2++, Buff1++ )
	{
		if((*Buff1 != *Buff2) && (*Buff2 != 0xFF))
			return false;
	}
	return true;
}
void* __findmemorycloneGG(const unsigned long start, const unsigned long end, const unsigned long clone, unsigned int clonesize)
{
	for( unsigned long ul = (unsigned long)start; (ul + clonesize) < end; ul++)
	{
		if(CompareMemoryXYZ(ul, clone, clonesize))
			return (void*)ul;
	}
	return NULL;
}
void* __findreferenceGG(const unsigned long start, const unsigned long end, const unsigned long address, const unsigned char type)
{
	unsigned char Pattern[5];

	if ( type == REFERENCE_ABSOLUTE_PUSH )
	{
		Pattern[0] = 0x68;
		*(unsigned long*)&Pattern[1] = address;
	}

	return FindMemoryCloneXYZ(start, end, Pattern, sizeof(Pattern)-1);
}


char* SoundsString = "S_StartDynamicSound: %s volume > 255\0";
void* OffsetPreSDynSound(void)
{
#define OFFs 0x9C // 0xAC

	unsigned long hlBase = (unsigned long)GetModuleHandle("hw.dll\0");
//	unsigned long hlSize = (unsigned long )0x146FFE;
	unsigned long hlSize = (unsigned long )0x2116000;
//	logme1("hlBase 0x%X\0",hlBase);

	SoundsString = (char*)FindMemoryClone(hlBase, hlBase+hlSize, SoundsString, strlen(SoundsString));
	if(SoundsString == NULL)
		return NULL;

	return (void*)((DWORD)FindReferenceXYZ(hlBase, hlBase+hlSize, SoundsString, REFERENCE_ABSOLUTE_PUSH)-OFFs);
}

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

void* studiodrawplayer()
{
	bool bMustLeave = false;

	PCHAR String = "Couldn't get client .dll studio model rendering interface.\0";
//	PCHAR String = (char*)"Couldn't get client .dll studio model rendering interface.";

	DWORD Address = (DWORD)FindMemoryClone(HW_MODULE_BASE, HW_MODULE_BASE+HW_MODULE_SIZE, String, strlen(String));
	PVOID SDPPtr = (PVOID)*(PDWORD)(FindReference(HW_MODULE_BASE, HW_MODULE_BASE+HW_MODULE_SIZE, Address) -0x0F);//-0x10 -0x0F
	
	if ( FarProc((DWORD)SDPPtr,HW_MODULE_BASE,HW_MODULE_END) )
	{
//		Error((char*)"Couldn't find studiodrawplayer pointer.\0");
		bMustLeave = true;
	}

	if(!bMustLeave)
	{
		return SDPPtr;
	}

	return 0;
}

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

DWORD FindPattern( PCHAR pattern , PCHAR mask , DWORD start , DWORD end , DWORD offset )
{
	int patternLength = native_strlen( pattern );
	bool found = false;

	for ( DWORD i = start; i < end - patternLength; i++ )
	{
		found = true;
		for ( int idx = 0; idx < patternLength; idx++ )
		{
			if ( mask[idx] == 'x' && pattern[idx] != *(PCHAR)( i + idx ) )
			{
				found = false;
				break;
			}
		}
		if ( found )
		{
			return i + offset;
		}
	}

	return 0;
}

//-------------------------------------------------------------------//

DWORD FindPattern( PCHAR pattern , DWORD start , DWORD end , DWORD offset )
{
	int patternLength = native_strlen( pattern );
	bool found = false;

	for ( DWORD i = start; i < end - patternLength; i++ )
	{
		found = true;
		for ( int idx = 0; idx < patternLength; idx++ )
		{
			if ( pattern[idx] != *(PCHAR)( i + idx ) )
			{
				found = false;
				break;
			}
		}
		if ( found )
		{
			return i + offset;
		}
	}

	return 0;
}

//-------------------------------------------------------------------//

DWORD FindReferenceX( DWORD start , DWORD end , DWORD Address )
{
	char szPattern[] = { 0x68 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 };
	*(PDWORD)&szPattern[1] = Address;
	return FindPattern( szPattern , start , end , 0 );
}

//-------------------------------------------------------------------//
















