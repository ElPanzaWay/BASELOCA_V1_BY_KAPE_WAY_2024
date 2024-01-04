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

struct Player_s Players[33];

//-------------------------------------------------------------------//

/*
bool isValidEnt(cl_entity_s *ent)
{
	if(ent && (ent != pEngfuncs->GetLocalPlayer())
		&& !(ent->curstate.effects & EF_NODRAW)
		&& ent->player
		&& !ent->curstate.spectator
		&& ent->curstate.solid
		&& !(ent->curstate.messagenum < pEngfuncs->GetLocalPlayer()->curstate.messagenum))
	{
		return true;
	}
	else
		return false;
}*/

void InitPlayers()
{
	for(unsigned int i=0; i<33; i++)
	{
		Players[i].index = 0;
		Players[i].alive = 0;

		Players[i].updatedbyentity = 0;
		Players[i].updateframes = 0;

		Players[i].team = 0;



		Players[i].distance = 999999;
		Players[i].visible= 0;

		Players[i].ducked= 0;
		Players[i].frozen= 0;
	}
}

void UpdatePlayers()
{
	for(unsigned int i=0; i<33; i++)
	{
	//	Players[i].updatedbyentity = 0;
		if(i == PlayerLocale.index) continue;


		cl_entity_s* theEnt = gEngfuncs.GetEntityByIndex(i);
		if(theEnt)
		{
			//////////////////////////////////////////////////////////////////////
			if(theEnt->player)// BLOCKEADA POR PLUGINS !!
			//////////////////////////////////////////////////////////////////////
			if(theEnt->index > 0 && theEnt->index < 33)
			{

				Players[i].index = theEnt->index;

				/////////////////////////////////////////////////////////////////////////////
				Players[i].alive = theEnt->curstate.solid;// BLOCKEADA POR PLUGINS !!
				/////////////////////////////////////////////////////////////////////////////

			//	if(Players[i].alive) Players[i].updatedbyentity = 1;

				Players[i].team = 0;
				hud_player_info_t pinfo;
				pEngfuncs->pfnGetPlayerInfo(i, &pinfo);
				if(pinfo.model)
				{
					if( strstr( pinfo.model, "arctic\0" ) || 
						strstr( pinfo.model, "guerilla\0" ) || 
						strstr( pinfo.model, "leet\0" ) || 
						strstr( pinfo.model, "terror\0" ) || 
						strstr( pinfo.model, "spetsnaz\0" )) 	
					{
						Players[i].team = 1;
					}
					else if( strstr( pinfo.model, "gign\0" ) || 
							 strstr( pinfo.model, "gsg9\0" ) || 
							 strstr( pinfo.model, "sas\0" ) || 
							 strstr( pinfo.model, "urban\0" ) || 
							 strstr( pinfo.model, "vip\0" )) 
					{
						Players[i].team = 2;
					}
				}


				Players[i].entorg[0] = theEnt->origin[0];
				Players[i].entorg[1] = theEnt->origin[1];
				Players[i].entorg[2] = theEnt->origin[2];

				CalculateVisibilityAimVector(theEnt->index, CVARS.aimvis);

				Players[i].entangles[0] = theEnt->angles[0];
				Players[i].entangles[1] = theEnt->angles[1];
				Players[i].entangles[2] = theEnt->angles[2];


				Players[i].ducked = (theEnt->curstate.usehull != 0 );

				Players[i].frozen = 0;

			}
		}
		else
		{
		}
	}
}

void ClearUpdatePlayers()// BAZADO EN FRAMES (se puede bazar en tiempo)
{
	for(unsigned int i=0; i<33; i++)
	{
		if(Players[i].updatedbyentity)
		{
			if(Players[i].updateframes>= CVARS.updateframes)
			{
				Players[i].updatedbyentity = 0;
				Players[i].updateframes = 0;
			}

			Players[i].updateframes++;
		}
	}
}

