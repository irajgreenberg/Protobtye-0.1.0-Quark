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
    setBackground(.8, .4, 0);
    isClicked = false;
    
    // light0
    light0->setDiffuse(Col4f(1, 1, 1, 1.0));
    light0->setAmbient(Col4f(.1, .1, .1, 1.0));
    light0->setSpecular(Col4f(1, .6, .6, 1.0));
    light0->on();
    
    cephalopod = ProtoCephalopod(Vec3f(0,0,0), Vec3f(0,0,0), Dim3f(60, 60, 60),ProtoColor4f(.9, .4, .7, 1), 8);
    
    float vals3[] = {0, .1, .2, .3, .4, .5, .6, .7, .8};
    ProtoMatrix3<float> mat01(vals3);
    std::cout << "mat01.getRow(0) = " << mat01.getColumn(0) << std::endl;
    std::cout << "mat01.getRow(1) = " << mat01.getRow(1) << std::endl;
    std::cout << "mat01.getRow(2) = " << mat01.getRow(2) << std::endl;
    std::cout << "mat01 = \n" << mat01 << std::endl;
    
    
    float vals4[] = {0, 2.1, 2.2, .3, .4, 3.5, .6, .7, .8 , .9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5};
    ProtoMatrix4<float> mat02(vals4);
    std::cout << "mat02.getRow(0) = " << mat02.getRow(0) << std::endl;
    std::cout << "mat02.getRow(1) = " << mat02.getRow(1) << std::endl;
    std::cout << "mat02.getRow(2) = " << mat02.getRow(2) << std::endl;
    std::cout << "mat02.getRow(3) = " << mat02.getRow(3) << std::endl;
    std::cout << "mat02 = \n" << mat02 << std::endl;
    
    std::cout << "mat02.getColumn(0) = " << mat02.getColumn(0) << std::endl;
    std::cout << "mat02.getColumn(1) = " << mat02.getColumn(1) << std::endl;
    std::cout << "mat02.getColumn(2) = " << mat02.getColumn(2) << std::endl;
    std::cout << "mat02.getColumn(3) = " << mat02.getColumn(3) << std::endl;
    
    std::cout << "mat01.getDeterminent = " << mat02.getDeterminent() << std::endl;

}


void Cephalopod01::run(){
    pushMatrix();
    translate(0, 0, -65);
    rotate(rotX+=.5, 1, .75, .3);
    cephalopod.display();
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



