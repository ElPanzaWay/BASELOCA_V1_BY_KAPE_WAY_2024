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

DWORD* HUD_Frame_SA = 0;
DWORD* HUD_Init_SA = 0;
DWORD* HUD_Redraw_SA = 0;
DWORD* HUD_PlayerMove_SA = 0;
DWORD* HUD_PlayerMoveInit_SA = 0;
DWORD* CL_CreateMove_SA = 0;
DWORD* V_CalcRefdef_SA = 0;
DWORD* HUD_AddEntity_SA = 0;
DWORD* HUD_PostRunCmd_SA = 0;
DWORD* HUD_Key_Event_SA = 0;
DWORD* HUD_TempEntUpdate_SA = 0;
DWORD* HUD_GetStudioModelInterface_SA = 0;

//-------------------------------------------------------------------//

SCREENINFO g_Screen;
bool Aimbot_Active = false;
usercmd_t g_Originalcmd;

//-------------------------------------------------------------------//

bool bCalcScreen( float *pflOrigin, float *pflVecScreen )// 101
{
	int iResult = gEngfuncs.pTriAPI->WorldToScreen( pflOrigin, pflVecScreen );
	if( pflVecScreen[0] < 1 && pflVecScreen[1] < 1 && pflVecScreen[0] > -1 && pflVecScreen[1] > -1 && !iResult )
	{
		pflVecScreen[0] = pflVecScreen[0] * ( g_Screen.iWidth / 2 ) + ( g_Screen.iWidth / 2 );
		pflVecScreen[1] = -pflVecScreen[1] * ( g_Screen.iHeight / 2 ) + ( g_Screen.iHeight / 2 );
		return true;
	}
	return false;
}

//-------------------------------------------------------------------//

bool FirstFrame = false;
net_status_t g_nStatus;

void Hooked_HUD_Frame( double time )
{
	g_Client.HUD_Frame( time );

/*	if ( !FirstFrame )
	{
		g_Screen.iSize = sizeof( SCREENINFO );
		FirstFrame = true;
	}
	
	g_Engine.pfnGetScreenInfo( &g_Screen );
	g_Engine.pNetAPI->Status( &( g_nStatus ) );
	*/
}

//if ( g_nStatus.connected ) {}


void Hooked_HUD_Init (void)
{
	g_Client.HUD_Init();
}

