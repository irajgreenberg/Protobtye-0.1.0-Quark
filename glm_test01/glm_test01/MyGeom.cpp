//
//  MyGeom.cpp
//  glm_test01
//
//  Created by iragreenberg on 12/2/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//

#include "MyGeom.h"


MyGeom::MyGeom(){
    init();
}

void MyGeom::init(){
    
    // Start attribute arrays
    // positions of vertices
    positionData[0]= -0.8f;
    positionData[1]= -0.8f;
    positionData[2]= 0.0f;
    positionData[3]= 0.8f;
    positionData[4]= -0.8f;
    positionData[5]= 0.0f;
    positionData[6]= 0.0f;
    positionData[7]= 0.8f;
    positionData[8]= 0.0f;
    
    // colors of vertices
    colorData[0]= 1.0f;
    colorData[1]= 0.0f;
    colorData[2]= 0.0f;
    colorData[3]= 0.0f;
    colorData[4]= 1.0f;
    colorData[5]= 0.0f;
    colorData[6]= 0.0f;
    colorData[7]= 0.0f;
    colorData[8]= 1.0f;
    
    // Start buffers/vbo's
    // create buffer objs
    GLuint vboHandles[2];
    glGenBuffers(2, vboHandles);
    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];
    
    std::cout << " positionBufferHandle = " <<  vboHandles[0] << std::endl;
    
    //populate the buffers
    // -first the vertex positions
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), positionData, GL_STATIC_DRAW);
    
    // -next the vertex colors
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(float), colorData, GL_STATIC_DRAW);
    
    // bind VAO
    // 1. create and set it up
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);
    std::cout << " vaoHandle = " <<  vaoHandle << std::endl;
    
    // enable vertex position and color attribute arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    // map index 0 to vertex position buffer
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
    
    // map index 0 to vertex color buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);
    
}
void MyGeom::draw(){
    glBindVertexArray(vaoHandle);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}