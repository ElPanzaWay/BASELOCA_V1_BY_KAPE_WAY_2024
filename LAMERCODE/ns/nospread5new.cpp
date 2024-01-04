//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

#include "includes.h"

//-------------------------------------------------------------------//

float vNoSpreadAngle[3]={0,0,0};

//-------------------------------------------------------------------//

void NA_UpdateWeaponData()
{
	if (me.alive)
	{
		switch (me.weaponid)
		{

		case WEAPONLIST_DEAGLE:
			if (!(me.spread.prcflags & FL_ONGROUND))
				me.spread.vecspread = 1.5 * (1 - me.spread.spreadvar);
			else if (g_ppmove->velocity.Length2D() > 0)
				me.spread.vecspread = 0.25 * (1 - me.spread.spreadvar);
			else if (me.spread.prcflags & FL_DUCKING)
				me.spread.vecspread = 0.115 * (1 - me.spread.spreadvar);
			else
				me.spread.vecspread = 0.13 * (1 - me.spread.spreadvar);
			break;


		case WEAPONLIST_GLOCK18:

			if ((me.spread.WeaponState & GLOCK18_BURST))
		//	if (IsCurWeaponInBurst())
			{
				if (!(me.spread.prcflags & FL_ONGROUND))
					me.spread.vecspread = 1.2 * (1 - me.spread.spreadvar);
				else if (g_ppmove->velocity.Length2D() > 0)
					me.spread.vecspread = 0.185 * (1 - me.spread.spreadvar);
				else if (me.spread.prcflags & FL_DUCKING)
					me.spread.vecspread = 0.095 * (1 - me.spread.spreadvar);
				else
					me.spread.vecspread = 0.3 * (1 - me.spread.spreadvar);
			}
			else
			{
				if (!(me.spread.prcflags & FL_ONGROUND))
					me.spread.vecspread = 1.0 * (1 - me.spread.spreadvar);
				else if (g_ppmove->velocity.Length2D() > 0)
					me.spread.vecspread = 0.165 * (1 - me.spread.spreadvar);
				else if (me.spread.prcflags & FL_DUCKING)
					me.spread.vecspread = 0.075 * (1 - me.spread.spreadvar);
				else
					me.spread.vecspread = 0.1 * (1 - me.spread.spreadvar);
			}
			break;


		case WEAPONLIST_USP:


			if ((me.spread.WeaponState & USP_SILENCER))
		//	if (IsCurWeaponSilenced())
			{
				if (!(me.spread.prcflags & FL_ONGROUND))
					me.spread.vecspread = 1.3 * (1 - me.spread.spreadvar);
				else if (g_ppmove->velocity.Length2D() > 0)
					me.spread.vecspread = 0.25 * (1 - me.spread.spreadvar);
				else if (me.spread.prcflags & FL_DUCKING)
					me.spread.vecspread = 0.125 * (1 - me.spread.spreadvar);
				else
					me.spread.vecspread = 0.15 * (1 - me.spread.spreadvar);
			}
			else
			{
				if (!(me.spread.prcflags & FL_ONGROUND))
					me.spread.vecspread = 1.2 * (1 - me.spread.spreadvar);
				else if (g_ppmove->velocity.Length2D() > 0)
					me.spread.vecspread = 0.225 * (1 - me.spread.spreadvar);
				else if (me.spread.prcflags & FL_DUCKING)
					me.spread.vecspread = 0.08 * (1 - me.spread.spreadvar);
				else
					me.spread.vecspread = 0.1 * (1 - me.spread.spreadvar);
			}
			break;


		case WEAPONLIST_P228:
			if (!(me.spread.prcflags & FL_ONGROUND))
				me.spread.vecspread = 1.5 * (1 - me.spread.spreadvar);
			else if (g_ppmove->velocity.Length2D() > 0)
				me.spread.vecspread = 0.255 * (1 - me.spread.spreadvar);
			else if (me.spread.prcflags & FL_DUCKING)
				me.spread.vecspread = 0.075 * (1 - me.spread.spreadvar);
			else
				me.spread.vecspread = 0.15 * (1 - me.spread.spreadvar);
			break;


		case WEAPONLIST_FIVESEVEN:
			if (!(me.spread.prcflags & FL_ONGROUND))
				me.spread.vecspread = 1.5 * (1 - me.spread.spreadvar);
			else if (g_ppmove->velocity.Length2D() > 0)
				me.spread.vecspread = 0.255 * (1 - me.spread.spreadvar);
			else if (me.spread.prcflags & FL_DUCKING)
				me.spread.vecspread = 0.075 * (1 - me.spread.spreadvar);
			else
				me.spread.vecspread = 0.15 * (1 - me.spread.spreadvar);
			break;


		case WEAPONLIST_ELITE:
			if (!(me.spread.prcflags & FL_ONGROUND))
				me.spread.vecspread = 1.3 * (1 - me.spread.spreadvar);
			else if (g_ppmove->velocity.Length2D() > 0)
				me.spread.vecspread = 0.175 * (1 - me.spread.spreadvar);
			else if (me.spread.prcflags & FL_DUCKING)
				me.spread.vecspread = 0.08 * (1 - me.spread.spreadvar);
			else
				me.spread.vecspread = 0.1 * (1 - me.spread.spreadvar);
			break;

		//

		case WEAPONLIST_AWP:
			if (!(me.spread.prcflags & FL_ONGROUND))
				me.spread.vecspread = 0.85;
			else if (g_ppmove->velocity.Length2D() > 140)
				me.spread.vecspread = 0.25;
			else if (g_ppmove->velocity.Length2D() > 10)
				me.spread.vecspread = 0.1;
			else if (me.spread.prcflags & FL_DUCKING)
				me.spread.vecspread = 0.0;
			else
				me.spread.vecspread = 0.001;

			if (me.fov == 90)
				me.spread.vecspread += 0.08f;
			break;

		case WEAPONLIST_SCOUT:
			if (!(me.spread.prcflags & FL_ONGROUND))
				me.spread.vecspread = 0.2;
			else if (g_ppmove->velocity.Length2D() > 170)
				me.spread.vecspread = 0.075;
			else if (me.spread.prcflags & FL_DUCKING)
				me.spread.vecspread = 0;
			else
				me.spread.vecspread = 0.007;

			if (me.fov == 90)
				me.spread.vecspread += 0.025f;
			break;

		case WEAPONLIST_G3SG1:
			if (!(me.spread.prcflags & FL_ONGROUND))
				me.spread.vecspread = 0.45;
			else if (g_ppmove->velocity.Length2D() > 0)
				me.spread.vecspread = 0.15;
			else if (me.spread.prcflags & FL_DUCKING)
				me.spread.vecspread = 0.035;
			else
				me.spread.vecspread = 0.055;

			if (me.fov == 90)
				me.spread.vecspread += 0.025f;
			break;
		
		case WEAPONLIST_SG552:
			if (!(me.spread.prcflags & FL_ONGROUND))
				me.spread.vecspread = me.spread.spreadvar * 0.45 + 0.035;
			else if (g_ppmove->velocity.Length2D() > 140)
				me.spread.vecspread = me.spread.spreadvar * 0.075 + 0.035;
			else
				me.spread.vecspread = me.spread.spreadvar * 0.02;
			break;

		//

		case WEAPONLIST_SG550:
			if (!(me.spread.prcflags & FL_ONGROUND))
				me.spread.vecspread = 0.45 * (1 - me.spread.spreadvar);
			else if (g_ppmove->velocity.Length2D() > 0)
				me.spread.vecspread = 0.15;
			else if (me.spread.prcflags & FL_DUCKING)
				me.spread.vecspread = 0.04 * (1 - me.spread.spreadvar);
			else
				me.spread.vecspread = 0.05 * (1 - me.spread.spreadvar);

			if (me.fov == 90)
				me.spread.vecspread += 0.025f;
			break;


		case WEAPONLIST_AK47:
			if (!(me.spread.prcflags & FL_ONGROUND))
				me.spread.vecspread = me.spread.spreadvar * 0.4 + 0.04;
			else if (g_ppmove->velocity.Length2D() > 140)
				me.spread.vecspread = me.spread.spreadvar * 0.07 + 0.04;
			else
				me.spread.vecspread = me.spread.spreadvar * 0.0275;
			break;


		case WEAPONLIST_M4A1:

			if ((me.spread.WeaponState & M4A1_SILENCER))
		//	if (IsCurWeaponSilenced())
			{
				if (!(me.spread.prcflags & FL_ONGROUND))
					me.spread.vecspread = me.spread.spreadvar * 0.4 + 0.035;
				else if (g_ppmove->velocity.Length2D() > 140)
					me.spread.vecspread = me.spread.spreadvar * 0.07 + 0.035;
				else
					me.spread.vecspread = me.spread.spreadvar * 0.025;
			}
			else
			{
				if (!(me.spread.prcflags & FL_ONGROUND))
					me.spread.vecspread = me.spread.spreadvar * 0.4 + 0.035;
				else if (g_ppmove->velocity.Length2D() > 140)
					me.spread.vecspread = me.spread.spreadvar * 0.07 + 0.035;
				else
					me.spread.vecspread = me.spread.spreadvar * 0.02;
			}
			break;


		case WEAPONLIST_FAMAS:
			if (!(me.spread.prcflags & FL_ONGROUND))
				me.spread.vecspread = me.spread.spreadvar * 0.3 + 0.030;
			else if (g_ppmove->velocity.Length2D() > 140)
				me.spread.vecspread = me.spread.spreadvar * 0.07 + 0.030;
			else
				me.spread.vecspread = me.spread.spreadvar * 0.02;


			if (!(me.spread.WeaponState & FAMAS_BURST))
		//	if (!IsCurWeaponInBurst()) 
				me.spread.vecspread += 0.01f;
			break;


		case WEAPONLIST_GALIL:
			if (!(me.spread.prcflags & FL_ONGROUND))
				me.spread.vecspread = me.spread.spreadvar * 0.3 + 0.04;
			else if (g_ppmove->velocity.Length2D() > 140)
				me.spread.vecspread = me.spread.spreadvar * 0.07 + 0.04;
			else
				me.spread.vecspread = me.spread.spreadvar * 0.0375;
			break;


		case WEAPONLIST_AUG:
			if (!(me.spread.prcflags & FL_ONGROUND))
				me.spread.vecspread = me.spread.spreadvar * 0.4 + 0.035;
			else if (g_ppmove->velocity.Length2D() > 140)
				me.spread.vecspread = me.spread.spreadvar * 0.07 + 0.035;
			else
				me.spread.vecspread = me.spread.spreadvar * 0.02;
			break;


		case WEAPONLIST_M249:
			if (!(me.spread.prcflags & FL_ONGROUND))
				me.spread.vecspread = me.spread.spreadvar * 0.5 + 0.045;
			else if (g_ppmove->velocity.Length2D() > 140)
				me.spread.vecspread = me.spread.spreadvar * 0.095 + 0.045;
			else
				me.spread.vecspread = me.spread.spreadvar * 0.03;
			break;

		//

		case WEAPONLIST_MAC10:
			if (me.spread.prcflags & FL_ONGROUND)
				me.spread.vecspread = 0.03 * me.spread.spreadvar;
			else
				me.spread.vecspread = 0.375 * me.spread.spreadvar;
			break;
		
		
		case WEAPONLIST_MP5:
			if (me.spread.prcflags & FL_ONGROUND)
				me.spread.vecspread = 0.04 * me.spread.spreadvar;
			else
				me.spread.vecspread = 0.2 * me.spread.spreadvar;
			break;

		case WEAPONLIST_P90:
			if (!(me.spread.prcflags & FL_ONGROUND))
				me.spread.vecspread = me.spread.spreadvar * 0.3;
			else if (g_ppmove->velocity.Length2D() > 170)
				me.spread.vecspread = me.spread.spreadvar * 0.115;
			else
				me.spread.vecspread = me.spread.spreadvar * 0.045;
			break;
		
		case WEAPONLIST_TMP:
			if (me.spread.prcflags & FL_ONGROUND)
				me.spread.vecspread = 0.03 * me.spread.spreadvar;
			else
				me.spread.vecspread = 0.25 * me.spread.spreadvar;
			break;

		case WEAPONLIST_UMP45:
			if (me.spread.prcflags & FL_ONGROUND)
				me.spread.vecspread = 0.04 * me.spread.spreadvar;
			else
				me.spread.vecspread = 0.24 * me.spread.spreadvar;
			break;

		//
		
		case WEAPONLIST_M3:
			me.spread.vecspread = 0.f;
			break;

		case WEAPONLIST_XM1014:
			me.spread.vecspread = 0;
			break;

		//

		default:
			me.spread.spreadvar = 0;
			me.spread.vecspread = 0;
		break;

		}
	}
}

