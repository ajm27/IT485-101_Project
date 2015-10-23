/**
 * gametest3d
 * @license The MIT License (MIT)
 *   @copyright Copyright (c) 2015 EngineerOfLies
 *    Permission is hereby granted, free of charge, to any person obtaining a copy
 *    of this software and associated documentation files (the "Software"), to deal
 *    in the Software without restriction, including without limitation the rights
 *    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the Software is
 *    furnished to do so, subject to the following conditions:
 *    The above copyright notice and this permission notice shall be included in all
 *    copies or substantial portions of the Software.
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *    SOFTWARE.
 */
#include <math.h>
#include <glib.h>
#include "simple_logger.h"
#include "graphics3d.h"
#include "shader.h"
#include "obj.h"
#include "vector.h"
#include "sprite.h"
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include "obj.h"
#include "boundingbox.h"
#include "body.h"
#include "entity.h"
#include "collisions.h"
#include "space.h"
#include "weapon.h"

Vec3D rtn_camera_position(Vec3D camPos, Vec3D camRot, Vec3D bodPos, Vec3D bodRot);
Vec3D rtn_camera_rotation(Vec3D camPos, Vec3D camRot, Vec3D bodPos, Vec3D bodRot);
void set_camera(Vec3D position, Vec3D rotation);

int main(int argc, char *argv[])
{
    GLuint vao;
    float r = 0;
    GLuint triangleBufferObject;
    char bGameLoopRunning = 1;
    Vec3D cameraPosition = {-34,-52,19.3};
    Vec3D cameraRotation = {57,0,0};
	Vec3D _origin = {0.0, 0.0, 0.0};
    SDL_Event e;
    Obj *obj,*bgobj;
    Sprite *texture,*bgtext;

	Entity *player, *guard, *hguard, *aguard;
	Space *space;

	Weapon knife, handgun, assault, grenade;
	Weapon *weapons[4];

	//GList *weapons;
	//g_list_append(weapons, knife);
	//g_list_append(weapons, handgun);
	//g_list_append(weapons, assault);
	//g_list_append(weapons, grenade);

    const float triangleVertices[] = {
        0.0f, 0.5f, 0.0f, 1.0f,
        0.5f, -0.366f, 0.0f, 1.0f,
        -0.5f, -0.366f, 0.0f, 1.0f,
        //next part contains vertex colors
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f  
    }; //we love you vertices!

    init_logger("gametest3d.log");
    if (graphics3d_init(1024,768,1,"gametest3d",33) != 0)
    {
        return -1;
    }
    model_init();
    obj_init();
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao); //make our vertex array object, we need it to restore state we set after binding it. Re-binding reloads the state associated with it.
    
    glGenBuffers(1, &triangleBufferObject); //create the buffer
    glBindBuffer(GL_ARRAY_BUFFER, triangleBufferObject); //we're "using" this one now
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW); //formatting the data for the buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind any buffers
    
    obj = obj_load("models/cube.obj");
    texture = LoadSprite("models/cube_text.png",1024,1024);

    bgobj = obj_load("models/map3.obj");
    bgtext = LoadSprite("models/mountain_text.png",1024,1024);
    
