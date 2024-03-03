#include <random>

#include "Nouriture.h"

Nouriture::Nouriture(){

}
Nouriture::~Nouriture(){

}

void Nouriture::loadTexture(const char *filename, SDL_Renderer *ren){
    SDL_Surface *surface = IMG_Load(filename);
    texture = SDL_CreateTextureFromSurface(ren, surface);
    SDL_FreeSurface(surface);
}

void Nouriture::setSRC(int h, int w, int x, int y){
    srcRect.h = h;
    srcRect.w = w;
    srcRect.x = x;
    srcRect.y = y;
}

void Nouriture::setDES(int h, int w, int x, int y){
    desRect.h = h;
    desRect.w = w;
    desRect.x = x;
    desRect.y = y;
}

SDL_Rect Nouriture::getDesRect(){
    return desRect;
}

int Nouriture::randomNumber(){
    std::random_device rd;
    std::mt19937 generate(rd());
    int max = 480;
    int min = 10;
    std::uniform_int_distribution<> distribution(min, max);
    int number = distribution(generate);

    return number-(number%10);
}

void Nouriture::randomDesRect(){
    desRect.x = Nouriture::randomNumber();
    desRect.y = Nouriture::randomNumber();
}

void Nouriture::presentTexture(SDL_Renderer *ren){
    SDL_RenderCopy(ren, texture, NULL, &desRect);
}
