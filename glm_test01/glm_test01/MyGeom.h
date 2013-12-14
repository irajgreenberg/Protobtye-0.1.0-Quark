//
//  MyGeom.h
//  glm_test01
//
//  Created by iragreenberg on 12/2/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//

#ifndef __glm_test01__MyGeom__
#define __glm_test01__MyGeom__

#include <iostream>

#if defined(_WIN32) || defined(__linux__)
#include <GL/glew.h>
#endif

#define GLFW_INCLUDE_GLCOREARB

// from OF documentation
// OSX link with " " instead of < > to avoid putting in defualt include path
#if (_MSC_VER)
#include <GLFW/glfw3.h>
#else
#include "GLFW/glfw3.h"
#endif



//using namespace ijg;

class MyGeom {

public:
    MyGeom();
    void draw();
    
private:
    void init();
    
    float positionData[9];
    float colorData[9];
    
    // VAO to group VBO's (especially since they're not currenlty interleaved)
    GLuint vaoHandle;
    
    
};


#endif /* defined(__glm_test01__MyGeom__) */
