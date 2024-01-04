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

/*
enum ENoSpread
{
	NOSPREAD_NONE,
	NOSPREAD_PITCH_YAW,
	NOSPREAD_PITCH_ROLL,
	NOSPREAD_PITCH_YAW_ROLL
};*/

//-------------------------------------------------------------------//

struct spread_info
{
	unsigned int random_seed;
	int recoil;// m_iShotsFired
	float gtime;// curtime
	float prevtime;
	float brokentime; // This is only supposed to be set to zero when you buy the sg550 or the g3sg1
					  // not when you reload, switch weapons or pick up a weapon, this is do to the
					  // cs bugs for these guns (valve fix your code please)
	float spreadvar;
	float recoiltime;// m_flDecreaseShotsFired
	bool firing;// m_bDelayFire
	int WeaponState;
	int prcflags;

	//

	float vecspread;

	//

//	float flLastSG550SpreadVar;
	float flNextPrimaryAttack;
	float flNextSecondaryAttack;

	int iInReload;
	float flNextAttack;

//	int iWeaponBit;// weaponstate
//	int iBurst;
};

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

void InitSpreadData();

/*
float cNoSpread4::GetSpreadFactor(float flSpeed)
{
	// when i am not attacking i set default spreadvar
	// for attack time is set in priattack and events after shot.. 
	if (cvar.aim_spreadvar == 1  && !me.attacking) 
	{
		// this function supports c4 and nates
	    me.spread.spreadvar = GetWeaponSpreadVar();

		// not calc weaponbit for c4 or nates, also the wav table doesnt support them
		if(!curC4orNate() && WeaponID != WEAPONLIST_KNIFE)
		{
		   dwBaseGun = *(PDWORD)(GetBaseGun());
		   me.spread.WeaponState = *(int*)(dwBaseGun + 0x128);
		}
	}*/


//-------------------------------------------------------------------//

/*
void GetSpreadXY(const unsigned& random_seed, const int& future, Vector& vecSpread);
void GetSpreadOffset(const unsigned& random_seed, const int& future, const QAngle& QInAngles, QAngle& QOutAngles, const int& type = NOSPREAD_PITCH_YAW_ROLL);
double GetConstantRemainder(const Vector& vecSpread);
*/



