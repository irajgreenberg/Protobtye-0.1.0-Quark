//
//  Cephalopod_Dev_02.h
//  Protobyte_dev_v02
//
//  Created by iragreenberg on 9/27/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//

#ifndef __Protobyte_dev_v02__Cephalopod_Dev_02__
#define __Protobyte_dev_v02__Cephalopod_Dev_02__

#include "ProtoBaseApp.h"
#include <iostream>
#include "ProtoCephalopod.h"


using namespace ijg;

class Cephalopod_Dev_02 : public ProtoBaseApp {

protected:
    Cephalopod* cephalopod;
  public:
   
    
    void init();
    void run();
    
};

#endif /* defined(__Protobyte_dev_v02__Cephalopod_Dev_02__) */
