/*!  \brief  ProtoVerletPath.cpp: (add brief description)
 ProtoVerletPath.cpp
 Protobyte Library v02
 
 Created by Ira on 12/26/13.
 Copyright (c) 2013 Ira Greenberg. All rights reserved.
 
 Library Usage:
 This work is licensed under the Creative Commons
 Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 To view a copy of this license, visit
 http://creativecommons.org/licenses/by-nc-sa/3.0/
 or send a letter to Creative Commons,
 444 Castro Street, Suite 900,
 Mountain View, California, 94041, USA.
 
 This notice must be retained any source distribution.
 
 \ingroup common
 This class is part of the group common (update)
 \sa NO LINK
 */

#include "ProtoVerletPath.h"

using namespace ijg;

ProtoVerletPath::ProtoVerletPath(){
}

// no Spline param - init() not called
ProtoVerletPath::ProtoVerletPath(float tension, AnchorMode anchorMode):
tension(tension), anchorMode(anchorMode){
}

// Spline3
ProtoVerletPath::ProtoVerletPath(const Spline3& spline, float tension, AnchorMode anchorMode):
vecs(vecs), tension(tension), anchorMode(anchorMode){
    init();
}

// **** not implemented yet
ProtoVerletPath::ProtoVerletPath(const Spline3& spline, float tensionMin, float tensionMax, AnchorMode anchorMode):
vecs(vecs), tensionMin(tensionMin), tensionMax(tensionMax), anchorMode(anchorMode){
    // init();
}

// *** not implemented yet
ProtoVerletPath::ProtoVerletPath(const Spline3& spline, const Tup2& edgeTensions, AnchorMode anchorMode){
    // init();
}

// build verlet chain
void ProtoVerletPath::init(){
    // in case this has been called before clean storage vectors
    balls.clear();
    sticks.clear();
    
    for(size_t i = 0; i<spline.getVerts().size(); ++i){
        
        balls.push_back(std::shared_ptr<VerletBall>(new VerletBall(&spline.getVerts().at(i))));
        
        // create sticks
        // ensure 1st 2 balls exist
        if(i>0){
            // set anchorsMode: ...tension, Tup2f(1, 0))));
            // NOTE:: only LEFT and RIGHT currently implemented
            switch(anchorMode){
                    // Modes:: LEFT,RIGHT,CENTER,ENDS,RANDOM,ALTERNATING,ALL,NONE
                case LEFT:
                    if (i==1){
                        sticks.push_back(std::unique_ptr<VerletStick>(new VerletStick(balls.at(i-1), balls.at(i), tension, Tup2f(0, .5))));
                    } else {
                        sticks.push_back(std::unique_ptr<VerletStick>(new VerletStick(balls.at(i-1), balls.at(i), tension, Tup2f(.5, .5))));
                    }
                    break;
                case RIGHT:
                    if (i==vecs.size()-1){
                        //    sticks.push_back(VerletStick(balls.at(i-1), balls.at(i), tension, Tup2f(.5, 0)));
                    } else {
                        //    sticks.push_back(VerletStick(balls.at(i-1), balls.at(i), tension));
                    }
                    break;
                    //                case CENTER:
                    //                    if (i==(vecs.size()-1)/2){
                    //                        sticks.push_back(VerletStick(balls.at(i-1), balls.at(i), tension, Tup2f(0, .5)));
                    //                    } else {
                    //                        sticks.push_back(VerletStick(balls.at(i-1), balls.at(i), tension));
                    //                    }
                    //                    break;
                    //                case ENDS:
                    //                    if (i==1){
                    //                        sticks.push_back(VerletStick(balls.at(i-1), balls.at(i), tension, Tup2f(0, .5)));
                    //                    } else if (i==vecs.size()-1){
                    //                        sticks.push_back(VerletStick(balls.at(i-1), balls.at(i), tension, Tup2f(.5, 0)));
                    //                    }
                    //                        else {
                    //                        sticks.push_back(VerletStick(balls.at(i-1), balls.at(i), tension));
                    //                    }
                    //                    break;
                    //                case RANDOM:
                    //                    if (i==1){
                    //                        sticks.push_back(VerletStick(balls.at(i-1), balls.at(i), tension, Tup2f(0, .5)));
                    //                    } else {
                    //                        sticks.push_back(VerletStick(balls.at(i-1), balls.at(i), tension));
                    //
                    //                        break;
                    //                    }
                    //                case ALL:
                    //                    if (i==1){
                    //                        sticks.push_back(VerletStick(balls.at(i-1), balls.at(i), tension, Tup2f(0, .5)));
                    //                    } else {
                    //                        sticks.push_back(VerletStick(balls.at(i-1), balls.at(i), tension));
                    //
                    //                        break;
                    //                    }
                default:
                    //   sticks.push_back(std::unique_ptr<VerletStick>(new VerletStick(std::move(balls.at(i-1)), std::move(balls.at(i)), tension)));
                    break;
            }
            
        }
    }
    
}

void ProtoVerletPath::setVecs(std::vector<Vec3> vecs){
    this->vecs = vecs;
    init();
}


void ProtoVerletPath::push(const Vec3& nudge){
    // sticks.at(sticks.size()-1).push(1, nudge);
}



void ProtoVerletPath::run() {
    for(size_t i = 1; i<balls.size(); ++i){
        balls.at(i)->verlet2();
    }
    
    /****************************************
     // order seems to matter: constrain
     // prior to verleting
     ****************************************/
    
    
    for(size_t i = 0; i<sticks.size(); ++i){
        sticks.at(i)->constrainLen();
        sticks.at(i)->display();
    }
    
    
}




// dstr
ProtoVerletPath::~ProtoVerletPath() {}
