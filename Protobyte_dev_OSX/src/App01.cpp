//
//  App01.cpp
//  Protobyte_dev_v02
//
//  Created by iragreenberg on 9/27/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//

#include "App01.h"

#include <unistd.h>
#define GetCurrentDir getcwd

using namespace ijg;
float x = 0;
float tx = 0;
float theta = 0;
int ind = 0;
int ind2 = 0;


void App01::init(){
    
    // set window background color
    setBackground(.1);
    
    isClicked = false;
    
    // light0
    //light0->off();
    light0->setPosition(Vec3f(100,100,-100));
    light0->setDiffuse(Col4f(.3, .3, .3, 1.0));
    light0->setAmbient(Col4f(0,0,0, 1.0));
    light0->setSpecular(Col4f(1, 1, 0, 1.0));
    
    // light1
    light1->on();
    light1->setPosition(Vec3f(0, 0, 50));
    light1->setSpecular(Col4f(.5, .5, 1, 1.0));
     light1->setAmbient(Col4f(0,0,0, 1.0));
    light1->setDiffuse(Col4f(.3, .3, .3, 1.0));
    
    // light2
    light2->on();
    light2->setPosition(Vec3f(-60, 0, -100));
    light2->setAmbient(Col4f(.1, .1, .1, 1.0));
    light2->setSpecular(Col4f(0, 1, 1, 1.0));
    light2->setDiffuse(Col4f(.3, .3, .3, 1.0));
    
    
    
    
    
    
    //window size is read only
    //    std::cout << "window width = " << getWidth() << std::endl;
    //    std::cout << "window height = " << getHeight() << std::endl;
    //    std::cout << "window size = " << getSize() << std::endl;
    //
    // START for relative resource loading
    char cCurrentPath[FILENAME_MAX];
    
    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        std::cout << "error loading from relative directory" << std::endl;
        //return errno;
    }
    // NOTE - make workspace project relative instead of using default derivedData path in Library
    //std::cout << "cCurrentPath = " << cCurrentPath << std::endl;
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
    std::string cp = cCurrentPath; //cast char[] to string
    std::cout << "current path = " << cp << std::endl;
    std::string pathExtension = "/resources/imgs";
    std::string imgName = "/shipPlate.raw";
    std::string url = cp+pathExtension+imgName;
    //std::cout << "url = " << url << std::endl;
    //std::string url = "/Users/33993405/Dropbox/ira_dev/Protobyte_dev_v02_OSX/build/resources/stiller.raw";
    
    // END for relative resource loading
    
    std::string textureImgs[6] = {url, url, url, url, url, url};
    
    
    for(int i=0; i<6; ++i) {
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(Vec3f(0,0,0),
                                                                                     Vec3f(0,0,0), Dim3f(40, 40, 1), ProtoColor4f(ProtoMath::random(.7, 1.0), 1.0, 1.0, .8), 37, 37, /*ProtoMath::random(.3, .8)*/ProtoMath::random(.02, .2), textureImgs[i], ProtoVerletSurface::ALL_EDGES)); // 91, 91
    }
    toroid2 = std::unique_ptr<ProtoToroid> (new ProtoToroid(Vec3f(0, 0, 0), Vec3f(0, ProtoMath::PI/3.0,0), Dim3f(20, 20, 20),ProtoColor4f(.2, .2, .2, 1.0), 75, 75, .9, .2));
    toroid2->setShininess(6);
    //toroid2->setEmissionMaterialColor(Col4f(0,0,0,1));
    glDepthMask(true);
    glEnable(GL_DEPTH_TEST);
    //glDisable(GL_CULL_FACE);
    //    glEnable(GL_FLAT);
    //glShadeModel(GL_FLAT);
    
    
    /* api ideas
     setGravity(-1 - 1);
     setWind(ProtoVector3);
     setChaos(0-1);
     setAntiAliasing(0-1);
     setShading(SMOOTH or FACETED);
     setLighting();
     */
    
    //setshininess("light0", 23);
    
}

