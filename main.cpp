#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.h"
#include "Object.hpp"
#include "me.hpp"
#include "Rope.hpp"
#include "EventManager.hpp"

int main(int argc, char* args[])
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

    RenderWindow window("BAD GAME", 1280, 720);

    SDL_Texture* grassTexture = window.loadTexture("/Users/rahuljain/Documents/lodalassan/lodalassan/ground_grass_1.png");

    bool gameRunning = true;
    bool Roped = false;
    bool slack = false;

    SDL_Event event;
    
    std::vector<class Object*> enemyList;
    
    //Instantiating main object and enemy object before game loop starts
    class Me* mainObject = new Me(600,30,15,0,0);
    class Object* enemy = new Object(500,300,10);
    class Object* enemy2 = new Object(800,400,10);
    enemyList.push_back(enemy);
    enemyList.push_back(enemy2);
    class Rope* aRope = new Rope();
    class eventManager* anEvent = new eventManager();

    while (gameRunning)
    {
        // Get our controls and events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                gameRunning = false;
            if(event.type == SDL_MOUSEBUTTONDOWN)
                Roped = anEvent->MouseClick(event.button,aRope,mainObject,enemyList);
        }

        window.clear();
        window.render(grassTexture);
        
        //checkCollision, if collision occurs, end program
        bool collided = mainObject->CheckCollision(mainObject, enemyList);
        if(collided) exit(1);
        
        window.drawObject(mainObject);
        window.drawAnotherObject(enemyList);
        if(Roped)
        {
            mainObject->setAcc_y(0);
            window.drawLine(mainObject, aRope->getEnemy());
            slack = aRope->RopeCalculus(slack);
            if(slack)
            {
                aRope->setSlackOccurence(mainObject->getPosn());
                Roped = false;
            }
        }
        else if(slack)
        {
            
            slack = aRope->RopeCalculus(slack);
            if(slack == false) Roped = true;
        }
        else
            mainObject->setAcc_y(g);
        
        mainObject->UpdatePosn();
        window.display();
        

    }

    window.cleanUp();
    SDL_Quit();

    return 0;
}