//

void NA_Simulate(float &m_flAccuracy, float &m_flSpread)//Simulate //getvecspread+primaryattack
{
//	int id=0;
//	id = GetCurWeaponId();

    bool m_bDelayFire = me.spread.firing;
    int m_iShotsFired = me.spread.recoil;

    switch (me.weaponid)
	{

	case WEAPONLIST_DEAGLE:

        if (me.spread.prevtime != 0.0)
        {
            m_flAccuracy -= (0.4f - (me.spread.gtime - me.spread.prevtime)) * 0.35f;

            if (m_flAccuracy > 0.9f)
                m_flAccuracy = 0.9f;
            else if (m_flAccuracy < 0.55f)
                m_flAccuracy = 0.55f;
        }

        if (!(me.spread.prcflags & FL_ONGROUND))
            m_flSpread = 1.5 * (1 - m_flAccuracy);
        else if (g_ppmove->velocity.Length2D() > 0)
            m_flSpread = 0.25 * (1 - m_flAccuracy);
        else if (me.spread.prcflags & FL_DUCKING)
            m_flSpread = 0.115 * (1 - m_flAccuracy);
        else
            m_flSpread = 0.13 * (1 - m_flAccuracy);
	break;


	case WEAPONLIST_GLOCK18:

        if (me.spread.prevtime)
        {
            m_flAccuracy -= (0.325f - (me.spread.gtime - me.spread.prevtime)) * 0.275f;

            if (m_flAccuracy > 0.9f)
                m_flAccuracy = 0.9f;
            else if (m_flAccuracy < 0.6f)
                m_flAccuracy = 0.6f;
        }

		if ((me.spread.WeaponState & GLOCK18_BURST))
	//	if (IsCurWeaponInBurst())
        {
            if (!(me.spread.prcflags & FL_ONGROUND))
                m_flSpread = 1.2 * (1 - m_flAccuracy);
            else if (g_ppmove->velocity.Length2D() > 0)
                m_flSpread = 0.185 * (1 - m_flAccuracy);
            else if (me.spread.prcflags & FL_DUCKING)
                m_flSpread = 0.095 * (1 - m_flAccuracy);
            else
                m_flSpread = 0.3 * (1 - m_flAccuracy);
        }
        else
        {
            if (!(me.spread.prcflags & FL_ONGROUND))
                m_flSpread = 1.0 * (1 - m_flAccuracy);
            else if (g_ppmove->velocity.Length2D() > 0)
                m_flSpread = 0.165 * (1 - m_flAccuracy);
            else if (me.spread.prcflags & FL_DUCKING)
                m_flSpread = 0.075 * (1 - m_flAccuracy);
            else
                m_flSpread = 0.1 * (1 - m_flAccuracy);
        }
	break;


	case WEAPONLIST_USP:

        if (me.spread.prevtime != 0.0f)
        {
            m_flAccuracy -= (0.3f - (me.spread.gtime - me.spread.prevtime)) * 0.275f;

            if (m_flAccuracy > 0.92f)
                m_flAccuracy = 0.92f;
            else if (m_flAccuracy < 0.6f)
                m_flAccuracy = 0.6f;
        }

		if ((me.spread.WeaponState & USP_SILENCER))
	//	if (IsCurWeaponSilenced())
        {
            if (!(me.spread.prcflags & FL_ONGROUND))
                m_flSpread = 1.3 * (1 - m_flAccuracy);
            else if (g_ppmove->velocity.Length2D() > 0)
                m_flSpread = 0.25 * (1 - m_flAccuracy);
            else if (me.spread.prcflags & FL_DUCKING)
                m_flSpread = 0.125 * (1 - m_flAccuracy);
            else
                m_flSpread = 0.15 * (1 - m_flAccuracy);
        }
        else
        {
            if (!(me.spread.prcflags & FL_ONGROUND))
                m_flSpread = 1.2 * (1 - m_flAccuracy);
            else if (g_ppmove->velocity.Length2D() > 0)
                m_flSpread = 0.225 * (1 - m_flAccuracy);
            else if (me.spread.prcflags & FL_DUCKING)
                m_flSpread = 0.08 * (1 - m_flAccuracy);
            else
                m_flSpread = 0.1 * (1 - m_flAccuracy);
        }
	break;


	case WEAPONLIST_P228:

        if (me.spread.prevtime != 0.0f)
        {
            m_flAccuracy -= (0.325f - (me.spread.gtime - me.spread.prevtime)) * 0.3f;

            if (m_flAccuracy > 0.9f)
                m_flAccuracy = 0.9f;
            else if (m_flAccuracy < 0.6f)
                m_flAccuracy = 0.6f;
        }

        if (!(me.spread.prcflags & FL_ONGROUND))
            m_flSpread = 1.5 * (1 - m_flAccuracy);
        else if (g_ppmove->velocity.Length2D() > 0)
            m_flSpread = 0.255 * (1 - m_flAccuracy);
        else if (me.spread.prcflags & FL_DUCKING)
            m_flSpread = 0.075 * (1 - m_flAccuracy);
        else
            m_flSpread = 0.15 * (1 - m_flAccuracy);
	break;


	case WEAPONLIST_FIVESEVEN:

        if (me.spread.prevtime != 0.0f)
        {
            m_flAccuracy -= (0.275f - (me.spread.gtime - me.spread.prevtime)) * 0.25f;

            if (m_flAccuracy > 0.92f)
                m_flAccuracy = 0.92f;
            else if (m_flAccuracy < 0.725f)
            {
                m_flAccuracy = 0.725f;
            }
        }

        if (!(me.spread.prcflags & FL_ONGROUND))
            m_flSpread = 1.5 * (1 - m_flAccuracy);
        else if (g_ppmove->velocity.Length2D() > 0)
            m_flSpread = 0.255 * (1 - m_flAccuracy);
        else if (me.spread.prcflags & FL_DUCKING)
            m_flSpread = 0.075 * (1 - m_flAccuracy);
        else
            m_flSpread = 0.15 * (1 - m_flAccuracy);
	break;


	case WEAPONLIST_ELITE:

        if (me.spread.prevtime)
        {
            m_flAccuracy -= (0.325f - me.spread.gtime - me.spread.prevtime) * 0.275f;

            if (m_flAccuracy > 0.88f)
                m_flAccuracy = 0.88f;
            else if (m_flAccuracy < 0.55f)
                m_flAccuracy = 0.55f;
        }

        if (!(me.spread.prcflags & FL_ONGROUND))
            m_flSpread = 1.3 * (1 - m_flAccuracy);
        else if (g_ppmove->velocity.Length2D() > 0)
            m_flSpread = 0.175 * (1 - m_flAccuracy);
        else if (me.spread.prcflags & FL_DUCKING)
            m_flSpread = 0.08 * (1 - m_flAccuracy);
        else
            m_flSpread = 0.1 * (1 - m_flAccuracy);
	break;

	//

	case WEAPONLIST_G3SG1:
        if (me.spread.prevtime)
        {
            m_flAccuracy = (me.spread.gtime - me.spread.prevtime) * 0.3f + 0.55f;

            if (m_flAccuracy > 0.98f)
                m_flAccuracy = 0.98f;
        }
        else
            m_flAccuracy = 0.98f;

        if (!(me.spread.prcflags & FL_ONGROUND))
            m_flSpread = 0.45;
        else if (g_ppmove->velocity.Length2D() > 0)
            m_flSpread = 0.15;
        else if (me.spread.prcflags & FL_DUCKING)
            m_flSpread = 0.035;
        else
            m_flSpread = 0.055;

        if (me.fov == 90)
            m_flSpread += 0.025f;
	break;


	case WEAPONLIST_SG552:
        m_bDelayFire = true;
        m_iShotsFired++;

        m_flAccuracy = ((m_iShotsFired * m_iShotsFired * m_iShotsFired) / 220) + 0.3f;

        if (m_flAccuracy > 1.0f)
            m_flAccuracy = 1.0f;

        if (!(me.spread.prcflags & FL_ONGROUND))
            m_flSpread = m_flAccuracy * 0.45 + 0.035;
        else if (g_ppmove->velocity.Length2D() > 140)
            m_flSpread = m_flAccuracy * 0.075 + 0.035;
        else
            m_flSpread = m_flAccuracy * 0.02;
	break;


    case WEAPONLIST_SG550:
        if (me.spread.prevtime)
        {
            m_flAccuracy = (me.spread.gtime - me.spread.prevtime) * 0.35f + 0.65f;

            if (m_flAccuracy > 0.98f)
                m_flAccuracy = 0.98f;
        }

        if (!(me.spread.prcflags & FL_ONGROUND))
            m_flSpread = 0.45 * (1 - m_flAccuracy);
        else if (g_ppmove->velocity.Length2D() > 0)
            m_flSpread = 0.15;
        else if (me.spread.prcflags & FL_DUCKING)
            m_flSpread = 0.04 * (1 - m_flAccuracy);
        else
            m_flSpread = 0.05 * (1 - m_flAccuracy);

        if (me.fov == 90)
            m_flSpread += 0.025f;
	break;

	//

	/*
	case WEAPONLIST_AK47:
		if (me.spread.prcflags & FL_ONGROUND)
		{
			if (speed > 140.0f)
				calculated_spread = me.spread.spreadvar * 0.07 + 0.04;
			else
				calculated_spread = me.spread.spreadvar * 0.0275;
		}
		else
			calculated_spread = me.spread.spreadvar * 0.4 + .04;

		break;*/
	/*
	case WEAPONLIST_AK47:
		me.spread.recoil++;
		me.spread.firing = true;

		me.spread.spreadvar = me.spread.recoil * me.spread.recoil * me.spread.recoil / 200.0f + 0.35;

		if (me.spread.spreadvar > 1.25)
			me.spread.spreadvar = 1.25f;

		me.spread.prevtime = me.spread.gtime;

		break;*/


    case WEAPONLIST_AK47:
        m_bDelayFire = true;
        m_iShotsFired++;

        m_flAccuracy = static_cast<float>((m_iShotsFired * m_iShotsFired) * (m_iShotsFired / 200)) + 0.35f;

        if (m_flAccuracy > 1.25f)
            m_flAccuracy = 1.25f;

        if (!(me.spread.prcflags & FL_ONGROUND))
            m_flSpread = m_flAccuracy * 0.4 + 0.04;
        else if (g_ppmove->velocity.Length2D() > 140)
            m_flSpread = m_flAccuracy * 0.07 + 0.04;
        else
            m_flSpread = m_flAccuracy * 0.0275;
	break;


	
	case WEAPONLIST_M4A1:
        m_bDelayFire = true;
        m_iShotsFired++;

        m_flAccuracy = ((m_iShotsFired * m_iShotsFired * m_iShotsFired) / 220) + 0.3f;

        if (m_flAccuracy > 1)
            m_flAccuracy = 1;

		if ((me.spread.WeaponState & M4A1_SILENCER))
	//	if (IsCurWeaponSilenced())
        {
            if (!(me.spread.prcflags & FL_ONGROUND))
                m_flSpread = m_flAccuracy * 0.4 + 0.035;
            else if (g_ppmove->velocity.Length2D() > 140)
                m_flSpread = m_flAccuracy * 0.07 + 0.035;
            else
                m_flSpread = m_flAccuracy * 0.025;
        }
        else
        {
            if (!(me.spread.prcflags & FL_ONGROUND))
                m_flSpread = m_flAccuracy * 0.4 + 0.035;
            else if (g_ppmove->velocity.Length2D() > 140)
                m_flSpread = m_flAccuracy * 0.07 + 0.035;
            else
                m_flSpread = m_flAccuracy * 0.02;
        }
	break;

    case WEAPONLIST_FAMAS:
        m_bDelayFire = true;
        m_iShotsFired++;

        m_flAccuracy = (m_iShotsFired * m_iShotsFired * m_iShotsFired / 215) + 0.3f;

        if (m_flAccuracy > 1.0f)
            m_flAccuracy = 1.0f;

        if (!(me.spread.prcflags & FL_ONGROUND))
            m_flSpread = m_flAccuracy * 0.3 + 0.030;
        else if (g_ppmove->velocity.Length2D() > 140)
            m_flSpread = m_flAccuracy * 0.07 + 0.030;
        else
            m_flSpread = m_flAccuracy * 0.02;


		if (!(me.spread.WeaponState & FAMAS_BURST))
	//	if (!IsCurWeaponInBurst())
			m_flSpread += 0.01f;

	break;
    

    case WEAPONLIST_GALIL:
        m_bDelayFire = true;
        m_iShotsFired++;

        m_flAccuracy = ((m_iShotsFired * m_iShotsFired * m_iShotsFired) / 200) + 0.35f;

        if (m_flAccuracy > 1.25f)
            m_flAccuracy = 1.25f;

        if (!(me.spread.prcflags & FL_ONGROUND))
            m_flSpread = m_flAccuracy * 0.3 + 0.04;
        else if (g_ppmove->velocity.Length2D() > 140)
            m_flSpread = m_flAccuracy * 0.07 + 0.04;
        else
            m_flSpread = m_flAccuracy * 0.0375;
	break;
    

	 case WEAPONLIST_AUG:
        m_bDelayFire = true;
        m_iShotsFired++;

        m_flAccuracy = ((m_iShotsFired * m_iShotsFired * m_iShotsFired) / 215) + 0.3f;

        if (m_flAccuracy > 1.0f)
            m_flAccuracy = 1.0f;

        if (!(me.spread.prcflags & FL_ONGROUND))
            m_flSpread = m_flAccuracy * 0.4 + 0.035;
        else if (g_ppmove->velocity.Length2D() > 140)
            m_flSpread = m_flAccuracy * 0.07 + 0.035;
        else
            m_flSpread = m_flAccuracy * 0.02;
	break;

	//

    case WEAPONLIST_M249:
        m_bDelayFire = true;
        m_iShotsFired++;

        m_flAccuracy = ((m_iShotsFired * m_iShotsFired * m_iShotsFired) / 175) + 0.4f;

        if (m_flAccuracy > 0.9f)
            m_flAccuracy = 0.9f;

        if (!(me.spread.prcflags & FL_ONGROUND))
            m_flSpread = m_flAccuracy * 0.5 + 0.045;
        else if (g_ppmove->velocity.Length2D() > 140)
            m_flSpread = m_flAccuracy * 0.095 + 0.045;
        else
            m_flSpread = m_flAccuracy * 0.03;
	break;

	//

    case WEAPONLIST_MAC10:
        m_bDelayFire = true;
        m_iShotsFired++;

        m_flAccuracy = ((m_iShotsFired * m_iShotsFired * m_iShotsFired) / 200) + 0.6f;

        if (m_flAccuracy > 1.65f)
            m_flAccuracy = 1.65f;

        if (me.spread.prcflags & FL_ONGROUND)
            m_flSpread = 0.03 * m_flAccuracy;
        else
            m_flSpread = 0.375 * m_flAccuracy;
	break;


    case WEAPONLIST_MP5:
        m_bDelayFire = true;
        m_iShotsFired++;

        m_flAccuracy = ((m_iShotsFired * m_iShotsFired) / 220.1) + 0.45f;

        if (m_flAccuracy > 0.75f)
            m_flAccuracy = 0.75f;

        if (me.spread.prcflags & FL_ONGROUND)
            m_flSpread = 0.04 * m_flAccuracy;
        else
            m_flSpread = 0.2 * m_flAccuracy;
	break;


    case WEAPONLIST_P90:
        m_bDelayFire = true;
        m_iShotsFired++;

        m_flAccuracy = (m_iShotsFired * m_iShotsFired / 175) + 0.45f;

        if (m_flAccuracy > 1)
            m_flAccuracy = 1;

        if (!(me.spread.prcflags & FL_ONGROUND))
            m_flSpread = m_flAccuracy * 0.3;
        else if (g_ppmove->velocity.Length2D() > 170)
            m_flSpread = m_flAccuracy * 0.115;
        else
            m_flSpread = m_flAccuracy * 0.045;
	break;
	

    case WEAPONLIST_TMP:
        m_bDelayFire = true;
        m_iShotsFired++;

        m_flAccuracy = ((m_iShotsFired * m_iShotsFired * m_iShotsFired) / 200) + 0.55f;

        if (m_flAccuracy > 1.4f)
            m_flAccuracy = 1.4f;

        if (me.spread.prcflags & FL_ONGROUND)
            m_flSpread = 0.03 * m_flAccuracy;
        else
            m_flSpread = 0.25 * m_flAccuracy;
	break;


    case WEAPONLIST_UMP45:
        m_bDelayFire = true;
        m_iShotsFired++;

        m_flAccuracy = ((m_iShotsFired * m_iShotsFired) / 210) + 0.5f;

        if (m_flAccuracy > 1.0f)
            m_flAccuracy = 1.0f;

        if (me.spread.prcflags & FL_ONGROUND)
            m_flSpread = 0.04 * m_flAccuracy;
        else
            m_flSpread = 0.24 * m_flAccuracy;
	break;

	//

	//

	default:
		m_flSpread = 0;
	break;
    
    }
}

