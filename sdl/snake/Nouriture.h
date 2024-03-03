#include "Game.h"
#include "Snake.h"

#ifndef __NOURITURE__
#define __NOURITURE__

class Nouriture {
    private:  
        SDL_Texture *texture;

    public:
        SDL_Rect srcRect, desRect;

        Nouriture();
        ~Nouriture();
        void loadTexture(const char *filename, SDL_Renderer *ren);
        void setSRC(int h, int w, int x, int y);
        void setDES(int h, int w, int x, int y);
        SDL_Rect getDesRect();
        int randomNumber();
        void randomDesRect();
        void presentTexture(SDL_Renderer *ren);
};

#endif