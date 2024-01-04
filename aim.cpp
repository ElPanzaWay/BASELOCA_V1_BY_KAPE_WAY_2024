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

int iAimTarget = -1;
float g_aimvector[3] = {0,0,0};
float g_aimangles[3] = {0,0,0};

//-------------------------------------------------------------------//

void PredictEntity(cl_entity_s *pEntity, Vector *vOutput, unsigned int fAmount)
{
	net_status_s sNetwork;
	gEngfuncs.pNetAPI->Status(&sNetwork);
	int nHistory = (pEntity->current_position + HISTORY_MAX - fAmount) % HISTORY_MAX;
	Vector vOldOrigin, vCurOrigin, vDeltaOrigin;
	vOldOrigin = pEntity->ph[nHistory].origin;
	vCurOrigin = pEntity->ph[pEntity->current_position].origin;
	VectorSubtract(vCurOrigin, vOldOrigin, vDeltaOrigin);
	float fPing = (float)sNetwork.latency;
	if (fPing < 0.0f) fPing = -fPing;
	VectorScale(vDeltaOrigin, fPing, vDeltaOrigin);
	VectorAdd(pEntity->origin, vDeltaOrigin, *vOutput);
}

/*
Vector vAimOrigin;
VectorCopy((*g_sAimbot.sTarget.cPlayer->BonePosition()), vAimOrigin);
		
if (CVAR(aim_prediction))
{
	Vector vDelta;
	cl_entity_s *pEntity = g_sAimbot.sTarget.cPlayer->Entity();
	VectorSubtract(vAimOrigin, pEntity->origin, vDelta);
	PredictEntity(pEntity, &vAimOrigin, (int)CVAR(aim_prediction));
	VectorAdd(vAimOrigin, vDelta, vAimOrigin);
}
cMe->CalcViewAngles(&vAimOrigin, NULL);
*/

//-------------------------------------------------------------------//

void CalculateAimVector(int iTARGET)
{
	if(iTARGET == -1) return;

	g_aimvector[0] = Players[iTARGET].entorg[0];
	g_aimvector[1] = Players[iTARGET].entorg[1];
	g_aimvector[2] = Players[iTARGET].entorg[2];

	//
	// TODO: aplicar position prediction
	//

	if(Players[iTARGET].ducked)
	{
		g_aimvector[2] = g_aimvector[2]+12;
		g_aimvector[2]+= CVARS.duck_h_correction;
	}
	else
	{
		g_aimvector[2] = g_aimvector[2]+17;
		g_aimvector[2]+= CVARS.stand_h_correction;
	}

	if(Players[iTARGET].frozen) g_aimvector[2] += CVARS.frozen_correction;// si está congelado dispararle al origin
	                                                                      // si está quieto en base o parado USAR """""""

	g_aimvector[0] += CVARS.origin_f;
	g_aimvector[1] += CVARS.origin_r;
	g_aimvector[2] += CVARS.origin_h;

}

//-------------------------------------------------------------------//

void CalculateAimAngles(int iTARGET)
{
	if(iTARGET == -1) return;

	float vec_to_target[3] = {0,0,0};

	CalculateAimVector(iTARGET);

	vec_to_target[0] = g_aimvector[0] - GetMyViewPoint()[0];
	vec_to_target[1] = g_aimvector[1] - GetMyViewPoint()[1];
	vec_to_target[2] = g_aimvector[2] - GetMyViewPoint()[2];

	VectorAngles(vec_to_target,g_aimangles);
	g_aimangles[0] *= -1;

	// g_aimangles = 0..360
	if (g_aimangles[0]>180) g_aimangles[0]-=360;
	if (g_aimangles[1]>180) g_aimangles[1]-=360;
	// g_aimangles = -180..180
}


//-------------------------------------------------------------------//

void SetAimAngles1(int iTARGET)
{
	if(iTARGET != -1)
		gEngfuncs.SetViewAngles(g_aimangles);
}

void SetAimAngles2(int iTARGET, struct ref_params_s* pparams)
{
	if(iTARGET != -1)
	{
		VectorCopy(g_aimangles, pparams->viewangles);
		VectorCopy(g_aimangles, pparams->cl_viewangles);
	}
}

//float g_aimvector[3] = {0,0,0};
//float g_aimangles[3] = {0,0,0};

float * GetAimVector()
{
	return g_aimvector;
}

float * GetAimAngles()
{
	return g_aimangles;
}

//-------------------------------------------------------------------//

