#include <stdio.h>
#include <string.h>
#include "vector.h"
#include "boundingbox.h"
#include "body.h"

void body_reset(Body *body)
{
    if (!body)return;
    body->needsBackOff = 0;
    body->backOffDone = 0;    
}

void body_process(Body *body)
{
    if (!body)return;
    if (body->needsBackOff )
    {
        vec3d_add(body->position,body->position,body->backOffVec);
    }
}

Body* body_Spawn(Vec3D _position, Vec3D _rotation, Vec3D _scale,
				Vec3D _velocity, Vec3D _acceleration, MglCallback _touch, 
				char _classname[50], int _needsBackOff, int _backOffDone,
				Vec3D _backOffVec, BoundingVolume _ent_BB)
{
	Body body;

	body.position	  = _position;
	body.rotation	  = _rotation;
	body.scale		  = _scale;
	body.velocity	  = _velocity;
	body.acceleration = _acceleration;
	body.touch		  = _touch;
	strcpy(body.classname, _classname);
	body.needsBackOff = _needsBackOff;
	body.backOffDone  = _backOffDone;
	body.backOffVec	  = _backOffVec;
	body.ent_BB		  = _ent_BB;
}

