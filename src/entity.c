#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include "obj.h"
#include "boundingbox.h"
#include "body.h"
#include "entity.h"
#include "simple_logger.h"

Entity entList[MAX_ENT];
Weapon weapList[MAX_WEAP];
int ent_count;
int weap_count;

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

Weapon* weapon_Start()
{
	int i;
	for(i = 0; i < 4; i++)
	{
		weapList[i].inuse = 1;
	}
	return weapList;
}

Weapon* weapon_Spawn()
{
	int i;

	for( i = 4; i < MAX_WEAP; i++ )
	{
		if (weapList[i].inuse == 0)
		{
			weapList[i].inuse = 1;
			weap_count++;

			return &weapList[i];
		}
		
		if(i == MAX_WEAP)
			fprintf ( stderr, "Max weapons reached. Please kill some entities before making more." );
	}
	return NULL;
}

Entity* ent_New(const char *name, Vec3D position, BoundingVolume bv, Vec4D colour, int _hasWeapons, int _maxHealth)
{
	Entity *ent;
	ent = ent_Spawn();
	if(!ent) return NULL;
	
	if(bv.selection == 2)
		ent->objModel = obj_load("models/cube.obj");
	if(bv.selection == 1)
		ent->objModel = obj_load("models/handgun.obj");
	ent->health = _maxHealth;
	ent->body.position = position;
	ent->body.rotation = vec3d(0,0,0);
	ent->body.scale = vec3d(0.5,0.5,0.5);
	ent->hasWeapons = _hasWeapons;
	if(ent->hasWeapons = 1)
	{
		ent->inventory = weapon_Start();
		//ent_SetInventory(ent,weapon_setup(ent));
		weapon_setup(ent);
	}
	ent->currentweapon = 0;
	mgl_callback_set(&ent->body.touch,touch_callback,ent);
	setBoundingVolume(&ent->body.ent_BB, bv);
	//slog("%s 's bounding volume set.", name);
	strcpy(ent->body.classname, name);
	ent->texture = NULL;
	ent->colour = colour;

	return ent;
}

Weapon* weapon_setup(Entity* entity)
{
	Weapon *weapons;
	weapons = entity->inventory;
	strcpy(weapons[0].item_name,"weapon_knife");
	strcpy(weapons[0].ammo_type,"none");
	weapons[0].max_ammo  = 0;
	weapons[0].damage	 = 50;
	weapons[0].offset    = vec3d(.5,1.75,.5);
	weapons[0].position  = vec3d(0,0,0);
	weapons[0].rotation  = vec3d(90,90,0);
	weapons[0].scale     = vec3d(.125,.125,.125);
	weapons[0].objmodel  = obj_load("models/knife2.obj");
	weapons[0].colour    = vec4d(0,0,0,1);
	weapons[0].texture	 = LoadSprite("models/cube_text.png",1024,1024);;

	//slog("Weapon set: %s with ammo %s", weapons[0].item_name, weapons[0].ammo_type);

	weapons = entity->inventory;
	strcpy(weapons[1].item_name,"weapon_handgun");
	strcpy(weapons[1].ammo_type,"bullets");
	weapons[1].max_ammo  = 36;
	weapons[1].damage	 = 25;
	weapons[1].offset    = vec3d(.5,1.75,.5);
	weapons[1].position  = vec3d(0,0,0);
	weapons[1].rotation  = vec3d(90,180,0);
	weapons[1].scale     = vec3d(0.25,0.25,0.25);
	weapons[1].objmodel  = obj_load("models/handgun.obj");
	weapons[1].colour    = vec4d(0,0,0,1);
	weapons[1].texture	 = LoadSprite("models/cube_text.png",1024,1024);;

	//slog("Weapon set: %s with ammo %s", weapons[1].item_name, weapons[1].ammo_type);

	weapons = entity->inventory;
	strcpy(weapons[2].item_name,"weapon_assaultrifle");
	strcpy(weapons[2].ammo_type,"bullets");
	weapons[2].max_ammo  = 120;
	weapons[2].damage	 = 35;
	weapons[2].offset    = vec3d(.5,1.75,.5);
	weapons[2].position  = vec3d(0,0,0);
	weapons[2].rotation  = vec3d(90,90,0);
	weapons[2].scale     = vec3d(0.25,0.25,0.25);
	weapons[2].objmodel  = obj_load("models/M16.obj");
	weapons[2].colour    = vec4d(0,0,0,1);
	weapons[2].texture	 = LoadSprite("models/cube_text.png",1024,1024);;

	//slog("Weapon set: %s with ammo %s", weapons[2].item_name, weapons[2].ammo_type);

	weapons = entity->inventory;
	strcpy(weapons[3].item_name,"weapon_grenade");
	strcpy(weapons[3].ammo_type,"grenade");
	weapons[3].max_ammo  = 3;
	weapons[3].damage	 = 105;
	weapons[3].offset    = vec3d(.5,1.75,.5);
	weapons[3].position  = vec3d(0,0,0);
	weapons[3].rotation  = vec3d(90,0,0);
	weapons[3].scale     = vec3d(0.0625,0.0625,0.0625);
	weapons[3].objmodel  = obj_load("models/grenade.obj");
	weapons[3].colour    = vec4d(0,0,0,1);
	weapons[3].texture	 = LoadSprite("models/cube_text.png",1024,1024);;

	//slog("Weapon set: %s with ammo %s", weapons[3].item_name, weapons[3].ammo_type);

	return weapons;
}

Vec3D rtn_weapon_position(Vec3D bodPos, Vec3D bodRot)
{
	Vec3D newPos;

	newPos.x = (sin(bodRot.z * DEGTORAD)) + bodPos.x;
	newPos.y = (-cos(bodRot.z * DEGTORAD)) + bodPos.y;

	//slog("X: %.2f, %.2f Y: %.2f, %.2f \n", sin(bodRot.z * DEGTORAD), -cos(bodRot.z * DEGTORAD), bodPos.x, bodPos.y);
	//slog("X: %.2f \n Y: %.2f \n", newPos.x, newPos.y);
	newPos.z = bodPos.z;

	return newPos;
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

	if(ent->hasWeapons = 1)
	{
		Vec3D temp;
		vec3d_add(temp, rtn_weapon_position(ent->body.position, ent->body.rotation), ent->inventory[ent->currentweapon].offset);
		//slog("BX: %.2f, BY: %.2f, BZ: %.2f \n", ent->body.position.x, ent->body.position.y, ent->body.position.z);
		//slog("X: %.2f, Y: %.2f, Z: %.2f \n", temp.x, temp.y, temp.z);
		obj_draw(
			ent->inventory[ent->currentweapon].objmodel,
			temp,
			ent->inventory[ent->currentweapon].rotation,
			ent->inventory[ent->currentweapon].scale,
			ent->inventory[ent->currentweapon].colour,
			ent->inventory[ent->currentweapon].texture
		);
	}
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