void Hooked_HUD_Redraw( float time, int intermission )
{
	g_Client.HUD_Redraw(time,intermission);


	static bool bStartUp1=true;
	if(bStartUp1){

		bStartUp1=false;

		g_Screen.iSize = sizeof( SCREENINFO );

		HookStudioDrawFuncsWithMyppinterface();


		gEngfuncs.pfnClientCmd("bind mouse1 +attack\0");
		gEngfuncs.pfnClientCmd("bind mouse2 +attack2\0");
		gEngfuncs.pfnClientCmd("bind mwheelup +jump\0");
		gEngfuncs.pfnClientCmd("bind mwheeldown +duck\0");
		gEngfuncs.pfnClientCmd("bind g drop\0");
		gEngfuncs.pfnClientCmd("bind ctrl +duck\0");
		gEngfuncs.pfnClientCmd("bind space +jump\0");
		gEngfuncs.pfnClientCmd("bind ENTER +attack\0");

		gEngfuncs.pfnClientCmd("crosshair 1\0");
		gEngfuncs.pfnClientCmd("cl_crosshair_translucent 1\0");
	//	gEngfuncs.pfnClientCmd("cl_crosshair_color \"0 255 0\"\0");
		char a51515[] = {'#','c','l','_','c','r','o','s','s','h','a','i','r','_','c','o','l','o','r',' ','\"','0',' ','2','5','5',' ','0','\"',0};
		gEngfuncs.pfnClientCmd(a51515);

		gEngfuncs.pfnClientCmd("hud_centerid 0\0");

		gEngfuncs.pfnClientCmd("hideradar\0");

		gEngfuncs.pfnClientCmd("hud_fastswitch 1\0");
		gEngfuncs.pfnClientCmd("_cl_autowepswitch 1\0");


		gEngfuncs.pfnClientCmd("cl_lw 1\0");// CL_LW 0 = desactiva cosas


	}


	gEngfuncs.pfnGetScreenInfo( &g_Screen );

	if(CVARS.hackon && CVARS.drawon && CVARS.myhud)
	{
	DrawHudString(g_Screen.iWidth-220, g_Screen.iHeight-80, 255, 155, 0, "FUCKING IDIOTS SINCE 2006\0");
	DrawHudString(g_Screen.iWidth-170, g_Screen.iHeight-60, 255, 155, 0, "BY Kape WaY\0");
	}

	gMenu.Init();
	gMenu.Draw2(g_Screen.iWidth, g_Screen.iHeight);

	UpdatePlayers();

	if ( CVARS.hackon && CVARS.aim && PlayerLocale.alive) TargetFinder();
	else iAimTarget = -1;


	if(CVARS.hackon && CVARS.drawon)
	{
		DrawPlayerESP();

		DrawInfo();
	}


	ClearUpdatePlayers();

	if(CVARS.removebobbing)
	{
		CVARS.removebobbing = 0;

		gEngfuncs.pfnClientCmd("cl_bob 0\0");
		gEngfuncs.pfnClientCmd("cl_bobup 0\0");
		gEngfuncs.pfnClientCmd("cl_bobcycle 0\0");
	}

	if(CVARS.allowbobbing)
	{
		CVARS.allowbobbing = 0;

		gEngfuncs.pfnClientCmd("cl_bob 0.01\0");
		gEngfuncs.pfnClientCmd("cl_bobup 0.5\0");
		gEngfuncs.pfnClientCmd("cl_bobcycle 0.8\0");
	}
}

//

void SmoothAimAngles(float *MyViewAngles, float *AimAngles, float *OutAngles, float Smoothing);

//

void PreV_CalcRefdef( struct ref_params_s* pparams )
{

	VectorCopy(pparams->punchangle, PlayerLocale.punchangles);


/*	if(CVARS.hackon && CVARS.aim && CVARS.no_visual_recoil && PlayerLocale.alive)
	{
		VectorClear(pparams->punchangle);
	}*/


	if(CVARS.hackon && CVARS.aim && PlayerLocale.alive)
	{
		if ( pparams->nextView == 0)//Ãé×¼
		{
			bool badwpn = (PlayerLocale.weaponid==WEAPONLIST_C4 ||
					   PlayerLocale.weaponid==WEAPONLIST_HEGRENADE||
					   PlayerLocale.weaponid==WEAPONLIST_SMOKEGRENADE||
					   PlayerLocale.weaponid==WEAPONLIST_FLASHBANG);

			if(!badwpn)
			if(PlayerLocale.clip)
			if(iAimTarget != -1)
			{

				if(pparams->cmd->buttons & IN_ATTACK )
			//	if(GetAsyncKeyState(VK_LBUTTON))
				{

					//
				//	CalculateAimAngles(iAimTarget);
				//	SetAimAngles2(iAimTarget, pparams);

					// en CreateMove..
					CalculateAimAngles(iAimTarget);
					float Angles[3]={0,0,0};
					float fSmooth = CVARS.smoothvalue;
					if(fSmooth< 1) fSmooth = 1;
					SmoothAimAngles(pparams->viewangles, GetAimAngles(), Angles, fSmooth);
				//	gEngfuncs.SetViewAngles(Angles);
					VectorCopy(Angles, pparams->viewangles);
					VectorCopy(Angles, pparams->cl_viewangles);

					//

				/*	if(VectorLength(PlayerLocale.punchangles) == 0)
					{
						pEngfuncs->pfnClientCmd("+attack\0");
					}*/

					Aimbot_Active = true;

				}

			}
		}
	}

	if(CVARS.hackon && CVARS.aim && CVARS.no_visual_recoil && PlayerLocale.alive)
	{
		if(Aimbot_Active && pparams->cmd->buttons & IN_ATTACK)
		VectorClear(pparams->punchangle);
	}
}