//-------------------------------------------------------------------//

void NA_GetSpreadXY(unsigned int seed, int future, float *vec, bool simulate)
{
	vec[0] = UTIL_SharedRandomFloat(seed + future, -0.5, 0.5) + UTIL_SharedRandomFloat(seed + 1 + future, -0.5, 0.5);
	vec[1] = UTIL_SharedRandomFloat(seed + 2 + future, -0.5, 0.5) + UTIL_SharedRandomFloat(seed + 3 + future, -0.5, 0.5);

	if (!simulate){
		vec[0] *= me.spread.vecspread;
		vec[1] *= me.spread.vecspread;
	} else {
		float m_flAccuracy, m_flSpread;
		NA_Simulate(m_flAccuracy, m_flSpread);
		vec[0] *= m_flSpread;
		vec[1] *= m_flSpread;
	}
}

//-------------------------------------------------------------------//

void NA_GetSpreadOffset(unsigned int seed, int future, float *inangles, float *outangles)
{
	if (cvar.nospread6_method == 0)
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

	/*
	if (me.alive && 
		
	//	IsCurWeaponGun()
		!HasBadWeapon() && !HasKnife()
		
		&& cmd->buttons & IN_ATTACK && 
		
	//	NA_CanAttack()
		(me.spread.flNextPrimaryAttack <= 0.0f && !me.spread.iInReload && me.spread.flNextAttack <= 0.0f)
		
	)*/
	{
		NewVector vAngles;
		NA_GetSpreadOffset(me.spread.random_seed, 1, cmd->viewangles, vAngles);
		
	//	vNoSpreadAngle = cmd->viewangles - vAngles;
		vNoSpreadAngle[0] = (cmd->viewangles.x - vAngles.x);
		vNoSpreadAngle[1] = (cmd->viewangles.y - vAngles.y);
		vNoSpreadAngle[2] = (cmd->viewangles.z - vAngles.z);

		if (cvar.nospread6_active)
		{
			NA_MakeAngle(vAngles, cmd);
		}
	}
}

