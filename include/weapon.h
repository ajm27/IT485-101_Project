#ifndef __WEAPON_H__
#define __WEAPON_H__

#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "vector.h"
#include "entity.h"

#define MAX_WEAP 4

typedef struct Weapon_S
{
	int inuse;

	char item_name[50];
	char ammo_type[50];
	int max_ammo;
	int damage;

	Vec3D offset;

	Body body;

	//struct Weapon *self;
	struct Entity *owner;
	
	Obj	   *objmodel;
	Vec4D   colour;
	Sprite *texture;

	void (*think)(struct Entity *self);
	//void (*update)(struct Entity *self);
	//void (*fire)(struct Entity *self);
	//void (*drop)(struct Entity *self);
} Weapon;

Weapon* weapon_Spawn();
//void weapon_setup(Entity *ent, Weapon *weapons[]);

#endif