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

struct Vec2{
    double x,y;
};

class Object{
private:
    Vec2 posn;
    double len;
public:
    Object(double x,double y, double len);
    //getters
    double getLen();
    Vec2 getPosn();
};

#endif /* Object_hpp */
