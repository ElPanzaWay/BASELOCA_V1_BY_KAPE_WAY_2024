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

/*
typedef struct cmd_s
{
	struct cmd_s	*pNext;
	PCHAR			pszName;
	DWORD			pfnFunc;
	BYTE			bCrap[20];
}	cmd_t, *pcmd_t;

//-------------------------------------------------------------------//

DWORD CopyCmd(char*oldName, char*newName, void(*oldFunc)())
{
	pcmd_t pCmd = g_pEngine->pfnGetCmdList();
	while (pCmd != NULL)
	{
		if (!strcmpi(pCmd->pszName, oldName))
		{
			pCmd->pszName = newName;
			g_pEngine->pfnAddCommand(oldName, oldFunc);
			return pCmd->pfnFunc;
		}
		pCmd = pCmd->pNext;
	}
	return 0;
}*/

//-------------------------------------------------------------------//

/*
pcmd_t CommandByName( char* szName )
{
	pcmd_t pCmd = nullptr;
	pCmd = g_Engine.pfnGetCmdList();

	while ( pCmd )
	{
		if ( !native_strcmp( pCmd->name , szName ) )
			return pCmd;

		pCmd = pCmd->next;
	}

	return 0;
}*/

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

/*
bool CheckCvarC(char* cVarName)
{
	cvar_s* cTemp = 0;
	cTemp = gEngfuncs.pfnGetCvarPointer(cVarName);
	if ((DWORD*)cTemp != 0)
		return true;
	else
		return false;
}

//-------------------------------------------------------------------//

bool CheckCvar(char* cVarName)
{
	if(!gEngfuncs.pfnGetCvarPointer) { return false; }
	cvar_s* test = gEngfuncs.pfnGetCvarPointer(cVarName);
	return (test!=NULL);	
}

//-------------------------------------------------------------------//
// CopyCvar ("fps_max\0","fps\0","999\0",0);

void CopyCvar(char* origCvarName, char* newCvarName, char* defaultValue, int origFlags)
{
    cvar_t* pCvar = gEngfuncs.pfnGetCvarPointer(origCvarName);
    if (!pCvar)
    {
        return;
    }
    cvar_t* pNewVar = pCvar;
    memcpy(pNewVar, pCvar, sizeof(cvar_t));
    char tmp[64]="\0";
    sprintf(tmp, "%s\0", newCvarName);    
    strcpy((char*)pCvar->name, tmp);                        
    gEngfuncs.pfnRegisterVariable(origCvarName, defaultValue, origFlags);
	//gEngfuncs.Cvar_Set(newCvarName, defaultValue);
	gEngfuncs.pfnCvar_Set(newCvarName, defaultValue);
}

//-------------------------------------------------------------------//

float* GetCopyCvar(char* origCvarName, char* newCvarName, char* defaultValue, int origFlags)
{
	cvar_t* pCvar = gEngfuncs.pfnGetCvarPointer( origCvarName );
	if(!pCvar)
		return NULL;
	cvar_t* pNewVar = pCvar;
	memcpy(pNewVar, pCvar, sizeof(cvar_t));
	char tmp[64]="\0";
	sprintf(tmp, "%s\0", newCvarName);    
	strcpy((char*)pCvar->name, tmp);                        
	gEngfuncs.pfnRegisterVariable(origCvarName, defaultValue, origFlags);
	gEngfuncs.pfnCvar_Set( newCvarName, defaultValue );
	return &pCvar->value;
}*/

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

/*
//#define cc(oldcvar, newcvar, value) CopyCvar(oldcvar,newcvar,value,0)

	fps_max = GetCopyCvar("fps_max\0", "totalfps\0", "999\0",0);
//	fps_max = GetCopyCvar("fps_max\0", "fps_max\0", "999\0",0);
	CopyCvar("fps_override\0", "fps\0", "0\0",0);

	//

//	gEngfuncs.pfnGetCvarPointer("fps\0")->value = 1;//99.5
	gEngfuncs.pfnClientCmd("fps_override 1\0");//99.5

	// hay que setearle un valor, porque es 0 cuando se declara (el juego setea a 20 el mínimo admisible)
	*fps_max = 999;

	gEngfuncs.pfnClientCmd("totalfps 999\0");

//	"fps_max" is "999"
//	] fps_override 1
*/


/*
// TKZ hack , Anti Valve src
//

#define cc(oldcvar, newcvar, value) func.CopyCvar(oldcvar,newcvar,value,0)

#define rc(cvar, name, value) {\
	cvar = gEngfuncs.pfnRegisterVariable(name,value,0);\
}

#define acmd(name, func) {gEngfuncs.pfnAddCommand(name, func);}

#define rcmd(name, one, two) {\
	gEngfuncs.pfnAddCommand("+name", one); \
	gEngfuncs.pfnAddCommand("-name", two); }

float *fps_max;
cvar_s *fps_helper;
cvar_s *fps_skip;
cc("r_drawviewmodel", "draw_weapon", "1");
cc("cl_timeout", "timeout", "39058741827469312");
fps_max = cc("fps_max", "fps_max", "1001");
rc(fps_skip, "fps_skipframes", "10");
rc(fps_helper, "fps_helper", "1001");
if(BuildInfo.Build <= 4554)
	cc("developer", "fps", "0");
else
	cc("fps_override", "fps", "0");
*/
