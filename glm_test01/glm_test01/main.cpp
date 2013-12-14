//
//  main.cpp
//  glm_test01
//
//  Created by Ira on 11/30/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//

#ifdef _WIN32
#include <GL/glew.h>
#endif


// from OF documentation
// OSX link with " " instead of < > to avoid putting in defualt include path
#if (_MSC_VER)
#include <GLFW/glfw3.h>
#else
#include "GLFW/glfw3.h"
#endif

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "glm/glm.hpp"
//#include "glm/gtc/matrix_projection.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"

#include "ProtoShader.h"

#include "MyGeom.h"

// use GL3 context (OpenGL 3.2-4.1)
#define GLFW_INCLUDE_GLCOREARB


using namespace ijg;


static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, const char * argv[])
{

    
    
    
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
   GLFWwindow* window = glfwCreateWindow(800, 600, "glfw_glm_glsl4_Test", NULL, NULL);
    
    // get window size
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    
    
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    // end GLW setup
    
//    
//    // set gl states
//    glClearColor(0, 0, 0, 1.0f);
//    glShadeModel(GL_SMOOTH);
//    // enable specualrity on textures
//    glLightModelf(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
//    glEnable(GL_LIGHTING);
//    glFrontFace(GL_CCW); // default
//    glEnable(GL_CULL_FACE);
//    glCullFace(GL_BACK);
//    glDisable(GL_CULL_FACE);
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//    //glShadeModel(GL_FLAT); // option
//    glEnable(GL_COLOR_MATERIAL); // incorporates per vertex color with lights
//    
//    // global ambinet unrelated to lights
//    float globalAmbient[4] = {.2, .2, .2, 1};
//    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,  globalAmbient);
//    
//    // let glColor contorl diffues and ambient material values
//    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
//    
//    //
//    glEnable(GL_BLEND);
//    //glBlendFunc(GL_DST_COLOR,GL_ZERO);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    //glBlendFunc(GL_DST_COLOR,GL_ZERO);
//    //glBlendFunc (GL_ONE, GL_ONE);
//    
//    //glEnable(GL_ALPHA_TEST);
//    //glAlphaFunc(GL_GREATER,0.0f);
//    
//    
//    
//    
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_NORMALIZE); //  good for uniform scaling
//    
//    
//    glClearStencil(0); // clear stencil buffer
//    glClearDepth(1.0f); // 0 is near, 1 is far
//    glDepthFunc(GL_LEQUAL);
    
    
    // manually handle modelview matrix transform
    
    // from http://www.swiftless.com/tutorials/opengl4/3-opengl-4-matrices.html
//    glm::mat4 projectionMatrix; // Store the projection matrix
//    glm::mat4 viewMatrix; // Store the view matrix
//    glm::mat4 modelMatrix; // Store the model matrix
//    
//    projectionMatrix = glm::perspective(60.0f, (float)width / (float)height, 0.1f, 100.f);
    // I may not use these, but...

    
    
    
    glm::vec4 position = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 5.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 mv = view*model;
    glm::vec4 transformed = mv*position;
    float viewAngle = 45.0f;
    float aspect = width/height;
    float nearDist = .1f;
    float farDist = 300.0f;
    
    // projection matrix
    glm::mat4 p = glm::perspective(viewAngle, aspect, nearDist, farDist);
    glm::mat4 mvp = p * mv;
    //glUniformMatrix4fv(0, 1, GL_FALSE, &proj[0][0]);
    
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    
    printf ("GL Renderer = %s\n", renderer);
    printf ("GL Vender = %s\n", vendor);
    printf ("GL Version = %s\n", version);
    printf ("GLSL Version = %s\n", glslVersion);
    
    // extensions
//    GLint nExtensions;
//    glGetIntegerv(GL_, <#GLint *params#>)
//    for(int i=0; i<)
    
    MyGeom geom;
    ProtoShader shader("toon1.vert", "toon1.frag");
    
    // map vertex positions and colors to shader input variable
    // use layout (location=#) in shader instead
    //glBindAttribLocation(shader.getID(), 0, "VertexPosition");
    //glBindAttribLocation(shader.getID(), 1, "VertexColor");
    
    
   
    
    float rotAngle = 5.0f;
    
    
    
    while (!glfwWindowShouldClose(window))
    {
        
        //glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        
        GLuint mvpLocation = glGetUniformLocation(shader.getID(), "MVPMatrix");
        if (mvpLocation >= 0){
            glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);
        }

        
        
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotAngle++, glm::vec3(0.0f, 1.0f, 1.0f));
        
        GLuint location = glGetUniformLocation(shader.getID(), "RotationMatrix");
        
        if (location >= 0){
            glUniformMatrix4fv(location, 1, GL_FALSE, &rotationMatrix[0][0]);
        }
        /*
         TO DO – fix timing issues with control for users:
         From: http://stackoverflow.com/questions/2182675/how-do-you-make-sure-the-speed-of-opengl-animation-is-consistent-on-different-ma
         */

        geom.draw();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