// event thread runs continuously
//ProtoWorld draw independently
void App01::run(){
    if(isClicked){
        //std::cout << "frameCount = " << frameCount << std::endl;
        //std::cout << "frameRate = " << frameRate << std::endl;
        //std::cout << "ind = " << ind << std::endl;
        //glPushMatrix();
        glTranslatef(0, 0, -100+tx);
        tx+=.05;
        glPushMatrix();
        glRotatef(x+=.2, 1, .75, .3);
        //light2->setPosition(Vec3f(x*.1, 0, 10));
        //light2->setShininess(24);
        //light7->setShininess(128);
        //glPopMatrix();
        //glRotatef(90, 0, 1, 0);
        glDisable(GL_TEXTURE_2D);
        toroid2->display();
        
        
        for(int i=0; i<6; ++i) {
           verletSurfs[i]->flow();
        }
        // left face
        glPushMatrix();
        glTranslatef(-verletSurfs[0]->getSize().w/2, 0, 0);
        glRotatef(90, 0, 1, 0);
        glEnable(GL_TEXTURE_2D);
        verletSurfs[0]->display();
        glPopMatrix();
        
        // right face
        glPushMatrix();
        glTranslatef(verletSurfs[1]->getSize().w/2, 0, 0);
        glRotatef(-90, 0, 1, 0);
        glEnable(GL_TEXTURE_2D);
        verletSurfs[1]->display();
        glPopMatrix();
        
        // front face
        glPushMatrix();
        glTranslatef(0, 0, verletSurfs[2]->getSize().w/2);
        glEnable(GL_TEXTURE_2D);
        verletSurfs[2]->display();
        glPopMatrix();
        
        // back face
        glPushMatrix();
        glTranslatef(0, 0, -verletSurfs[3]->getSize().w/2);
        glRotatef(180, 0, 1, 0);
        glEnable(GL_TEXTURE_2D);
        //verletSurfs[3]->display();
        verletSurfs[3]->display(ProtoGeom3::VERTEX_BUFFER_OBJECT, ProtoGeom3::WIREFRAME, .01);
        glPopMatrix();
        
        // top face
        glPushMatrix();
        glTranslatef(0, verletSurfs[4]->getSize().h/2, 0);
        glRotatef(90, 1, 0, 0);
        glEnable(GL_TEXTURE_2D);
        //verletSurfs[4]->display();
        verletSurfs[4]->display(ProtoGeom3::VERTEX_BUFFER_OBJECT, ProtoGeom3::WIREFRAME, .01);
        glPopMatrix();
        
        // bottom face
        glPushMatrix();
        {
            glTranslatef(0, -verletSurfs[5]->getSize().h/2, 0);
            glRotatef(-90, 1, 0, 0);
            
            glEnable(GL_TEXTURE_2D);
            verletSurfs[5]->setMeshColor(Col4f(1.0, 1.0, 1.0, 1.0));
            //verletSurfs[5]->display(ProtoGeom3::VERTEX_BUFFER_OBJECT, ProtoGeom3::SURFACE, .1);
            
            //glDisable(GL_TEXTURE_2D);
            verletSurfs[5]->setMeshColor(Col4f(1.0, .4, .4, .3));
            verletSurfs[5]->display(ProtoGeom3::VERTEX_BUFFER_OBJECT, ProtoGeom3::WIREFRAME, .01);
        }
        glPopMatrix();
        
        
        //     verletSurf->flow();
        //    verletSurf->setMeshColor(Col4f(1.0, 1.0, 1.0, 1.0)); // not really working at present
        //
        //    glEnable(GL_TEXTURE_2D);
        //    verletSurf->display(ProtoGeom3::VERTEX_BUFFER_OBJECT, ProtoGeom3::SURFACE, .1);
        //    glDisable(GL_TEXTURE_2D);
        //    verletSurf->setMeshColor(Col4f(.4, .4, .4, .2));
        //    verletSurf->display(ProtoGeom3::VERTEX_BUFFER_OBJECT, ProtoGeom3::WIREFRAME, .01);
        glPopMatrix();
    }
    
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
void App01::mouseMoved(){
    
}
void App01::mouseDragged(){
    
}

void App01::onResized(){
    
}
void App01::onClosed(){
    // std::cout << "in Closed" << std::endl;
}



