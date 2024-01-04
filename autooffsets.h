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

#pragma once

//-------------------------------------------------------------------//

extern cl_clientfunc_t *g_pClient;
extern cl_clientfunc_t g_Client;
//extern ClientDll_t gClientDll;

extern cl_enginefuncs_s * pEngfuncs;
extern struct cl_enginefuncs_s gEngfuncs;

extern engine_studio_api_s * pstudio;
extern struct engine_studio_api_s IEngineStudio;

extern struct r_studio_interface_s** ppinterface;

extern struct playermove_s* g_ppmove;

extern DWORD dwPDS;

extern double* globalTime;

//-------------------------------------------------------------------//

bool GetModuleInfo();

DWORD FindClientTable();
void* ClientFuncs(void);

DWORD FindEngineTable();
void* EngineFuncs(void);

DWORD FindStudioTable();// no anda con el nuevo STEAM
DWORD EngineStudio(void);

//-------------------------------------------------------------------//

DWORD FindSVCMessages();// no anda con el nuevo STEAM
DWORD FindSVCMessages2();// no anda con el nuevo STEAM


void* Sound();
void* Sound1(void);
void* OffsetPreSDynSound(void);


void* studiodrawplayer();

//-------------------------------------------------------------------//