//    obj = obj_load("models/mountainvillage.obj");
    
	/* Setting up entities */
	player	= ent_New("Player", ENTITY_PLAYER);
	guard	= ent_New("Guard", ENTITY_GUARD);
	hguard	= ent_New("Heavy Guard", ENTITY_HEAVYG);
	aguard	= ent_New("Armoured Guard", ENTITY_ARMOUREDG);
	//sphere1 = ent_New("Sphere1", vec3d(-35.5,-40,0), newSphere(vec3d(-1,-1,-1), 1.0), vec4d(1,0,1,1));

	//cube2->body.velocity.x = -0.1;
    space = space_New();
    space_set_steps(space,100);

	space_add_body(space,&player->body);
	space_add_body(space,&guard->body);
	space_add_body(space,&hguard->body);
	space_add_body(space,&aguard->body);
    //space_add_body(space,&cube2->body);
	//space_add_body(space,&sphere1->body);

	while (bGameLoopRunning)
    {
		int started = 1;
		int count = 0;
		int i;

		if(count < 200000)
		{
			//slog("Camera Pos: %.2f, %.2f, %.2f", cameraPosition.x, cameraPosition.y, cameraPosition.z);
			//slog("Camera Rot: %.2f, %.2f, %.2f", cameraRotation.x, cameraRotation.y, cameraRotation.z);
			//slog("%.2f, %.2f, %.2f", player->body.position.x, player->body.position.y, player->body.position.z);
			count++;
		}
		for (i = 0; i < 100;i++)
        {
            space_do_step(space);
        }
        while ( SDL_PollEvent(&e) ) 
        {
            if (e.type == SDL_QUIT)
            {
                bGameLoopRunning = 0;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    bGameLoopRunning = 0;
                }
                else if (e.key.keysym.sym == SDLK_SPACE)
                {
                    //cameraPosition.z++;
					player->body.position.z++;
                }
                else if (e.key.keysym.sym == SDLK_c)
                {
                    //cameraPosition.z--;
					player->body.position.z--;
                }
				  else if (e.key.keysym.sym == SDLK_q)
                {
					player->currentweapon--;
					if(player->currentweapon < 0) {player->currentweapon = 3;}
					slog("Current weapon: %i", player->currentweapon);
					slog("Current weapon: %s", player->inventory[player->currentweapon].item_name);
                    //weapon_Switch(player, 0);
                }
				  else if (e.key.keysym.sym == SDLK_e)
                {
					player->currentweapon++;
					if(player->currentweapon > 3) {player->currentweapon = 0;}
					slog("Current weapon: %i", player->currentweapon);
					slog("Current weapon: %s", player->inventory[player->currentweapon].item_name);
					//weapon_Switch(player, 1);
                }
                else if (e.key.keysym.sym == SDLK_w)
                {
                    /*vec3d_add(
                        cameraPosition,
                        cameraPosition,
                        vec3d(
                            -sin(cameraRotation.z * DEGTORAD),
                            cos(cameraRotation.z * DEGTORAD),
                            0
                        ));*/
					vec3d_add(
						player->body.position,
                        player->body.position,
                        vec3d(
                            -sin(player->body.rotation.z * DEGTORAD),
                            cos(player->body.rotation.z * DEGTORAD),
                            0
                        ));
                }
                else if (e.key.keysym.sym == SDLK_s)
                {
                    /*vec3d_add(
                        cameraPosition,
                        cameraPosition,
                        vec3d(
                            sin(cameraRotation.z * DEGTORAD),
                            -cos(cameraRotation.z * DEGTORAD),
                            0
                        ));*/
					vec3d_add(
						player->body.position,
                        player->body.position,
                        vec3d(
                            sin(player->body.rotation.z * DEGTORAD),
                            -cos(player->body.rotation.z * DEGTORAD),
                            0
                        ));
                }
                else if (e.key.keysym.sym == SDLK_d)
                {
                    /*vec3d_add(
                        cameraPosition,
                        cameraPosition,
                        vec3d(
                            cos(cameraRotation.z * DEGTORAD),
                            sin(cameraRotation.z * DEGTORAD),
                            0
                        ));*/
					/*vec3d_add(
						player->body.position,
                        player->body.position,
                        vec3d(
                            cos(player->body.position.z * DEGTORAD),
							sin(player->body.position.z * DEGTORAD),
                            0
                        ));*/
					player->body.rotation.z -= 5;
                }
                else if (e.key.keysym.sym == SDLK_a)
                {
                   /* vec3d_add(
                        cameraPosition,
                        cameraPosition,
                        vec3d(
                            -cos(cameraRotation.z * DEGTORAD),
                            -sin(cameraRotation.z * DEGTORAD),
                            0
                        ));*/
					/*vec3d_add(
						player->body.position,
                        player->body.position,
                        vec3d(
                            -cos(player->body.position.z * DEGTORAD),
							-sin(player->body.position.z * DEGTORAD),
                            0
                        ));*/
					player->body.rotation.z += 5;
                }
                else if (e.key.keysym.sym == SDLK_LEFT)
                {
                    //cameraRotation.z += 1;
					ent_Info(player);
                }
                else if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    //cameraRotation.z -= 1;
					slog("Camera Pos: %.2f, %.2f, %.2f", cameraPosition.x, cameraPosition.y, cameraPosition.z);
					slog("Camera Rot: %.2f, %.2f, %.2f", cameraRotation.x, cameraRotation.y, cameraRotation.z);
					slog("Body Pos: %.2f, %.2f, %.2f", player->body.position.x, player->body.position.y, player->body.position.z);
					slog("Body Rot: %.2f, %.2f, %.2f", player->body.rotation.x, player->body.rotation.y, player->body.rotation.z);
                }
                else if (e.key.keysym.sym == SDLK_UP)
                {
					int i;
					for(i = 0; i < 4; i++)
					{
						slog("Slot %i: %s", i, player->inventory[i].item_name);
					}
                    //cameraRotation.x += 1;
                }
                else if (e.key.keysym.sym == SDLK_DOWN)
                {
                    cameraRotation.x -= 1;
                }
            }
        }

        graphics3d_frame_begin();
        
        glPushMatrix();

		set_camera(
			rtn_camera_position(cameraPosition, cameraRotation, player->body.position, player->body.rotation),
			//cameraRotation
			rtn_camera_rotation(cameraPosition, cameraRotation, player->body.position, player->body.rotation)
			);
		/*set_camera(
			cameraPosition,
			cameraRotation,
			player->body);*/

		ent_DrawAll();
		

        obj_draw(
            bgobj,
            vec3d(0,0,2),
            vec3d(90,90,0),
            vec3d(5,5,5),
            vec4d(0,0,1,1),
            bgtext
        );
        
        /*obj_draw(
            obj,
            vec3d(0,0,0),
            vec3d(90,r++,0),
            vec3d(0.5,0.5,0.5),
            vec4d(1,1,1,1),
            texture
        );*/
        if (r > 360)r -= 360;
        glPopMatrix();
        /* drawing code above here! */
        graphics3d_next_frame();
    } 
    return 0;
}

