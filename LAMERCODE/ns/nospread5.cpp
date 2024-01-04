//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

#include "includes.h"

//-------------------------------------------------------------------//

float vNoSpreadAngle[3]={0,0,0};

//-------------------------------------------------------------------//

void NA_GetSpreadXY(unsigned int seed, int future, float *vec, bool simulate)
{
	vec[0] = UTIL_SharedRandomFloat(seed + future, -0.5, 0.5) + UTIL_SharedRandomFloat(seed + 1 + future, -0.5, 0.5);
	vec[1] = UTIL_SharedRandomFloat(seed + 2 + future, -0.5, 0.5) + UTIL_SharedRandomFloat(seed + 3 + future, -0.5, 0.5);

	if (!simulate){
		vec[0] *= me.myweapon.m_flSpread;
		vec[1] *= me.myweapon.m_flSpread;
	} else {
		float m_flAccuracy, m_flSpread;
		Simulate(m_flAccuracy, m_flSpread);
		vec[0] *= m_flSpread;
		vec[1] *= m_flSpread;
	}
}

//-------------------------------------------------------------------//

void NA_GetSpreadOffset(unsigned int seed, int future, float *inangles, float *outangles)
{
	if (cvar.rage_nospread_method == 0)
	{
		double PitchSine=0, PitchCosine=0;
		double CosineInput=0, CosinePitch=0, PitchInput=0;
		double ReciprocalYaw_1=0, ReciprocalYaw_2=0, UpVal=0, Yaw_1=0;

		QAngle QAdjusterAngles, QAngles, QInputAngles, QInputRoll, QNewAngles, QTestAngles, QOldAngles;

		NewVector Dir, Forward, Right, Up;
		NewVector ReciprocalVector, InputRight, InputRight2;

		NewVector Spread;

		NewVector UnRotatedPitch, RotatedPitch;

		NA_GetSpreadXY(seed, future, Spread);

		QAngles = (QAngle)0;

		QAngles.AngleVectors(&Forward, &Right, &Up);

		Dir = Forward + (-Spread[0] * Right) + (-Spread[1] * Up);

		Dir.Normalize();

		QAngles.Init(inangles);

		QOldAngles = QAngles;

		QAngles = Dir.ToEulerAngles();

		QAngles.Normalize();

		QAngles.AngleVectors(&Forward, &Right, &Up);

		UpVal = Up[2];

		QAngles = QOldAngles;

		CosineInput = QAngles[0] * (M_PI * 2 / 360);

		CosinePitch = cos(CosineInput);

		if (CosinePitch != 0)
		{
			Yaw_1 = 1 / CosinePitch;
		}
		else
		{
			Yaw_1 = 0;
		}

		Yaw_1 *= Dir[1];

		InputRight[1] = Yaw_1;

		if (Yaw_1 >= 1 || Yaw_1 <= -1)
		{
			InputRight[1] = 1 / Yaw_1;

			InputRight[0] = 0;
		}
		else
		{
			InputRight[0] = sqrt((1 - (InputRight[1] * InputRight[1])));
		}

		InputRight[2] = 0;

		QAdjusterAngles[1] = (RAD2DEG(atan2(InputRight[1], InputRight[0])));

		QAdjusterAngles.Normalize();

		InputRight2[1] = Dir[1];

		if (Dir[1] >= 1 || Dir[1] <= -1)
		{
			InputRight2[1] = 1 / Dir[1];

			InputRight2[0] = 0;
		}
		else
		{
			InputRight2[0] = sqrt((1 - (InputRight2[1] * InputRight2[1])));
		}

		if (InputRight[0] != 0)
		{
			ReciprocalYaw_1 = InputRight[1] / InputRight[0];
		}
		else
		{
			ReciprocalYaw_1 = 0;
		}

		if (InputRight2[0] != 0)
		{
			ReciprocalYaw_2 = InputRight2[1] / InputRight2[0];
		}
		else
		{
			ReciprocalYaw_2 = 0;
		}

		PitchInput = 0;

		if (QAngles[0] != 0)
		{
			if (ReciprocalYaw_1 != 0 && ReciprocalYaw_2 != 0)
			{
				PitchInput = 1;

				if (abs(ReciprocalYaw_1) < abs(ReciprocalYaw_2))
				{
					PitchInput = ReciprocalYaw_1 / ReciprocalYaw_2;
				}
				else if (abs(ReciprocalYaw_2) < abs(ReciprocalYaw_1))
				{
					PitchInput = ReciprocalYaw_2 / ReciprocalYaw_1;
				}
			}
		}
		else
		{
			PitchInput = 1;
		}

		QInputAngles = (QAngle)0;

		if (PitchInput > 1 && PitchInput < -1)
		{
			PitchCosine = PitchInput;
			PitchSine = sqrt(1 - PitchInput * PitchInput);

			UnRotatedPitch[0] = PitchSine;
			UnRotatedPitch[1] = PitchCosine;
			UnRotatedPitch[2] = 0;

			double TempPitch = QAngles[0];

			if (TempPitch < 0)
			{
				TempPitch = -TempPitch;
			}

			TempPitch = ((45 - TempPitch) * 2);

			RotatedPitch.VectorRotate(UnRotatedPitch, QAngle(0, TempPitch, 0));

			if (QAngles[0] < 0)
			{
				QInputAngles[0] = RAD2DEG(atan2(RotatedPitch[1], RotatedPitch[0]));
			}
			else
			{
				QInputAngles[0] = RAD2DEG(atan2(-RotatedPitch[1], RotatedPitch[0]));
			}
		}

		QInputAngles.Normalize();

		QInputAngles.AngleVectors(&Forward, &Right, &Up);

		Dir = Forward + (Spread[0] * Right) + (Spread[1] * Up);

		Dir.Normalize();

		QAdjusterAngles[0] = QAngles[0] + (RAD2DEG(atan2(Dir[2], Dir[0])));

		QAdjusterAngles.Normalize();

		QNewAngles = QOldAngles;

		QNewAngles[0] = QAdjusterAngles[0];
		QNewAngles[1] += QAdjusterAngles[1];
		QNewAngles[2] = 0;

		QNewAngles.Normalize();

		for (unsigned int Iterator = 0; Iterator < 5; Iterator++)
		{
			QNewAngles.AngleVectors(&Forward, &Right, &Up);

			Dir = Forward + (Spread[0] * Right) + (Spread[1] * Up);

			Dir.Normalize();

			QTestAngles = Dir.ToEulerAngles();

			QTestAngles.Normalize();

			QNewAngles[0] += (QAngles[0] - QTestAngles[0]);
			QNewAngles[1] += (QAngles[1] - QTestAngles[1]);

			QNewAngles.Normalize();
		}

		outangles[0] = QNewAngles[0];
		outangles[1] = QNewAngles[1];
		outangles[2] = QNewAngles[2];
	}
	else
	{
		NewVector vecForward, vecRight, vecUp, vecDir, vecRandom;

		QAngle QAngles, QNewAngles, QTempAngles;

		NA_GetSpreadXY(seed, future, vecRandom);

		QAngles = inangles;

		QTempAngles = (QAngle)0;

		QTempAngles.AngleVectors(&vecForward, &vecRight, &vecUp);

		vecDir = vecForward + (vecRight * vecRandom[0]) + (vecUp * vecRandom[1]);

		vecDir.Normalize();

		QNewAngles = vecDir.ToEulerAngles();

		QNewAngles[0] -= QAngles[0];

		QNewAngles.Normalize();

		QNewAngles.AngleVectorsTranspose(&vecForward, &vecRight, &vecUp);

		vecDir = vecForward;

		QNewAngles = vecDir.ToEulerAngles(&vecUp);

		QNewAngles.Normalize();

		QNewAngles[1] += QAngles[1];

		QNewAngles.Normalize();

		outangles[0] = QNewAngles[0];
		outangles[1] = QNewAngles[1];
		outangles[2] = 0;
	}
}

