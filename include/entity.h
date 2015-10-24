#ifndef __ENTITY_H__
#define __ENTITY_H__

#define MAX_ENT  1048
#define MAX_WEAP 4

#include <SDL.h>
#include <SDL_image.h>
#include "obj.h"
#include "weapon.h"

typedef struct Weapon_S 
{
	int inuse;

	char item_name[50];
	char ammo_type[50];
	int max_ammo;
	int damage;

	Vec3D offset;
	Vec3D position;
	Vec3D rotation;
	Vec3D scale;

	Obj	   *objmodel;
	Vec4D   colour;
	Sprite *texture;

} Weapon;

enum {
	ENTITY_NONE = 0,
	ENTITY_PLAYER,
	ENTITY_GUARD,
	ENTITY_HEAVYG,
	ENTITY_ARMOUREDG
} Entity_States;

typedef struct Entity 
{
	int		inuse;
	
	int		classtype;		    // type of entity spawned
	int		uid;		/**<unique id of this entity*/

	Body    body;

	struct Entity	*self;		// points to self
	struct Entity	*owner;		// points to who owns the entity
	struct Entity	*target;	// waypoint of entity to move to onSpawn
	
	Obj	    *objModel;
	Vec4D   colour;
	Sprite  *texture;

	int		hasWeapons;
	
	int		maxHealth;
	int		health;

	Weapon *inventory;
	int		currentweapon;

	void	(*think)(struct Entity *self);		// pointer to entity's think function
	void	(*update)(struct Entity *self);		// pointer to entity's update function
	void	(*attack)(struct Entity *self);		// pointer to entity's attack function
	void	(*die)(struct Entity *self);		// pointer to entity's die function
}Entity;

Entity* ent_Spawn();										// Brings entity into game world
Entity* ent_New(const char *_name, int entType);
//void	ent_SetInventory(Entity *ent, Weapon *weapons);
void	ent_Info(Entity *ent);
void	ent_DrawPlayer(Entity* ent, float camChange);
void	ent_Draw(Entity* ent);
void	ent_DrawAll();
void	ent_CheckCollision ( Entity* self, Entity* other );	// Checks collision between two entities
void	ent_Kill (Entity* ent);								// Removes entity from world and frees up memory

Weapon* weapon_Start();
Weapon* weapon_Spawn();
Weapon* weapon_setup(Entity *ent, int entType);
void	weapon_Switch(Entity *ent, int i);

void	touch_callback(void *data, void *context);
#endif