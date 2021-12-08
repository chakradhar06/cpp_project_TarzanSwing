#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.h"


RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if (texture == NULL)
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

    return texture;
}

void RenderWindow::drawObject(Me* obj)
{
    SDL_Rect rect;
    rect.x = obj->getPosn().x;
    rect.y = obj->getPosn().y;
    rect.w = obj->getWidth() ;
    rect.h = obj->getHeight();

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void RenderWindow::drawEnemyObject(std::vector<Object*> enemyList)
{
    for(auto it: enemyList)
    {
        SDL_Rect rect;
        rect.x = it->getPosn().x;
        rect.y = it->getPosn().y;
        rect.w = it->getLen();
        rect.h = it->getLen();

        SDL_SetRenderDrawColor(renderer, 238, 75, 43, 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
}

void RenderWindow::drawFrendObject(std::vector<Object*> frendList)
{
    for(auto it: frendList)
    {
        SDL_Rect rect;
        rect.x = it->getPosn().x;
        rect.y = it->getPosn().y;
        rect.w = it->getLen();
        rect.h = it->getLen();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
}

void RenderWindow::drawLine(Me* o1, Object* o2)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderDrawLine(renderer, o1->getPosn().x, o1->getPosn().y, o2->getPosn().x, o2->getPosn().y);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void RenderWindow::dealTheDead()
{
//    clear();
    TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 100);
    SDL_Color White = {255, 255, 255};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "LMAO DED!!", White);

    // now you can convert it into a texture
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 300;  //controls the rect's x coordinate
    Message_rect.y = 300; // controls the rect's y coordinte
    Message_rect.w = 100; // controls the width of the rect
    Message_rect.h = 100; // controls the height of the rect

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_RenderPresent(renderer);

    // Don't forget to free your surface and texture
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}

void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::render(SDL_Texture* p_tex)
{
    SDL_RenderCopy(renderer, p_tex, NULL, NULL);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}