void TargetFinder()// Vermilion trigger method
{
	if(CVARS.targetlock||PlayerLocale.weaponid==WEAPONLIST_KNIFE)
	{
		if(iAimTarget != -1)
		{
			if(Players[iAimTarget].alive && GetAimingTeam(iAimTarget) &&

				(Players[iAimTarget].updatedbyentity)

				)
			{
				if(Players[iAimTarget].visible)
				{
					float SCR_Entity[2] = { 0 };
					float SCR_Aim[2] = { 0 };

					bool duck = 0;
					bool jump = 0;
					bool shielded = 0;
					cl_entity_s* pEnt = gEngfuncs.GetEntityByIndex(iAimTarget);
					if(pEnt)
					{
						duck = (pEnt->curstate.usehull != 0 ) && !CVARS.ducktargetaim;
						jump = (pEnt->curstate.gaitsequence==6) && !CVARS.airtargetaim;
						shielded = (pEnt->curstate.sequence == 97 || pEnt->curstate.sequence == 98) && !CVARS.shieldattack;
					}

					if(duck);
					else if(jump);
					else if(shielded);

					//

					else if ( AimCalcScreen( Players[iAimTarget].entorg , SCR_Entity ) && 
							 AimCalcScreen( Players[iAimTarget].visibility_aimvec , SCR_Aim ) );

					//
					else return;
				}
			}
		}
	}

	//

	iAimTarget = -1;

	float max_screen_dist = CVARS.maxscreendist; //20;

	float center_screen[2];
	center_screen[0] = g_Screen.iWidth / 2;
	center_screen[1] = g_Screen.iHeight / 2;

	for(unsigned int ax=0; ax<33; ax++)//MAX_VPLAYERS
	{
		if(ax ==0 ) continue;
		if(ax == PlayerLocale.index) continue;

		if(Players[ax].alive && GetAimingTeam(ax) &&

			(Players[ax].updatedbyentity)

			)
		{
			if(Players[ax].visible)
			{
				bool duck = 0;
				bool jump = 0;
				bool shielded = 0;
				cl_entity_s* pEnt = gEngfuncs.GetEntityByIndex(ax);
				if(pEnt)
				{
					duck = (pEnt->curstate.usehull != 0 ) && !CVARS.ducktargetaim;
					jump = (pEnt->curstate.gaitsequence==6) && !CVARS.airtargetaim;
					shielded = (pEnt->curstate.sequence == 97 || pEnt->curstate.sequence == 98) && !CVARS.shieldattack;
				}

				if(duck) continue;
				if(jump) continue;
				if(shielded) continue;

				float SCR_Entity[2] = { 0 };
				float SCR_Aim[2] = { 0 };

				if ( AimCalcScreen( Players[ax].entorg , SCR_Entity ) && 
					 AimCalcScreen( Players[ax].visibility_aimvec , SCR_Aim ) )
				{
					float screen_dist = CalcDistPlayerScreen( center_screen , SCR_Aim );
					if ( screen_dist < max_screen_dist )
					{
						max_screen_dist = screen_dist;
						iAimTarget = ax;
					}
				}
			}
		}
	}
}

//-------------------------------------------------------------------//

void CalculateVisibilityAimVector(int px, int iAimvis)
{
	if(iAimvis)
	{
		Players[px].visibility_aimvec[0] = Players[px].entorg[0];
		Players[px].visibility_aimvec[1] = Players[px].entorg[1];
		Players[px].visibility_aimvec[2] = Players[px].entorg[2];

		if(Players[px].ducked)
		{
			Players[px].visibility_aimvec[2] = Players[px].visibility_aimvec[2]+12;
			Players[px].visibility_aimvec[2]+= CVARS.duck_h_correction;
		}
		else
		{
			Players[px].visibility_aimvec[2] = Players[px].visibility_aimvec[2]+17;
			Players[px].visibility_aimvec[2]+= CVARS.stand_h_correction;
		}

		if(Players[px].frozen) 
			Players[px].visibility_aimvec[2] += CVARS.frozen_correction;// si está congelado dispararle al origin
																		// si está quieto en base o parado USAR """""""


		Players[px].visibility_aimvec[0] += CVARS.origin_f;
		Players[px].visibility_aimvec[1] += CVARS.origin_r;
		Players[px].visibility_aimvec[2] += CVARS.origin_h;


		Players[px].visible = PathFree(GetMyViewPoint(),Players[px].visibility_aimvec);
	}

	else
	{
		Players[px].visible = PathFree(GetMyViewPoint(),Players[px].entorg);
	}

}

//-------------------------------------------------------------------//

void tintArea(int x,int y,int w,int h,int r,int g,int b,int a){

//	oglSubtractive = true;
	gEngfuncs.pfnFillRGBA(x,y,w,h,r,g,b,a);
//	oglSubtractive = false;
}

void gDrawFilledBoxAtLocation( float* origin, DWORD color, int radius)
{
	float vecScreen[2]; 
	if( !bCalcScreen(origin, vecScreen) ) { return; }
	int red   = (color>>24);
	int green = (color>>16)&0xFF;
	int blue  = (color>>8)&0xFF;
	int alpha = (color)&0xFF;
	int radius2 = radius<<1;
//	oglSubtractive = true;
	tintArea(vecScreen[0]-radius,vecScreen[1]-radius,radius2,radius2,red,green,blue,alpha);
//	oglSubtractive = false;
}

void CalculateAimVectorDraw(int ax)
{
	float avdraw[3] = {0,0,0};

	avdraw[0] = Players[ax].entorg[0];
	avdraw[1] = Players[ax].entorg[1];
	avdraw[2] = Players[ax].entorg[2];

	if(Players[ax].ducked)
	{
		avdraw[2] = avdraw[2]+12;
		avdraw[2]+= CVARS.duck_h_correction;
	}
	else
	{
		avdraw[2] = avdraw[2]+17;
		avdraw[2]+= CVARS.stand_h_correction;
	}

	if(Players[ax].frozen) avdraw[2] += CVARS.frozen_correction;// si está congelado dispararle al origin
	                                                            // si está quieto en base o parado USAR """""""


	avdraw[0] += CVARS.origin_f;
	avdraw[1] += CVARS.origin_r;
	avdraw[2] += CVARS.origin_h;



	register DWORD color = 0xFFFFFFFF;
	gDrawFilledBoxAtLocation(avdraw,color,4);
}

//-------------------------------------------------------------------//


