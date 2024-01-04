//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

#ifndef NOSPREAD5NEW_H
#define NOSPREAD5NEW_H

//-------------------------------------------------------------------//

void NA_GetSpreadXY(unsigned int seed, int future, float* vec, bool simulate = false);
void NA_GetSpreadOffset(unsigned int seed, int future, float* inangles, float* outangles);
void NA_VectorAngles(const float* forward, float* angles);
void NA_MakeAngle(float* angles, struct usercmd_s* cmd);
void NA_FixMoveStart(struct usercmd_s* cmd);
void NA_FixMoveEnd(struct usercmd_s* cmd);
void NA_NoSpread(usercmd_s *cmd);

//-------------------------------------------------------------------//

void NA_UpdateWeaponData();
void NA_Simulate(float &m_flAccuracy, float &m_flSpread);
void NA_ItemPostFrame(struct usercmd_s* cmd);
void NA_ItemPreFrame(struct local_state_s *from, 
				  struct local_state_s *to, 
				  struct usercmd_s *usercmd, 
				  int runfuncs, 
				  double time, 
				  unsigned int random_seed);

//-------------------------------------------------------------------//

#endif

//-------------------------------------------------------------------//
