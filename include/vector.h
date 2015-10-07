#ifndef __VECTOR_H__
#define __VECTOR_H__

typedef struct
{
    float x,y;
}Vec2D;

typedef struct
{
    float x,y,z;
}Vec3D;

typedef struct
{
    float x,y,z,w;
}Vec4D;

Vec2D vec2d(float x,float y);
Vec3D vec3d(float x,float y, float z);
Vec4D vec4d(float x,float y, float z, float w);

#define vec2d_add(dst,a,b)   (dst.x = a.x+b.x,dst.y = a.y+b.y)
#define vec3d_add(dst,a,b)   (dst.x = a.x+b.x,dst.y = a.y+b.y,dst.z = a.z+b.z)
#define vec4d_add(dst,a,b)   (dst.x = a.x+b.x,dst.y = a.y+b.y,dst.z = a.z+b.z,dst.w = a.w+b.w)

#define vec2d_set(dst, a, b)		 (dst.x = (a), dst.y = (b))
#define vec3d_set(dst, a, b, c)		 (dst.x = (a), dst.y = (b), dst.z = (c))
#define vec4d_set(dst, a, b, c, d)	 (dst.x = (a), dst.y = (b), dst.z = (c), dst.w = (d))

#endif
