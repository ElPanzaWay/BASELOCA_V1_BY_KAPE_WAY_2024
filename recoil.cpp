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

/*
QAngles[0] += client_state->punchangle[0] * 2.f;
QAngles[1] += client_state->punchangle[1] * 2.f;
*/

//-------------------------------------------------------------------//

/*
void Event_m4a1(struct event_args_s *args)
{
	//float spread[2], x, y;
	//char buffer[256];
 
	if (args->entindex == me.ent->index)
	{
		sprintf(buffer, "Start m4a1 shot number %d", me.recoil);
		outstream << buffer << std::endl;
 
		sprintf(buffer, "hl angles: %f %f", args->angles[0], args->angles[1]);
		outstream << buffer << std::endl;
 
		sprintf(buffer, "me angles: %f %f", me.Angles[0], me.Angles[1]);
		outstream << buffer << std::endl;
 
		sprintf(buffer, "hl origin: %f %f", args->origin[0], args->origin[1], args->origin[2]);
		outstream << buffer << std::endl;
 
		sprintf(buffer, "me origin: %f %f", me.Origin[0], me.Origin[1], me.Origin[2]);
		outstream << buffer << std::endl;
 
		sprintf(buffer, "hl velocity: %f %f %f", args->velocity[0], args->velocity[1], args->velocity[2]);
		outstream << buffer << std::endl;
 
		sprintf(buffer, "me velocity: %f %f %f", me.Velocity[0], me.Velocity[1], me.Velocity[2]);
		outstream << buffer << std::endl;
 
		sprintf(buffer, "hl pungle: %f %f", (float)args->iparam1 / 100.0, (float)args->iparam2 / 100.0);
		outstream << buffer << std::endl;
 
		sprintf(buffer, "me pungle: %f %f", me.PunchAngle[0], me.PunchAngle[1]);
		outstream << buffer << std::endl;
 
		sprintf(buffer, "hl spread: %f %f", args->fparam1, args->fparam2);
		outstream << buffer << std::endl;
 
		GetSpreadXY(me.random_seed, 0, me.Velocity, spread);
 
		sprintf(buffer, "me spread: %f %f", spread[0], spread[1]);
		outstream << buffer << std::endl;
 
		x = UTIL_SharedRandomFloat(me.random_seed, -0.5, 0.5) + UTIL_SharedRandomFloat(me.random_seed + 1, -0.5, 0.5);
		y = UTIL_SharedRandomFloat(me.random_seed + 2, -0.5, 0.5) + UTIL_SharedRandomFloat(me.random_seed + 3, -0.5, 0.5);
 
		sprintf(buffer, "vec: %f %f", args->fparam1 / x, args->fparam2 / y);
		outstream << buffer << std::endl;
 
		sprintf(buffer, "End m4a1 shot number %d", me.recoil);
		outstream << buffer << std::endl;

		//

		me.spread.recoil++;
		me.spread.firing = true;
		
		me.spread.spreadvar = me.spread.recoil * me.spread.recoil * me.spread.recoil / 220 + 0.3;
 
		if (me.spread.spreadvar > 1)
			me.spread.spreadvar = 1.0f;
 
		me.spread.prevtime = me.spread.gtime;
	}
 
	m4a1Org(args);
}*/

//-------------------------------------------------------------------//

/*
//#include <fstream>
//std::ofstream outstream("D:\\jumpshootdebug.txt");
void PlaybackEvent(int flags, const edict_t *pInvoker, unsigned short eventindex, float delay, 
				   float *origin, float *angles, 
				   float fparam1, float fparam2, int iparam1, int iparam2, int bparam1, int bparam2)
{
	float x, y;
	char buffer[256];
 
	outstream << "Start shot" << std::endl;
 
	sprintf(buffer, "hl pungle: %f %f", (float)iparam1 / 100.0, (float)iparam2 / 100.0);
	outstream << buffer << std::endl;
 
	sprintf(buffer, "hl spread: %f %f", fparam1, fparam2);
	outstream << buffer << std::endl;
 
	x = UTIL_SharedRandomFloat(me.random_seed + 1, -0.5, 0.5) + UTIL_SharedRandomFloat(me.random_seed + 2, -0.5, 0.5);
	y = UTIL_SharedRandomFloat(me.random_seed + 3, -0.5, 0.5) + UTIL_SharedRandomFloat(me.random_seed + 4, -0.5, 0.5);
 
	sprintf(buffer, "vec: %f %f", x, y);
	outstream << buffer << std::endl;
 
	outstream << "End shot" << std::endl;

	gEngfuncs.pfnPlaybackEvent(flags, pInvoker, eventindex, delay, origin, angles, fparam1, fparam2, iparam1, iparam2, bparam1, bparam2);
}*/

//-------------------------------------------------------------------//


