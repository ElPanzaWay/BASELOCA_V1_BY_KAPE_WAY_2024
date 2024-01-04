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

#pragma comment(lib,"winmm.lib")

#pragma comment(lib,"GLaux.lib")

#pragma comment(lib,"OpenGL32.lib")

#pragma comment(lib,"GLu32.lib")// symbol _gluBuild2DMipmaps@28

//#pragma comment(lib,"GLaux.lib")

//-------------------------------------------------------------------//

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#ifndef __cplusplus
#define __cplusplus
#endif

#ifndef UNICODE
//#define UNICODE
#endif

//-------------------------------------------------------------------//

#include <windows.h>
#include <assert.h>
#include <list> // ->>>> ScheduleList
#include <map> // ->>>> playeritems y stringfinder
#include <math.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include <TLHELP32.H>
#include <vector>

#include <fstream>

using namespace std;

#include <gl\gl.h>
#include <gl\glu.h>
//#include <gl\glut.h>
#include <gl\glaux.h>
//#include "glaux.h"

//-------------------------------------------------------------------//

#include "halflife-master\common\interface.h"
#include "halflife-master\cl_dll\wrect.h"
#include "halflife-master\cl_dll\cl_dll.h"
#include "halflife-master\engine\cdll_int.h"
#include "halflife-master\common\r_studioint.h"
#include "halflife-master\common\com_model.h"
#include "halflife-master\common\cl_entity.h"
#include "halflife-master\common\ref_params.h"
#include "halflife-master\pm_shared\pm_defs.h"
#include "halflife-master\pm_shared\pm_movevars.h"
#include "halflife-master\engine\studio.h"
//#include "halflife-master\parsemsg.h"
#include "parsemsg.h"
#include "halflife-master\common\cvardef.h"
#include "halflife-master\common\triangleapi.h"
#include "halflife-master\common\pmtrace.h"
#include "halflife-master\common\event_api.h"
#include "halflife-master\common\r_efx.h"
#include "halflife-master\common\entity_types.h"
#include "halflife-master\common\screenfade.h"
#include "halflife-master\common\net_api.h"

//#include "halflife-master\common\entity_state.h"

#include "KEYDEFS.h"

#define MAXSTUDIOBONES		128		// total bones actually used
typedef float TransformMatrix[MAXSTUDIOBONES][3][4];

//-------------------------------------------------------------------//

#include "defs.h"

//-------------------------------------------------------------------//

#include "cvars.h"
#include "client.h"
#include "autooffsets.h"
#include "draw.h"
#include "drawtext.h"
#include "steamid.h"
#include "engine.h"
#include "enginestudio.h"
#include "enginemsg.h"
#include "usermsg.h"
#include "recoil.h"
#include "spread.h"
#include "hook.h"

#include "aim.h"
#include "antiaim.h"
#include "aimutils.h"
#include "enginestudiodraw.h"
#include "keyhandling.h"
#include "attackutils.h"
#include "menu_nk.h"
#include "player.h"
#include "ENTS.h"
#include "GUNS.h"
#include "functions.h"
#include "commands.h"
#include "fireevents.h"
#include "soundhack.h"

//-------------------------------------------------------------------//

#include "xorstr.h"

//-------------------------------------------------------------------//

void logme1(const char *fmt, ... );

//-------------------------------------------------------------------//
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























