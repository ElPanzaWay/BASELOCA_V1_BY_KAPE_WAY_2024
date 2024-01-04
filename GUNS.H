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
ID   NAME                  SPEED   CLIP   AMMO   AID   ANAME             COST   ACOST   BUYNAME   BUYNAME2   
 1   weapon_p228             250     13     52     9   ammo_357sig        600      50   p228      228compact 
     weapon_shield             0      0      0     0                     2200       0   shield               
 3   weapon_scout            260     10     90     2   ammo_762nato      2750      80   scout                
 4   weapon_hegrenade        250             1    12                      300       0   hegren               
 5   weapon_xm1014           240      7     32     5   ammo_buckshot     3000      65   xm1014    autoshotgun
 6   weapon_c4               250      0      1    14                        0       0                        
 7   weapon_mac10            250     30    100     6   ammo_45acp        1400      25   mac10                
 8   weapon_aug              240     30     90     4   ammo_556nato      3500      60   aug       bullpup    
 9   weapon_smokegrenade     250             1    13                      300       0   sgren                
10   weapon_elite            250     30    120    10   ammo_9mm           800      20   elites               
11   weapon_fiveseven        250     20    100     7   ammo_57mm          750      50   fn57      fiveseven  
12   weapon_ump45            250     25    100     6   ammo_45acp        1700      25   ump45                
13   weapon_sg550            210     30     90     4   ammo_556nato      4200      60   sg550     krieg550   
14   weapon_galil            240     35     90     4   ammo_556nato      2000      60   galil     defender   
15   weapon_famas            240     25     90     4   ammo_556nato      2250      60   famas     clarion    
16   weapon_usp              250     12    100     6   ammo_45acp         500      25   usp       km45       
17   weapon_glock18          250     20    120    10   ammo_9mm           400      20   glock     9x19mm     
18   weapon_awp              210     10     30     1   ammo_338magnum    4750     125   awp       magnum     
19   weapon_mp5navy          250     30    120    10   ammo_9mm          1500      20   mp5       smg        
20   weapon_m249             220    100    200     3   ammo_556natobox   5750      60   m249                 
21   weapon_m3               230      8     32     5   ammo_buckshot     1700      65   m3        12gauge    
22   weapon_m4a1             230     30     90     4   ammo_556nato      3100      60   m4a1                 
23   weapon_tmp              250     30    120    10   ammo_9mm          1250      20   tmp       mp         
24   weapon_g3sg1            210     20     90     2   ammo_762nato      5000      80   g3sg1     d3au1      
25   weapon_flashbang        250             2    11                      200       0   flash                
26   weapon_deagle           250      7     35     8   ammo_50ae          650      40   deagle    nighthawk  
27   weapon_sg552            235     30     90     4   ammo_556nato      3500      60   sg552     krieg552   
28   weapon_ak47             221     30     90     2   ammo_762nato      2500      80   ak47      cv47       
29   weapon_knife            250      0      0     0                        0       0                        
30   weapon_p90              245     50    100     7   ammo_57mm         2350      50   p90       c90
*/

//-------------------------------------------------------------------//

#define MAX_WEAPONS		32		// ???
#define MAX_WEAPON_NAME 50 //32

#define WEAPONLIST_NONE 0
#define WEAPONLIST_P228		1
#define	WEAPONLIST_UNKNOWN1	2
#define	WEAPONLIST_SCOUT	3
#define	WEAPONLIST_HEGRENADE 4
#define	WEAPONLIST_XM1014 5
#define	WEAPONLIST_C4 6
#define	WEAPONLIST_MAC10 7
#define	WEAPONLIST_AUG 8
#define	WEAPONLIST_SMOKEGRENADE 9
#define	WEAPONLIST_ELITE 10
#define	WEAPONLIST_FIVESEVEN 11
#define	WEAPONLIST_UMP45 12
#define	WEAPONLIST_SG550 13
#define	WEAPONLIST_GALIL 14
#define	WEAPONLIST_FAMAS 15
#define	WEAPONLIST_USP 16
#define	WEAPONLIST_GLOCK18 17
#define	WEAPONLIST_AWP 18
#define	WEAPONLIST_MP5 19
#define	WEAPONLIST_M249 20
#define	WEAPONLIST_M3 21
#define	WEAPONLIST_M4A1 22
#define	WEAPONLIST_TMP 23
#define	WEAPONLIST_G3SG1 24
#define	WEAPONLIST_FLASHBANG 25
#define	WEAPONLIST_DEAGLE 26
#define	WEAPONLIST_SG552 27
#define	WEAPONLIST_AK47 28
#define	WEAPONLIST_KNIFE 29
#define	WEAPONLIST_P90 30

