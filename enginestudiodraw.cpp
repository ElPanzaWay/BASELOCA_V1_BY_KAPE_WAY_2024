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

//static 
int (*OrigStudioDrawPlayer)(int flags,struct entity_state_s* pplayer) = 0;


//static 
int (*OrigStudioDrawModel)(int flags) = 0;

//-------------------------------------------------------------------//

int NewStudioDrawPlayer(int flags, struct entity_state_s* pplayer)
{
	//
	int ret = 0;
	ret = (*OrigStudioDrawPlayer)(flags, pplayer);


	if(pstudio && pEngfuncs)
	{
		if ( flags & STUDIO_RENDER ) // Are we rendering?
		{
			if ( ret )
			{
				
			// COPIAR DATOS DE PPPLAYER A ENTX LUEGO DE LA LLAMADA
			//	if(pplayer->modelindex)
			//	if(pplayer->entityType == ET_PLAYER)
			//	if(pplayer->owner)
			//	if(pplayer->weaponmodel)
				if(pplayer->number >=1 && pplayer->number<=32)
				{
				//	if(Players[pplayer->number].alive) 
						Players[pplayer->number].updatedbyentity = 1;

					//
					// a place to calculate hitboxes
					//

				}
			}
		}
	}

	return ret;
}

//-------------------------------------------------------------------//

int NewStudioDrawModel( int flags )
{
	int ret = OrigStudioDrawModel(flags);
	return ret;
}

//-------------------------------------------------------------------//

int Hooked_HUD_GetStudioModelInterface(int version, 
									   struct r_studio_interface_s** ppinterfaceX, 
									   struct engine_studio_api_s* pstudioX)// se llama al principío
{
	int iRet = g_Client.HUD_GetStudioModelInterface(version,ppinterfaceX,pstudioX);

//	logme1("Hooked_HUD_GetStudioModelInterface OK\0");

	if(ppinterfaceX && *ppinterfaceX)
	{
		ppinterface = (struct r_studio_interface_s**)ppinterfaceX;
	//	logme1("ppinterface 0x%X\0", ppinterface);
		
		OrigStudioDrawPlayer = (*ppinterfaceX)->StudioDrawPlayer;
		(*ppinterfaceX)->StudioDrawPlayer = NewStudioDrawPlayer;
		
		OrigStudioDrawModel = (*ppinterfaceX)->StudioDrawModel;
		(*ppinterfaceX)->StudioDrawModel = NewStudioDrawModel;

		
	}
	
	return iRet;
}

//-------------------------------------------------------------------//

void HookStudioDrawFuncsWithMyppinterface()// en REDRAW, si ya se obtuvo el ptr
{
	/*
	if(ppinterface && *ppinterface)
	{
		OrigStudioDrawPlayer = (*ppinterface)->StudioDrawPlayer;
		(*ppinterface)->StudioDrawPlayer = NewStudioDrawPlayer;
		
		OrigStudioDrawModel = (*ppinterface)->StudioDrawModel;
		(*ppinterface)->StudioDrawModel = NewStudioDrawModel;
	}*/
}

//-------------------------------------------------------------------//

/*
PVOID StudioAPI()// hpp v6
{
	auto ptr = FindDownPattern((PCHAR)V("\xC7\xFF\xFF\xFF\xFF\xFF\xF3\xA5\xB9\xFF\xFF\xFF\xFF\xE8\xFF\xFF\xFF\xFF\x5F\xB8\xFF\xFF\xFF\xFF\x5E\xC3"), (PCHAR)V("x?????xxx????x????xx????xx"), Module[CLIENT].base, Module[CLIENT].end, 0x2);

	if (AddressNotInSpace(ptr, Module[CLIENT].base, Module[CLIENT].end))
	{
		Utils::TraceLog(V("%s: not found.\n"), V(__FUNCTION__));
		return NULL;
	}

	return (PVOID)*(r_studio_interface_t**)ptr;
}*/

//-------------------------------------------------------------------//
