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

extern int iAimTarget;

//-------------------------------------------------------------------//

void TargetFinder();

void CalculateAimAngles(int iTARGET);
void SetAimAngles1(int iTARGET);
void SetAimAngles2(int iTARGET, struct ref_params_s* pparams);


void CalculateVisibilityAimVector(int px, int iAimvis);

void CalculateAimVectorDraw(int ax);

//-------------------------------------------------------------------//

float * GetAimVector();
float * GetAimAngles();

//-------------------------------------------------------------------//
