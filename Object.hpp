//
//  Object.hpp
//  SDL_EXPERIMENTING
//
//  Created by Rahul Jain on 04/12/21.
//

#ifndef Object_hpp
#define Object_hpp

#include <stdio.h>
#include <math.h>
#define gravity .05

struct Vec2{
    double x,y;
};
struct Vel2{
    double Vx=0,Vy=0;
};
struct Acc2{
    double Ax =0;
    double Ay =0;//under constant affect of gravity
};

class Object{
private:
    Vec2 posn;
    Vel2 velocity;
    Acc2 acceleration;
    double len;
    bool evil;
    double mass = 1000;
public:
    Object(bool evil, double x,double y, double len);
    void UpdatePosn();
    
    //getters
    double getLen();
    Vec2 getPosn();
    Vel2 getVel();
    Acc2 getAcc();
    double getMass();
    
    //setters
    void setAcc_x(double acc);
    void setAcc_y(double acc);
    void setPosn_x(double x){posn.x = x;}
    void setPosn_y(double y){posn.y = y;}
    void setVel_x(double velx){velocity.Vx = velx;}
    void setVel_y(double vely){velocity.Vy = vely;}
};

#endif /* Object_hpp */
