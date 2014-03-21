//
//  Cephalopod_Dev_02.cpp
//  Protobyte_dev_v02
//
//  Created by iragreenberg on 9/27/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//

#include "Cephalopod_Dev_02.h"

using namespace ijg;

namespace {
    float rotX = 0.0;
    float rotY = 0.0;
    float rotZ = 0.0;
}



void Cephalopod_Dev_02::init(){
    setBackground(.35, .35, .375);
    
    // light0
    light0->setDiffuse(Col4f(1, 1, 1, 1.0));
    light0->setAmbient(Col4f(.1, .1, .1, 1.0));
    light0->setSpecular(Col4f(1, .6, .6, 1.0));
    light0->on();
    
    
    // light1
    light1->setPosition(Vec3f(3.5, 0, 2));
    light1->setDiffuse(Col4f(.2, .2, 1, 1.0));
    light1->setAmbient(Col4f(.1, .1, .1, 1.0));
    light1->setSpecular(Col4f(1, .6, .6, 1.0));
    light1->on();

    
    cephalopod = new Cephalopod(Vec3f(0,0,0), Vec3f(0,0,0), Dim3f(20, 20, 20),ProtoColor4f(.9, .4, .7, 1), 12, "pebbles.jpg");
}


void Cephalopod_Dev_02::run(){
    pushMatrix();
    translate(0, 0, -50);
    rotate(rotX+=.3, 1, .75, .3);
    rotate(rotY+=.55, .25, 1, .3);
    cephalopod->display();
    popMatrix();

}




