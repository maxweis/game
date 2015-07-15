#include "event.h"

bool MouseMove()
{
        if (event.motion.x > 0 || event.motion.y > 1)
                return true;
        else
                return true;
}

void InitEvent()
{
        mouse_hold = false;
        key_hold = false;
}

void HandleButtonPress()
{
        SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
        SDL_PollEvent(&event);
        keystate = SDL_GetKeyboardState(NULL);

        key_press = false;

        if (event.type == SDL_KEYDOWN){
                if (!key_hold)
                        key_press = true;
                key_hold = true;
        }

        if (event.type == SDL_KEYUP)
                key_hold = false;

        mouse_click = false;

        if (event.button.type == SDL_MOUSEBUTTONDOWN){
                if (event.button.button == SDL_BUTTON_LEFT){
                        if (!mouse_hold)
                                mouse_click = true;
                        mouse_hold = true;
                }
        }

        if (event.button.type == SDL_MOUSEBUTTONUP)
                mouse_hold = false;
}

void CheckUniversalEvents()
{
        HandleButtonPress();

        if (event.type == SDL_QUIT)
                done = true;

        if (keystate[SDL_SCANCODE_ESCAPE])
                done = true;
}

void CheckMenuEvents()
{
        CheckUniversalEvents();

        if ((keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP]) &&
                        key_press)
                menu_selection--;

        if ((keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN]) &&
                        key_press)
                menu_selection++;

        if (keystate[SDL_SCANCODE_RETURN] || keystate[SDL_SCANCODE_SPACE] ||
                        (mouse_click && event.button.button == SDL_BUTTON_LEFT))
                menu_enter = true;

        SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
}

void CheckGameEvents()
{
        CheckUniversalEvents();

        if (keystate[SDL_SCANCODE_LSHIFT])
                player->run = true;
        else
                player->run = false;

        if (keystate[SDL_SCANCODE_W])
                player->move(UP);

        if (keystate[SDL_SCANCODE_D])
                player->move(RIGHT);

        if (keystate[SDL_SCANCODE_S])
                player->move(DOWN);

        if (keystate[SDL_SCANCODE_A])
                player->move(LEFT);

        /*if (keystate[SDL_SCANCODE_SPACE])*/

        SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
}