void DrawPlayerESP()
{
	int r=255;
	int g=255;
	int b=255;
	int a=255;
	for(unsigned int i=0; i<33; i++)
	{
		if(Players[i].updatedbyentity)
		{

			if(CVARS.aimdraw)
			{
				CalculateAimVectorDraw(i);
			}

			float vecScreen[2];
			if( bCalcScreen(Players[i].entorg,vecScreen) )
			{
				int x = vecScreen[0];
				int y = vecScreen[1];
				enum{ CHAR_HEIGHT = 12 };
				int ystep = -CHAR_HEIGHT;

				if(i == iAimTarget)
				{
					r=255;
					g=255;
					b=0;
				}
				else if(Players[i].team==1)
				{
					r=255;
					g=0;
					b=0;
				}
				else if(Players[i].team==2)
				{
					r=0;
					g=0;
					b=255;
				}
				else
				{
					r=255;
					g=255;
					b=255;
				}


				if(CVARS.playername)
				{
					hud_player_info_t pinfo;
					pEngfuncs->pfnGetPlayerInfo(i, &pinfo);
					if(pinfo.name)
					{

					DrawConStringCenter(x,y,r,g,b,/*format_string*//*%s\0*/XorStr<0xA1,4,0x15069BBD>("\x84\xD1\xA3"+0x15069BBD).s
						,pinfo.name);
					y += ystep;

					}
				}
			
			}
		
		}

	}
}

//-------------------------------------------------------------------//

bool GetAimingTeam(unsigned int ax){

	if (CVARS.aimingteam<=0 && (PlayerLocale.team != Players[ax].team)) return true;
	if (CVARS.aimingteam==1)											return true;
	if (CVARS.aimingteam>1 &&  (PlayerLocale.team == Players[ax].team)) return true;
	return false;
}

//-------------------------------------------------------------------//

struct PlayerLocale_s PlayerLocale;

//-------------------------------------------------------------------//

void InitPlayerLocale()
{
	PlayerLocale.index = 0;
	PlayerLocale.alive = 0;
	PlayerLocale.team = 0;
	PlayerLocale.ducked = 0;
	PlayerLocale.frozen = 0;
	PlayerLocale.inzoom = 0;
}

void UpdatePlayerLocale()
{
	cl_entity_s* pMe = gEngfuncs.GetLocalPlayer();

	PlayerLocale.index = 0;
	PlayerLocale.alive = 0;
	PlayerLocale.team = 0;

	if(pMe)
	{
		///////////////////////////////////////////////////////////
		if(pMe->player)// BLOCKEADA POR PLUGINS !!
		///////////////////////////////////////////////////////////
		if(pMe->index > 0 && pMe->index < 33)
		{
			PlayerLocale.index = pMe->index;

			///////////////////////////////////////////////////////////////////////////
			PlayerLocale.alive = pMe->curstate.solid;// BLOCKEADA POR PLUGINS !!
			///////////////////////////////////////////////////////////////////////////

			hud_player_info_t pinfo;
			pEngfuncs->pfnGetPlayerInfo(pMe->index, &pinfo);

			if(pinfo.model)
			{
				if( strstr( pinfo.model, "arctic\0" ) || 
					strstr( pinfo.model, "guerilla\0" ) || 
					strstr( pinfo.model, "leet\0" ) || 
					strstr( pinfo.model, "terror\0" ) || 
					strstr( pinfo.model, "spetsnaz\0" )) 	
				{
					PlayerLocale.team = 1;
				}
				else if( strstr( pinfo.model, "gign\0" ) || 
					     strstr( pinfo.model, "gsg9\0" ) || 
					     strstr( pinfo.model, "sas\0" ) || 
					     strstr( pinfo.model, "urban\0" ) || 
					     strstr( pinfo.model, "vip\0" )) 
				{
					PlayerLocale.team = 2;
				}
			}
			
		}
	}
}


