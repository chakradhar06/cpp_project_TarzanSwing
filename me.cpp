//
//  me.cpp
//  SDL_EXPERIMENTING
//
//  Created by Rahul Jain on 04/12/21.
//

#include "me.hpp"

    Me::Me(double x,double y, double len, double vx, double vy)
    {
        posn.x = x;
        posn.y = y;
        this->len = len;
        velocity.Vx = vx;
        velocity.Vy = vy;
    }
    
    //Collision Detection
    bool Me::CheckCollision(class Me* me, std::vector<Object*> enemyList)
    {
        for(auto it: enemyList)
        {
            double rIdeal = me->len + it->getLen();
            rIdeal *= rIdeal;
            double Seperation = pow( (me->posn.x - it->getPosn().x),2 ) + pow( (me->posn.y - it->getPosn().y),2 );
            if(Seperation <= rIdeal)
                return true;
        }
        return false;
    }
    
    void Me::UpdatePosn()
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
    Vec2 Me::getPosn(){return posn;}
    Vel2 Me::getVel(){return velocity;}
    Acc2 Me::getAcc(){return acceleration;}
    double Me::getRadius(){return len;}
    double Me::getMass(){return mass;}
    
    //setters
    void Me::setAcc_x(double acc){acceleration.Ax = acc;}
    void Me::setAcc_y(double acc){acceleration.Ay = acc;}

    

