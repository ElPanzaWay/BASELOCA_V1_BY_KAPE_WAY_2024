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

struct Player_s
{

	bool alive;
	int team;
	int index;

	int health;

	float entorg[3];
	float visibility_aimvec[3];



	float entangles[3];



	float distance;



	bool visible;

	bool updatedbyentity;
	int updateframes;



	bool frozen;
	bool ducked;

};

//-------------------------------------------------------------------//

struct PlayerLocale_s
{
	bool alive;
	int team;
	int index;

	int health;


	float eyeposition[3];


	float viewangles[3];



	int weaponid;
	int clip;



	bool frozen;
	bool ducked;



	float punchangles[3];

	bool inzoom;


	struct spread_info spread;


};

//-------------------------------------------------------------------//

extern struct Player_s Players[33];
extern struct PlayerLocale_s PlayerLocale;

//-------------------------------------------------------------------//

void InitPlayers();
void UpdatePlayers();
void ClearUpdatePlayers();
void DrawPlayerESP();

void InitPlayerLocale();
void UpdatePlayerLocale();
void DrawInfo();

//-------------------------------------------------------------------//

bool GetAimingTeam(unsigned int ax);

float * GetMyViewPoint();
float * GetMyViewAngles();

//-------------------------------------------------------------------//



