//-------------------------------------------------------------------//

void NA_ResetAccuracy()
{
    me.spread.firing = false;
    me.spread.recoil = 0;
    me.spread.recoiltime = me.spread.gtime;
    me.spread.prevtime = 0;

    switch (me.weaponid)
    {
    case WEAPONLIST_AK47:
    case WEAPONLIST_AUG:
    case WEAPONLIST_FAMAS:
    case WEAPONLIST_G3SG1:
    case WEAPONLIST_GALIL:
    case WEAPONLIST_M4A1:
    case WEAPONLIST_M249:
    case WEAPONLIST_P90:
    case WEAPONLIST_SG552:
    case WEAPONLIST_TMP:
        me.spread.spreadvar = 0.2f;
	break;
    case WEAPONLIST_DEAGLE:
    case WEAPONLIST_GLOCK18:
    case WEAPONLIST_P228:
        me.spread.spreadvar = 0.9f;
	break;
    case WEAPONLIST_ELITE:
        me.spread.spreadvar = 0.88f;
	break;
    case WEAPONLIST_FIVESEVEN:
        me.spread.spreadvar = 0.92f;
	break;
    case WEAPONLIST_MAC10:
        me.spread.spreadvar = 0.15f;
	break;
    case WEAPONLIST_USP:
        me.spread.spreadvar = 0.92f;
        break;
    default:
        me.spread.spreadvar = 0;
	break;
    }
}

