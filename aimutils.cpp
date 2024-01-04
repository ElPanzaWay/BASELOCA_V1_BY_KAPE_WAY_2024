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

#define M_PI 3.14159265358979323846f

//-------------------------------------------------------------------//

void VectorAngles (const float * forward, float * angles)
{ 
	if(!forward[1]==0 && !forward[0]==0) 
	{
		angles[0] = (float)((atan2(forward[2],(sqrt(forward[0]*forward[0]+forward[1]*forward[1])))* 180.0f / M_PI)); 
		angles[1] = (float)((atan2(forward[1],forward[0])* 180.0f / M_PI)); 
		angles[2] = 0; 
	}
}

//-------------------------------------------------------------------//

void AngleVectors(const float *angles, float *forward, float *right, float *up)
{
	float angle = 0;
	float sr = 0, sp = 0, sy = 0, cr = 0, cp = 0, cy = 0;
	angle = (float)angles[1] * (M_PI*2 / 360.0f);
	sy = (float)sin(angle);
	cy = (float)cos(angle);
	angle = (float)angles[0] * (M_PI*2 / 360.0f);
	sp = (float)sin(angle);
	cp = (float)cos(angle);
	angle = (float)angles[2] * (M_PI*2 / 360.0f);
	sr = (float)sin(angle);
	cr = (float)cos(angle);
	
	if (forward)
	{
		forward[0] = cp*cy;
		forward[1] = cp*sy;
		forward[2] = -sp;
	}
	if (right)
	{
		right[0] = (-1*sr*sp*cy+-1*cr*-sy);
		right[1] = (-1*sr*sp*sy+-1*cr*cy);
		right[2] = -1*sr*cp;
	}
	if (up)
	{
		up[0] = (cr*sp*cy+-sr*-sy);
		up[1] = (cr*sp*sy+-sr*cy);
		up[2] = cr*cp;
	}
}

//-------------------------------------------------------------------//

/*
bool bWillHit (float *fSpreadangles,float *fPunchangles,float *fAimAngles)
{
    pmtrace_t *vis;
    float fTraceVec[3],Origin[3];
    fTraceVec[0] = fSpreadangles[0] + fPunchangles[0] + fAimAngles[0];
    fTraceVec[1] = fSpreadangles[1] + fPunchangles[1] + fAimAngles[1];
    fTraceVec[2] = fSpreadangles[2] + fPunchangles[2] + fAimAngles[2];
    VectorAngles(fTraceVec,Origin);
    vis = gEngfuncs.PM_TraceLine( me.pmEyePos, Origin, PM_TRACELINE_PHYSENTSONLY, 2, -1 );
	return (vis->inopen == false); 
}*/

//-------------------------------------------------------------------//

/*
int PATHFREE(int target, struct usercmd_s* cmd)// it has a prediction
{
	pmtrace_t tr;
	float flEnd[3], flForward[3], flDistance = gNoSpread0.ShotDistance();

	// Maximum shot distance
	pEngfuncs->pfnAngleVectors(cmd->viewangles, flForward, NULL, NULL);
	flEnd[0] = me.pmEyePos[0] + flForward[0] * flDistance;
	flEnd[1] = me.pmEyePos[1] + flForward[1] * flDistance;
	flEnd[2] = me.pmEyePos[2] + flForward[2] * flDistance;

	gEngfuncs.pEventAPI->EV_SetUpPlayerPrediction(false, true);
	gEngfuncs.pEventAPI->EV_SetTraceHull(2);
	gEngfuncs.pEventAPI->EV_PlayerTrace(me.pmEyePos, flEnd, PM_GLASS_IGNORE, -1, &tr);

	// Ghetto fix
	bool bUseHull = (gEngfuncs.GetEntityByIndex(target)->curstate.usehull != 0);

	// The trace was a success...
	if(tr.fraction != 1.0 || bUseHull)
	{
		// ... and it hit our target
		if(gEngfuncs.pEventAPI->EV_IndexFromTrace((pmtrace_t*)&tr) == target || bUseHull)
		{
			// If it's a shotgun, make sure we're doing enough damage to make the shot worth it
			// NOTE: This assumes no spread for shotguns
			if(me.weaponid == WEAPONLIST_M3 || me.weaponid == WEAPONLIST_XM1014)
			{
				int iShots = (me.weaponid == WEAPONLIST_M3) ? 6 : 8;
				int iDamage = (int)(iShots * 20 * (1.0 - tr.fraction));// usa iShots !!!!!!!!!!!!!!!!!!!!!!!!!

				// If our shot will do less than 100 damage, don't bother shooting
				if(iDamage < 100)
					return false;

				return true;
			}
			else
			{
				return true;
			}
		}
	}
	return false;
}*/

