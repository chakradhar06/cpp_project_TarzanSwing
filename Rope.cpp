//
//  Rope.cpp
//  SDL_EXPERIMENTING
//
//  Created by Rahul Jain on 04/12/21.
//

#include "Rope.hpp"
#include <iostream>
    void Rope::setTarget(SDL_MouseButtonEvent& b, Me* hero, std::vector<Object*> enemyList, std::vector<Object*> frendList)
    {
        double targetMouseDistance = INT_MAX;
        for(auto it: enemyList)
        {
            double seperation = pow((b.x - it->getPosn().x),2) + pow((b.y - it->getPosn().y),2);
            if(seperation < targetMouseDistance)
            {
                otherNode = it;
                targetMouseDistance = seperation;
            }
        }
        for(auto it: frendList)
        {
            double seperation = pow((b.x - it->getPosn().x),2) + pow((b.y - it->getPosn().y),2);
            if(seperation < targetMouseDistance)
            {
                otherNode = it;
                targetMouseDistance = seperation;
            }
        }
        meNode = hero;
        initialPosn = otherNode->getPosn();
        initialVel = otherNode->getVel();
        ropeLength = pow((otherNode->getPosn().y - meNode->getPosn().y ),2) + pow((otherNode->getPosn().x - meNode->getPosn().x ),2);
        ropeLength = pow(ropeLength,0.5);
    }

    double Rope::giveInitialSep()
    {
        double seperation = pow((otherNode->getPosn().y - meNode->getPosn().y ),2) + pow((otherNode->getPosn().x - meNode->getPosn().x ),2);
        return seperation;
    }
    
    bool Rope::RopeCalculus(bool slack, std::vector<Object*> enemyList, std::vector<Object*> frendList)
    {
        double seperation = pow((otherNode->getPosn().y - meNode->getPosn().y ),2) + pow((otherNode->getPosn().x - meNode->getPosn().x ),2);
        seperation = pow(seperation,0.5);
//        double acc = K*(seperation - originalLen);///meNode->getMass();
        double tension;
        
        //cloclwise counterclockwise issue resolution
        bool counterClock = true;

        if(initialPosn.x - meNode->getPosn().x > 0 && initialVel.Vy>0)
            counterClock = false;
        
        if(initialPosn.x - meNode->getPosn().x < 0 && initialVel.Vy<0)
            counterClock = false;

        double XwrtO = otherNode->getPosn().x - meNode->getPosn().x;
        double YwrtO = otherNode->getPosn().y - meNode->getPosn().y;
        
        double Vsqr = pow(initialVel.Vx,2) + pow(initialVel.Vy,2) - 2*gravity*(otherNode->getPosn().y - initialPosn.y);
        //When rope slacks
        if(slack)
        {
            //Slack mechanics
            for(auto it: enemyList)
                it->setAcc_y(-gravity);
            for(auto it: frendList)
                it->setAcc_y(-gravity);
            
            double SlackDiffY = slackOccurence.y - meNode->getPosn().y;
            if(otherNode->getPosn().y - meNode->getPosn().y <= -SlackDiffY)
            {
                initialPosn = otherNode->getPosn();
                initialVel = otherNode->getVel();
                std::cout<<"SLACK"<<std::endl;
                return false;
            }
            return true;
        }
        if(Vsqr < 0)
        {
//            std::cout<<Vsqr<<std::endl;
            return true;
        }
        //Normal condition
        else if(counterClock == true)
        {
            for(auto it:enemyList) it->setAcc_x(0);
            for(auto it:enemyList) it->setAcc_y(0);
            for(auto it:frendList) it->setAcc_y(0);
            for(auto it:frendList) it->setAcc_y(0);
            
            double Vnet = pow(Vsqr,.5);

            if(XwrtO == 0)
            {
                tension = gravity + Vsqr/ropeLength;
                if(YwrtO < 0)
                {
//                    meNode->setVel_x(-Vnet);
//                    meNode->setVel_y(0);
                    for(auto it:enemyList) it->setVel_x(-Vnet);
                    for(auto it:frendList) it->setVel_x(-Vnet);
                    for(auto it:frendList) it->setVel_y(0);
                    for(auto it:enemyList) it->setVel_y(0);
                }
                else
                {
//                    meNode->setVel_x(Vnet);
//                    meNode->setVel_y(0);
                    for(auto it:enemyList) it->setVel_x(Vnet);
                    for(auto it:frendList) it->setVel_x(Vnet);
                    for(auto it:frendList) it->setVel_y(0);
                    for(auto it:enemyList) it->setVel_y(0);
                }
            }
            else
            {
                double theta = atan(XwrtO/YwrtO);
                
                //1st quadrant tick
                //sin+ cos+
                if(XwrtO>0 && YwrtO<0)
                {
//                    std::cout<<"1st  "<<meNode->getVel().Vy<<std::endl;
//                    meNode->setVel_x(-Vnet*cos(theta));
//                    meNode->setVel_y(Vnet*sin(theta));
                    for(auto it:enemyList) it->setVel_x(-Vnet*cos(theta));
                    for(auto it:frendList) it->setVel_x(-Vnet*cos(theta));
                    for(auto it:frendList) it->setVel_y(Vnet*sin(theta));
                    for(auto it:enemyList) it->setVel_y(Vnet*sin(theta));
                }
                //2nd quadrant tick
                //sin- cos+
                else if(XwrtO>0 && YwrtO>0)
                {
//                    std::cout<<"2nd  "<<meNode->getVel().Vy<<std::endl;
//                    meNode->setVel_x(Vnet*cos(theta));
//                    meNode->setVel_y(-Vnet*sin(theta));
                    for(auto it:enemyList) it->setVel_x(Vnet*cos(theta));
                    for(auto it:frendList) it->setVel_x(Vnet*cos(theta));
                    for(auto it:frendList) it->setVel_y(-Vnet*sin(theta));
                    for(auto it:enemyList) it->setVel_y(-Vnet*sin(theta));
                }
                //3rd quadrant tick
                //sin- cos-
                else if(XwrtO<0 && YwrtO>0)
                {
//                    std::cout<<"3rd  "<<meNode->getVel().Vy<<std::endl;
//                    meNode->setVel_x(Vnet*cos(theta));
//                    meNode->setVel_y(-Vnet*sin(theta));
                    for(auto it:enemyList) it->setVel_x(Vnet*cos(theta));
                    for(auto it:frendList) it->setVel_x(Vnet*cos(theta));
                    for(auto it:frendList) it->setVel_y(-Vnet*sin(theta));
                    for(auto it:enemyList) it->setVel_y(-Vnet*sin(theta));
                }
                //4th quadrant tick
                //sin+ cos-
                else if(XwrtO<0 && YwrtO<0)
                {
//                    std::cout<<"4th  "<<meNode->getVel().Vy<<std::endl;
//                    meNode->setVel_x(-Vnet*cos(theta));
//                    meNode->setVel_y(Vnet*sin(theta));
                    for(auto it:enemyList) it->setVel_x(-Vnet*cos(theta));
                    for(auto it:frendList) it->setVel_x(-Vnet*cos(theta));
                    for(auto it:frendList) it->setVel_y(Vnet*sin(theta));
                    for(auto it:enemyList) it->setVel_y(Vnet*sin(theta));
                }
                
            }
        }
        else if(counterClock == false)
        {
            double Vnet = pow(Vsqr,.5);

            if(XwrtO == 0)
            {
                tension = gravity + Vsqr/ropeLength;
                if(YwrtO < 0)
                {
//                    meNode->setVel_x(Vnet);
//                    meNode->setVel_y(0);
                    for(auto it:enemyList) it->setVel_x(Vnet);
                    for(auto it:frendList) it->setVel_x(Vnet);
                    for(auto it:frendList) it->setVel_y(0);
                    for(auto it:enemyList) it->setVel_y(0);
                }
                else
                {
//                    meNode->setVel_x(-Vnet);
//                    meNode->setVel_y(0);
                    for(auto it:enemyList) it->setVel_x(-Vnet);
                    for(auto it:frendList) it->setVel_x(-Vnet);
                    for(auto it:frendList) it->setVel_y(0);
                    for(auto it:enemyList) it->setVel_y(0);
                }
            }
            else
            {
                double theta = atan(XwrtO/YwrtO);

                //1st quadrant tick
                //sin+ cos+
                if(XwrtO>0 && YwrtO<0)
                {
//                    meNode->setVel_x(Vnet*cos(theta));
//                    meNode->setVel_y(-Vnet*sin(theta));
                    for(auto it:enemyList) it->setVel_x(Vnet*cos(theta));
                    for(auto it:frendList) it->setVel_x(Vnet*cos(theta));
                    for(auto it:frendList) it->setVel_y(-Vnet*sin(theta));
                    for(auto it:enemyList) it->setVel_y(-Vnet*sin(theta));
                }
                //2nd quadrant tick
                //sin- cos+
                else if(XwrtO>0 && YwrtO>0)
                {
//                    meNode->setVel_x(-Vnet*cos(theta));
//                    meNode->setVel_y(Vnet*sin(theta));
                    for(auto it:enemyList) it->setVel_x(-Vnet*cos(theta));
                    for(auto it:frendList) it->setVel_x(-Vnet*cos(theta));
                    for(auto it:frendList) it->setVel_y(Vnet*sin(theta));
                    for(auto it:enemyList) it->setVel_y(Vnet*sin(theta));
                }
                //3rd quadrant tick
                //sin- cos-
                else if(XwrtO<0 && YwrtO>0)
                {
//                    meNode->setVel_x(-Vnet*cos(theta));
//                    meNode->setVel_y(Vnet*sin(theta));
                    for(auto it:enemyList) it->setVel_x(-Vnet*cos(theta));
                    for(auto it:frendList) it->setVel_x(-Vnet*cos(theta));
                    for(auto it:frendList) it->setVel_y(Vnet*sin(theta));
                    for(auto it:enemyList) it->setVel_y(Vnet*sin(theta));
                }
                //4th quadrant tick
                //sin+ cos-
                else if(XwrtO<0 && YwrtO<0)
                {
//                    meNode->setVel_x(Vnet*cos(theta));
//                    meNode->setVel_y(-Vnet*sin(theta));
                    for(auto it:enemyList) it->setVel_x(Vnet*cos(theta));
                    for(auto it:frendList) it->setVel_x(Vnet*cos(theta));
                    for(auto it:frendList) it->setVel_y(-Vnet*sin(theta));
                    for(auto it:enemyList) it->setVel_y(-Vnet*sin(theta));
                }
                
            }
        }
        return false;
    }
        
