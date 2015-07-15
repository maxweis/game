#include "object.h"

int CountList(char **list)
{
        int i;
        for (i = 0; list[i] != NULL; i++)
                ;
        return i;
}

void InitObject()
{
        object_number = 0;
        object_amount = CountList(object_list);
}

void ObjectAdd(Object object)
{
        objects[object_number++] = object;
}

Object *ObjectCreate(bool solid, int x, int y, int width, int height, int scale, int id, int angle, int vel_x, int vel_y)
{
        Object *temp = malloc(sizeof(Object));
        temp->sprite = SpriteInit(width, height, scale, object_list[id]);

        temp->sprite->angle = angle;
        temp->sprite->frame = 0;

        temp->id = id;
        temp->sprite->rect->x = x;
        temp->sprite->rect->y = y;

        temp->move = NONE;

        temp->temp_rect = malloc(sizeof(SDL_Rect));

        *temp->temp_rect = *temp->sprite->rect;

        temp->dimensions.x = temp->sprite->rect->w;
        temp->dimensions.y = temp->sprite->rect->h;

        temp->vel.x = vel_x;
        temp->vel.y = vel_y;

        temp->solid = solid;
        return temp;
}

void ObjectReset(Object *object)
{
        object->move = DirUpdate(NONE);
}

void ObjectMove(Object *object)
{
        Vector vel = object->vel;
        static double accel = 1;

        /*if (accel < 1)*/
                /*accel += .1;*/

        switch(object->move){
                case NORTH:
                        object->temp_rect->y -= (vel.y * accel);
                        break;
                case NORTHEAST:
                        object->temp_rect->x += (vel.x * accel / 2);
                        object->temp_rect->y -= (vel.y * accel / 2);
                        break;
                case EAST:
                        object->temp_rect->x += (vel.x * accel);
                        break;
                case SOUTHEAST:
                        object->temp_rect->x += (vel.x * accel / 2);
                        object->temp_rect->y += (vel.y * accel / 2);
                        break;
                case SOUTH:
                        object->temp_rect->y += (vel.y * accel);
                        break;
                case SOUTHWEST:
                        object->temp_rect->x -= (vel.x * accel / 2);
                        object->temp_rect->y += (vel.y * accel / 2);
                        break;
                case WEST:
                        object->temp_rect->x -= (vel.x * accel);
                        break;
                case NORTHWEST:
                        object->temp_rect->x -= (vel.x * accel / 2);
                        object->temp_rect->y -= (vel.y * accel / 2);
                        break;
        }
}

void ObjectMoveApply(Object *object)
{
        if (!ScreenCollision(object->temp_rect, 5)){
                if (!ObjectsCollision(object->temp_rect)){
                        object->sprite->rect->x = object->temp_rect->x;
                        object->sprite->rect->y = object->temp_rect->y;
                }
        }
        object->temp_rect->x = object->sprite->rect->x;
        object->temp_rect->y = object->sprite->rect->y;
}

void UpdateObject()
{
}