//-------------------------------------------------------------------//

/*
	gEngfuncs.pEventAPI->EV_SetTraceHull( 2 );
	gEngfuncs.pEventAPI->EV_SetUpPlayerPrediction( false, true );

	// Store off the old count
	gEngfuncs.pEventAPI->EV_PushPMStates();
	gEngfuncs.pEventAPI->EV_KillEvents( idx, "events/gaussspin.sc" );
	gEngfuncs.pEventAPI->EV_StopSound( idx, CHAN_WEAPON, "ambience/pulsemachine.wav" );

	if ( gEngfuncs.GetMaxClients() > 1 )
	{
	EV_HLDM_FireBullets( idx, forward, right, up, 4, vecSrc, vecAiming, 2048, BULLET_PLAYER_BUCKSHOT, 0, &tracerCount[idx-1], 0.08716, 0.04362 );
	}
	else
	{
	EV_HLDM_FireBullets( idx, forward, right, up, 6, vecSrc, vecAiming, 2048, BULLET_PLAYER_BUCKSHOT, 0, &tracerCount[idx-1], 0.08716, 0.08716 );
	}

	gEngfuncs.pEventAPI->EV_PopPMStates();
*/

//-------------------------------------------------------------------//

int CanPenetrate (float * start, float * end, int power) 
{ 
	pmtrace_t pmtrace;
	pmtrace_t* tr = (pmtrace_t*) &pmtrace;
	float view[3]; 
	float dir[3]; 
	view[0] = end[0] - start[0]; 
	view[1] = end[1] - start[1]; 
	view[2] = end[2] - start[2]; 
	float length = VectorLength(view); 
	dir[0] = view[0] / length; 
	dir[1] = view[1] / length; 
	dir[2] = view[2] / length; 
	float position[3]; 
	position[0] = start[0]; 
	position[1] = start[1]; 
	position[2] = start[2]; 
	tr->startsolid = true; 
	while( power ) 
	{ 
		if( !tr->startsolid ) 
			power--; 
	//	tr = gEngfuncs.PM_TraceLine( position, end, PM_TRACELINE_PHYSENTSONLY, 2, -1);
		tr = pEngfuncs->PM_TraceLine( position, end, PM_TRACELINE_PHYSENTSONLY, 2, -1);
		if( tr->fraction==1.0f ) 
			return 1; 
		if( tr->allsolid ) 
			return 0; 
		position[0] = tr->endpos[0] + dir[0] * 8.0f; 
		position[1] = tr->endpos[1] + dir[1] * 8.0f; 
		position[2] = tr->endpos[2] + dir[2] * 8.0f; 
	} 
	return 0; 
}

//-------------------------------------------------------------------//

int CorrectGunX()
{

	if (PlayerLocale.weaponid == WEAPONLIST_SG550 || 
		PlayerLocale.weaponid == WEAPONLIST_G3SG1 || 
		PlayerLocale.weaponid == WEAPONLIST_SCOUT || 
		PlayerLocale.weaponid == WEAPONLIST_AWP)
	{ 
		return 3; 
	}
	if (PlayerLocale.weaponid == WEAPONLIST_AUG || 
		PlayerLocale.weaponid == WEAPONLIST_M249 || 
		PlayerLocale.weaponid == WEAPONLIST_M4A1 ||  
		PlayerLocale.weaponid == WEAPONLIST_DEAGLE || 
		PlayerLocale.weaponid == WEAPONLIST_SG552 || 
		PlayerLocale.weaponid == WEAPONLIST_AK47) 
	{ 
		return 2; 
	} 

	return 0;
}

//-------------------------------------------------------------------//

int PathFree (float * from, float * to) 
{ 
	int pathtest = 0; 
	pmtrace_t tr; 
	pEngfuncs->pEventAPI->EV_SetTraceHull( 2 ); 
	pEngfuncs->pEventAPI->EV_PlayerTrace( from, to, PM_GLASS_IGNORE, PlayerLocale.index, &tr ); 
	pathtest = (tr.fraction == 1.0f); 
	if (!pathtest && CVARS.autowall && CorrectGunX())
	{ 
		pathtest = CanPenetrate(from, to, CorrectGunX()); 
	} 
	return pathtest; 
}

//-------------------------------------------------------------------//

int PathFree2 (float * from, float * to) 
{ 
	int pathtest = 0; 
	pmtrace_t * vis = pEngfuncs->PM_TraceLine(from, to, 0, 2, -1);
	pathtest = (vis->fraction == 1.0f); 
	if (!pathtest && CVARS.autowall && CorrectGunX())
	{ 
		pathtest = CanPenetrate(from, to, CorrectGunX()); 
	} 
	return pathtest; 
}

