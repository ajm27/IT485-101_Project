#ifndef __BODY_H__
#define __BODY_H__

#include "mgl_callback.h"

typedef struct Body_S
{
	Vec3D position;
	Vec3D rotation;
	Vec3D scale;
	Vec3D velocity;
	Vec3D acceleration;

	MglCallback touch;

	char  classname[50];

	int   needsBackOff;
	int   backOffDone;
	Vec3D backOffVec;

	BoundingVolume	ent_BB;
}Body;

void	body_reset(Body* body);							// Resets body's pre-physics calculation
void	body_process(Body* body);					// Checks to see if a body needs a back off

#endif