void PostV_CalcRefdef( struct ref_params_s* pparams )
{

	if(CVARS.hackon && CVARS.aim && PlayerLocale.alive && CVARS.testdynamics)
	{
	VectorCopy(GetMyViewPoint(),pparams->vieworg);
	VectorCopy(GetMyViewAngles(),pparams->viewangles);
//	VectorCopy(GetMyViewAngles(), pparams->cl_viewangles);
	}
}

void Hooked_V_CalcRefdef( struct ref_params_s* pparams )
{

	PreV_CalcRefdef(pparams);

	g_Client.V_CalcRefdef( pparams );

	PostV_CalcRefdef(pparams);

}

//

void Hooked_CL_CreateMove( float frametime, struct usercmd_s* usercmd, int active )// el PMEYEPOS para calcular el aimvec está 1 frame (o tick) atrás
{
	g_Client.CL_CreateMove( frametime, usercmd, active );

	UpdatePlayerLocale();

	memcpy(&g_Originalcmd, usercmd, sizeof(usercmd_t));

	bool badwpn = (PlayerLocale.weaponid==WEAPONLIST_C4 ||
		           PlayerLocale.weaponid==WEAPONLIST_HEGRENADE||
				   PlayerLocale.weaponid==WEAPONLIST_SMOKEGRENADE||
				   PlayerLocale.weaponid==WEAPONLIST_FLASHBANG);


	if(CVARS.hackon && CVARS.aim && CVARS.no_weapon_recoil && PlayerLocale.alive 
		&& Aimbot_Active && usercmd->buttons & IN_ATTACK)
	{
		if(!badwpn)
		{
		//	AntiPitchRecoil(frametime,PlayerLocale.punchangles,usercmd->viewangles);
			float offs1 = (PlayerLocale.punchangles[0] * CVARS.recoilvalue);
			float offs2 = (PlayerLocale.punchangles[1] * CVARS.recoilvalue);
			usercmd->viewangles[0] -= offs1;
			usercmd->viewangles[1] -= offs2;
		}
	}


	void ApplyNS(float * cmd_view_angles, int ns_type, bool bApplyOnlyIf);
	if(CVARS.hackon && CVARS.aim && CVARS.nospread && PlayerLocale.alive 
	/*	&& Aimbot_Active*/ && usercmd->buttons & IN_ATTACK)
	{
		if(!badwpn)
		{
			ApplyNS(usercmd->viewangles, CVARS.nospread, Aimbot_Active);
		}
	}



	if(CVARS.hackon && CVARS.aim && CVARS.fixmove && (CVARS.no_weapon_recoil || CVARS.nospread) && PlayerLocale.alive)
	{
		// If we modified our angles we need to fix our movement
		float flLen[3];
		flLen[0] = g_Originalcmd.viewangles[0] - usercmd->viewangles[0];
		flLen[1] = g_Originalcmd.viewangles[1] - usercmd->viewangles[1];
		flLen[2] = g_Originalcmd.viewangles[2] - usercmd->viewangles[2];
		if ( flLen[0] || flLen[1] || flLen[2] )
		{
			Vector viewforward, viewright, viewup, aimforward, aimright, aimup;
			gEngfuncs.pfnAngleVectors(Vector(0.0f, g_Originalcmd.viewangles.y, 0.0f), viewforward, viewright, viewup); 
			gEngfuncs.pfnAngleVectors(Vector(0.0f, usercmd->viewangles.y, 0.0f), aimforward, aimright, aimup); 

			usercmd->forwardmove = DotProduct(g_Originalcmd.forwardmove * viewforward.Normalize(), aimforward) + 
				DotProduct(g_Originalcmd.sidemove * viewright.Normalize(), aimforward) + 
				DotProduct(g_Originalcmd.upmove * viewup.Normalize(), aimforward); 
		
			usercmd->sidemove = DotProduct(g_Originalcmd.forwardmove * viewforward.Normalize(), aimright) + 
				DotProduct(g_Originalcmd.sidemove * viewright.Normalize(), aimright) + 
				DotProduct(g_Originalcmd.upmove * viewup.Normalize(), aimright); 
		
			usercmd->upmove = DotProduct(g_Originalcmd.forwardmove * viewforward.Normalize(), aimup) + 
				DotProduct(g_Originalcmd.sidemove * viewright.Normalize(), aimup) + 
				DotProduct(g_Originalcmd.upmove * viewup.Normalize(), aimup); 
		}
	}


	if(CVARS.hackon &&CVARS.choppyfire&& PlayerLocale.alive)
		if(VectorLength(PlayerLocale.punchangles) != 0) 
			usercmd->buttons &= (~IN_ATTACK);

//	gEngfuncs.pfnClientCmd("-attack\0");
	Aimbot_Active = false;
}