//-------------------------------------------------------------------//

float forwardmove, sidemove, upmove;//backup for fixmove
NewVector vViewForward, vViewRight, vViewUp, vAimForward, vAimRight, vAimUp;//backup for fixmove

void NA_FixMoveStart(struct usercmd_s *cmd)
{
	forwardmove = cmd->forwardmove;
	sidemove = cmd->sidemove;
	upmove = cmd->upmove;

	if (g_ppmove->movetype == MOVETYPE_WALK)
		gEngfuncs.pfnAngleVectors(Vector(0.0f, cmd->viewangles.y, 0.0f), vViewForward, vViewRight, vViewUp);
	else
		gEngfuncs.pfnAngleVectors(cmd->viewangles, vViewForward, vViewRight, vViewUp);
}

//-------------------------------------------------------------------//

// avoid all library calls
// Relies on UINTMAX_MAX >= FLT_MAX_CONTINUOUS_INTEGER - 1
float my_roundf(float x)
{
	// Test for large values of x 
	// All of the x values are whole numbers and need no rounding
 
#define FLT_MAX_CONTINUOUS_INTEGER  (FLT_RADIX/FLT_EPSILON)
	if (x >= FLT_MAX_CONTINUOUS_INTEGER) return x;
	if (x <= -FLT_MAX_CONTINUOUS_INTEGER) return x;
  
	// Positive numbers
	// Important: _no_ precision lost in the subtraction
	// This is the key improvement over OP's method
	if (x > 0)
	{
		float floor_x = (float)(unsigned int) x;
		if (x - floor_x >= 0.5)
		{
			floor_x += 1.0f;
		}
		return floor_x;
	}

	if (x < 0) return - my_roundf(-x);
	return x; //  x is 0.0, -0.0 or NaN
}

