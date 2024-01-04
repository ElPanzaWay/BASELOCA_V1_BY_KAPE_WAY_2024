///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "inclusions.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
#define NORMALIZE(v,dist) \
		if(dist==0){ \
			v[0]=0; \
			v[1]=0; \
			v[2]=1; \
		} else { \
			dist=1/dist; \
			v[0]=v[0]*dist; \
			v[1]=v[1]*dist; \
			v[2]=v[2]*dist; \
		}*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NORMALIZEX(float* v,float dist)
{
	if(dist==0)
	{
		v[0]=0;
		v[1]=0;
		v[2]=1;
	} else {
		dist=1/dist;
		v[0]=v[0]*dist;
		v[1]=v[1]*dist;
		v[2]=v[2]*dist;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FixUpAngleDifference(usercmd_t* cmd)
{
	vec3_t viewforward, viewright, viewup, aimforward, aimright, aimup, v;
	float newforward, newright, newup, fTime;
	float forward = cmd->forwardmove;
	float right = cmd->sidemove;
	float up = cmd->upmove;
	bool movetype_walk = (me.GetMe()->curstate.movetype == MOVETYPE_WALK);
	int iHasShiftHeld = GetAsyncKeyState(VK_LSHIFT);
	if(movetype_walk){
		v[0]=0.0f;
		v[1]=cmd->viewangles[1];
		v[2]=0.0f;
		gEngfuncs.pfnAngleVectors(v, viewforward, viewright, viewup);
	} else {
		gEngfuncs.pfnAngleVectors(cmd->viewangles, viewforward, viewright, viewup);}
	if(movetype_walk && !iHasShiftHeld && !(cmd->buttons & IN_ATTACK) && !(cmd->buttons & IN_USE)){
		fTime = gEngfuncs.GetClientTime();
		cmd->viewangles.y = fmod(fTime * 11 * 360.0f, 360.0f);
	}
	if(movetype_walk){
		v[0]=0.0f;
		v[1]=cmd->viewangles[1];
		v[2]=0.0f;
		gEngfuncs.pfnAngleVectors(v, aimforward, aimright, aimup);
	} else {
		gEngfuncs.pfnAngleVectors(cmd->viewangles, aimforward, aimright, aimup);}
	float flLen1=(float)sqrt(viewforward[0]*viewforward[0]+viewforward[1]*viewforward[1]+viewforward[2]*viewforward[2]);
	float flLen2=(float)sqrt(viewright[0]*viewright[0]+viewright[1]*viewright[1]+viewright[2]*viewright[2]);
	float flLen3=(float)sqrt(viewup[0]*viewup[0]+viewup[1]*viewup[1]+viewup[2]*viewup[2]);
	NORMALIZEX(viewforward,flLen1);
	NORMALIZEX(viewright,flLen2);
	NORMALIZEX(viewup,flLen3);
	viewforward[0]=forward*viewforward[0];
	viewforward[1]=forward*viewforward[1];
	viewforward[2]=forward*viewforward[2];
	viewright[0]=right*viewright[0];
	viewright[1]=right*viewright[1];
	viewright[2]=right*viewright[2];
	viewup[0]=up*viewup[0];
	viewup[1]=up*viewup[1];
	viewup[2]=up*viewup[2];
	newforward = ( (viewforward[0]*aimforward[0] + viewforward[1]*aimforward[1] + viewforward[2]*aimforward[2])+
                   (viewright[0]*aimforward[0] + viewright[1]*aimforward[1] + viewright[2]*aimforward[2])+
				(viewup[0]*aimforward[0] + viewup[1]*aimforward[1] + viewup[2]*aimforward[2]));
	newright = ( (viewforward[0]*aimright[0] + viewforward[1]*aimright[1] + viewforward[2]*aimright[2])+
                 (viewright[0]*aimright[0] + viewright[1]*aimright[1] + viewright[2]*aimright[2])+
				 (viewup[0]*aimright[0] + viewup[1]*aimright[1] + viewup[2]*aimright[2]));
	newup = ( (viewforward[0]*aimup[0] + viewforward[1]*aimup[1] + viewforward[2]*aimup[2])+
	          (viewright[0]*aimup[0] + viewright[1]*aimup[1] + viewright[2]*aimup[2])+
			  (viewup[0]*aimup[0] + viewup[1]*aimup[1] + viewup[2]*aimup[2]));
	cmd->forwardmove = newforward;
	cmd->sidemove = newright;
	cmd->upmove = newup;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void antiaim_one(usercmd_t *ucmd,usercmd_t orig_cmd)
{
	 if(!(ucmd->buttons&IN_ATTACK)&&
	   !(ucmd->buttons&IN_USE)&&
       me.alive &&
	   (me.currentWeaponID!=WEAPONLIST_HEGRENADE&&
	    me.currentWeaponID!=WEAPONLIST_FLASHBANG&&
	    me.currentWeaponID!=WEAPONLIST_SMOKEGRENADE))
    {
    Vector viewforward,viewright,viewup,aimforward,aimright,aimup;
    float newforward,newright,newup;
    float forward=orig_cmd.forwardmove;
    float right=orig_cmd.sidemove;
    float up=orig_cmd.upmove;
		//if you do not use (usercmd->buttons & IN_ATTACK) for your nospread
		//you might want to lower this to about 80
		ucmd->viewangles.x=180;
        ucmd->viewangles.y+=180;
    //horizontal velocity movement fix
    gEngfuncs.pfnAngleVectors(Vector(0.0f, orig_cmd.viewangles.y, 0.0f), viewforward, viewright, viewup);
	//gEngfuncs.pfnAngleVectors(Vector(0.0f, ucmd->viewangles.y, 0.0f), viewforward, viewright, viewup);
	//
    gEngfuncs.pfnAngleVectors(Vector(0.0f, ucmd->viewangles.y, 0.0f), aimforward, aimright, aimup);
	//
    newforward=DotProduct(forward*viewforward.Normalize(),aimforward)+DotProduct(right*viewright.Normalize(),aimforward)+DotProduct(up*viewup.Normalize(),aimforward);
    newright=DotProduct(forward*viewforward.Normalize(),aimright)+DotProduct(right*viewright.Normalize(),aimright)+DotProduct(up*viewup.Normalize(),aimright);
    newup=DotProduct(forward*viewforward.Normalize(),aimup)+DotProduct(right*viewright.Normalize(),aimup)+DotProduct(up*viewup.Normalize(),aimup);
 
    ucmd->forwardmove=-newforward;
    ucmd->sidemove=newright;
	ucmd->upmove=newup;
	}
}
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void antiaim_two(usercmd_t *ucmd,usercmd_t orig_cmd)
{
        if(!(ucmd->buttons&IN_ATTACK)&&
	   !(ucmd->buttons&IN_USE)&&
           me.alive &&
	   (me.currentWeaponID!=WEAPONLIST_HEGRENADE&&
	    me.currentWeaponID!=WEAPONLIST_FLASHBANG&&
	    me.currentWeaponID!=WEAPONLIST_SMOKEGRENADE))
    {
    Vector viewforward,viewright,viewup,aimforward,aimright,aimup;
    float newforward,newright,newup;
    float forward=orig_cmd.forwardmove;
    float right=orig_cmd.sidemove;
    float up=orig_cmd.upmove;
		//if you do not use (usercmd->buttons & IN_ATTACK) for your nospread
		//you might want to lower this to about 80
		ucmd->viewangles.x=-179;
        ucmd->viewangles.y = ucmd->viewangles.y + 180;
    //horizontal velocity movement fix
    gEngfuncs.pfnAngleVectors(Vector(0.0f, orig_cmd.viewangles.y, 0.0f), viewforward, viewright, viewup);
	//gEngfuncs.pfnAngleVectors(Vector(0.0f, ucmd->viewangles.y, 0.0f), viewforward, viewright, viewup);
	//
    gEngfuncs.pfnAngleVectors(Vector(0.0f, ucmd->viewangles.y, 0.0f), aimforward, aimright, aimup);
	//
    newforward=DotProduct(forward*viewforward.Normalize(),aimforward)+DotProduct(right*viewright.Normalize(),aimforward)+DotProduct(up*viewup.Normalize(),aimforward);
    newright=DotProduct(forward*viewforward.Normalize(),aimright)+DotProduct(right*viewright.Normalize(),aimright)+DotProduct(up*viewup.Normalize(),aimright);
    newup=DotProduct(forward*viewforward.Normalize(),aimup)+DotProduct(right*viewright.Normalize(),aimup)+DotProduct(up*viewup.Normalize(),aimup);
 
    ucmd->forwardmove=-newforward;
    ucmd->sidemove=newright;
    ucmd->upmove=newup;
    }
}
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void antiaim_three(usercmd_t *ucmd,usercmd_t orig_cmd)
{
    if(!(ucmd->buttons&IN_ATTACK)&&
	   !(ucmd->buttons&IN_USE)&&
       me.alive &&
	   (me.currentWeaponID!=WEAPONLIST_HEGRENADE&&
	    me.currentWeaponID!=WEAPONLIST_FLASHBANG&&
	    me.currentWeaponID!=WEAPONLIST_SMOKEGRENADE))
    {
    float fTime;
    fTime = gEngfuncs.GetClientTime();
    Vector viewforward,viewright,viewup,aimforward,aimright,aimup;
    float newforward,newright,newup;
    float forward=orig_cmd.forwardmove;
    float right=orig_cmd.sidemove;
    float up=orig_cmd.upmove;
    ucmd->viewangles.x=180;
    ucmd->viewangles.y = sin(fTime * 11 * 3.14159265358979323846) * 360.0f;
 
    gEngfuncs.pfnAngleVectors(Vector(0.0f, orig_cmd.viewangles.y, 0.0f), viewforward, viewright, viewup);
	//gEngfuncs.pfnAngleVectors(Vector(0.0f, ucmd->viewangles.y, 0.0f), viewforward, viewright, viewup);
	//
    gEngfuncs.pfnAngleVectors(Vector(0.0f, ucmd->viewangles.y, 0.0f), aimforward, aimright, aimup);
	//
    newforward=DotProduct(forward*viewforward.Normalize(),aimforward)+DotProduct(right*viewright.Normalize(),aimforward)+DotProduct(up*viewup.Normalize(),aimforward);
    newright=DotProduct(forward*viewforward.Normalize(),aimright)+DotProduct(right*viewright.Normalize(),aimright)+DotProduct(up*viewup.Normalize(),aimright);
    newup=DotProduct(forward*viewforward.Normalize(),aimup)+DotProduct(right*viewright.Normalize(),aimup)+DotProduct(up*viewup.Normalize(),aimup);
 
    ucmd->forwardmove=-newforward;
    ucmd->sidemove=newright;
    ucmd->upmove=newup;
    }
}
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void antiaim_four(usercmd_t *ucmd,usercmd_t orig_cmd)
{
    if(!(ucmd->buttons&IN_ATTACK)&&
	   !(ucmd->buttons&IN_USE)&&
       me.alive &&
	   (me.currentWeaponID!=WEAPONLIST_HEGRENADE&&
	    me.currentWeaponID!=WEAPONLIST_FLASHBANG&&
	    me.currentWeaponID!=WEAPONLIST_SMOKEGRENADE))
    {
    float fTime;
    fTime = gEngfuncs.GetClientTime();
    Vector viewforward,viewright,viewup,aimforward,aimright,aimup;
    float newforward,newright,newup;
    float forward=orig_cmd.forwardmove;
    float right=orig_cmd.sidemove;
    float up=orig_cmd.upmove;
    ucmd->viewangles.x=-179;
    ucmd->viewangles.y = sin(fTime * 11 * 3.14159265358979323846) * 360.0f;
 
    gEngfuncs.pfnAngleVectors(Vector(0.0f, orig_cmd.viewangles.y, 0.0f), viewforward, viewright, viewup);
	//gEngfuncs.pfnAngleVectors(Vector(0.0f, ucmd->viewangles.y, 0.0f), viewforward, viewright, viewup);
	//
    gEngfuncs.pfnAngleVectors(Vector(0.0f, ucmd->viewangles.y, 0.0f), aimforward, aimright, aimup);
	//
    newforward=DotProduct(forward*viewforward.Normalize(),aimforward)+DotProduct(right*viewright.Normalize(),aimforward)+DotProduct(up*viewup.Normalize(),aimforward);
    newright=DotProduct(forward*viewforward.Normalize(),aimright)+DotProduct(right*viewright.Normalize(),aimright)+DotProduct(up*viewup.Normalize(),aimright);
    newup=DotProduct(forward*viewforward.Normalize(),aimup)+DotProduct(right*viewright.Normalize(),aimup)+DotProduct(up*viewup.Normalize(),aimup);
 
    ucmd->forwardmove=-newforward;
    ucmd->sidemove=newright;
    ucmd->upmove=newup;
    }
}
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void antiaim_five(usercmd_t *ucmd,usercmd_t orig_cmd)
{
	    
	if(!(ucmd->buttons&IN_ATTACK)&&
	   !(ucmd->buttons&IN_USE)&&
           me.alive &&
	   (me.currentWeaponID!=WEAPONLIST_HEGRENADE&&
	    me.currentWeaponID!=WEAPONLIST_FLASHBANG&&
	    me.currentWeaponID!=WEAPONLIST_SMOKEGRENADE))
    {
    Vector viewforward,viewright,viewup,aimforward,aimright,aimup;
    float newforward,newright,newup;
    float forward=orig_cmd.forwardmove;
    float right=orig_cmd.sidemove;
    float up=orig_cmd.upmove;
		//if you do not use (usercmd->buttons & IN_ATTACK) for your nospread
		//you might want to lower this to about 80
		ucmd->viewangles.x=-179;
        ucmd->viewangles.y = ucmd->viewangles.y + 90;
 
    //horizontal velocity movement fix
    gEngfuncs.pfnAngleVectors(Vector(0.0f, orig_cmd.viewangles.y, 0.0f), viewforward, viewright, viewup);
	//gEngfuncs.pfnAngleVectors(Vector(0.0f, ucmd->viewangles.y, 0.0f), viewforward, viewright, viewup);
	//
    gEngfuncs.pfnAngleVectors(Vector(0.0f, ucmd->viewangles.y, 0.0f), aimforward, aimright, aimup);
	//
    newforward=DotProduct(forward*viewforward.Normalize(),aimforward)+DotProduct(right*viewright.Normalize(),aimforward)+DotProduct(up*viewup.Normalize(),aimforward);
    newright=DotProduct(forward*viewforward.Normalize(),aimright)+DotProduct(right*viewright.Normalize(),aimright)+DotProduct(up*viewup.Normalize(),aimright);
    newup=DotProduct(forward*viewforward.Normalize(),aimup)+DotProduct(right*viewright.Normalize(),aimup)+DotProduct(up*viewup.Normalize(),aimup);
 
    ucmd->forwardmove=-newforward;
    ucmd->sidemove=newright;
    ucmd->upmove=newup;
    }
}
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void antiaim_six(usercmd_t *ucmd,usercmd_t orig_cmd)
{
	         
	if(!(ucmd->buttons&IN_ATTACK)&&
	   !(ucmd->buttons&IN_USE)&&
           me.alive &&
	   (me.currentWeaponID!=WEAPONLIST_HEGRENADE&&
	    me.currentWeaponID!=WEAPONLIST_FLASHBANG&&
	    me.currentWeaponID!=WEAPONLIST_SMOKEGRENADE))
    {
    Vector viewforward,viewright,viewup,aimforward,aimright,aimup;
    float newforward,newright,newup;
    float forward=orig_cmd.forwardmove;
    float right=orig_cmd.sidemove;
    float up=orig_cmd.upmove;
		//if you do not use (usercmd->buttons & IN_ATTACK) for your nospread
		//you might want to lower this to about 80
		ucmd->viewangles.x=-179;
        ucmd->viewangles.y = ucmd->viewangles.y + 270;
 
    //horizontal velocity movement fix
    gEngfuncs.pfnAngleVectors(Vector(0.0f, orig_cmd.viewangles.y, 0.0f), viewforward, viewright, viewup);
	//gEngfuncs.pfnAngleVectors(Vector(0.0f, ucmd->viewangles.y, 0.0f), viewforward, viewright, viewup);
	//
    gEngfuncs.pfnAngleVectors(Vector(0.0f, ucmd->viewangles.y, 0.0f), aimforward, aimright, aimup);
	//
    newforward=DotProduct(forward*viewforward.Normalize(),aimforward)+DotProduct(right*viewright.Normalize(),aimforward)+DotProduct(up*viewup.Normalize(),aimforward);
    newright=DotProduct(forward*viewforward.Normalize(),aimright)+DotProduct(right*viewright.Normalize(),aimright)+DotProduct(up*viewup.Normalize(),aimright);
    newup=DotProduct(forward*viewforward.Normalize(),aimup)+DotProduct(right*viewright.Normalize(),aimup)+DotProduct(up*viewup.Normalize(),aimup);
 
    ucmd->forwardmove=-newforward;
    ucmd->sidemove=newright;
    ucmd->upmove=newup;
    }
}
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void antiaim_seven(struct usercmd_s* usercmd)
{
       
	if(!(usercmd->buttons&IN_ATTACK)&&
	   !(usercmd->buttons&IN_USE)&&
           me.alive &&
	   (me.currentWeaponID!=WEAPONLIST_HEGRENADE&&
	    me.currentWeaponID!=WEAPONLIST_FLASHBANG&&
	    me.currentWeaponID!=WEAPONLIST_SMOKEGRENADE))
    {
	vec3_t viewforward, viewright, viewup, aimforward, aimright, aimup, v;
	float newforward, newright, newup, fTime;
	float forward = usercmd->forwardmove;
	float right = usercmd->sidemove;
	float up = usercmd->upmove;
	bool movetype_walk = (me.GetMe()->curstate.movetype == MOVETYPE_WALK);
	if(movetype_walk){
		v[0]=0.0f;
		v[1]=usercmd->viewangles[1];
		v[2]=0.0f;
		gEngfuncs.pfnAngleVectors(v, viewforward, viewright, viewup);
	} else {
		gEngfuncs.pfnAngleVectors(usercmd->viewangles, viewforward, viewright, viewup);}
		fTime = gEngfuncs.GetClientTime();
		usercmd->viewangles.x = cos(fTime * 11 * 3.14159265358979323846) * 360.0f;
      	usercmd->viewangles.y = sin(fTime * 11 * 3.14159265358979323846) * 360.0f;
		usercmd->viewangles.x = cos(fTime * 11 * 3.14159265358979323846) * 90.0f;
	if(movetype_walk){
		v[0]=0.0f;
		v[1]=usercmd->viewangles[1];
		v[2]=0.0f;
		gEngfuncs.pfnAngleVectors(v, aimforward, aimright, aimup);
	} else {
		gEngfuncs.pfnAngleVectors(usercmd->viewangles, aimforward, aimright, aimup);}
	float flLen1=(float)sqrt(viewforward[0]*viewforward[0]+viewforward[1]*viewforward[1]+viewforward[2]*viewforward[2]);
	float flLen2=(float)sqrt(viewright[0]*viewright[0]+viewright[1]*viewright[1]+viewright[2]*viewright[2]);
	float flLen3=(float)sqrt(viewup[0]*viewup[0]+viewup[1]*viewup[1]+viewup[2]*viewup[2]);
	NORMALIZEX(viewforward,flLen1);
	NORMALIZEX(viewright,flLen2);
	NORMALIZEX(viewup,flLen3);
	viewforward[0]=forward*viewforward[0];
	viewforward[1]=forward*viewforward[1];
	viewforward[2]=forward*viewforward[2];
	viewright[0]=right*viewright[0];
	viewright[1]=right*viewright[1];
	viewright[2]=right*viewright[2];
	viewup[0]=up*viewup[0];
	viewup[1]=up*viewup[1];
	viewup[2]=up*viewup[2];
	newforward = ( (viewforward[0]*aimforward[0] + viewforward[1]*aimforward[1] + viewforward[2]*aimforward[2])+
                   (viewright[0]*aimforward[0] + viewright[1]*aimforward[1] + viewright[2]*aimforward[2])+
				(viewup[0]*aimforward[0] + viewup[1]*aimforward[1] + viewup[2]*aimforward[2]));
	newright = ( (viewforward[0]*aimright[0] + viewforward[1]*aimright[1] + viewforward[2]*aimright[2])+
                 (viewright[0]*aimright[0] + viewright[1]*aimright[1] + viewright[2]*aimright[2])+
				 (viewup[0]*aimright[0] + viewup[1]*aimright[1] + viewup[2]*aimright[2]));
	newup = ( (viewforward[0]*aimup[0] + viewforward[1]*aimup[1] + viewforward[2]*aimup[2])+
	          (viewright[0]*aimup[0] + viewright[1]*aimup[1] + viewright[2]*aimup[2])+
			  (viewup[0]*aimup[0] + viewup[1]*aimup[1] + viewup[2]*aimup[2]));
	usercmd->forwardmove = newforward;
	usercmd->sidemove = newright;
	usercmd->upmove = newup;
	}
}
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void antiaim_eight(usercmd_t *ucmd,usercmd_t orig_cmd)
{
	       
	if(!(ucmd->buttons&IN_ATTACK)&&
	   !(ucmd->buttons&IN_USE)&&
           me.alive &&
	   (me.currentWeaponID!=WEAPONLIST_HEGRENADE&&
	    me.currentWeaponID!=WEAPONLIST_FLASHBANG&&
	    me.currentWeaponID!=WEAPONLIST_SMOKEGRENADE))
    {
    Vector viewforward,viewright,viewup,aimforward,aimright,aimup;
    float newforward,newright,newup;
    float forward=orig_cmd.forwardmove;
    float right=orig_cmd.sidemove;
    float up=orig_cmd.upmove;
		//if you do not use (usercmd->buttons & IN_ATTACK) for your nospread
		//you might want to lower this to about 80
		ucmd->viewangles.x=89;
        ucmd->viewangles.y = ucmd->viewangles.y + 90;
 
    //horizontal velocity movement fix
    gEngfuncs.pfnAngleVectors(Vector(0.0f, orig_cmd.viewangles.y, 0.0f), viewforward, viewright, viewup);
	//gEngfuncs.pfnAngleVectors(Vector(0.0f, ucmd->viewangles.y, 0.0f), viewforward, viewright, viewup);
	//
    gEngfuncs.pfnAngleVectors(Vector(0.0f, ucmd->viewangles.y, 0.0f), aimforward, aimright, aimup);
	//
    newforward=DotProduct(forward*viewforward.Normalize(),aimforward)+DotProduct(right*viewright.Normalize(),aimforward)+DotProduct(up*viewup.Normalize(),aimforward);
    newright=DotProduct(forward*viewforward.Normalize(),aimright)+DotProduct(right*viewright.Normalize(),aimright)+DotProduct(up*viewup.Normalize(),aimright);
    newup=DotProduct(forward*viewforward.Normalize(),aimup)+DotProduct(right*viewright.Normalize(),aimup)+DotProduct(up*viewup.Normalize(),aimup);
 
    ucmd->forwardmove=newforward;
    ucmd->sidemove=newright;
    ucmd->upmove=newup;
    }
}
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void antiaim_nine(usercmd_t *ucmd,usercmd_t orig_cmd)
{
	        
	if(!(ucmd->buttons&IN_ATTACK)&&
	   !(ucmd->buttons&IN_USE)&&
           me.alive &&
	   (me.currentWeaponID!=WEAPONLIST_HEGRENADE&&
	    me.currentWeaponID!=WEAPONLIST_FLASHBANG&&
	    me.currentWeaponID!=WEAPONLIST_SMOKEGRENADE))
    {
    Vector viewforward,viewright,viewup,aimforward,aimright,aimup;
    float newforward,newright,newup;
    float forward=orig_cmd.forwardmove;
    float right=orig_cmd.sidemove;
    float up=orig_cmd.upmove;
		//if you do not use (usercmd->buttons & IN_ATTACK) for your nospread
		//you might want to lower this to about 80
		ucmd->viewangles.x=89;
        ucmd->viewangles.y = ucmd->viewangles.y + 270;
 
    //horizontal velocity movement fix
    gEngfuncs.pfnAngleVectors(Vector(0.0f, orig_cmd.viewangles.y, 0.0f), viewforward, viewright, viewup);
	//gEngfuncs.pfnAngleVectors(Vector(0.0f, ucmd->viewangles.y, 0.0f), viewforward, viewright, viewup);
	//
    gEngfuncs.pfnAngleVectors(Vector(0.0f, ucmd->viewangles.y, 0.0f), aimforward, aimright, aimup);
	//
    newforward=DotProduct(forward*viewforward.Normalize(),aimforward)+DotProduct(right*viewright.Normalize(),aimforward)+DotProduct(up*viewup.Normalize(),aimforward);
    newright=DotProduct(forward*viewforward.Normalize(),aimright)+DotProduct(right*viewright.Normalize(),aimright)+DotProduct(up*viewup.Normalize(),aimright);
    newup=DotProduct(forward*viewforward.Normalize(),aimup)+DotProduct(right*viewright.Normalize(),aimup)+DotProduct(up*viewup.Normalize(),aimup);
 
    ucmd->forwardmove=newforward;
    ucmd->sidemove=newright;
    ucmd->upmove=newup;
    }
}
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double m_lastUpdateTime=0;
float  timeSinceLastUpdate() { return (float)(ClientTime::current-m_lastUpdateTime); }
void SetUpdated(){m_lastUpdateTime=ClientTime::current;}
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void antiaim_ten(usercmd_t *ucmd,usercmd_t orig_cmd)
{
	         
	if(!(ucmd->buttons&IN_ATTACK)&&
	   !(ucmd->buttons&IN_USE)&&
           me.alive &&
	   (me.currentWeaponID!=WEAPONLIST_HEGRENADE&&
	    me.currentWeaponID!=WEAPONLIST_FLASHBANG&&
	    me.currentWeaponID!=WEAPONLIST_SMOKEGRENADE))
    {
    Vector viewforward,viewright,viewup,aimforward,aimright,aimup;
    float newforward,newright,newup;
    float forward=orig_cmd.forwardmove;
    float right=orig_cmd.sidemove;
    float up=orig_cmd.upmove;
		
	//if you do not use (usercmd->buttons & IN_ATTACK) for your nospread
	//you might want to lower this to about 80
	ucmd->viewangles.x=89;
	static bool bDirection=false;
	if(timeSinceLastUpdate() > 0.1)
	{
		bDirection=!bDirection;
		SetUpdated();
	}
	ucmd->viewangles.y = ucmd->viewangles.y + (bDirection?90:270);
 
    //horizontal velocity movement fix
    gEngfuncs.pfnAngleVectors(Vector(0.0f, orig_cmd.viewangles.y, 0.0f), viewforward, viewright, viewup);
	//gEngfuncs.pfnAngleVectors(Vector(0.0f, ucmd->viewangles.y, 0.0f), viewforward, viewright, viewup);
	//
    gEngfuncs.pfnAngleVectors(Vector(0.0f, ucmd->viewangles.y, 0.0f), aimforward, aimright, aimup);
	//
    newforward=DotProduct(forward*viewforward.Normalize(),aimforward)+DotProduct(right*viewright.Normalize(),aimforward)+DotProduct(up*viewup.Normalize(),aimforward);
    newright=DotProduct(forward*viewforward.Normalize(),aimright)+DotProduct(right*viewright.Normalize(),aimright)+DotProduct(up*viewup.Normalize(),aimright);
    newup=DotProduct(forward*viewforward.Normalize(),aimup)+DotProduct(right*viewright.Normalize(),aimup)+DotProduct(up*viewup.Normalize(),aimup);
 
    ucmd->forwardmove=newforward;
    ucmd->sidemove=newright;
    ucmd->upmove=newup;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void _AntiAim(usercmd_t *ucmd)
{
	switch (cvar.antiaim)
	{
	case 1:
		{
		antiaim_one(ucmd, g_Originalcmd);
	//	useDirCorrection = true;
		}
		break;
	case 2:
		{
		antiaim_two(ucmd, g_Originalcmd);
	//	useDirCorrection = true;
		}
		break;
	case 3:
		{
		antiaim_three(ucmd, g_Originalcmd);
	//	useDirCorrection = true;
		}
		break;
	case 4:
		{
		antiaim_four(ucmd, g_Originalcmd);
	//	useDirCorrection = true;
		}
		break;
	case 5:
		{
		antiaim_five(ucmd, g_Originalcmd);
	//	useDirCorrection = true;
		}
		break;
	case 6:
		{
		antiaim_six(ucmd, g_Originalcmd);
	//	useDirCorrection = true;
		}
		break;
	case 7:
		{
		antiaim_seven(ucmd);
	//	useDirCorrection = true;
		}
		break;
	case 8:
		{
		antiaim_eight(ucmd, g_Originalcmd);
	//	useDirCorrection = true;
		}
		break;
	case 9:
		{
		antiaim_nine(ucmd, g_Originalcmd);
	//	useDirCorrection = true;
		}
		break;
	case 10:
		{
		antiaim_ten(ucmd, g_Originalcmd);
	//	useDirCorrection = true;
		}
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
void vec_dodger(usercmd_t* cmd, usercmd_t orig_cmd)
{
    Vector viewforward, viewright, viewup, aimforward, aimright, aimup;
    float newforward, newright, newup;
	//
    float forward = orig_cmd.forwardmove;
    float right = orig_cmd.sidemove;
    float up = orig_cmd.upmove;
	//
//	float forward = cmd->forwardmove;
//  float right = cmd->sidemove;
//  float up = cmd->upmove;
	//

	//
    //ghetto vec dodger v1.0 by Horndog, yay...
    if(!(cmd->buttons & IN_ATTACK) &&!(cmd->buttons & IN_USE))
    {
		//if you do not use (usercmd->buttons & IN_ATTACK) for your nospread 
		//you might want to lower this to about 80
     //   cmd->viewangles.x = -89; // seg�n wav

		//
        cmd->viewangles.y = cmd->viewangles.y + 180;
    }

    //horizontal velocity movement fix
    g_Engine.pfnAngleVectors(Vector(0.0f, orig_cmd.viewangles.y, 0.0f), viewforward, viewright, viewup);
	//g_Engine.pfnAngleVectors(Vector(0.0f, cmd->viewangles.y, 0.0f), viewforward, viewright, viewup);

	//
    g_Engine.pfnAngleVectors(Vector(0.0f, cmd->viewangles.y, 0.0f), aimforward, aimright, aimup);

	//
    newforward = DotProduct(forward * viewforward.Normalize(), aimforward) + 
		DotProduct(right * viewright.Normalize(), aimforward) + 
		DotProduct(up * viewup.Normalize(), aimforward);

    newright = DotProduct(forward * viewforward.Normalize(), aimright) + 
		DotProduct(right * viewright.Normalize(), aimright) + 
		DotProduct(up * viewup.Normalize(), aimright);

    newup = DotProduct(forward * viewforward.Normalize(), aimup) + 
		DotProduct(right * viewright.Normalize(), aimup) + 
		DotProduct(up * viewup.Normalize(), aimup);

    cmd->forwardmove = newforward;
    cmd->sidemove = newright;
    cmd->upmove = newup;
}
*/

