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

struct ControlVariables_s CVARS;

//-------------------------------------------------------------------//

void InitControlVariables()
{


	CVARS.hackon=1;
	CVARS.drawon=1;


	CVARS.info=1;
	CVARS.myhud=1;
	CVARS.playername=1;

	CVARS.aim=1;
	CVARS.aimthru=0;
	CVARS.autowall=0;
	CVARS.targetlock=0;
	CVARS.aimdraw=1;


	CVARS.aimvis = 1;
	CVARS.aimingteam = 1;




	CVARS.choppyfire = 1;



	CVARS.ducktargetaim=1;
	CVARS.airtargetaim=1;



	CVARS.shieldattack = 0;


	CVARS.maxscreendist = 20;




	CVARS.origin_f = 0;
	CVARS.origin_r = 0;
	CVARS.origin_h = 0;//3



	CVARS.duck_h_correction = 0;
	CVARS.stand_h_correction = 0;
	CVARS.frozen_correction = 0;



	CVARS.updateframes = 2;



	CVARS.no_visual_recoil = 1;
	CVARS.no_weapon_recoil = 1;


	CVARS.recoilvalue = 2;



	CVARS.nospread = 1;

	CVARS.fixmove = 0;



	CVARS.smoothvalue = 1;

	CVARS.testdynamics=0;
	CVARS.removebobbing=0;
	CVARS.allowbobbing=0;


	CVARS.menukey=147;

	CVARS.menu_cat2_sub1=69;
	CVARS.menu_cat2_sub2=50;//126
	CVARS.menu_cat2_sub3=201;//181
	CVARS.menu_cat2_sub4=18;
	CVARS.menu_cat2_sub5=-1;
	CVARS.menu_cat2_sub6=0;
	CVARS.menu_cat2_sub7=0;
	CVARS.menu_cat2_sub8=0;
	CVARS.menu_cat2_sub9=0;

	CVARS.menu_cat3_sub1=0.00f;
	CVARS.menu_cat3_sub2=0.00f;
	CVARS.menu_cat3_sub3=255.00f;
	CVARS.menu_cat3_sub4=255.00f;

	CVARS.menutitle1=0.00;
	CVARS.menutitle2=0.00;
	CVARS.menutitle3=0.00;
	CVARS.menutitle4=0.00;
	CVARS.menutitle5=0.00;
	CVARS.menutitle6=0.00;
	CVARS.menutitle7=0.00;
	CVARS.menutitle8=0.00;
	CVARS.menutitle9=0.00;
	CVARS.menutitle10=0.00;


	CVARS.dummy=0;


	CVARS.testx1=0;
	CVARS.testx2=0;
	CVARS.testx3=0;
	CVARS.testx4=0;

}

//-------------------------------------------------------------------//













