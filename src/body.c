#include <stdio.h>
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