void Hooked_HUD_PlayerMove( struct playermove_s* ppmove, int server )
{
	g_Client.HUD_PlayerMove( ppmove, server );


	gEngfuncs.pEventAPI->EV_LocalPlayerViewheight(PlayerLocale.eyeposition);
	PlayerLocale.eyeposition[0]+= ppmove->origin[0];
	PlayerLocale.eyeposition[1]+= ppmove->origin[1];
	PlayerLocale.eyeposition[2]+= ppmove->origin[2];

	//
	// TODO..
	//


	PlayerLocale.viewangles[0] = ppmove->angles[0];
	PlayerLocale.viewangles[1] = ppmove->angles[1];
	PlayerLocale.viewangles[2] = ppmove->angles[2];

}


void Hooked_HUD_PlayerMoveInit( struct playermove_s* ppmove )
{
	g_Client.HUD_PlayerMoveInit( ppmove );
}


void Hooked_HUD_UpdateClientData(client_data_t* cdata, float flTime)
{
	g_Client.HUD_UpdateClientData(cdata, flTime);
}

int Hooked_HUD_AddEntity( int type, struct cl_entity_s* ent, const char* modelname )
{
	int iRet = g_Client.HUD_AddEntity( type, ent, modelname );


	if(ent)
	////////////////////////////////////////////////////////
//	if(ent->player)// BLOCKEADA POR PLUGINS !!
	////////////////////////////////////////////////////////
	if(ent->index >=1 && ent->index<=32)
	{

		// remueve efectos etc
		ent->curstate.rendermode = 0;
		ent->curstate.renderfx = 0;


	//	if(Players[ent->index].alive) 
		Players[ent->index].updatedbyentity = 1;
	}




	return iRet;
}

void Hooked_HUD_PostRunCmd( struct local_state_s* from, struct local_state_s* to, 
							struct usercmd_s* usercmd, int runfuncs, 
							double time, unsigned int random_seed )// CL_LW 0 = desactiva cosas
{
	g_Client.HUD_PostRunCmd( from, to, usercmd, runfuncs, time, random_seed );

	//g_Weapon.ItemPreFrame(to, cmd, runfuncs, time, random_seed);

	if (runfuncs)
	{
		PlayerLocale.weaponid = to->client.m_iId;

		if(to->client.m_iId> 0 && to->client.m_iId <MAX_WEAPONS)
		{
			PlayerLocale.clip = to->weapondata[to->client.m_iId].m_iClip;
			PlayerLocale.spread.random_seed = random_seed;
			PlayerLocale.spread.gtime = time;
			PlayerLocale.spread.prcflags = to->client.flags;
			PlayerLocale.spread.WeaponState = to->weapondata[to->client.m_iId].m_iWeaponState;
			PlayerLocale.spread.flNextPrimaryAttack = to->weapondata[to->client.m_iId].m_flNextPrimaryAttack;
			PlayerLocale.spread.flNextSecondaryAttack = to->weapondata[to->client.m_iId].m_flNextSecondaryAttack;
			PlayerLocale.spread.flNextAttack = to->client.m_flNextAttack;
			PlayerLocale.spread.iInReload = (to->weapondata[to->client.m_iId].m_fInReload || !to->weapondata[to->client.m_iId].m_iClip);
		//	PlayerLocale.spread.iInReload = to->weapondata[to->client.m_iId].m_fInReload;
			int iFOV = to->client.fov;
			if(iFOV<90) PlayerLocale.inzoom=true;
			else PlayerLocale.inzoom=false;

		}
	}
}

