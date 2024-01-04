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

#define POW(x) ((x)*(x))

//-------------------------------------------------------------------//

/*
bool bCanShoot(struct usercmd_s* pCmd)
{
	if ( (me.spread.flNextPrimaryAttack - pCmd->msec / 1000) > 0 ) return false;
	return true;
}*/

/*
bool NA_CanAttack(void)
{
    if (me.spread.flNextPrimaryAttack <= 0.0f && !me.spread.iInReload && me.spread.flNextAttack <= 0.0f)
        return true;
    else
        return false;
}*/

//-------------------------------------------------------------------//

bool AimCalcScreen( float *pflOrigin , float *pflVecScreen )
{
	int iResult = gEngfuncs.pTriAPI->WorldToScreen( pflOrigin , pflVecScreen );

	if ( pflVecScreen[0] < 1 && pflVecScreen[1] < 1 && pflVecScreen[0] > -1 && pflVecScreen[1] > -1 && !iResult )
	{
		pflVecScreen[0] = pflVecScreen[0] * ( g_Screen.iWidth / 2 ) + ( g_Screen.iWidth / 2 );
		pflVecScreen[1] = -pflVecScreen[1] * ( g_Screen.iHeight / 2 ) + ( g_Screen.iHeight / 2 );
		return true;
	}

	return false;
}

//-------------------------------------------------------------------//

float CalcDistPlayerScreen( float fScreenCenter[2] , float fPlayerPosScreen[2] )
{
	return ( sqrt( 
		
		POW( fPlayerPosScreen[0] - fScreenCenter[0] ) + 
		
		POW( fPlayerPosScreen[1] - fScreenCenter[1] ) ) );
}

//-------------------------------------------------------------------//

/*
bool CheckFOV(Vector dest, int * iScreen, float fFov)
{
	float fScrPos[2] =
	{
		abs(dest.x - iScreen[0]),
		abs(dest.y - iScreen[1])
	};
	return (fScrPos[0] <= fFov && fScrPos[1] <= fFov);
}

//-------------------------------------------------------------------//

bool CheckFOV(Vector dest, int * iScreen, float fFovX, float fFovY)
{
	float fScrPos[2] =
	{
		abs(dest.x - iScreen[0]),
		abs(dest.y - iScreen[1])
	};
	return (fScrPos[0] <= fFovX && fScrPos[1] <= fFovY);
}*/

//-------------------------------------------------------------------//

/*
void BulletControl_CreateMove( usercmd_s *cmd )
{
	static int SaveICLIP = 0;

	if ( cmd->buttons & IN_ATTACK )
	{
		g_Local.iShotsFired = abs( SaveICLIP - g_Local.iClip );
	}
	else
	{
		SaveICLIP = g_Local.iClip;

		if ( !g_Local.bIsNoShot )
			g_Local.iShotsFired = 0;
	}
}*/

//-------------------------------------------------------------------//


