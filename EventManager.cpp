//
//  EventManager.cpp
//  SDL_EXPERIMENTING
//
//  Created by Rahul Jain on 05/12/21.
//

#include "EventManager.hpp"
#include <iostream>


bool eventManager::MouseClick(SDL_MouseButtonEvent& b, Rope* aRope)
{
    if(b.button == SDL_BUTTON_LEFT)
    {
        std::cout<<"DANCE"<<std::endl;
        aRope->setInitialPosn(aRope->giveMe()->getPosn());
        aRope->setInitialVel(aRope->giveMe()->getVel());
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
