//
//  Rope.hpp
//  SDL_EXPERIMENTING
//
//  Created by Rahul Jain on 04/12/21.
//

#ifndef Rope_hpp
#define Rope_hpp

#include <stdio.h>
#include <math.h>
#include "Object.hpp"
#include "me.hpp"
#define K 0.0005
#define originalLen 0

class Rope{
private:
    Me* meNode;
    Object* otherNode;
    Vec2 initialPosn;
    Vel2 initialVel;
    double ropeLength;
//    double K, originalLen;
public:
    Rope(Me* meNode,Object* otherNode);
    bool RopeCalculus();
    
    void setInitialPosn(Vec2 posn){initialPosn = posn;}
    void setInitialVel(Vel2 vel){initialVel = vel;}
    void setRopeLength(double len){ropeLength = len;}
    Me* giveMe(){return meNode;}
    double giveInitialSep();
};

#endif /* Rope_hpp */
