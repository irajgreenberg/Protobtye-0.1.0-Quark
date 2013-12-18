//
//  Cephalopod01.h
//  Protobyte_dev_v02
//
//  Created by iragreenberg on 9/27/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//

#ifndef __Protobyte_dev_v02__Cephalopod01__
#define __Protobyte_dev_v02__Cephalopod01__

#include "ProtoBaseApp.h"
#include <iostream>
#include "ProtoCephalopod.h"


using namespace ijg;

class Cephalopod01 : public ProtoBaseApp {

protected:
    ProtoCephalopod cephalopod;
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

#endif /* defined(__Protobyte_dev_v02__Cephalopod01__) */
