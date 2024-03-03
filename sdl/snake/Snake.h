#include "Game.h"

#ifndef __SNAKE__
#define __SNAKE__

class Snake{
    private:  
        SDL_Texture *texture;

    public:
        SDL_Rect srcRect, desRect;

        Snake();
        ~Snake();
        void loadTexture(const char *filename, SDL_Renderer *ren);
        void setSRC(int h, int w, int x, int y);
        void setDES(int h, int w, int x, int y);
        SDL_Rect getDesRect();
        void presentTexture(SDL_Renderer *ren);

};

#endif