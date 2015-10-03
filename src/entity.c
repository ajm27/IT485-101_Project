#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include "obj.h"
#include "boundingbox.h"

#include "entity.h"

Entity entList[MAX_ENT];
int ent_count;

Entity* Spawn_Ent()
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
		
		fprintf ( stderr, "Max entities reached. Please kill some entities before making more." );
	}
	return NULL;
}

void entDraw(Entity *ent)
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

void KillEnt(Entity* ent)
{
	ent_count--;
	ent->inuse = 0;
}