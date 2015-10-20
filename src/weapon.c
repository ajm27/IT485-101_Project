//#include <stdio.h>
//#include <string.h>
//#include <SDL.h>
//#include <SDL_image.h>
//#include "obj.h"
//#include "vector.h"
//#include "mgl_callback.h"
#include "boundingbox.h"
#include "body.h"
#include "simple_logger.h"
#include "entity.h"
#include "weapon.h"

Weapon weapList[MAX_WEAP];
int weap_count;

Weapon* weapon_Spawn()
{
	int i;

	for( i = 0; i < MAX_WEAP; i++ )
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

void weapon_setup(Entity *ent, Weapon *weapons[])
{
	weapons[0] = weapon_Spawn();
	strcpy(weapons[0]->item_name,"weapon_knife");
	strcpy(weapons[0]->ammo_type,"none");
	weapons[0]->max_ammo = 0;
	weapons[0]->damage	 = 50;
	weapons[0]->offset   = vec3d(1.1,1.1,1.1);
	weapons[0]->body	 = body_Spawn(vec3d(0,0,0), vec3d(0,0,0), vec3d(0,0,0), newCube(vec3d(-0.25,-0.25,-0.25),vec3d(-0.25,-0.25,-0.25)));
	weapons[0]->owner    = ent;
	weapons[0]->objmodel = obj_load("models/knife.obj");
	weapons[0]->colour   = vec4d(0,0,0,1);
	weapons[0]->texture	 = NULL;

	slog("Knife set: %s with ammo %s", weapons[0]->item_name, weapons[0]->ammo_type);

	weapons[1] = weapon_Spawn();
	strcpy(weapons[1]->item_name,"weapon_handgun");
	strcpy(weapons[1]->ammo_type,"bullets");
	weapons[1]->max_ammo = 36;
	weapons[1]->damage	 = 25;
	weapons[1]->offset   = vec3d(1.1,1.1,1.1);
	weapons[1]->body	 = body_Spawn(vec3d(0,0,0), vec3d(0,0,0), vec3d(0,0,0), newCube(vec3d(-0.25,-0.25,-0.25),vec3d(-0.25,-0.25,-0.25)));
	weapons[1]->owner    = ent;
	weapons[1]->objmodel = obj_load("models/handgun.obj");
	weapons[1]->colour   = vec4d(0,0,0,1);
	weapons[1]->texture	 = NULL;

	slog("Knife set: %s with ammo %s", weapons[1]->item_name, weapons[1]->ammo_type);

	weapons[2] = weapon_Spawn();
	strcpy(weapons[2]->item_name,"weapon_assaultrifle");
	strcpy(weapons[2]->ammo_type,"bullets");
	weapons[2]->max_ammo = 120;
	weapons[2]->damage	 = 35;
	weapons[2]->offset   = vec3d(1.1,1.1,1.1);
	weapons[2]->body	 = body_Spawn(vec3d(0,0,0), vec3d(0,0,0), vec3d(0,0,0), newCube(vec3d(-0.25,-0.25,-0.25),vec3d(-0.25,-0.25,-0.25)));
	weapons[2]->owner    = ent;
	weapons[2]->objmodel = obj_load("models/M16.obj");
	weapons[2]->colour   = vec4d(0,0,0,1);
	weapons[2]->texture	 = NULL;

	slog("Knife set: %s with ammo %s", weapons[2]->item_name, weapons[2]->ammo_type);

	weapons[3] = weapon_Spawn();
	strcpy(weapons[3]->item_name,"weapon_grenade");
	strcpy(weapons[3]->ammo_type,"grenade");
	weapons[3]->max_ammo = 3;
	weapons[3]->damage	 = 105;
	weapons[3]->offset   = vec3d(1.1,1.1,1.1);
	weapons[3]->body	 = body_Spawn(vec3d(0,0,0), vec3d(0,0,0), vec3d(0,0,0), newCube(vec3d(-0.25,-0.25,-0.25),vec3d(-0.25,-0.25,-0.25)));
	weapons[3]->owner    = ent;
	weapons[3]->objmodel = obj_load("models/grenade.obj");
	weapons[3]->colour   = vec4d(0,0,0,1);
	weapons[3]->texture	 = NULL;

	slog("Knife set: %s with ammo %s", weapons[3]->item_name, weapons[3]->ammo_type);

	memcpy(ent->inventory,weapons,sizeof(weapons)); 
}

//Weapon weaponList[] =
//{
//	{NULL},
//
//	{
//		1,
//		"weapon_knife",
//		"None",
//		0,
//		50,
//		vec3d(1.1,1.1,1.1),
//		body_Spawn(vec3d(0,0,0),vec3d(0,0,0),vec3d(0,0,0),newCube(vec3d(-0.25,-0.25,-0.25),vec3d(0.25,0.25,0.25))),
//		NULL,
//		obj_load("model/knife.obj"),
//		vec4d(0,0,0,1),
//		NULL
//	},
//
//	{
//		2,
//		"weapon_handgun",
//		"bullets",
//		36,
//		25,
//		vec3d(1.1,1.1,1.1),
//		body_Spawn(vec3d(0,0,0),vec3d(0,0,0),vec3d(0,0,0),newCube(vec3d(-0.25,-0.25,-0.25),vec3d(0.25,0.25,0.25))),
//		NULL,
//		obj_load("model/handgun.obj"),
//		vec4d(0,0,0,1),
//		NULL
//	},
//
//	{
//		3,
//		"weapon_assault_rifle",
//		"bullets",
//		120,
//		35,
//		vec3d(1.1,1.1,1.1),
//		body_Spawn(vec3d(0,0,0),vec3d(0,0,0),vec3d(0,0,0),newCube(vec3d(-0.25,-0.25,-0.25),vec3d(0.25,0.25,0.25))),
//		NULL,
//		obj_load("model/M16.obj"),
//		vec4d(0,0,0,1),
//		NULL
//	},
//
//	{
//		4,
//		"weapon_grenade",
//		"grenade",
//		3,
//		105,
//		vec3d(1.1,1.1,1.1),
//		body_Spawn(vec3d(0,0,0),vec3d(0,0,0),vec3d(0,0,0),newCube(vec3d(-0.25,-0.25,-0.25),vec3d(0.25,0.25,0.25))),
//		NULL,
//		obj_load("model/grenade.obj"),
//		vec4d(0,0,0,1),
//		NULL
//	},
//};


//Weapon weapList[4];
//int weap_count;
//
//Weapon *weapon_Spawn()
//{
//	int i;
//
//	for( i = 0; i < 4; i++ )
//	{
//		if (weapList[i].inuse == 0)
//		{
//			weapList[i].inuse = 1;
//			weap_count++;
//
//			return &weapList[i];
//		}
//		
//		if(i == 4)
//			fprintf ( stderr, "Max entities reached. Please kill some entities before making more." );
//	}
//	return NULL;
//}
//
//void weapon_Setup(Entity *ent, Space *space)
//{
//	ent->inventory[0] = weapon_Spawn();
//	space_add_body(space,ent->inventory[0]->body);
//	strcpy(ent->inventory[0]->item_name, "knife");
//	strcpy(ent->inventory[0]->ammo_type, "NULL");
//	ent->inventory[0]->max_ammo = -1;
//	ent->inventory[0]->damage   = 50;
//	ent->inventory[0]->offset   = vec3d(1.1,1.1,1.1);
//	//mgl_callback_set(&ent->inventory[0]->body->touch, touch_callback_knife, &ent->inventory[0]);
//	ent->inventory[0]->body	   = body_Spawn(vec3d(0,0,0), vec3d(0,0,0), vec3d(0,0,0), 
//											vec3d(0,0,0), vec3d(0,0,0), 
//											"knife", 0, 0, vec3d(0,0,0), 
//											newCube(vec3d(-0.5,-0.5,-0.5),vec3d(0.5,0.5,0.5))//,
//											/*ent->inventory[0]->body->touch*/);
//	//ent->inventory[0]->self = &ent->inventory[0];
//	ent->inventory[0]->owner    = ent;
//	ent->inventory[0]->objmodel = obj_load("model/knife.obj"); //export in blender
//	ent->inventory[0]->colour   = vec4d(0,0,0,1);
//	ent->inventory[0]->texture  = NULL;	
//
//
//
//	ent->inventory[1] = weapon_Spawn();
//	space_add_body(space,ent->inventory[1]->body);
//	strcpy(ent->inventory[1]->item_name, "handgun");
//	strcpy(ent->inventory[1]->ammo_type, "bullets");
//	ent->inventory[1]->max_ammo = 36;
//	ent->inventory[1]->damage   = 25;
//	ent->inventory[1]->offset   = vec3d(1.1,1.1,1.1);
//	ent->inventory[1]->body	   = NULL;
//	//ent->inventory[1]->self = &ent->inventory[1];
//	ent->inventory[1]->owner    = ent;
//	ent->inventory[1]->objmodel = obj_load("model/handgun.obj");
//	ent->inventory[1]->colour   = vec4d(0,0,0,1);
//	ent->inventory[1]->texture  = NULL;
//
//	ent->inventory[2] = weapon_Spawn();
//	space_add_body(space,ent->inventory[2]->body);
//	strcpy(ent->inventory[2]->item_name, "assault_rifle");
//	strcpy(ent->inventory[2]->ammo_type, "bullets");
//	ent->inventory[2]->max_ammo = 120;
//	ent->inventory[2]->damage   = 37;
//	ent->inventory[2]->offset   = vec3d(1.1,1.1,1.1);
//	ent->inventory[2]->body	   = NULL;
//	//ent->inventory[2]->self = &ent->inventory[2];
//	ent->inventory[2]->owner    = ent;
//	ent->inventory[2]->objmodel = obj_load("model/M16.obj"); //export in blender
//	ent->inventory[2]->colour   = vec4d(0,0,0,1);
//	ent->inventory[2]->texture  = NULL;
//
//	ent->inventory[3] = weapon_Spawn();
//	space_add_body(space,ent->inventory[3]->body);
//	strcpy(ent->inventory[3]->item_name, "grenade");
//	strcpy(ent->inventory[3]->ammo_type, "grenade");
//	ent->inventory[3]->max_ammo = 3;
//	ent->inventory[3]->damage   = 105;
//	ent->inventory[3]->offset   = vec3d(1.1,1.1,1.1);
//	ent->inventory[3]->body	   = NULL;
//	//ent->inventory[3]->self = &ent->inventory[3];
//	ent->inventory[3]->owner    = ent;
//	ent->inventory[3]->objmodel = obj_load("model/grenade.obj"); //find and export in blender
//	ent->inventory[3]->colour   = vec4d(0,0,0,1);
//	ent->inventory[3]->texture  = NULL;
//}
//
////void weapon_Equip(Entity *ent, int weaponindex)
////{
////	
////}
//
//void weapon_Switch(Entity *ent)
//{
//	ent->currentweapon++;
//
//	if(ent->currentweapon >= 4)
//	{
//		ent->currentweapon = 0;
//	}	
//
//	//weapon_Equip(ent, ent->currentweapon);
//}
//
//void touch_callback_knife(void *data, void *context)
//{
//    slog("knife callback");
//}