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
    class Me* mainObject = new Me(600,400,15,0,0);
    
    //Generating random Frend and Enemy Objects
    srand(time(0));
    for(int i=0;i<2;i++)
    {
        double randX = rand() % WindowWidth;
        double randY = rand() % WindowHeight;
        Object* temp = new Object(true,randX,randY,20);
        enemyList.push_back(temp);
    }
    for(int i=0;i<100;i++)
    {
        double randX = rand() % WindowWidth;
        double randY = rand() % WindowHeight;
        Object* temp = new Object(false,randX,randY,20);
        frendList.push_back(temp);
    }

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
            TotalScore += 100;
            std::cout<<TotalScore<<std::endl; 
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
                slack = aRope->RopeCalculus(slack,enemyList,frendList);
                if(slack)
                {
                    aRope->setSlackOccurence(aRope->giveOther()->getPosn());
                    Roped = false;
                }
            }
            else if(slack)
            {
                for(auto it:enemyList) it->setAcc_y(-gravity);
                for(auto it:frendList) it->setAcc_y(-gravity);
                slack = aRope->RopeCalculus(slack,enemyList,frendList);
                if(slack == false) Roped = true;
            }
            else
            {
//                mainObject->setAcc_y(gravity);
                for(auto it:enemyList) it->setAcc_y(-gravity);
                for(auto it:frendList) it->setAcc_y(-gravity);
            }
            
            for(auto it:enemyList) it->UpdatePosn();
            for(auto it:frendList) it->UpdatePosn();
        }
        
        else if(collided)
        {
            window.dealTheDead();
        }
        
        window.display();
//        std::cout<<mainObject->getPosn().x<<" "<<mainObject->getPosn().y<<std::endl;
        

    }
        

    window.cleanUp();
    SDL_Quit();

    return 0;
}
