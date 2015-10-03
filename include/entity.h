#ifndef __ENTITY_H__
#define __ENTITY_H__

#define MAX_ENT 255

typedef struct Body
{
	Vec3D position;
	Vec3D rotation;
	Vec3D scale;
	Vec3D velocity;
	Vec3D acceleration;

	BoundingVolume*	ent_BB;
}Body;

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

Entity* Spawn_Ent();										// Brings entity into game world
void	entDraw();
void	entCheckCollision ( Entity* self, Entity* other );	// Checks collision between two entities
void	Kill_Ent (Entity* ent);								// Removes entity from world and frees up memory

#endif