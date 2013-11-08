//
//  ProtoBaseApp.cpp
//  Protobyte_dev_v02
//
//  Created by iragreenberg on 9/26/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//

#include "ProtoBaseApp.h"

using namespace ijg;

// required call by subclass cstr
ProtoBaseApp::ProtoBaseApp() {
    //std::cout << "in base class cstr" << std::endl;
}

// get handle to world
void ProtoBaseApp::setWorld(std::unique_ptr<ProtoWorld> world){
    this->world = std::move(world);
}

// ownerhship was passed from Protoplasm to BaseApp, so BaseApp must start World rendering loop
void ProtoBaseApp::runWorld() {
    world->run();
}


void ProtoBaseApp::add(std::unique_ptr<ProtoGeom3> geom){
    world->add(std::move(geom));
}

void ProtoBaseApp::add(std::unique_ptr<ProtoLight> lt){
     world->add(std::move(lt));
}

void ProtoBaseApp::add(std::unique_ptr<ProtoCamera> cam){
    world->add(std::move(cam));
}

// gen funcs
// overloaded background
void ProtoBaseApp::setBackground(float r, float g, float b){
    bgColor.setR(r);
    bgColor.setG(r);
    bgColor.setB(r);
    world->setBackgroundColor(Col3f(r, g, b));
}

void ProtoBaseApp::setBackground(float c){
    setBackground(c, c, c);
}

void ProtoBaseApp::setBackground(const Col3f& col){
    setBackground(col.getR(), col.getG(), col.getB());
}

void ProtoBaseApp::setBackground(const Col4f& col){
    setBackground(col.getR(), col.getG(), col.getB());
}

// END background

// window details
void ProtoBaseApp::setWidth(int canvasWidth){
    this->canvasWidth = canvasWidth;
}

void ProtoBaseApp::setHeight(int canvasHeight){
    this->canvasHeight = canvasHeight;
}

void ProtoBaseApp::setSize(const Dim2i& canvasSize){
    this->canvasSize = canvasSize;
}


int ProtoBaseApp::getWidth() const{
    return canvasWidth;
}

int ProtoBaseApp::getHeight() const{
     return canvasHeight;
}

 Dim2i ProtoBaseApp::getSize()const {
     return canvasSize;
}

// Load Image
void ProtoBaseApp::loadImage(std::string imageName){
    // START for relative resource loading
    char cCurrentPath[FILENAME_MAX];
    
    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        std::cout << "error loading from relative directory" << std::endl;
        //return errno;
    }
    // NOTE - workspace project relative instead of using default derivedData path in Library
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
    std::string cp = cCurrentPath; //cast char[] to string
    std::cout << "current path = " << cp << std::endl;
    std::string pathExtension = "/resources/imgs";
    std::string imgName = "/"+ imageName;
    std::string url = cp+pathExtension+imgName;
    sf::Texture texture;
    if (!texture.loadFromFile(url))
    {
        // error...
    }
}

// END window details


// EVENTS
void ProtoBaseApp::keyPressed(){}
void ProtoBaseApp::mousePressed(){}
void ProtoBaseApp::mouseRightPressed(){}
void ProtoBaseApp::mouseReleased(){}
void ProtoBaseApp::mouseRightReleased(){}
void ProtoBaseApp::mouseMoved(){}
void ProtoBaseApp::mouseDragged(){}

// window events
void ProtoBaseApp::onResized(){}
void ProtoBaseApp::onClosed(){}




