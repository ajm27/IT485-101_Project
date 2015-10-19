#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include "obj.h"
#include "boundingbox.h"
#include "body.h"
#include "entity.h"
#include "weapon.h"
#include "simple_logger.h"

Entity entList[MAX_ENT];
int ent_count;

Entity* ent_Spawn()
{
	int i;

	for( i = 0; i < MAX_ENT; i++ )
	{
		if (entList[i].inuse == 0)
		{
			entList[i].inuse = 1;
			ent_count++;

			return &entList[i];
		}
		
		if(i == MAX_ENT)
			fprintf ( stderr, "Max entities reached. Please kill some entities before making more." );
	}
	return NULL;
}

Entity* ent_New(const char *name, Vec3D position, BoundingVolume bv, Vec4D colour)
{
	Entity *ent;
	ent = ent_Spawn();
	if(!ent) return;
	
	if(bv.selection == 2)
		ent->objModel = obj_load("models/cube.obj");
	if(bv.selection == 1)
		ent->objModel = obj_load("models/handgun.obj");
	ent->body.position = position;
	ent->body.rotation = vec3d(0,0,0);
	ent->body.scale = vec3d(0.5,0.5,0.5);
	mgl_callback_set(&ent->body.touch,touch_callback,ent);
	setBoundingVolume(&ent->body.ent_BB, bv);
	slog("%s 's bounding volume set.", name);
	strcpy(ent->body.classname, name);
	ent->texture = NULL;
	ent->colour = colour;

	return ent;
}

void ent_Draw(Entity *ent)
{
	if (!ent) return;

	obj_draw(
		ent->objModel,
		ent->body.position,
		ent->body.rotation,
		ent->body.scale,
		ent->colour,
		ent->texture
	);
}

void ent_DrawAll()
{
    int i;
    for (i = 0;i < 1048/*ENT_MAX*/;i++)
    {
        if (entList[i].inuse)
        {
            ent_Draw(&entList[i]);
			//slog("Entity drawn!");
        }
    }
}


void touch_callback(void *data, void *context)
{
    Entity *me,*other;
    Body *obody;
    if ((!data)||(!context))return;
    me = (Entity *)data;
    obody = (Body *)context;
    if (1/*entity_is_entity(obody->touch.data)*/)
    {
        other = (Entity *)obody->touch.data;
        //slog("%s is ",other->name);
    }
    //slog("touching me.... touching youuuuuuuu");
}

void ent_Kill(Entity* ent)
{
	ent_count--;
	ent->inuse = 0;
}