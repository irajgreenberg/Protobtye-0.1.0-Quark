//
//  ProtoBaseApp.cpp
//  Protobyte_dev_v02
//
//  Created by iragreenberg on 9/26/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//

#include "ProtoBaseApp.h"

using namespace ijg;

// NOTE: called before GL context created
ProtoBaseApp::ProtoBaseApp() {
   // std::cout << "in base class cstr" << std::endl;
}

// Get handle to world and init BaseApp
// Note: this function does some work of cstr because
// it is called after GL context has been created.
void ProtoBaseApp::setWorld(std::shared_ptr<ProtoWorld> world){
    this->world = world;
    
    //instantiate lights
    light0 = std::shared_ptr<ProtoLight>(new ProtoLight());
    light1 = std::shared_ptr<ProtoLight>(new ProtoLight());
    light2 = std::shared_ptr<ProtoLight>(new ProtoLight());
    light3 = std::shared_ptr<ProtoLight>(new ProtoLight());
    light4 = std::shared_ptr<ProtoLight>(new ProtoLight());
    light5 = std::shared_ptr<ProtoLight>(new ProtoLight());
    light6 = std::shared_ptr<ProtoLight>(new ProtoLight());
    light7 = std::shared_ptr<ProtoLight>(new ProtoLight());


    // set default light on
    world->add(light0);
     world->add(light1);
     world->add(light2);
     world->add(light3);
     world->add(light4);
     world->add(light5);
     world->add(light6);
     world->add(light7);
    light0->on();

    
    


}

// ownerhship was passed from Protoplasm to BaseApp, so BaseApp must start World rendering loop
void ProtoBaseApp::runWorld() {
    world->run();
}


void ProtoBaseApp::add(std::unique_ptr<ProtoGeom3> geom){
    world->add(std::move(geom));
}

//void ProtoBaseApp::add(std::unique_ptr<ProtoLight> lt){
//     world->add(std::move(lt));
//}

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