//-------------------------------------------------------------------//

void NA_PrimaryAttack()
{
    switch (me.weaponid)
    {

	case WEAPONLIST_DEAGLE:
        if (me.spread.recoil < 1)
            me.spread.recoil++;
        else
            return;

        if (me.spread.prevtime != 0.0)
        {
            me.spread.spreadvar -= (0.4f - (me.spread.gtime - me.spread.prevtime)) * 0.35f;

            if (me.spread.spreadvar > 0.9f)
                me.spread.spreadvar = 0.9f;
            else if (me.spread.spreadvar < 0.55f)
                me.spread.spreadvar = 0.55f;
        }
	break;


	case WEAPONLIST_GLOCK18:

		if (!(me.spread.WeaponState & GLOCK18_BURST))
	//	if (!IsCurWeaponInBurst())
        {
            if (me.spread.recoil < 1)
                me.spread.recoil++;
            else
                return;
        }

        if (me.spread.prevtime)
        {
            me.spread.spreadvar -= (0.325f - (me.spread.gtime - me.spread.prevtime)) * 0.275f;

            if (me.spread.spreadvar > 0.9f)
                me.spread.spreadvar = 0.9f;
            else if (me.spread.spreadvar < 0.6f)
                me.spread.spreadvar = 0.6f;
        }
        break;


	case WEAPONLIST_USP:
        if (me.spread.recoil < 1)
            me.spread.recoil++;
        else
            return;

        if (me.spread.prevtime != 0.0f)
        {
            me.spread.spreadvar -= (0.3f - (me.spread.gtime - me.spread.prevtime)) * 0.275f;

            if (me.spread.spreadvar > 0.92f)
                me.spread.spreadvar = 0.92f;
            else if (me.spread.spreadvar < 0.6f)
                me.spread.spreadvar = 0.6f;
        }
        break;
    

	case WEAPONLIST_FIVESEVEN:
        if (me.spread.recoil < 1)
            me.spread.recoil++;
        else
            return;

        if (me.spread.prevtime != 0.0f)
        {
            me.spread.spreadvar -= (0.275f - (me.spread.gtime - me.spread.prevtime)) * 0.25f;

            if (me.spread.spreadvar > 0.92f)
                me.spread.spreadvar = 0.92f;
            else if (me.spread.spreadvar < 0.725f)
            {
                me.spread.spreadvar = 0.725f;
            }
        }
        break;

	case WEAPONLIST_ELITE:
        if (me.spread.recoil < 1)
            me.spread.recoil++;
        else
            return;

        if (me.spread.prevtime)
        {
            me.spread.spreadvar -= (0.325f - me.spread.gtime - me.spread.prevtime) * 0.275f;

            if (me.spread.spreadvar > 0.88f)
                me.spread.spreadvar = 0.88f;
            else if (me.spread.spreadvar < 0.55f)
                me.spread.spreadvar = 0.55f;
        }
        break;

	//

	case WEAPONLIST_G3SG1:
        if (me.spread.prevtime)
        {
            me.spread.spreadvar = (me.spread.gtime - me.spread.prevtime) * 0.3f + 0.55f;

            if (me.spread.spreadvar > 0.98f)
                me.spread.spreadvar = 0.98f;
        }
        else
            me.spread.spreadvar = 0.98f;
        break;

	case WEAPONLIST_SG552:
        me.spread.firing = true;
        me.spread.recoil++;

        me.spread.spreadvar = ((me.spread.recoil * me.spread.recoil * me.spread.recoil) / 220) + 0.3f;

        if (me.spread.spreadvar > 1.0f)
            me.spread.spreadvar = 1.0f;
	break;

	//

	case WEAPONLIST_SG550:
        if (me.spread.prevtime)
        {
            me.spread.spreadvar = (me.spread.gtime - me.spread.prevtime) * 0.35f + 0.65f;

            if (me.spread.spreadvar > 0.98f)
                me.spread.spreadvar = 0.98f;
        }
	break;


    case WEAPONLIST_AK47:
        me.spread.firing = true;
        me.spread.recoil++;

        me.spread.spreadvar = ((me.spread.recoil * me.spread.recoil * me.spread.recoil) / 200) + 0.35f;

        if (me.spread.spreadvar > 1.25f)
            me.spread.spreadvar = 1.25f;
	break;

	case WEAPONLIST_M4A1:
        me.spread.firing = true;
        me.spread.recoil++;

        me.spread.spreadvar = ((me.spread.recoil * me.spread.recoil * me.spread.recoil) / 220) + 0.3f;

        if (me.spread.spreadvar > 1)
            me.spread.spreadvar = 1;
	break;
    
    case WEAPONLIST_FAMAS:
        me.spread.firing = true;
        me.spread.recoil++;

        me.spread.spreadvar = (me.spread.recoil * me.spread.recoil * me.spread.recoil / 215) + 0.3f;

        if (me.spread.spreadvar > 1.0f)
            me.spread.spreadvar = 1.0f;
        break;
    
    
    case WEAPONLIST_GALIL:
        me.spread.firing = true;
        me.spread.recoil++;

        me.spread.spreadvar = ((me.spread.recoil * me.spread.recoil * me.spread.recoil) / 200) + 0.35f;

        if (me.spread.spreadvar > 1.25f)
            me.spread.spreadvar = 1.25f;
	break;

	case WEAPONLIST_AUG:
        me.spread.firing = true;
        me.spread.recoil++;

        me.spread.spreadvar = ((me.spread.recoil * me.spread.recoil * me.spread.recoil) / 215) + 0.3f;

        if (me.spread.spreadvar > 1.0f)
            me.spread.spreadvar = 1.0f;
	break;


    case WEAPONLIST_M249:
        me.spread.firing = true;
        me.spread.recoil++;

        me.spread.spreadvar = ((me.spread.recoil * me.spread.recoil * me.spread.recoil) / 175) + 0.4f;

        if (me.spread.spreadvar > 0.9f)
            me.spread.spreadvar = 0.9f;
        break;

	//

    case WEAPONLIST_MAC10:
        me.spread.firing = true;
        me.spread.recoil++;

        me.spread.spreadvar = ((me.spread.recoil * me.spread.recoil * me.spread.recoil) / 200) + 0.6f;

        if (me.spread.spreadvar > 1.65f)
            me.spread.spreadvar = 1.65f;
	break;

    case WEAPONLIST_MP5:
        me.spread.firing = true;
        me.spread.recoil++;

        me.spread.spreadvar = ((me.spread.recoil * me.spread.recoil) / 220.1) + 0.45f;

        if (me.spread.spreadvar > 0.75f)
            me.spread.spreadvar = 0.75f;
	break;

    case WEAPONLIST_P90:
        me.spread.firing = true;
        me.spread.recoil++;

        me.spread.spreadvar = (me.spread.recoil * me.spread.recoil / 175) + 0.45f;

        if (me.spread.spreadvar > 1)
            me.spread.spreadvar = 1;
	break;

    case WEAPONLIST_P228:
        if (me.spread.recoil < 1)
            me.spread.recoil++;
        else
            return;

        if (me.spread.prevtime != 0.0f)
        {
            me.spread.spreadvar -= (0.325f - (me.spread.gtime - me.spread.prevtime)) * 0.3f;

            if (me.spread.spreadvar > 0.9f)
                me.spread.spreadvar = 0.9f;
            else if (me.spread.spreadvar < 0.6f)
                me.spread.spreadvar = 0.6f;
        }
	break;
    
    case WEAPONLIST_TMP:
        me.spread.firing = true;
        me.spread.recoil++;

        me.spread.spreadvar = ((me.spread.recoil * me.spread.recoil * me.spread.recoil) / 200) + 0.55f;

        if (me.spread.spreadvar > 1.4f)
            me.spread.spreadvar = 1.4f;
	break;

    case WEAPONLIST_UMP45:
        me.spread.firing = true;
        me.spread.recoil++;

        me.spread.spreadvar = ((me.spread.recoil * me.spread.recoil) / 210) + 0.5f;

        if (me.spread.spreadvar > 1.0f)
            me.spread.spreadvar = 1.0f;
	break;

	//

    case WEAPONLIST_M3:
        if (me.spread.recoil < 1)
            me.spread.recoil++;
	break;

    case WEAPONLIST_XM1014:
        if (me.spread.recoil < 1)
            me.spread.recoil++;
	break;

	default:
		me.spread.firing = false;
        me.spread.recoil = 0;
        me.spread.spreadvar = 0;
	break;

    }
	
	//

	me.spread.prevtime = me.spread.gtime;
}

