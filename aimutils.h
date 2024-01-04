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

void VectorAngles (const float * forward, float * angles);
void AngleVectors(const float *angles, float *forward, float *right, float *up);
int CanPenetrate (float * start, float * end, int power);
int PathFree (float * from, float * to);
int PathFree2 (float * from, float * to);

//-------------------------------------------------------------------//

/*
Well, the flag is what matters here.

PM_WORLD_ONLY and PM_GLASS_IGNORE is keyword here.

Code:
#define PM_GLASS_IGNORE	0x00000004	// Ignore entities with non-normal rendermode
#define PM_WORLD_ONLY	0x00000008	// Only trace against the world

if bypass is on and tr.fraction == 1 && detection returns false it means that 
it hit a player's hitbox so it will force the player to visible, and mark the hitbox for shooting.

if bypass is off and detection returns true (aka no server side funny anti cheat feature), 
then it'll also mark the hitbox for shooting.

the big factor is also the flag, when the server changes the player's rendering flags 
to throw off your internal hack, you need to think outside the box sorta (not rocket science) 
to reliably tell apart the players from map objects, obviously if you trace a valid part of the world 
in one trace then it'll return true, and the tr.fraction will be 1, but if tr.fraction is 1 and 
it didn't hit the "world" then it means you hit the player obviously.

Honestly this could be written a bit more simple/cleaner but it's pretty ok.
*/

/*
fraction = 1 means we actually hit something, doesn't matter if the trace returns false or true.

BYPASS: OFF = trace.fraction equals to 1, PM_GLASS_IGNORE (server ac feature off) -> detect = true 
so the vanilla way of tracing works, if detect = false it means we hit something before the player.

BYPASS: ON = trace.fration equals to 1, PM_WORLD_ONLY (server ac feature on) -> detect = false 
so it means we hit a player, if detect = true it means we hit something before the player.
*/

/*
pmtrace_t tr;
	int detect = 0;
 
	for (auto&& hitbox : Hitboxes)
	{
		g_Engine.pEventAPI->EV_SetTraceHull(2);
 
		if (cvar.bypass_trace_blockers)
			g_Engine.pEventAPI->EV_PlayerTrace(g_Local.vEye, g_PlayerExtraInfoList[i].vHitbox[hitbox], PM_WORLD_ONLY, -1, &tr);
		else
			g_Engine.pEventAPI->EV_PlayerTrace(g_Local.vEye, g_PlayerExtraInfoList[i].vHitbox[hitbox], PM_GLASS_IGNORE, -1, &tr);
 
		detect = g_Engine.pEventAPI->EV_IndexFromTrace(&tr);
 
		if ((cvar.bypass_trace_blockers && tr.fraction == 1 && !detect) || (!cvar.bypass_trace_blockers && detect == i))
		{
			g_Player[i].bVisible = true;
			g_PlayerExtraInfoList[i].bHitboxVisible[hitbox] = true;
		}
		else
		{
			g_PlayerExtraInfoList[i].bHitboxVisible[hitbox] = false;
 
			int iOriginalPenetration = CurPenetration();
 
			if (iOriginalPenetration && walls)
			{
				int iDamage = CurDamage();
				int iBulletType = CurBulletType();
				float flDistance = CurDistance();
				float flRangeModifier = CurWallPierce();
 
				int iCurrentDamage = FireBullets(g_Local.vEye, g_PlayerExtraInfoList[i].vHitbox[hitbox], flDistance, iOriginalPenetration, iBulletType, iDamage, flRangeModifier);
 
				if (iCurrentDamage > 0)
				{
					g_Player[i].bVisible = true;
					g_PlayerExtraInfoList[i].bHitboxVisible[hitbox] = true;
				}
			}
		}*/