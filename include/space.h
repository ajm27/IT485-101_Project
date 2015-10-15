#ifndef __SPACE_H__
#define __SPACE_H__

typedef struct Space_S Space;

Space *space_New();

void space_add_body(Space *space, Body *body);
void space_remove_body(Space* space, Body* body);
void space_set_steps(Space* space, int steps);
void space_do_step(Space* space);
void space_Free(Space* space);

#endif