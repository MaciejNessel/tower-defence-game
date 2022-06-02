//
// Created by Maciej on 02.06.2022.
//

#ifndef TOWER_DEFENCE_GAME_SDL_CIRCLE_H
#define TOWER_DEFENCE_GAME_SDL_CIRCLE_H
#include "SDL.h"

class SDL_Circle{
public:
    static int Draw(SDL_Renderer * renderer, int x, int y, int radius)
    {
        int offsetx, offsety, d;
        int status;

        offsetx = 0;
        offsety = radius;
        d = radius -1;
        status = 0;

        while (offsety >= offsetx) {
            status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
            status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
            status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
            status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
            status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
            status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
            status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
            status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

            if (status < 0) {
                status = -1;
                break;
            }

            if (d >= 2*offsetx) {
                d -= 2*offsetx + 1;
                offsetx +=1;
            }
            else if (d < 2 * (radius - offsety)) {
                d += 2 * offsety - 1;
                offsety -= 1;
            }
            else {
                d += 2 * (offsety - offsetx - 1);
                offsety -= 1;
                offsetx += 1;
            }
        }

        return status;
    }

};
#endif //TOWER_DEFENCE_GAME_SDL_CIRCLE_H