int Hooked_HUD_Key_Event( int eventcode, int keynum, const char* pszCurrentBinding )
{

	int iRet = g_Client.HUD_Key_Event( eventcode, keynum, pszCurrentBinding );


	if (keynum == CVARS.menukey && eventcode)
	{
		gMenu.Active = !gMenu.Active;
		return 0;
	}

	if(gMenu.Active && eventcode)
	{
		if (!gMenu.KeyEvent(keynum))
		{
			return 0;
		}
	}

	return iRet;
}

void Hooked_HUD_TempEntUpdate (
		double frametime,   			// Simulation time
		double client_time, 			// Absolute time on client
		double cl_gravity,  			// True gravity on client
		TEMPENTITY **ppTempEntFree,   	// List of freed temporary ents
		TEMPENTITY **ppTempEntActive, 	// List 
		int		( *Callback_AddVisibleEntity )( cl_entity_t *pEntity ),
		void	( *Callback_TempEntPlaySound )( TEMPENTITY *pTemp, float damp ) )
{
	g_Client.HUD_TempEntUpdate(frametime,client_time,cl_gravity,ppTempEntFree,ppTempEntActive,
		Callback_AddVisibleEntity,Callback_TempEntPlaySound);
}

/*
void HUD_ProcessPlayerState(struct entity_state_s* dst, const struct entity_state_s* src)
{
	// Send bbox down to client for use during prediction.
//	Vector mins;
//	Vector maxs;

	if (cvar.bypass_valid_blockers)
	{
		for (int i = 0; i < 3; i++)
			src->mins[i] = i == 2 ? -36 : -16;
		for (int i = 0; i < 3; i++)
			src->maxs[i] = i == 2 ? 36 : 16;
	}
	g_Client.HUD_ProcessPlayerState(dst, src);
}*/

/*
void HUD_VoiceStatus(int entindex, qboolean bTalking)
{
	g_Client.HUD_VoiceStatus(entindex, bTalking);
}*/

/*
int Hooked_CL_IsThirdPerson( void )
{
	return g_Client.CL_IsThirdPerson();
}*/

//-------------------------------------------------------------------//

