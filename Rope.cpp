//
//  Rope.cpp
//  SDL_EXPERIMENTING
//
//  Created by Rahul Jain on 04/12/21.
//

#include "Rope.hpp"
#include <iostream>
    Rope::Rope(Me* meNode,Object* otherNode)
    {
        this->meNode = meNode;
        this->otherNode = otherNode;
        initialPosn = meNode->getPosn();
        initialVel = meNode->getVel();
        ropeLength = pow((otherNode->getPosn().y - meNode->getPosn().y ),2) + pow((otherNode->getPosn().x - meNode->getPosn().x ),2);
        ropeLength = pow(ropeLength,0.5);
    }

    double Rope::giveInitialSep()
    {
        double seperation = pow((otherNode->getPosn().y - meNode->getPosn().y ),2) + pow((otherNode->getPosn().x - meNode->getPosn().x ),2);
        return seperation;
    }
    
    bool Rope::RopeCalculus()
    {
        double seperation = pow((otherNode->getPosn().y - meNode->getPosn().y ),2) + pow((otherNode->getPosn().x - meNode->getPosn().x ),2);
        seperation = pow(seperation,0.5);
//        double acc = K*(seperation - originalLen);///meNode->getMass();
        double tension;
        bool counterClock = true;
        if(initialPosn.x - otherNode->getPosn().x > 0)
            counterClock = false;

        double XwrtO = meNode->getPosn().x - otherNode->getPosn().x;
        double YwrtO = meNode->getPosn().y - otherNode->getPosn().y;
        double Vsqr = pow(initialVel.Vx,2) + pow(initialVel.Vy,2) + 2*g*(meNode->getPosn().y - initialPosn.y);
        //When rope slacks
        if(Vsqr < 0)
        {
            std::cout<<Vsqr<<std::endl;
            return false;
        }
        //Normal condition
        else if(counterClock == true)
        {
            double Vnet = pow(Vsqr,.5);

            if(XwrtO == 0)
            {
                tension = g + Vsqr/ropeLength;
                if(YwrtO < 0)
                {
                    meNode->setVel_x(-Vnet);
                    meNode->setVel_y(0);
                }
                else
                {
                    meNode->setVel_x(Vnet);
                    meNode->setVel_y(0);
                }
            }
            else
            {
                double theta = atan(XwrtO/YwrtO);

                //1st quadrant tick
                //sin+ cos+
                if(XwrtO>0 && YwrtO<0)
                {
                    meNode->setVel_x(-Vnet*cos(theta));
                    meNode->setVel_y(Vnet*sin(theta));
                }
                //2nd quadrant tick
                //sin- cos+
                else if(XwrtO>0 && YwrtO>0)
                {
                    meNode->setVel_x(Vnet*cos(theta));
                    meNode->setVel_y(-Vnet*sin(theta));
                }
                //3rd quadrant tick
                //sin- cos-
                else if(XwrtO<0 && YwrtO>0)
                {
                    meNode->setVel_x(Vnet*cos(theta));
                    meNode->setVel_y(-Vnet*sin(theta));
                }
                //4th quadrant tick
                //sin+ cos-
                else if(XwrtO<0 && YwrtO<0)
                {
                    meNode->setVel_x(-Vnet*cos(theta));
                    meNode->setVel_y(Vnet*sin(theta));
                }
                
            }
        }
        else if(counterClock == false)
        {
            double Vnet = pow(Vsqr,.5);

            if(XwrtO == 0)
            {
                tension = g + Vsqr/ropeLength;
                if(YwrtO < 0)
                {
                    meNode->setVel_x(Vnet);
                    meNode->setVel_y(0);
                }
                else
                {
                    meNode->setVel_x(-Vnet);
                    meNode->setVel_y(0);
                }
            }
            else
            {
                double theta = atan(XwrtO/YwrtO);

                //1st quadrant tick
                //sin+ cos+
                if(XwrtO>0 && YwrtO<0)
                {
                    meNode->setVel_x(Vnet*cos(theta));
                    meNode->setVel_y(-Vnet*sin(theta));
                }
                //2nd quadrant tick
                //sin- cos+
                else if(XwrtO>0 && YwrtO>0)
                {
                    meNode->setVel_x(-Vnet*cos(theta));
                    meNode->setVel_y(Vnet*sin(theta));
                }
                //3rd quadrant tick
                //sin- cos-
                else if(XwrtO<0 && YwrtO>0)
                {
                    meNode->setVel_x(-Vnet*cos(theta));
                    meNode->setVel_y(Vnet*sin(theta));
                }
                //4th quadrant tick
                //sin+ cos-
                else if(XwrtO<0 && YwrtO<0)
                {
                    meNode->setVel_x(Vnet*cos(theta));
                    meNode->setVel_y(-Vnet*sin(theta));
                }
                
            }
        }
        return true;
    }
        
