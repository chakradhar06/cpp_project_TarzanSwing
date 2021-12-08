#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>

#include "RenderWindow.h"
#include "Object.hpp"
#include "me.hpp"
#include "Rope.hpp"
#include "EventManager.hpp"

#define WindowWidth 1280
#define WindowHeight 720

int main(int argc, char* args[])
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

    RenderWindow window("BAD GAME", WindowWidth, WindowHeight);


    bool gameRunning = true;
    bool Roped = false;
    bool slack = false;
    int TotalScore = 0;

    SDL_Event event;
    
    std::vector<class Object*> enemyList;
    std::vector<class Object*> frendList;
    
    //Instantiating main object and enemy object before game loop starts
    class Me* mainObject = new Me(600,30,15,0,0);
    
    //Generating random Frend and Enemy Objects
    srand(time(0));
    for(int i=0;i<5;i++)
    {
        double randX = rand() % WindowWidth;
        double randY = rand() % WindowHeight;
        Object* temp = new Object(true,randX,randY,20);
        enemyList.push_back(temp);
    }
    for(int i=0;i<8;i++)
    {
        double randX = rand() % WindowWidth;
        double randY = rand() % WindowHeight;
        Object* temp = new Object(false,randX,randY,20);
        frendList.push_back(temp);
    }
    
//    class Object* enemy = new Object(true,500,100,20);
//    class Object* enemy2 = new Object(true,800,400,20);
//    enemyList.push_back(enemy);
//    enemyList.push_back(enemy2);
    class Rope* aRope = new Rope();
    class eventManager* anEvent = new eventManager();
    bool collided = false;
    int ScoredObjectIndex;

    SDL_Texture* grassTexture = window.loadTexture("/Users/rahuljain/Documents/GameDevelopment/SDL_EXPERIMENTING/SDL_EXPERIMENTING/BLACK.jpg");
    while (gameRunning)
    {
        // Get our controls and events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                gameRunning = false;
            if(event.type == SDL_MOUSEBUTTONDOWN)
                Roped = anEvent->MouseClick(event.button,aRope,mainObject,enemyList,frendList);
                
        }

        window.clear();
        
        //checkCollision, if collision occurs, end program
        collided = mainObject->CheckCollision(mainObject, enemyList);
        ScoredObjectIndex = mainObject->CheckScoreHit(mainObject, frendList);
        if(ScoredObjectIndex != -1)
        {
            delete(frendList[ScoredObjectIndex]);
            frendList[ScoredObjectIndex] = NULL;
            frendList.erase(frendList.begin()+ScoredObjectIndex);
        }
        
        if(!collided)
        {
            window.render(grassTexture);
            window.drawObject(mainObject);
            window.drawEnemyObject(enemyList);
            window.drawFrendObject(frendList);
            if(Roped)
            {
                mainObject->setAcc_y(0);
                window.drawLine(mainObject, aRope->getTarget());
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
        }
        
        else if(collided)
        {
            window.dealTheDead();
        }
        
        window.display();
//        std::cout<<mainObject->getPosn().x<<" "<<mainObject->getPosn().y<<std::endl;
        std::cout<<TotalScore<<std::endl; 

    }
        

    window.cleanUp();
    SDL_Quit();

    return 0;
}
