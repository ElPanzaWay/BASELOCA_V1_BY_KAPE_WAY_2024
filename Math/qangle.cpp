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

//#include "client_headers.h"
#define IM_PI           3.14159265358979323846f

#include <assert.h>

#include <math.h> // #define isfinite(arg) since 99
#include <float.h>


#define RAD2DEG(x) ((float)(x) * (float)(180.f / IM_PI))
#define DEG2RAD(x) ((float)(x) * (float)(IM_PI / 180.f))

/*
#include <cfloat>
#include <cmath>
#include <iostream>
*/

#include "vector.h"
#include "qangle.h"
#include "matrix3x4.h"
//using namespace std;

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

void QAngle::AngleVectors(Vector* Forward, Vector* Right, Vector* Up)
{
	float radx = x * (IM_PI * 2.f / 360.f);
	float rady = y * (IM_PI * 2.f / 360.f);
	float radz = z * (IM_PI * 2.f / 360.f);

	float sp = sin(radx);
	float sy = sin(rady);
	float sr = sin(radz);

	float cp = cos(radx);
	float cy = cos(rady);
	float cr = cos(radz);

	if (Forward) 
	{
		Forward->x = cp * cy;
		Forward->y = cp * sy;
		Forward->z = -sp;
	}

	if (Right) 
	{
		Right->x = -1.f * sr * sp * cy + -1.f * cr * -sy;
		Right->y = -1.f * sr * sp * sy + -1.f * cr * cy;
		Right->z = -1.f * sr * cp;
	}

	if (Up) 
	{
		Up->x = cr * sp * cy + -sr * -sy;
		Up->y = cr * sp * sy + -sr * cy;
		Up->z = cr * cp;
	}
}

//-------------------------------------------------------------------//

void QAngle::AngleVectorsTranspose(Vector* Forward, Vector* Right, Vector* Up)
{
	float radx = x * (IM_PI * 2.f / 360.f);
	float rady = y * (IM_PI * 2.f / 360.f);
	float radz = z * (IM_PI * 2.f / 360.f);

	float sp = sin(radx);
	float sy = sin(rady);
	float sr = sin(radz);

	float cp = cos(radx);
	float cy = cos(rady);
	float cr = cos(radz);

	if (Forward) 
	{
		Forward->x = cp * cy;
		Forward->y = sr * sp * cy + cr * -sy;
		Forward->z = cr * sp * cy + -sr * -sy;
	}

	if (Right) 
	{
		Right->x = cp * sy;
		Right->y = sr * sp * sy + cr * cy;
		Right->z = cr * sp * sy + -sr * cy;
	}

	if (Up) 
	{
		Up->x = -sp;
		Up->y = sr * cp;
		Up->z = cr * cp;
	}
}

//-------------------------------------------------------------------//

