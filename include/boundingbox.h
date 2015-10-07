#ifndef __BOUNDNIGBOX_H__
#define __BOUNDNIGBOX_H__

typedef struct
{
	float X, Y, Z;  // x, y ,z coordinates for the opposite corner of the cube
}BigXYZ;

typedef struct
{
	float x, y, z;	// x, y, z coordinates in space, the top-left-front corner
	float w, h, d;	// width, height, depth of bounding box
	BigXYZ XYZ;		
}Cube;

typedef struct 
{
	float x, y, z;	// x, y, z coordinates in space, the center
	float r;		// radius of the sphere
}Sphere;

typedef union		// list of the possible volume-types used for bounding boxes
{
	Sphere sphere;
	Cube cube;
}VolumeType;

typedef enum		// enum to allow selection of the volume-type
{
	BV_None = 0,
	BV_Sphere,
	BV_Cube
}VolumeSelection;

typedef struct		// description of the bounding volume
{
	VolumeType volume;
	VolumeSelection selection;
}BoundingVolume;

BoundingVolume newSphere(Vec3D center,float r);
BoundingVolume newCube(Vec3D xyz, Vec3D whd);
void setBoundingVolume(BoundingVolume* bvp, BoundingVolume bv);
void setBigs(BoundingVolume bv);
int checkCollision( BoundingVolume bv1, BoundingVolume bv2 );
#endif