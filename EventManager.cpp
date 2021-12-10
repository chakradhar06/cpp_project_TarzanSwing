//
//  EventManager.cpp
//  SDL_EXPERIMENTING
//
//  Created by Rahul Jain on 05/12/21.
//

#include "EventManager.hpp"
#include <iostream>

bool eventManager::Exit_MouseClick(int x, int y, int text_width, int scr_width){
    int k1 = (scr_width - text_width)/2;
    int k2 = (scr_width + text_width)/2;
    if((x>=k1) && (x<=k2) && (y>=600) && (y<=600+38))
        return false;
    return true;
}

bool eventManager::Play_MouseClick(int x, int y, int text_width, int scr_width){
    int k1 = (scr_width - text_width)/2;
    int k2 = (scr_width + text_width)/2;
    if((x>=k1) && (x<=k2) && (y>=350) && (y<=350+38))
        return true;
    return false;
}


bool eventManager::MouseClick(SDL_MouseButtonEvent& b, Rope* aRope, Me* mainObject, std::vector<Object*> enemyList, std::vector<Object*> frendList)
{
    if(b.button == SDL_BUTTON_LEFT)
    {
        std::cout<<"DANCE"<<std::endl;
        aRope->setTarget(b, mainObject, enemyList, frendList);
//        aRope->setInitialPosn(aRope->giveMe()->getPosn());
        aRope->setInitialPosn(aRope->giveOther()->getPosn());
        
//        aRope->setInitialVel(aRope->giveMe()->getVel());
        aRope->setInitialVel(aRope->giveOther()->getVel());
        
        aRope->setRopeLength( aRope->giveInitialSep() );
//        aRope->RopeCalculus();
        return true;
    }
    if(b.button == SDL_BUTTON_RIGHT)
    {
        return false;
    }
    return false;
}
