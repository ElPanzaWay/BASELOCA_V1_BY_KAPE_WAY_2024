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

struct ControlVariables_s
{

	int hackon;
	int drawon;

	int info;
	int myhud;
	int playername;

	int aim;
	int aimthru;
	int autowall;
	int targetlock;
	int aimdraw;



	int aimvis;
	int aimingteam;


	int choppyfire;

	int ducktargetaim;
	int airtargetaim;



	int shieldattack;

	float maxscreendist;




	float origin_f;
	float origin_r;
	float origin_h;



	float duck_h_correction;
	float stand_h_correction;
	float frozen_correction;


	int updateframes;



	int no_visual_recoil;
	int no_weapon_recoil;

	float recoilvalue;


	int nospread;

	int fixmove;


	int smoothvalue;

	int testdynamics;
	int removebobbing;
	int allowbobbing;


	int menukey;

	int menu_cat2_sub1;
	int menu_cat2_sub2;
	int menu_cat2_sub3;
	int menu_cat2_sub4;
	int menu_cat2_sub5;
	int menu_cat2_sub6;
	int menu_cat2_sub7;
	int menu_cat2_sub8;
	int menu_cat2_sub9;
	int menu_cat2_sub10;

	float menu_cat3_sub1;
	float menu_cat3_sub2;
	float menu_cat3_sub3;
	float menu_cat3_sub4;


	float menutitle1;
	float menutitle2;
	float menutitle3;
	float menutitle4;
	float menutitle5;
	float menutitle6;
	float menutitle7;
	float menutitle8;
	float menutitle9;
	float menutitle10;


	int dummy;

	int testx1;
	int testx2;
	int testx3;
	int testx4;

};

//-------------------------------------------------------------------//

extern struct ControlVariables_s CVARS;

//-------------------------------------------------------------------//

void InitControlVariables();

//-------------------------------------------------------------------//
