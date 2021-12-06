//
//  EventManager.hpp
//  SDL_EXPERIMENTING
//
//  Created by Rahul Jain on 05/12/21.
//

#ifndef EventManager_hpp
#define EventManager_hpp

#include <stdio.h>
#include <vector>

#include "Rope.hpp"
#include "RenderWindow.h"
#include "me.hpp"
#include "Object.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class eventManager{
public:
//    eventManager();
    bool MouseClick(SDL_MouseButtonEvent& b, Rope* aRope, Me* mainObject, std::vector<Object*> enemyList);
};

#endif /* EventManager_hpp */
