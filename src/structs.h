#pragma once

#include "enums.h"

typedef struct Vector{
        double x;
        double y;
} Vector;

typedef struct Sprite{
        int frame;
        double angle;
        double temp_angle;
        int scale;
        SDL_Texture *image;
        SDL_Rect *rect;
} Sprite;

typedef struct Object{
        Sprite *sprite;

        bool solid;

        double vel;

        double accel;

        Direction move;

        Direction collision;

        SDL_Rect *temp_rect;

        Vector dimensions;

        int id;
} Object;

typedef struct Player{
        Object *object;

        int health;
        int health_max;
        int attack;
        int defense;

        bool alive;
        bool run;
} Player;

typedef struct Enemy{
        Object *object;

        int health;
        int attack;
        int defense;

        void (*update)(Object *self);
} Enemy;

typedef struct Map{
        SDL_Rect *rect;
        Vector tiles;
        SDL_Rect *view;
} Map;
