//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

#ifndef NOSPREAD5_H
#define NOSPREAD5_H

//-------------------------------------------------------------------//

void NA_GetSpreadXY(unsigned int seed, int future, float* vec, bool simulate = false);
void NA_GetSpreadOffset(unsigned int seed, int future, float* inangles, float* outangles);
void NA_VectorAngles(const float* forward, float* angles);
void NA_MakeAngle(float* angles, struct usercmd_s* cmd);
void NA_FixMoveStart(struct usercmd_s* cmd);
void NA_FixMoveEnd(struct usercmd_s* cmd);
void NA_NoSpread(usercmd_s *cmd);

//-------------------------------------------------------------------//

#endif

//-------------------------------------------------------------------//
