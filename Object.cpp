//
//  Object.cpp
//  SDL_EXPERIMENTING
//
//  Created by Rahul Jain on 04/12/21.
//

#include "Object.hpp"

    Object::Object(bool evil, double x,double y, double len)
    {
        posn.x = x;
        posn.y = y;
        this->len = len;
        this->evil = evil;
    }
    //getters
    double Object::getLen(){return len;}
    Vec2 Object::getPosn(){return posn;}
