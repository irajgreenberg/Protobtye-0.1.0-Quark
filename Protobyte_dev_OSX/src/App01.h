//
//  App01.h
//  Protobyte_dev_v02
//
//  Created by iragreenberg on 9/27/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//

#ifndef __Protobyte_dev_v02__App01__
#define __Protobyte_dev_v02__App01__

#include "ProtoBaseApp.h"
#include <iostream>

#include "ProtoVerletCube.h"
#include "ProtoVerletSurface.h"
#include "ProtoImage.h"

using namespace ijg;

class App01 : public ProtoBaseApp {

private:
    std::unique_ptr<ProtoToroid> toroid2;
    std::unique_ptr<ProtoVerletSurface> verletSurf;
    std::unique_ptr<ProtoVerletSurface> verletSurfs[6];
    std::unique_ptr<ProtoVerletCube> verletCube;

public:
    void init();
    void run();
    
    // Mouses/Key Events
    void keyPressed();
    void mousePressed();
    void mouseRightPressed();
    void mouseReleased();
    void mouseRightReleased();
    void mouseMoved(int mx, int my);
    void mouseDragged();
    
    // window events
    void onResized();
    void onClosed();

    bool isClicked;
    
    
};

#endif /* defined(__Protobyte_dev_v02__App01__) */
