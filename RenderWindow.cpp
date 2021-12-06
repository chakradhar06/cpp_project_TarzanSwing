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
    rect.w = obj->getRadius() ;
    rect.h = obj->getRadius();

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void RenderWindow::drawAnotherObject(std::vector<Object*> enemyList)
{
    for(auto it: enemyList)
    {
        SDL_Rect rect;
        rect.x = it->getPosn().x;
        rect.y = it->getPosn().y;
        rect.w = it->getLen();
        rect.h = it->getLen();

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
}

void RenderWindow::drawLine(Me* o1, Object* o2)
{
    SDL_RenderDrawLine(renderer, o1->getPosn().x, o1->getPosn().y, o2->getPosn().x, o2->getPosn().y);
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
