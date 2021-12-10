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
#include"LTexture.hpp"

#define WindowWidth 1280
#define WindowHeight 720

int main(int argc, char* args[])
{
    if(SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

    if(!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

    //Initialize SDL_ttf
    if(TTF_Init() == -1)
    std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << SDL_GetError() << std::endl;

    RenderWindow window("BAD GAME", WindowWidth, WindowHeight);
    SDL_Window* gWindow = window.get_renderer_window();
    SDL_Renderer* gRenderer = window.get_SDL_renderer();

    bool gameRunning = true;
    bool main_game = false; // it will be true when we enteres into main game
    bool Roped = false;
    int Quadrant;
    int TotalScore = 0;

    TTF_Font* gFont1 = NULL;
    TTF_Font* gFont2 = NULL;

    LTexture* gTextTexture1 = new LTexture();
    LTexture* gTextTexture2 = new LTexture();
    LTexture* gTextTexture3 = new LTexture();

    class Me* mainObject = NULL;

    std::vector<class Object*> enemyList;
    std::vector<class Object*> frendList;

    //Instantiating main object and enemy object before game loop starts
    mainObject = new Me(600,400,15,0,0);

    class Rope* aRope = new Rope();
    class eventManager* anEvent = new eventManager();
    bool collided = false;
    int ScoredObjectIndex;

    SDL_Event event;

    if(main_game == false)
    {
        SDL_Color textColor1 = {210, 105, 30, 255};
		SDL_Color textColor2 = {0, 255, 0, 255};
	    SDL_Color textColor3 = {178, 34, 34, 255};
	    gFont1 = TTF_OpenFont("/Users/rahuljain/Documents/GameDevelopment/SDL_EXPERIMENTING/SDL_EXPERIMENTING/game.ttf", 52);
		if(gFont1 == NULL){
		    printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	    }

		if(!gTextTexture1->loadFromRenderedText("BAD GAME", textColor1, gRenderer, gFont1)){
		    printf("Failed to render text texture!\n");
	    }

		gFont2 = TTF_OpenFont("/Users/rahuljain/Documents/GameDevelopment/SDL_EXPERIMENTING/SDL_EXPERIMENTING/game.ttf", 38);
	    if(gFont2 == NULL){
		    printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		}
		
	    if(!gTextTexture2->loadFromRenderedText("PLAY", textColor2, gRenderer, gFont2)){
		    printf("Failed to render text texture!\n");
		}
		
		if(!gTextTexture3->loadFromRenderedText("EXIT", textColor3, gRenderer, gFont2)){
		    printf("Failed to render text texture!\n");
	    }
    }
    
    statement:
    if(main_game == true){    
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
    }
    
    SDL_Texture* grassTexture = window.loadTexture("/Users/rahuljain/Documents/GameDevelopment/SDL_EXPERIMENTING/SDL_EXPERIMENTING/BLACK.jpg");

    while(gameRunning)
    {
        // Get our controls and events
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                gameRunning = false;
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(main_game == false){
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    int k1 = gTextTexture3->getWidth();
                    int k2 = gTextTexture2->getWidth();
                    gameRunning = anEvent->Exit_MouseClick(x, y, k1, WindowWidth);
                    main_game = anEvent->Play_MouseClick(x, y, k2, WindowWidth);
                    if(main_game == true) goto statement;
                }

                else if(main_game == true)
                    Roped = anEvent->MouseClick(event.button, aRope, mainObject, enemyList, frendList);
            }
        }

        if(main_game == false)
        {
            //Clear screen
			SDL_SetRenderDrawColor(gRenderer, 30, 30, 30, 0xFF);
			SDL_RenderClear(gRenderer);

			//Render current frame
			gTextTexture1->render((WindowWidth - gTextTexture1->getWidth()) / 2, 100, gRenderer);
			gTextTexture2->render((WindowWidth - gTextTexture2->getWidth()) / 2, 350, gRenderer);
			gTextTexture3->render((WindowWidth - gTextTexture3->getWidth()) / 2, 600, gRenderer);

            //Update screen
			SDL_RenderPresent(gRenderer);
        }

        else if(main_game == true)
        {
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
                    Roped = aRope->RopeCalculus(Roped,enemyList,frendList);
                }
                if(Roped == false)
                {
    //                mainObject->setAcc_y(gravity);
                    for(auto it:enemyList)
                    {
                        it->setAcc_y(-gravity);
                        it->setAcc_x(0);
                    }
                    
                    for(auto it:frendList)
                    {
                        it->setAcc_y(-gravity);
                        it->setAcc_x(0);

                    }
                }
            
                for(auto it:enemyList) it->UpdatePosn();
                for(auto it:frendList) it->UpdatePosn();
            }
        
            else if(collided)
            {
                window.dealTheDead();
            }
        
            window.display();
//          std::cout<<mainObject->getPosn().x<<" "<<mainObject->getPosn().y<<std::endl;
        }
    }


    window.cleanUp();

    gTextTexture1->free();
	gTextTexture2->free();
	gTextTexture3->free();

    TTF_CloseFont(gFont1);
	gFont1 = NULL;

    TTF_CloseFont(gFont2);
	gFont2 = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