//-------------------------------------------------------------------//

void NA_ItemPostFrame(struct usercmd_s* cmd)
{
	if (me.alive)
	{
		static int iOldWeaponID = WEAPONLIST_NONE;

		if (iOldWeaponID != me.weaponid)
		{
			NA_ResetAccuracy();
			iOldWeaponID = me.weaponid;
		}

		if (cmd->buttons & IN_ATTACK && 
			
		//	NA_CanAttack()
			(me.spread.flNextPrimaryAttack <= 0.0f && !me.spread.iInReload && me.spread.flNextAttack <= 0.0f)
			
			)
		{
			// Can't shoot during the freeze period
			// Always allow firing in single player
		//	if (!IsFreezePeriod() && (m_pPlayer->m_bCanShoot && !m_pPlayer->m_bIsDefusing))
			if (!(me.iuser3 & PLAYER_FREEZE_TIME_OVER) && (me.iuser3 & PLAYER_CAN_SHOOT))
			{
				NA_PrimaryAttack();
			}
		}
		else if (me.spread.iInReload || cmd->buttons & IN_RELOAD)
		{
			// reload when reload is pressed, or if no buttons are down and weapon is empty.
            NA_ResetAccuracy();
		}
		else if (!(cmd->buttons & (IN_ATTACK | IN_ATTACK2)))
		{
			// no fire buttons down

			// The following code prevents the player from tapping the firebutton repeatedly
			// to simulate full auto and retaining the single shot accuracy of single fire
			if (me.spread.firing)
			{
				me.spread.firing = false;

				if (me.spread.recoil > 15)
				{
					me.spread.recoil = 15;
				}

				me.spread.recoiltime = me.spread.gtime + 0.4f;
			}

			// if it's a pistol then set the shots fired to 0 after the player releases a button
			if (HasPistol())
			{
				me.spread.recoil = 0;
			}
			else
			{
				if (me.spread.recoil > 0 && me.spread.recoiltime < me.spread.gtime)
				{
					me.spread.recoiltime = me.spread.recoiltime + 0.0225f;
					me.spread.recoil--;
				}
			}
		}
	}
}