#define GLOCK18_BURST (1 << 1)
#define USP_SILENCER (1 << 0)
#define ELITE_LEFT (1 << 4)
#define M4A1_SILENCER (1 << 2)
#define FAMAS_BURST (1 << 4)

#define VECTOR_CONE_5DEGREES 0.04362
#define VECTOR_CONE_10DEGREES 0.08716
#define VECTOR_CONE_20DEGREES 0.17365

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

#define WALL_PEN0 0
#define WALL_PEN1 1
#define WALL_PEN2 2
#define WALL_PEN3 3

//-------------------------------------------------------------------//

enum
{
	BULLETTYPE_0=0,
	BULLETTYPE_1=1,
	BULLETTYPE_2=2,
	BULLETTYPE_3=3,
	BULLETTYPE_4=4,
	BULLETTYPE_5=5,
	BULLETTYPE_6=6,
	BULLETTYPE_7=7,
	BULLETTYPE_8=8,
	BULLETTYPE_9=9,
	BULLETTYPE_10=10,
	BULLETTYPE_11=11,
	BULLETTYPE_12=12,
	BULLETTYPE_13=13,
	BULLETTYPE_14=14,
	BULLETTYPE_15=15
};

enum Bullet
{
    BULLET_NONE,
    BULLET_PLAYER_9MM,
    BULLET_PLAYER_MP5,
    BULLET_PLAYER_357,
    BULLET_PLAYER_BUCKSHOT,
    BULLET_PLAYER_CROWBAR,
    BULLET_MONSTER_9MM,
    BULLET_MONSTER_MP5,
    BULLET_MONSTER_12MM,
    BULLET_PLAYER_45ACP,
    BULLET_PLAYER_338MAG,
    BULLET_PLAYER_762MM,
    BULLET_PLAYER_556MM,
    BULLET_PLAYER_50AE,
    BULLET_PLAYER_57MM,
    BULLET_PLAYER_357SIG,
};

#define BULLET_NONE BULLETTYPE_0
#define BULLET_AK47 BULLETTYPE_11
#define BULLET_AUG BULLETTYPE_12
#define BULLET_AWP BULLETTYPE_10
#define BULLET_DEAGLE BULLETTYPE_13
#define BULLET_ELITE BULLETTYPE_1
#define BULLET_FIVESEVEN BULLETTYPE_15
#define BULLET_G3SG1 BULLETTYPE_11
#define BULLET_GLOCK18 BULLETTYPE_1
#define BULLET_M249 BULLETTYPE_12
#define BULLET_M4A1 BULLETTYPE_12
#define BULLET_MAC10 BULLETTYPE_9
#define BULLET_MP5 BULLETTYPE_1
#define BULLET_P228 BULLETTYPE_15
#define BULLET_P90 BULLETTYPE_14
#define BULLET_SCOUT BULLETTYPE_11
#define BULLET_SG550 BULLETTYPE_12
#define BULLET_SG552 BULLETTYPE_12
#define BULLET_TMP BULLETTYPE_1
#define BULLET_UMP45 BULLETTYPE_9
#define BULLET_USP BULLETTYPE_9
#define BULLET_M3 BULLETTYPE_0
#define BULLET_XM1014 BULLETTYPE_0
#define BULLET_GALIL BULLETTYPE_12
#define BULLET_FAMAS BULLETTYPE_12

//-------------------------------------------------------------------//

struct HlWeaponInfo
{
	char	szName[MAX_WEAPON_NAME];
	int		iAmmoType;
	int		iAmmo2Type;
	int		iMax1;
	int		iMax2;
	int		iSlot;
	int		iSlotPos;
	int		iFlags;
	int		iId;
	int		iClip;
	int ClipCap;
	int penetrate;
	float distance;
	int bullettype;
	float wallpierce1;
	float wallpierce2;
	int damage1;
	int damage2;
};

//-------------------------------------------------------------------//