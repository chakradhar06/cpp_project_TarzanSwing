#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Object.hpp"
#include "me.hpp"

class RenderWindow
{
public:
    RenderWindow(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTexture(const char* p_filePath);
    void cleanUp();
    void clear();
    void render(SDL_Texture* p_tex);
    void display();
    void drawObject(Me* obj);
    void drawAnotherObject(Object* obj);
    void drawLine(Me* o1, Object* o2);
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};
