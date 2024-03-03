#include <iostream>
#include <vector>

#include "Game.h"
#include "Snake.h"
#include "Nouriture.h"

std::vector<Snake> s;
Nouriture n;
SDL_Rect rect;

bool first = true;

Game::Game(){

}

Game::~Game(){

}

void Game::initKEY(){
    rigth = false;
    left = false;
    up = false;
    down  = false;
}

SDL_Rect cpRect(SDL_Rect r){
    SDL_Rect rect;

    rect.x = r.x;
    rect.y = r.y;
    rect.h = r.h;
    rect.w = r.w;

    return rect;
}

bool cmpRect(SDL_Rect rect1, SDL_Rect rect2){
    if((rect1.x == rect2.x) && (rect1.y == rect2.y))
        return true;
    else
        return false;
}

bool Game::running(){
    return is_running;
}

void Game::init(const char *title, int w, int h){
    int position = 0;
    
    if(!SDL_Init(SDL_INIT_VIDEO)){
        std::cout << "Initialisation de la SDL ..." << std::endl;

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
        if(window){
            std::cout << "Creation du fenetre ..." << std::endl;

            renderer = SDL_CreateRenderer(window, -1, 0);
            if(renderer){
                std::cout << "Creation du rendue ..." << std::endl;
            }
            else{
                std::cout << "Erreur de la creation du rendue!!!" << std::endl;
            }

            is_running = true;

            s.push_back(Snake());
            s.push_back(Snake());
            s.push_back(Snake());

            for(auto &object : s){
                object.loadTexture("./snake.png", renderer);
                object.setSRC(0, 0, 0, 0);
                object.setDES(10, 10, 100-position, 100);
                position += 10;
            }

            n = Nouriture();
            n.loadTexture("./nouriture.png", renderer);
            n.setSRC(0, 0, 0, 0);
            n.setDES(10,10, 0, 0);
            n.randomDesRect();

            gameOver = false;
            rigth = true;
        }
        else{
            std::cout << "Echec de la creation du fenetre!!!" << std::endl;
        }
    }
    else{
        std::cout << "Erreur de l'initialisation du SDL!!!" << std::endl;
    }

}

void Game::update(){

    if(first){
        first = false;
    }
    else{
        rect = cpRect(s[0].desRect);
        
        if(rigth){
            s[0].desRect.x += 10; 
        }
        if(left){
            s[0].desRect.x -= 10; 
        }
        if(up){
            s[0].desRect.y -= 10; 
        }
        if(down){
            s[0].desRect.y += 10; 
        }

        for(int i=1;i<s.size();i++){
            SDL_Rect r;
            r = cpRect(s[i].desRect);
            s[i].desRect = cpRect(rect);
            rect = cpRect(r);
        }
    }
}

void Game::present(){
    SDL_Rect r = {10, 10, 480, 480};

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 77, 77, 77, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 38, 208, 28, 255);

    SDL_RenderFillRect(renderer, &r);
    for(auto &object : s){
        object.presentTexture(renderer);
    }
    n.presentTexture(renderer);
    SDL_RenderPresent(renderer);
}

void Game::getEvent(){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type){
        case SDL_QUIT:
            is_running = false;
            break;

        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                case SDLK_UP:
                    Game::initKEY();
                    up = true;
                    //std::cout << "up" << std::endl;
                    break;

                case SDLK_DOWN:
                    Game::initKEY();
                    down = true;
                    //std::cout << "down" << std::endl;
                    break;

                case SDLK_RIGHT:
                    Game::initKEY();
                    rigth = true;
                    //std::cout << "right" << std::endl;
                    break;

                case SDLK_LEFT:
                    Game::initKEY();
                    left = true;
                    //std::cout << "left" << std::endl;
                    break;
            }
            break;
    }
}

void Game::wait(Uint32 delay){
    Uint32 start = SDL_GetTicks();
    while((SDL_GetTicks() - start) < delay){
        Game::getEvent();
    }
}

void Game::check(){
    if(cmpRect(s[0].getDesRect(), n.getDesRect())){
    r:
        n.randomDesRect();
        for(auto &obj : s){
            if(cmpRect(n.getDesRect(), obj.desRect)){
                goto r;
            }
        }
        s.push_back(Snake());
        s[s.size()-1].loadTexture("./snake.png", renderer);
        s[s.size()-1].setSRC(0, 0, 0, 0);
        s[s.size()-1].desRect = cpRect(s[s.size()-2].desRect);
        s[s.size()-1].desRect.x -= 10;
    }

    for(int i=1;i<s.size();i++){
        if(cmpRect(s[0].desRect, s[i].desRect)){
            gameOver = true;
        }
    }

    if(s[0].desRect.x < 10 || s[0].desRect.x > 480 || s[0].desRect.y < 10 || s[0].desRect.y > 480  ){
        gameOver = true;
    }
}

void Game::clean(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Quit ..." << std::endl;
}