//-------------------------------------------------------------------//

float AimCalcFOV(Vector a,Vector b,float lena=0,float lenb=0)
{
	float l1=0.0f, l2=0.0f;
	if(lena>0)l1=lena;
	else l1=a.Length();
	if(lenb>0)l2=lenb;else l2=b.Length();
	float sc=a.x*b.x+a.y*b.y+a.z*b.z;
	return acos(sc/(l1*l2))*(180.0/M_PI);
}

//-------------------------------------------------------------------//

#define MIN_SMOOTH 0.000001f

void SmoothAimAngles(float *MyViewAngles, float *AimAngles, float *OutAngles, float Smoothing)
{
	if (Smoothing < 0.0000001f)
		return;

	VectorSubtract(AimAngles, MyViewAngles, OutAngles);

	if (OutAngles[1] > 180.0f)
		OutAngles[1] -= 360.0f;
	if (OutAngles[1] < -180.0f)
		OutAngles[1] += 360.0f;

	OutAngles[0] = OutAngles[0] / Smoothing + MyViewAngles[0];
	OutAngles[1] = OutAngles[1] / Smoothing + MyViewAngles[1];

	if (OutAngles[1] > 360.0f)
		OutAngles[1] -= 360.0f;
	if (OutAngles[1] < 0.0f)
		OutAngles[1] += 360.0f;
}

/*
void SmootherMe(float* Source, float* Destination, float* NewDestination, float Factor)
{
	if(Factor == MIN_SMOOTH)
		return;
	VectorSubtract(Destination, Source, NewDestination);
	if(NewDestination[YAW] > 180.0f)
		NewDestination[YAW] -= 360.0f;
	if(NewDestination[YAW] < -180.0f)
		NewDestination[YAW] += 360.0f;
	NewDestination[PITCH] = NewDestination[PITCH] / Factor + Source[PITCH];
	NewDestination[YAW] = NewDestination[YAW] / Factor + Source[YAW];
	if(NewDestination[YAW] > 360.0f) 
		NewDestination[YAW] -= 360.0f;
	if(NewDestination[YAW] < 0.0f)
		NewDestination[YAW] += 360.0f;
}

float AngleBetvenVectors(Vector a,Vector b,float lena = 0, float lenb = 0)
{
	float l1=0.0f, l2=0.0f;
	if(lena>0)l1=lena;else l1=a.Length();
	if(lenb>0)l2=lenb;else l2=b.Length();
	float sc=a.x*b.x+a.y*b.y+a.z*b.z;
	return acos(sc/(l1*l2))*(180.0/M_PI);
}*/

/*
void SmoothAimAngles(Vector *vStart, Vector *vTarget, Vector *vOutput, float fSmoothness)
{
	if(fSmoothness == MIN_SMOOTH)
		return;
	Vector vDelta;
	VectorSubtract((*vTarget), (*vStart), vDelta);
	if (vDelta[1] > 180.0f) vDelta[1] -= 360.0f;
	if (vDelta[1] < -180.0f) vDelta[1] += 360.0f;
	vDelta[0] = vDelta[0] / fSmoothness;
	vDelta[1] = vDelta[1] / fSmoothness;
	VectorAdd((*vStart), vDelta, (*vOutput));
}*/

/*
if (CVAR(aim_active) && CVAR(aim_smoothness))
		{
			if (bDoSmoothAim)
			{
				SmoothAimAngles(&(g_cPlayers.Me()->Info()->vPreAimAngles), &(g_cPlayers.Me()->Info()->vAimAngles), &(g_cPlayers.Me()->Info()->vPreAimAngles), CVAR(aim_smoothness));
				VectorCopy(g_cPlayers.Me()->Info()->vPreAimAngles, cmd->viewangles);
			}
			else
			{
				Vector vDelta;
				VectorSubtract(g_cPlayers.Me()->Info()->vPreAimAngles, g_cPlayers.Me()->Info()->vViewAngles, vDelta);
				if (vDelta[0] == 0.0f && vDelta[1] == 0.0f)
				{
					VectorCopy(g_cPlayers.Me()->Info()->vViewAngles, g_cPlayers.Me()->Info()->vPreAimAngles);
				}
				else
				{
					SmoothAimAngles(
						&(g_cPlayers.Me()->Info()->vPreAimAngles), 
						&(cmd->viewangles), 
						&(g_cPlayers.Me()->Info()->vPreAimAngles), CVAR(aim_smoothness));
					VectorCopy(g_cPlayers.Me()->Info()->vPreAimAngles, cmd->viewangles);
				}
			}
		}*/