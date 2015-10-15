#include <stdio.h>
#include <math.h>
#include "simple_logger.h"
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

void setBoundingVolume(BoundingVolume* bvp, BoundingVolume bv)
{
	if(!bvp) return;

	bvp->selection = bv.selection;
	bvp->volume = bv.volume;
}

void setBigs( Cube cube )
{
	cube.XYZ.X = cube.x + cube.w + cube.h + cube.d;
	cube.XYZ.Y = cube.y + cube.w + cube.h + cube.d;
	cube.XYZ.Z = cube.z + cube.w + cube.h + cube.d;
}

int ScissorMeXerxes( Cube a, Cube b ) // Cube_verus_Cube method
{
	/*setBigs(a);
	setBigs(b);*/
	if ((a.x > b.x + b.w) || (b.x > a.x + a.w) ||
        (a.y > b.y + b.h) || (b.y > a.y + a.h) ||
        (a.z > b.z + b.d) || (b.z > a.z + a.d))
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
		//fprintf (stderr, "Cube V Cube Checked");
		//return ScissorMeXerxes( bv1, bv2 );
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