bool LoadOffsets()
{
	if(GetModuleInfo())
	{
		g_pClient=(struct cl_clientfuncs_s *)FindClientTable();// OK
		pEngfuncs=(struct cl_enginefuncs_s *)FindEngineTable();// OK
	//	pstudio=(struct engine_studio_api_s *)FindStudioTable();// no anda con el nuevo STEAM
		pstudio=(struct engine_studio_api_s *)EngineStudio();// OK

		if(g_pClient && pEngfuncs && pstudio)
		{
			logme1("g_pClient 0x%X\0", g_pClient);
			logme1("pEngfuncs 0x%X\0", pEngfuncs);
			logme1("pstudio 0x%X\0", pstudio);

			memcpy( &g_Client, (LPVOID)g_pClient, sizeof( cl_clientfunc_t ) );
			RtlCopyMemory(&gEngfuncs, pEngfuncs, sizeof(cl_enginefunc_t));
			RtlCopyMemory(&IEngineStudio, pstudio, sizeof(engine_studio_api_t));

		/*	g_pStudio->StudioCheckBBox = StudioCheckBBox;
			g_pStudio->StudioEntityLight = StudioEntityLight;*/

			//
			// crashea con el nuevo STEAM

		//	DWORD dwSVCmessages =FindSVCMessages();
		//	logme1("dwSVCmessages 0x%X\0", dwSVCmessages);

		//	DWORD dwSVCmessages2 =FindSVCMessages2();
		//	logme1("dwSVCmessages2 0x%X\0", dwSVCmessages2);

			//

		//	dwPDS = (DWORD)Sound();// no anda con el nuevo STEAM
		//	logme1("dwPDS 0x%X\0", dwPDS);

		//	dwPDS = (DWORD)Sound1();// no anda con el nuevo STEAM
		//	logme1("dwPDS 0x%X\0", dwPDS);


		//	dwPDS = (DWORD)OffsetPreSDynSound();// OK
		//	logme1("dwPDS 0x%X\0", dwPDS);

			//

		//	ppinterface = (struct r_studio_interface_s**)studiodrawplayer();// OK
		//	logme1("ppinterface 0x%X\0", ppinterface);

			return true;
		}

		else
		{

			if(!g_pClient) logme1("client ptr failed.\0");
			if(!pEngfuncs) logme1("engine ptr failed.\0");
			if(!pstudio) logme1("studio ptr failed.\0");

			// crashea con el nuevo STEAM
		//	DWORD dwSVCmessages =FindSVCMessages();
		//	logme1("dwSVCmessages 0x%X\0", dwSVCmessages);

		}

	}


	return false;
}

//-------------------------------------------------------------------//

bool HookClient()
{
	if(g_pClient)
	{
		/*1*/HUD_Init_SA = (DWORD*)((DWORD*)(g_pClient)+0x4);
		/*3*/HUD_Redraw_SA = (DWORD*)((DWORD*)(g_pClient)+0xC);
		/*6*/HUD_PlayerMove_SA = (DWORD*)((DWORD*)(g_pClient)+0x18);
		/*7*/HUD_PlayerMoveInit_SA = (DWORD*)((DWORD*)(g_pClient)+0x1C);
		/*14*/CL_CreateMove_SA = (DWORD*)((DWORD*)(g_pClient)+0x38);
		/*19*/V_CalcRefdef_SA = (DWORD*)((DWORD*)(g_pClient)+0x4C);
		/*20*/HUD_AddEntity_SA = (DWORD*)((DWORD*)(g_pClient)+0x50);
		/*25*/HUD_PostRunCmd_SA = (DWORD*)((DWORD*)(g_pClient)+0x64);
		/*33*/HUD_Frame_SA = (DWORD*)((DWORD*)(g_pClient)+0x84);
		/*34*/HUD_Key_Event_SA = (DWORD*)((DWORD*)(g_pClient)+0x88);
		/*35*/HUD_TempEntUpdate_SA = (DWORD*)((DWORD*)(g_pClient)+0x8C);
		/*39*/HUD_GetStudioModelInterface_SA = (DWORD*)((DWORD*)(g_pClient)+0x9C);
		

		if (!IsBadReadPtr((void*)HUD_Init_SA,sizeof(DWORD)) && 
			*(DWORD*)HUD_Init_SA !=NULL) 
		{

			/*
			PARA INJECTED SE DEBEN CORREGIR LOS RETURNS DE ALGUNAS CLIENTE
			*/

			g_Client.HUD_Redraw = g_pClient->HUD_Redraw;
			g_pClient->HUD_Redraw=(t_HUD_Redraw)(&Hooked_HUD_Redraw);


			g_Client.HUD_PlayerMove = g_pClient->HUD_PlayerMove;
			g_pClient->HUD_PlayerMove=(t_HUD_PlayerMove)(&Hooked_HUD_PlayerMove);

			g_Client.CL_CreateMove = g_pClient->CL_CreateMove;
			g_pClient->CL_CreateMove=(t_CL_CreateMove)(&Hooked_CL_CreateMove);

			g_Client.V_CalcRefdef = g_pClient->V_CalcRefdef;
			g_pClient->V_CalcRefdef=(t_V_CalcRefdef)(&Hooked_V_CalcRefdef);


			g_Client.HUD_AddEntity = g_pClient->HUD_AddEntity;
			g_pClient->HUD_AddEntity=(t_HUD_AddEntity)(&Hooked_HUD_AddEntity);


			g_Client.HUD_PostRunCmd = g_pClient->HUD_PostRunCmd;
			g_pClient->HUD_PostRunCmd=(t_HUD_PostRunCmd)(&Hooked_HUD_PostRunCmd);


			g_Client.HUD_Key_Event = g_pClient->HUD_Key_Event;
			g_pClient->HUD_Key_Event=(t_HUD_Key_Event)(&Hooked_HUD_Key_Event);

		//	g_Client.HUD_TempEntUpdate = g_pClient->HUD_TempEntUpdate;
		//	g_pClient->HUD_TempEntUpdate=(t_HUD_TempEntUpdate)(&Hooked_HUD_TempEntUpdate);

		//	g_Client.HUD_GetStudioModelInterface = g_pClient->HUD_GetStudioModelInterface;
		//	g_pClient->HUD_GetStudioModelInterface=(t_HUD_GetStudioModelInterface)(&Hooked_HUD_GetStudioModelInterface);


			return true;
		}
	}

	return false;
}

