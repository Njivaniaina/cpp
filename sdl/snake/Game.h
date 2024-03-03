#include <SDL.h>
#include <SDL_image.h>

#ifndef __GAME__
#define __GAME__

class Game{
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        bool is_running;
        bool rigth, left, up, down;

    public:
        bool gameOver;

        Game();
        ~Game();
        void initKEY();
        bool running();
        void init(const char *title, int w, int h);
        void update();
        void present();
        void getEvent();
        void wait(Uint32 delay);
        void check();
        void clean();
};

#endif