void DrawInfo()
{
	if(CVARS.info == 1)
	{

	DrawHudString(60, 70, 0, 0, 0, "me.alive %d\0", PlayerLocale.alive);
	DrawHudString(60, 90, 0, 0, 0, "me.index %d\0", PlayerLocale.index);


	DrawHudString(60, 110, 0, 0, 0, "me.weaponid %d\0", PlayerLocale.weaponid);
	DrawHudString(60, 130, 0, 0, 0, "me.clip %d\0", PlayerLocale.clip);
	DrawHudString(60, 150, 0, 0, 0, "me.inzoom %d\0", PlayerLocale.inzoom);

	DrawHudString(60, 190, 0, 0, 0, "Aimbot_Active %d\0", Aimbot_Active);
	DrawHudString(60, 210, 0, 0, 0, "iAimTarget %d\0", iAimTarget);

	}

	if(CVARS.info == 2)
	{

	DrawHudString(60, 70, 0, 0, 0, "spread.firing %d\0", PlayerLocale.spread.firing);
	DrawHudString(60, 90, 0, 0, 0, "spread.WeaponState %d\0", PlayerLocale.spread.WeaponState);
	DrawHudString(60, 110, 0, 0, 0, "spread.prcflags %d\0", PlayerLocale.spread.prcflags);
	DrawHudString(60, 130, 0, 0, 0, "spread.iInReload %d\0", PlayerLocale.spread.iInReload);
	DrawHudString(60, 150, 0, 0, 0, "spread.random_seed %d\0", PlayerLocale.spread.random_seed);
	DrawHudString(60, 170, 0, 0, 0, "spread.gtime %f\0", PlayerLocale.spread.gtime);
	DrawHudString(60, 190, 0, 0, 0, "spread.recoil %d\0", PlayerLocale.spread.recoil);
	DrawHudString(60, 210, 0, 0, 0, "spread.recoiltime %f\0", PlayerLocale.spread.recoiltime);
	DrawHudString(60, 230, 0, 0, 0, "spread.spreadvar %f\0", PlayerLocale.spread.spreadvar);
	DrawHudString(60, 250, 0, 0, 0, "spread.vecspread %f\0", PlayerLocale.spread.vecspread);


	/*PlayerLocale.spread.prevtime = 0;
	PlayerLocale.spread.brokentime = 0;
	PlayerLocale.spread.flNextPrimaryAttack = 0;
	PlayerLocale.spread.flNextSecondaryAttack = 0;
	PlayerLocale.spread.flNextAttack = 0;*/

	}
}

void InitSpreadData()
{
	PlayerLocale.spread.firing = 0;

	PlayerLocale.spread.WeaponState = 0;
	PlayerLocale.spread.prcflags = 0;
	PlayerLocale.spread.random_seed = 0;
	PlayerLocale.spread.gtime = 0;
	PlayerLocale.spread.spreadvar = 0;
	PlayerLocale.spread.recoil = 0;
	PlayerLocale.spread.recoiltime = 0;

	PlayerLocale.spread.prevtime = 0;
	PlayerLocale.spread.brokentime = 0;

	PlayerLocale.spread.iInReload = 0;
	PlayerLocale.spread.flNextPrimaryAttack = 0;
	PlayerLocale.spread.flNextSecondaryAttack = 0;
	PlayerLocale.spread.flNextAttack = 0;

	PlayerLocale.spread.vecspread = 0;
}

//-------------------------------------------------------------------//

int GetPlayerLocaleWeaponState()
{
	return PlayerLocale.spread.WeaponState;
}

int GetPlayerLocaleWeaponFlags()
{
	return PlayerLocale.spread.prcflags;
}

float GetPlayerLocaleSpreadVar()
{
	return PlayerLocale.spread.spreadvar;
}

float GetPlayerLocaleVecSpread()
{
	return PlayerLocale.spread.vecspread;
}

float GetPlayerLocaleRandomSeed()
{
	return PlayerLocale.spread.random_seed;
}

float GetPlayerLocaleGlobalTime()
{
	return PlayerLocale.spread.gtime;
}

int GetPlayerLocaleWeaponInReload()
{
	return PlayerLocale.spread.iInReload;
}

//-------------------------------------------------------------------//

float * GetMyViewPoint()
{
	 return PlayerLocale.eyeposition;
}

float * GetMyViewAngles()
{
	 return PlayerLocale.viewangles;
}

//-------------------------------------------------------------------//

/*
PVOID PlayerExtraInfo()// hpp v6
{
	auto start = (uintptr_t)(g_pClient->HUD_GetPlayerTeam);

	if (!start) // On 4554 == 0x0
		start = (uintptr_t)(g_pClient->HUD_ChatInputPosition);

	auto ptr = FindDownPattern((PCHAR)V("\x0F\xBF\x04\xFF\xFF\xFF\xFF\xFF\xC3"), (PCHAR)V("xxx?????x"), start, (uintptr_t)(g_pClient->ClientFactory));

	if (AddressNotInSpace(ptr, Module[CLIENT].base, Module[CLIENT].end))
	{
		Utils::TraceLog(V("%s: not found.\n"), V(__FUNCTION__));
		return NULL;
	}

	ptr = *(PDWORD)(ptr + 4);

	ptr = (ptr - offsetof(extra_player_info_t, team_id));

	return (PVOID)ptr;
}*/