#include "render.h"

SDL_Texture *cursor = NULL;
void InitCursorRender()
{
        cursor = IMG_LoadTexture(render, "art/cursors/game.png");
}

void CursorRender()
{
        if (cursor == NULL)
                InitCursorRender();
        SDL_Rect mouse = {mouse_pos.x - 15, mouse_pos.y - 15, 31, 31};
        SDL_RenderCopy(render, cursor, NULL, &mouse); 
}

void PlayerRender()
{
        SDL_Rect sprite = {player->object->sprite->rect->x,
               player->object->sprite->rect->y,
               player->object->sprite->rect->w,
               player->object->sprite->rect->h};

        SDL_Rect slide = {player->object->sprite->rect->w / player->object->sprite->scale * player->object->sprite->frame,
               0,
               player->object->sprite->rect->w / player->object->sprite->scale,
               player->object->sprite->rect->h / player->object->sprite->scale};

        SDL_RenderCopyEx(render, player->object->sprite->image, &slide, &sprite,
                        player->object->sprite->angle, NULL, SDL_FLIP_NONE);
}

void ObjectRender()
{
        if (object_number != 0){
                for (int i = 0; i < object_number; i++){
                        SDL_Rect sprite = {objects[i].sprite->rect->x,
                                objects[i].sprite->rect->y,
                                objects[i].sprite->rect->w,
                                objects[i].sprite->rect->h};

                        SDL_Rect slide = {objects[i].sprite->rect->w / objects[i].sprite->scale * objects[i].sprite->frame,
                                0,
                                objects[i].sprite->rect->w / objects[i].sprite->scale,
                                objects[i].sprite->rect->h / objects[i].sprite->scale};

                        SDL_RenderCopy(render, objects[i].sprite->image, &slide, &sprite);
                }
        }
}

TTF_Font *mono_font = NULL;
int font_size = 0;
char font_name[256];
void InitTextRender(char *font)
{
        mono_font = TTF_OpenFont(font, font_size);
        if (mono_font == NULL)
                fprintf(stderr, "Missing font: %s\n", TTF_GetError());
}

void TextRender(char *text, SDL_Rect box, char *font, SDL_Color color, int size, bool center)
{
        if (mono_font == NULL || font_size != size ||
                        !strcmp(font_name, font)){
                TTF_CloseFont(mono_font);
                strcpy(font_name, font);
                font_size = size;
                InitTextRender(font);
        }

        SDL_Surface *text_surface = TTF_RenderText_Solid(mono_font, text, color);

        box.w = text_surface->w;
        box.h = text_surface->h;

        if (center)
                box.x -= box.w / 2;

        SDL_Texture *present = SDL_CreateTextureFromSurface(render, text_surface);

        SDL_FreeSurface(text_surface);

        SDL_RenderCopy(render, present, NULL, &box);
}

SDL_Texture *background = NULL;
void InitBackgroundRender(char *background_path)
{
        background = IMG_LoadTexture(render, background_path); 
}

void BackgroundRender(char *background_path)
{
        SDL_Rect size = {0, 0, SWIDTH, SHEIGHT};

        if (background == NULL)
                InitBackgroundRender(background_path);

        SDL_RenderCopy(render, background, NULL, &size);
}

void StartMenuRender()
{
        SDL_Rect option_1 = {SWIDTH / 2 - 50, SHEIGHT * (1.0 / 4), 
                100, 100};

        SDL_Rect option_2 = {SWIDTH / 2 - 50, SHEIGHT * (2.0 / 4), 
                100, 100};

        SDL_Rect option_3 = {SWIDTH / 2 - 50, SHEIGHT * (3.0 / 4), 
                100, 100};

        SDL_Color white = {255, 255, 255};
        SDL_Color red = {255, 0, 0};

        SDL_RenderClear(render);

        TextRender("Start Game", option_1, "art/fonts/UbuntuMono-R.ttf", 
                        menu_selection == 0 ? red : white, 72, true);
        TextRender("Options", option_2, "art/fonts/UbuntuMono-R.ttf",
                        menu_selection == 1 ? red : white, 72, true);
        TextRender("Exit", option_3, "art/fonts/UbuntuMono-R.ttf",
                        menu_selection == 2 ? red : white, 72, true);

        SDL_RenderPresent(render);
}

void GameScreenRender()
{
        SDL_RenderClear(render);

        BackgroundRender(background_list[level_background]);
        PlayerRender();
        ObjectRender();
        CursorRender();

        SDL_RenderPresent(render);
}
