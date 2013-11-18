//
//  App01.cpp
//  Protobyte_dev_v02
//
//  Created by iragreenberg on 9/27/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//

#include "App01.h"


using namespace ijg;

float x = 0;
float tx = 0;

void App01::init(){
    
    // set world state
    // set window background color
    setBackground(.2, .4, .45);
    /* api ideas
     setGravity(-1 - 1);
     setWind(ProtoVector3);
     setChaos(0-1);
     setAntiAliasing(0-1);
     setShading(SMOOTH or FACETED);
     setLighting();
     */
    
    isClicked = false;
    
    // light0
    light0->setPosition(Vec3f(30, 0, 30));
    light0->setDiffuse(Col4f(1, 1, 1, 1.0));
    light0->setAmbient(Col4f(.1, .1, .1, 1.0));
    light0->setSpecular(Col4f(1, 0, 0, 1.0));
    light0->on();
    
    // light1
    light1->setPosition(Vec3f(-30, 0, -30));
    light1->setSpecular(Col4f(.8, .8, 0, 1.0));
    light1->setAmbient(Col4f(.1, .1, .1, 0));
    light1->setDiffuse(Col4f(1, 1, 1, 1.0));
    light1->on();
    
    // light2
    light2->setPosition(Vec3f(0, 30, 0));
    light2->setAmbient(Col4f(.1, .1, .1, 1.0));
    light2->setSpecular(Col4f(0, 0, 1, 1.0));
    light2->setDiffuse(Col4f(1, 1, 1, 1.0));
    light2->on();
    
    
    std::string imgs[6] = {"pebbles.jpg", "shipPlate.jpg", "lentils.jpg", "fabric.JPG", "leather.jpg" , "leather2.jpg" };
    verletCube = std::unique_ptr<ProtoVerletCube> (new ProtoVerletCube(Vec3f(0,0,0), Vec3f(0,0,0), Dim3f(40, 40, 40), ProtoColor4f(ProtoMath::random(.7, 1.0), ProtoMath::random(.7, 1.0), ProtoMath::random(.7, 1.0), .75), Tup2i(27, 27), ProtoMath::random(.02, .2), "water.jpg", ProtoVerletSurface::ALL_CORNERS));
    
    
    
    toroid2 = std::unique_ptr<ProtoToroid> (new ProtoToroid(Vec3f(0, 0, 0), Vec3f(0, ProtoMath::PI/3.0,0), Dim3f(20, 20, 20),ProtoColor4f(.7, .5, .7, 1.0), 75, 75, .9, .2));
    toroid2->setShininess(65);
    
}

// event thread runs continuously
//ProtoWorld draw independently
void App01::run(){
    // if(isClicked){
    //std::cout << "frameCount = " << frameCount << std::endl;
    //std::cout << "frameRate = " << frameRate << std::endl;
    //std::cout << "ind = " << ind << std::endl;
    //light1->setPosition(Vec3f(0, 0, 100));
    
    pushMatrix();
    translate(0, 0, -65);
    toroid2->display(POINTS, .02);
    popMatrix();
    
    pushMatrix();
    translate(0, 0, -65);
    rotate(x+=.5, 1, .75, .3);
    verletCube->textureOn();
    verletCube->pulse();
    ProtoGeom3::renderMode modes[] = {SURFACE, POINTS, WIREFRAME, POINTS, SURFACE, POINTS};
    float pointSizes[] = {.2, .8, 1.2, 3, 5, .02, .02};
    //verletCube->display(modes, pointSizes);
    verletCube->display();
    popMatrix();
    
    
}

void App01::keyPressed(){
    
}


void App01::mousePressed(){
    std::cout << "in MousePressed" << std::endl;
    isClicked = true;
    
}
void App01::mouseRightPressed(){
    
    
}
void App01::mouseReleased(){
    
}
void App01::mouseRightReleased(){
    
}
void App01::mouseMoved(int mx, int my){
    //light1->setPosition(Vec3f(0, 0, mx));
    
}
void App01::mouseDragged(){
    
}

void App01::onResized(){
    
}
void App01::onClosed(){
    // std::cout << "in Closed" << std::endl;
}