//-------------------------------------------------------------------//

void LoadHack()
{
	if(LoadOffsets())
	{
		InitControlVariables();
		InitPlayers();
		InitPlayerLocale();
		InitSpreadData();


		bool bClientHooked = HookClient();

		if(!bClientHooked)
		{
		//	MessageBox(0,"CLIENT not hooked.\0",0,0);
		}
		else
		{

		// HL CONTROL BASE by serenity
		// recall ClientDll & HUD initialization to hook events & usermsgs
	//	g_pClient->Initialize(pEngfuncs, CLDLL_INTERFACE_VERSION);
	//	g_pClient->HUD_Init();// falla

		gEngfuncs.pfnClientCmd(/*fs_lazy_precache 1\0*/XorStr<0x11,20,0x696CC46E>("\x77\x61\x4C\x78\x74\x6C\x6E\x47\x69\x68\x7E\x7F\x7C\x7D\x77\x45\x01\x13\x23"+0x696CC46E).s);
		gEngfuncs.pfnClientCmd(/*toggleconsole\0*/XorStr<0x07,15,0x0D308514>("\x73\x67\x6E\x6D\x67\x69\x6E\x61\x61\x63\x7E\x7E\x76\x14"+0x0D308514).s);
	
		gEngfuncs.pfnConsolePrint(/*\nSTEAMWALL v0.1 [2024]\n\0*/XorStr<0x1A,25,0xA558CFDF>("\x10\x48\x48\x58\x5F\x52\x77\x60\x6E\x6F\x04\x53\x16\x09\x19\x09\x71\x19\x1C\x1F\x1A\x72\x3A\x31"+0xA558CFDF).s);
				
		gEngfuncs.pfnConsolePrint(/*\nBUILD: 000001 (21-08-2023)\n\0*/XorStr<0x18,30,0x98F2DC6B>("\x12\x5B\x4F\x52\x50\x59\x24\x3F\x10\x11\x12\x13\x14\x14\x06\x0F\x1A\x18\x07\x1B\x14\x00\x1C\x1F\x02\x02\x1B\x39\x34"+0x98F2DC6B).s);

		gEngfuncs.pfnConsolePrint(/*\nYT Channel1 CS_85: https://www.youtube.com/@TornadoWayOfficial\n\0*/XorStr<0xDA,66,0xFCF70DC8>("\xD0\x82\x88\xFD\x9D\xB7\x81\x8F\x8C\x86\x88\xD4\xC6\xA4\xBB\xB6\xD2\xDE\xD6\xCD\x86\x9B\x84\x81\x81\xC9\xDB\xDA\x81\x80\x8F\xD7\x83\x94\x89\x89\x8B\x9D\x65\x2F\x61\x6C\x69\x2A\x46\x53\x67\x7B\x64\x6A\x68\x62\x59\x6E\x69\x5E\x74\x75\x7D\x76\x7F\x76\x74\x13\x1A"+0xFCF70DC8).s);
		gEngfuncs.pfnConsolePrint(/*\nYT Channel2 CS_85: https://www.youtube.com/@DavidTornadoOchentaycinco\n\0*/XorStr<0xFE,73,0xBF1F0BC0>("\xF4\xA6\x54\x21\x41\x6B\x65\x6B\x68\x62\x64\x3B\x2A\x48\x5F\x52\x36\x3A\x2A\x31\x7A\x67\x60\x65\x65\x2D\x37\x36\x6D\x6C\x6B\x33\x67\x70\x55\x55\x57\x41\x41\x0B\x45\x48\x45\x06\x6A\x6F\x4D\x5B\x47\x4B\x64\x5E\x40\x5D\x55\x51\x59\x78\x5B\x51\x5F\x55\x48\x5C\x47\x5C\x29\x2F\x21\x2C\x4E\x45"+0xBF1F0BC0).s);
		gEngfuncs.pfnConsolePrint(/*\nYT Channel3 CS_85: https://www.youtube.com/@TheKingOfTheCheat\n\0*/XorStr<0x3B,65,0x7F6FE7EE>("\x31\x65\x69\x1E\x7C\x28\x20\x2C\x2D\x21\x29\x75\x67\x0B\x1A\x15\x73\x79\x77\x6E\x27\x24\x25\x22\x20\x6E\x7A\x79\x20\x2F\x2E\x74\x22\x33\x28\x2A\x2A\x02\x04\x4C\x00\x0B\x08\x49\x27\x3C\x01\x0F\x20\x05\x03\x09\x20\x16\x25\x1A\x16\x37\x1D\x13\x16\x0C\x73\x7A"+0x7F6FE7EE).s);
		
		gEngfuncs.pfnConsolePrint(/*\nHOTMAIL: darvo_nonsteam@hotmail.com\0*/XorStr<0x05,38,0x662C12C3>("\x0F\x4E\x48\x5C\x44\x4B\x42\x40\x37\x2E\x6B\x71\x63\x64\x7C\x4B\x7B\x79\x79\x6B\x6D\x7F\x7A\x71\x5D\x76\x70\x54\x4C\x43\x4A\x48\x0B\x45\x48\x45\x29"+0x662C12C3).s);
	//	gEngfuncs.pfnConsolePrint(/*\nsend me your inquiries or suggestions and report any problems. njoy the run.\0*/XorStr<0xBC,79,0x2D1A63FF>("\xB6\xCE\xDB\xD1\xA4\xE1\xAF\xA6\xE4\xBC\xA9\xB2\xBA\xE9\xA3\xA5\xBD\xB8\xA7\xBD\xB9\xB4\xA1\xF3\xBB\xA7\xF6\xA4\xAD\xBE\xBD\xBE\xAF\xA9\xB7\xB0\x8E\x92\xC2\x82\x8A\x81\xC6\x95\x8D\x99\x85\x99\x98\xCD\x8F\x81\x89\xD1\x82\x81\x9B\x97\x9A\x92\x95\x8A\xD4\xDB\x92\x97\x91\x86\x20\x75\x6A\x66\x24\x77\x73\x69\x26\x09"+0x2D1A63FF).s);
		gEngfuncs.pfnConsolePrint(/*\n\nDone By D4rv0\n\n\0*/XorStr<0x74,19,0xCAB06239>("\x7E\x7F\x32\x18\x16\x1C\x5A\x39\x05\x5D\x3A\x4B\xF2\xF7\xB2\x89\x8E\x85"+0xCAB06239).s);

	//	RandomizeSTEAMID(1);

		}
	}
}

//-------------------------------------------------------------------//