//-------------------------------------------------------------------//

DWORD delay = 0;

void NA_ItemPreFrame(struct local_state_s *from, 
				  struct local_state_s *to, 
				  struct usercmd_s *usercmd, 
				  int runfuncs, 
				  double time, 
				  unsigned int random_seed)
{
	if (runfuncs)
	{
		me.spread.random_seed = random_seed;
		me.spread.gtime = time;
		me.spread.prcflags = to->client.flags;

		me.spread.flNextPrimaryAttack = to->weapondata[to->client.m_iId].m_flNextPrimaryAttack;
		me.spread.flNextSecondaryAttack = to->weapondata[to->client.m_iId].m_flNextSecondaryAttack;
		me.spread.flNextAttack = to->client.m_flNextAttack;
		me.spread.iInReload = (to->weapondata[to->client.m_iId].m_fInReload || !to->weapondata[to->client.m_iId].m_iClip);
		me.spread.WeaponState = to->weapondata[to->client.m_iId].m_iWeaponState;
		me.iuser1 = to->client.iuser1;
		me.iuser2 = to->client.iuser2;
		me.iuser3 = to->client.iuser3;
		me.iuser4 = to->client.iuser4;

		static int iLastWpnID = me.weaponid;
		if (iLastWpnID != me.weaponid)
		{
			if (me.alive) delay = GetTickCount();
			iLastWpnID = me.weaponid;
		}

	/*	if (me.lastweaponid2 != me.weaponid)
		{
			me.lastweaponid2 = me.weaponid;

			if (me.alive) delay = GetTickCount();
		}*/
	}
}

//-------------------------------------------------------------------//


