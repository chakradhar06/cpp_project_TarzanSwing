//
//  me.hpp
//  SDL_EXPERIMENTING
//
//  Created by Rahul Jain on 04/12/21.
//

#ifndef me_hpp
#define me_hpp

#include <stdio.h>
#include <math.h>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Object.hpp"
#define g .05

//struct Vec2{
//    double x,y;
//};
struct Vel2{
    double Vx=0,Vy=0;
};
struct Acc2{
    double Ax =0;
    double Ay =g;//under constant affect of gravity
};

class Me{
private:
    Vec2 posn;
    Vel2 velocity;
    Acc2 acceleration;
    double len;
    double mass = 1000;
public:
    Me(double x,double y, double len, double vx, double vy);
    
    //Collision Detection
    bool CheckCollision(class Me* me, std::vector<Object*> enemyList);
    void UpdatePosn();
    
    //getters
    Vec2 getPosn();
    Vel2 getVel();
    Acc2 getAcc();
    double getRadius();
    double getMass();
    
    //setters
    void setAcc_x(double acc);
    void setAcc_y(double acc);
    void setPosn_x(double x){posn.x = x;}
    void setPosn_y(double y){posn.y = y;}
    void setVel_x(double velx){velocity.Vx = velx;}
    void setVel_y(double vely){velocity.Vy = vely;}

};

#endif /* me_hpp */
