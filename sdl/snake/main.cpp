#include "Game.h"
#include "Snake.h"

int main(int argc, char **argv){
    Game *g = new Game();

    g->init("Snake", 500, 500);

    while(g->running()){
        g->getEvent();
        if(!g->gameOver){
            g->update();
            g->check();
        }
        g->present();
        g->wait(100);
    }
    
    g->clean();

    return 0;
}