Vec3D rtn_camera_position(Vec3D camPos, Vec3D camRot, Vec3D bodPos, Vec3D bodRot)
{
	Vec3D newPos;

	newPos.x = (sin(bodRot.z * DEGTORAD) * OFFSET_DEPTH) + bodPos.x;
	newPos.y = (-cos(bodRot.z * DEGTORAD) * OFFSET_DEPTH) + bodPos.y;

	newPos.z = bodPos.z + OFFSET_HEIGHT;

	return newPos;
}

Vec3D rtn_camera_rotation(Vec3D camPos, Vec3D camRot, Vec3D bodPos, Vec3D bodRot)
{
	camRot.z = bodRot.z;

	return camRot;
}

void set_camera(Vec3D position, Vec3D rotation)
{
    glRotatef(-(rotation.x), 1.0f, 0.0f, 0.0f);
    glRotatef(-(rotation.y), 0.0f, 1.0f, 0.0f);
    glRotatef(-(rotation.z), 0.0f, 0.0f, 1.0f);
    glTranslatef(-(position.x),
                 -(position.y),
                 -(position.z));
}

//void set_camera(Vec3D position, Vec3D rotation, Body body)
//{
//    glRotatef(-(body.rotation.x + 45), 1.0f, 0.0f, 0.0f);
//    glRotatef(-(body.rotation.y), 0.0f, 1.0f, 0.0f);
//    glRotatef(-(body.rotation.z), 0.0f, 0.0f, 1.0f);
//    glTranslatef(-(body.position.x),
//				 -(body.position.y - 5),
//                 -(body.position.z + PLAYER_HEIGHT));
//}

//void set_camera(Vec3D position, Vec3D rotation, Body body)
//{
//    glRotatef(-(rotation.x), 1.0f, 0.0f, 0.0f);
//    glRotatef(-(rotation.y), 0.0f, 1.0f, 0.0f);
//    glRotatef(-(rotation.z), 0.0f, 0.0f, 1.0f);
//	glTranslatef(-(-(sin(body.rotation.z) * PLAYER_DEPTH) + body.position.x),
//				 -(-(cos(body.rotation.z) * PLAYER_DEPTH) + body.position.y),
//                 -(PLAYER_DEPTH + PLAYER_HEIGHT));
//}

/*eol@eof*/