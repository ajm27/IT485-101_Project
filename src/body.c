#include <stdio.h>
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

Body body_Spawn(Vec3D _position, Vec3D _rotation, Vec3D _scale, BoundingVolume	_ent_BB)
{
	Body body;

	vec3d_cpy(body.position, _position);
	vec3d_cpy(body.rotation, _rotation);
	vec3d_cpy(body.scale, _scale);

	body.ent_BB = _ent_BB;

	return body;
}

