#ifndef __ENTITY_H__
#define __ENTITY_H__

#define MAX_ENT 1048

typedef struct Entity 
{
	int		inuse;
	int		uid;		/**<unique id of this entity*/

	Vec4D   colour;
	Sprite  *texture;

	Body    body;

	Obj	    *objModel;

	struct Entity	*self;		// points to self
	struct Entity	*owner;		// points to who owns the entity
	struct Entity	*target;	// waypoint of entity to move to onSpawn

	char	classname[50];		// type of entity spawned

	void	(*think)(struct Entity *self);		// pointer to entity's think function
	void	(*update)(struct Entity *self);		// pointer to entity's update function
	void	(*attack)(struct Entity *self);		// pointer to entity's attack function
	void	(*die)(struct Entity *self);		// pointer to entity's die function
}Entity;

Entity* ent_Spawn();										// Brings entity into game world
Entity* ent_New(const char *name, Vec3D position, BoundingVolume bv);
void	ent_Draw();
void	ent_DrawAll();
void	ent_CheckCollision ( Entity* self, Entity* other );	// Checks collision between two entities
void	ent_Kill (Entity* ent);								// Removes entity from world and frees up memory
void	touch_callback(void *data, void *context);
#endif