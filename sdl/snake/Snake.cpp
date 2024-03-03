#include "Snake.h"

Snake::Snake(){

}
Snake::~Snake(){

}

void Snake::loadTexture(const char *filename, SDL_Renderer *ren){
    SDL_Surface *surface = IMG_Load(filename);
    texture = SDL_CreateTextureFromSurface(ren, surface);
    SDL_FreeSurface(surface);
}

void Snake::setSRC(int h, int w, int x, int y){
    srcRect.h = h;
    srcRect.w = w;
    srcRect.x = x;
    srcRect.y = y;
}

void Snake::setDES(int h, int w, int x, int y){
    desRect.h = h;
    desRect.w = w;
    desRect.x = x;
    desRect.y = y;
}

SDL_Rect Snake::getDesRect(){
    return desRect;
}

// void Game::setDESX(int x){
//     desRect.x = x;
// }
// void Game::setDESY(int y){
//     desRect.y = y;
// }

void Snake::presentTexture(SDL_Renderer *ren){
    SDL_RenderCopy(ren, texture, NULL, &desRect);
}

