#include <stdio.h>
#include <math.h>
#include "vector.h"
#include "boundingbox.h"

BoundingVolume newSphere(Vec3D center,float r)
{
	BoundingVolume bv;
	bv.selection = BV_Sphere;
	bv.volume.sphere.x = center.x;
	bv.volume.sphere.y = center.y;
	bv.volume.sphere.z = center.z;
	bv.volume.sphere.r = r;
	
	return bv;
}

BoundingVolume newCube(Vec3D xyz, Vec3D whd)
{
	BoundingVolume bv;
	bv.selection = BV_Cube;
	bv.volume.cube.x = xyz.x;
	bv.volume.cube.y = xyz.y;
	bv.volume.cube.z = xyz.z;
	bv.volume.cube.w = whd.x;
	bv.volume.cube.h = whd.y;
	bv.volume.cube.d = whd.z;

	return bv;
}

void setBigs(BoundingVolume bv)
{
	bv.volume.cube.XYZ.X = bv.volume.cube.x + bv.volume.cube.w + bv.volume.cube.h + bv.volume.cube.d;
	bv.volume.cube.XYZ.Y = bv.volume.cube.y + bv.volume.cube.w + bv.volume.cube.h + bv.volume.cube.d;
	bv.volume.cube.XYZ.Z = bv.volume.cube.z + bv.volume.cube.w + bv.volume.cube.h + bv.volume.cube.d;
}

int ScissorMeXerxes( BoundingVolume bv1, BoundingVolume bv2 ) // Cube_verus_Cube method
{
	setBigs(bv1);
	setBigs(bv2);
	if (bv1.volume.cube.XYZ.X < bv2.volume.cube.x ||
		bv1.volume.cube.XYZ.Y < bv2.volume.cube.y ||
		bv1.volume.cube.XYZ.Z < bv2.volume.cube.z ||
		bv2.volume.cube.XYZ.X < bv1.volume.cube.x ||
		bv2.volume.cube.XYZ.Y < bv1.volume.cube.y ||
		bv2.volume.cube.XYZ.Z < bv1.volume.cube.z)
	{
		return 0;
	}
	return 1;
}

int Cube_verus_Sphere( BoundingVolume bv1, BoundingVolume bv2 )
{
	
	return 0;
}

int Sphere_verus_Sphere( BoundingVolume bv1, BoundingVolume bv2 )
{
	int d;
	d = (pow((bv1.volume.sphere.x - bv2.volume.sphere.x), 2) +  
		 pow((bv1.volume.sphere.y - bv2.volume.sphere.y), 2) +
		 pow((bv1.volume.sphere.z - bv2.volume.sphere.z), 2));
	if( pow(bv1.volume.sphere.r,2) > d || pow(bv2.volume.sphere.r,2) > d )
	{
		return 1;
	}
	return 0;
}

int checkCollision ( BoundingVolume bv1, BoundingVolume bv2 )
{
	if (bv1.selection == BV_Cube && bv2.selection == BV_Cube)
	{
		fprintf (stderr, "Cube V Cube Checked");
		return ScissorMeXerxes( bv1, bv2 );
	}
	if ((bv1.selection == BV_Cube && bv2.selection == BV_Sphere) || 
			  (bv1.selection == BV_Sphere && bv2.selection == BV_Cube))
	{
		fprintf (stderr, "Sphere V Cube Checked");
		return Cube_verus_Sphere( bv1, bv2 );
	}
	else
	{
		fprintf (stderr, "Sphere V Sphere Checked");
		return Sphere_verus_Sphere( bv1, bv2 );
	}
}