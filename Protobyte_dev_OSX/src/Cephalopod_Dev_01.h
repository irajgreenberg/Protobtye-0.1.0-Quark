//
//  Cephalopod_Dev_01.h
//  Protobyte_dev_v02
//
//  Created by iragreenberg on 9/27/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//

#ifndef __Protobyte_dev_v02__Cephalopod_Dev_01__
#define __Protobyte_dev_v02__Cephalopod_Dev_01__

#include "ProtoBaseApp.h"
#include <iostream>
#include "ProtoCephalopod.h"
#include "ProtoGeoSphere.h"
#include "ProtoCylinder.h"
#include "ProtoMatrix3.h"
#include "ProtoMatrix4.h"
#include "ProtoToroid.h"


using namespace ijg;

class Cephalopod_Dev_01 : public ProtoBaseApp {

protected:
    Cephalopod* cephalopod;
    std::vector<ProtoCylinder> cylinders;
    ProtoGeoSphere geoSphere;
    
    Vec3 centroid;
    Mat3 frame;
    
    Toroid toroid;
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

#endif /* defined(__Protobyte_dev_v02__Cephalopod_Dev_01__) */
