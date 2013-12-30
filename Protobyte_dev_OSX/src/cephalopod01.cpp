//
//  Cephalopod01.cpp
//  Protobyte_dev_v02
//
//  Created by iragreenberg on 9/27/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//

#include "Cephalopod01.h"

using namespace ijg;

namespace {
    float rotX = 0.0;
    float rotY = 0.0;
    float rotZ = 0.0;
}



void Cephalopod01::init(){
    setBackground(0);
    isClicked = false;
    
    // light0
    light0->setDiffuse(Col4f(1, 1, 1, 1.0));
    light0->setAmbient(Col4f(.1, .1, .1, 1.0));
    light0->setSpecular(Col4f(1, .6, .6, 1.0));
    light0->on();
    
    cephalopod = new Cephalopod(Vec3f(0,0,0), Vec3f(0,0,0), Dim3f(60, 60, 60),ProtoColor4f(.9, .4, .7, 1), 12);



}


void Cephalopod01::run(){
    pushMatrix();
    translate(0, 0, -65);
    rotate(rotX+=.005, 1, .75, .3);
    rotate(rotX+=.0057, .25, 1, .3);
    
    cephalopod->display();
    popMatrix();

}

void Cephalopod01::keyPressed(){
    
}


void Cephalopod01::mousePressed(){
    std::cout << "in MousePressed" << std::endl;
    isClicked = true;
    
}
void Cephalopod01::mouseRightPressed(){
    
    
}
void Cephalopod01::mouseReleased(){
    
}
void Cephalopod01::mouseRightReleased(){
    
}
void Cephalopod01::mouseMoved(int mx, int my){
    //light1->setPosition(Vec3f(0, 0, mx));
    
}
void Cephalopod01::mouseDragged(){
    
}

void Cephalopod01::onResized(){
    
}
void Cephalopod01::onClosed(){
    // std::cout << "in Closed" << std::endl;
}