//-------------------------------------------------------------------//

void NA_NormalizeAngles(float *angles)
{
	for (unsigned int i = 0; i < 3; ++i)
	{
		float flRevolutions = angles[i] / 360;

		if (angles[i] > 180 || angles[i] < -180)
		{
			if (flRevolutions < 0)
			{
				flRevolutions = -flRevolutions;
			}

		//	flRevolutions = round(flRevolutions);
			flRevolutions = my_roundf(flRevolutions);

			if (angles[i] < 0)
			{
				angles[i] = (angles[i] + 360 * flRevolutions);
			}
			else
			{
				angles[i] = (angles[i] - 360 * flRevolutions);
			}
		}
	}
}

//-------------------------------------------------------------------//

void NA_VectorAngles(const float *forward, float *angles)
{
	float tmp = 0, yaw = 0, pitch = 0;

	if (forward[1] == 0 && forward[0] == 0)
	{
		yaw = 0;
		if (forward[2] > 0)
			pitch = 270;
		else
			pitch = 90;
	}
	else
	{
		yaw = (atan2(forward[1], forward[0]) * 180 / M_PI);
		if (yaw < 0)
			yaw += 360;

		tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = (atan2(-forward[2], tmp) * 180 / M_PI);
		if (pitch < 0)
			pitch += 360;
	}

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;

	while (angles[0] < -89) { angles[0] += 180; angles[1] += 180; }
	while (angles[0] > 89) { angles[0] -= 180; angles[1] += 180; }
	while (angles[1] < -180) { angles[1] += 360; }
	while (angles[1] > 180) { angles[1] -= 360; }
}

//-------------------------------------------------------------------//

void NA_FixMoveEnd(struct usercmd_s *cmd)
{
	NA_NormalizeAngles(cmd->viewangles);

	if (g_ppmove->movetype == MOVETYPE_WALK)
		gEngfuncs.pfnAngleVectors(Vector(0.0f, cmd->viewangles.y, 0.0f), vAimForward, vAimRight, vAimUp);
	else
		gEngfuncs.pfnAngleVectors(cmd->viewangles, vAimForward, vAimRight, vAimUp);

	NewVector forwardmove_normalized = forwardmove * vViewForward;
	NewVector sidemove_normalized = sidemove * vViewRight;
	NewVector upmove_normalized = upmove * vViewUp;

	cmd->forwardmove = forwardmove_normalized.Dot(vAimForward) + sidemove_normalized.Dot(vAimForward) + upmove_normalized.Dot(vAimForward);
	cmd->sidemove = forwardmove_normalized.Dot(vAimRight) + sidemove_normalized.Dot(vAimRight) + upmove_normalized.Dot(vAimRight);
	cmd->upmove = forwardmove_normalized.Dot(vAimUp) + sidemove_normalized.Dot(vAimUp) + upmove_normalized.Dot(vAimUp);

	NewVector vMove(cmd->forwardmove, cmd->sidemove, cmd->upmove);
	float flSpeed = sqrt(vMove.x * vMove.x + vMove.y * vMove.y), flYaw;
	Vector vecMove, vecRealView(cmd->viewangles);
	NA_VectorAngles(vMove, vecMove);
	flYaw = (cmd->viewangles.y - vecRealView.y + vecMove.y) * M_PI / 180.0f;

	cmd->forwardmove = cos(flYaw) * flSpeed;

	if (cmd->viewangles.x >= 90 || cmd->viewangles.x <= -90)
		cmd->forwardmove *= -1;

	cmd->sidemove = sin(flYaw) * flSpeed;
}

//-------------------------------------------------------------------//

void NA_MakeAngle(float *angles, struct usercmd_s *cmd)
{
	NA_FixMoveStart(cmd);

	cmd->viewangles[0] = angles[0];
	cmd->viewangles[1] = angles[1];
	cmd->viewangles[2] = angles[2];

	NA_FixMoveEnd(cmd);
}

//-------------------------------------------------------------------//

void NA_NoSpread(usercmd_s *cmd)
{
	if (me.alive && IsCurWeaponGun() && cmd->buttons & IN_ATTACK && CanAttack())
	{
		NewVector vAngles;
		NA_GetSpreadOffset(me.myweapon.random_seed, 1, cmd->viewangles, vAngles);
		
	//	vNoSpreadAngle = cmd->viewangles - vAngles;
		vNoSpreadAngle[0] = (cmd->viewangles.x - vAngles.x);
		vNoSpreadAngle[1] = (cmd->viewangles.y - vAngles.y);
		vNoSpreadAngle[2] = (cmd->viewangles.z - vAngles.z);

		if (cvar.rage_active)
		{
			NA_MakeAngle(vAngles, cmd);
		}
	}
}

//-------------------------------------------------------------------//

//rage_nospread_method
//rage_active

//-------------------------------------------------------------------//




