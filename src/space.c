#include <stdlib.h>
#include <glib.h>
#include "vector.h"
#include "boundingbox.h"
#include "body.h"
#include "space.h"
#include "collisions.h"
#include "simple_logger.h"

struct Space_S
{
	GList *bodylist;
	int steps;
	int stepstaken;
	float stepFactor;
}; 

Space* space_New()
{
	Space* space;
	space = (Space *)calloc(1,sizeof(struct Space_S));
    return space;
}

void space_add_body(Space* space, Body* body)
{
	if(!space) return;
	if(!body) return;

	space->bodylist = g_list_append(space->bodylist, body);
}

void space_remove_body(Space* space, Body* body)
{
	if(!space) return;
	if(!body) return;

	space->bodylist = g_list_remove(space->bodylist, body);
}

void space_set_steps(Space* space, int steps)
{
	if(!space) return;
	if(!steps)
	{
		slog("cannot support 0 steps");
		return;
	}

	space->steps = steps;
	space->stepFactor = 1.0/steps;
}

static void space_body_update(Space *space,Body* body)
{
    GList *it;									
    Cube a,b;
    Body *other;
    Vec3D stepVector;
    Vec3D stepOffVector;
    
    if ((!body) || (body->backOffDone))return;				     //if the body does not exist or the backoff has been completely, end method
    
    vec3d_scale(stepVector,body->velocity,space->stepFactor);	 //scale up the stepVector from the body's current velocity by a factor of the stepFactor?
    vec3d_negate(stepOffVector,stepVector);					     //remove the stepVector from the stepOffVector?
    
    vec3d_add(body->position,body->position,stepVector);		 //add the stepVector to the body position
    
	a.x = body->position.x + body->ent_BB.volume.cube.x;		 
    a.y = body->position.y + body->ent_BB.volume.cube.y;
    a.z = body->position.z + body->ent_BB.volume.cube.z;
    a.w = body->ent_BB.volume.cube.w;
    a.h = body->ent_BB.volume.cube.h;
    a.d = body->ent_BB.volume.cube.d;
	
	//slog("%s: Position %.2f, %.2f, %.2f", body->classname, body->position.x, body->position.y, body->position.z);
	//slog("%s: Absolute Bounds %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,", body->classname, a.x, a.y, a.z, a.w, a.h, a.d);

    for (it = space->bodylist;it != NULL;it = g_list_next(it))
    {
        if (!it->data)continue;
        if (it->data == body)continue;
        /*check for collision*/
        other = (Body *)it->data;
        //vec3d_cpy(b,other->position);
		b.x = other->position.x + other->ent_BB.volume.cube.x;		 
		b.y = other->position.y + other->ent_BB.volume.cube.y;
		b.z = other->position.z + other->ent_BB.volume.cube.z;
        b.w = other->ent_BB.volume.cube.w;
        b.h = other->ent_BB.volume.cube.h;
        b.d = other->ent_BB.volume.cube.d;
		
		//slog("%s: %.2f, %.2f, %.2f", other->classname, other->position.x, other->position.y, other->position.z);
		//slog("%s: %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,", other->classname, b.x, b.y, b.z, b.w, b.h, b.d);


        vec3d_add(b,b,other->ent_BB.volume.cube);
		if (ScissorMeXerxes(a,b))
        {
			//slog("ScissorMeXerxes is true");
            /*call touch functions*/
            /*back the fuck off*/
            vec3d_cpy(body->backOffVec, stepOffVector);
            body->backOffDone = 1;
            body->needsBackOff = 1;
            if (body->touch.function)
            {
                body->touch.function(body->touch.data,other);
				//slog("collision");
            }
        }
    }
}

static void space_update(Space *space)
{
    GList *it;
    for (it = space->bodylist;it != NULL;it = g_list_next(it))
    {
        if (!it->data)continue;
        space_body_update(space,(Body*)it->data);
    }
    for (it = space->bodylist;it != NULL;it = g_list_next(it))
    {
        if (!it->data)continue;
        body_process((Body *)it->data);
    }
}

void space_do_step(Space* space)
{
	GList *it;
	if (!space)return;
    if (space->stepstaken == space->steps)
    {
		space->stepstaken = 0;
        for (it = space->bodylist;it != NULL;it = g_list_next(it))
        {
            if (!it->data)continue;
            body_reset((Body *)it->data);
        }
    }
    /*run one iteration of space update*/
    space_update(space);
    /*for each body, update it a little*/
    space->stepstaken++;
}
