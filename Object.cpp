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
    acceleration.Ay = -gravity;
}

void Object::UpdatePosn()
{
//        Uint32 mTicksCount = 0;
//        float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
//        mTicksCount = SDL_GetTicks();
    double deltaTime = 1;
    
        velocity.Vx = velocity.Vx + acceleration.Ax*deltaTime;
        posn.x = posn.x + velocity.Vx*deltaTime;

        velocity.Vy = velocity.Vy + acceleration.Ay*deltaTime;
        posn.y = posn.y + velocity.Vy*deltaTime;

    
}

//getters
double Object::getLen(){return len;}
Vec2 Object::getPosn(){return posn;}
Vel2 Object::getVel(){return velocity;}
Acc2 Object::getAcc(){return acceleration;}
double Object::getMass(){return mass;}

//setters
void Object::setAcc_x(double acc){acceleration.Ax = acc;}
void Object::setAcc_y(double acc){acceleration.Ay = acc;}
