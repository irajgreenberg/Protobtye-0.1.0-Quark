//
//  App01.cpp
//  Protobyte_dev_v02
//
//  Created by iragreenberg on 9/27/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//

#include "App01.h"
#include <GLUT/glut.h>


using namespace ijg;

float x = 0;
float tx = 0;

void App01::init(){
    
    // set world state
    // set window background color
    setBackground(.8, .4, 0);
    /* api ideas
     setGravity(-1 - 1);
     setWind(ProtoVector3);
     setChaos(0-1);
     setAntiAliasing(0-1);
     setShading(SMOOTH or FACETED);
     setLighting();
     */
    
    isClicked = false;
    
    // light0
    light0->setDiffuse(Col4f(1, 1, 1, 1.0));
    light0->setAmbient(Col4f(.1, .1, .1, 1.0));
    light0->setSpecular(Col4f(1, .6, .6, 1.0));
    light0->on();
    
    // light1
    light1->setSpecular(Col4f(.6, .6, 0, 1.0));
    light1->setAmbient(Col4f(.1, .1, .1, 0));
    light1->setDiffuse(Col4f(1, 1, 1, 1.0));
    light1->on();
    
    // light2
    light2->setAmbient(Col4f(0, 0, 0, 1.0));
    light2->setSpecular(Col4f(1, .5, .4, 1.0));
    light2->setDiffuse(Col4f(.2, .2, .2, 1.0));
    //light2->on();
    
    // light3
    light3->setAmbient(Col4f(.1, .1, .1, 1.0));
    light3->setSpecular(Col4f(0, .3, .7, 1.0));
    light3->setDiffuse(Col4f(1, 1, 1, 1.0));
    //light3->on();
    
    light0->setPosition(Vec3f(.2, 0, 1));
    light1->setPosition(Vec3f(-1, 0, 0));
    light2->setPosition(Vec3f(0, 0, 1));
    light3->setPosition(Vec3f(0, 1, .3));
    
    // not working
    shader = ProtoShader("toon1.vert", "toon1.frag");
    //shader.bind();
    
    toroid2 = std::unique_ptr<ProtoToroid> (new ProtoToroid(Vec3f(0, 0, 0), Vec3f(0, ProtoMath::PI/3.0,0), Dim3f(30, 30, 30),ProtoColor4f(.8, .7, .9, 1.0), 25, 25, .9, .12, "water.jpg"));
    toroid2->setShininess(90);
    
    
    std::string imgs[6] = {"fabric.jpg", "corroded_metal.jpg", "leather2.jpg", "corroded_shipPlate.jpg", "water.jpg" , "pebbles.jpg" };
    verletCube = std::unique_ptr<ProtoVerletCube> (new ProtoVerletCube(Vec3f(0,0,0), Vec3f(0,0,0), Dim3f(40, 40, 40), ProtoColor4f(ProtoMath::random(.7, 1.0), ProtoMath::random(.7, 1.0), ProtoMath::random(.7, 1.0), .65), Tup2i(27, 27), ProtoMath::random(.02, .2), imgs, ALL_CORNERS));
    
    int shinys[6] = {20, 8, 90, 45, 39, 110};
    verletCube->setShininess(shinys);
    
    verletCube2 = std::unique_ptr<ProtoVerletCube> (new ProtoVerletCube(Vec3f(0,0,0), Vec3f(0,0,0), Dim3f(10, 10, 10), ProtoColor4f(ProtoMath::random(.7, 1.0), ProtoMath::random(.7, 1.0), ProtoMath::random(.7, 1.0), .65), Tup2i(23, 23), ProtoMath::random(.02, .2), "metal_grate.jpg", ALL_EDGES));
    
    verletCube2->setShininess(12);
    
    verletCube3 = std::unique_ptr<ProtoVerletCube> (new ProtoVerletCube(Vec3f(0,0,0), Vec3f(0,0,0), Dim3f(70, 70, 70), ProtoColor4f(ProtoMath::random(.7, 1.0), ProtoMath::random(.7, 1.0), ProtoMath::random(.7, 1.0), .35), Tup2i(27, 27), ProtoMath::random(.02, .2), "shipPlate.jpg", ALL_CORNERS));
    
    //ProtoSphere::ProtoSphere(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f size,
    //const ProtoColor4f col4, const std::string& textureImageURL, float textureScale, int spines, int spineNodes) :
    //glEnable(GL_F)
    sphere = std::unique_ptr<ProtoSphere> (new ProtoSphere(Vec3f(0, 0, 0), Vec3f(0, ProtoMath::PI/3.0,0), Dim3f(20, 20, 20),ProtoColor4f(.9, .4, .7, 1), "rockWall.jpg", 1, 4, 4));
    sphere->setShininess(68);
    std::cout << "sphere->getFaces().size() = " << sphere->getFaces().size() << std::endl;
    
    
    
   //const ProtoSpline3& path, float radius, int crossSectionDetail, bool isClosed
    const int pathCount = 30;
    std::vector<Vec3> vecs;
    float _theta = 0.0;
    float _radius = 5;
    float h = 0;
    for(int i=0; i<pathCount; ++i){
        vecs.push_back(Vec3(cos(_theta)*_radius, sin(_theta)*_radius, h+=1.2));
        _theta += ProtoMath::PI/9;
        _radius -=.12;
    }
        //const std::vector<Vec3f>& controlPts, int interpDetail, bool isCurveClosed, float smoothness
    ProtoSpline3 path(vecs, 3, 0, .5);
   //const ProtoSpline3& path, float radius, int crossSectionDetail, bool isClosed
    tube = std::unique_ptr<ProtoTube>(new ProtoTube(path, 2, 12, ProtoTransformFunction(ProtoTransformFunction::LINEAR_INVERSE), false));
    
    tube2 = ProtoTube(path, 2, 12, ProtoTransformFunction(ProtoTransformFunction::LINEAR_INVERSE), false);
    
    icos = std::unique_ptr<ProtoGeoSphere>(new ProtoGeoSphere(Vec3f(0,0,0), Vec3f(0,0,0), Dim3f(60, 60, 60), ProtoColor4f(ProtoMath::random(.7, 1.0), ProtoMath::random(.7, 1.0), ProtoMath::random(.7, 1.0), 1), 1, "shipPlate.jpg"));
   
    icos->setShininess(98);
    
    std::vector<ProtoFace3> icosFaces = icos->getFaces();
    //frames.clear();
    for(size_t i=0; i<icosFaces.size(); ++i){
        // calulate local frenet frame using face normal
        Vec3 N = icosFaces.at(i).getNorm();
        Vec3 v0 = *(icosFaces.at(i).getVert0_ptr()->getPos_ptr());
        Vec3 v1 = *(icosFaces.at(i).getVert1_ptr()->getPos_ptr());
        v1 -= v0;
        Vec3 T = v1;
        Vec3 B = cross(N, T);
        frames.push_back(ProtoMatrix3<float>(N, T, B));
    }
    
    
    cephalopod = ProtoCephalopod(Vec3f(0,0,0), Vec3f(0,0,0), Dim3f(60, 60, 60),ProtoColor4f(.9, .4, .7, 1), 8);
    
    
    
}

// event thread runs continuously
//ProtoWorld draw independently
void App01::run(){
   
    // if(isClicked){
    //std::cout << "frameCount = " << frameCount << std::endl;
    //std::cout << "frameRate = " << frameRate << std::endl;
    //std::cout << "ind = " << ind << std::endl;
    
    
    //shader.bind();
    //shader.unbind();
    // std::cout << "shader.getID() = " << shader.getID() << std::endl;
    //shader.bind();
    pushMatrix();
    translate(0, 0, -125);
    //glScalef(20, 20, 20);
    //rotate(x+=.5, 1, 0, 0);
    //rotate(-x, 0, 1, 0);
    //toroid2->textureOn();
    
    //toroid2->display();
    //glutSolidTorus(20, 50, 12, 12);
    
    
    
    //glutSolidIcosahedron();
    
//    for(int i=0; i<frames.size(); i++){
//            pushMatrix();
//            Vec3 temp(1, 0, 0);
//            temp = frames.at(i)*temp;
//            translate(x2, y, z);
//            //rotate(f*180/PI, 1, 0, 0);
//            //rotate(q*180/PI, 0, 0, 1);
//            tube->display();
//            popMatrix();
//            
//            f+=PI/segs;
//        }
//        q+=TWO_PI/slices;
//    }
    
    //icos->textureOn();
    //icos->display();
    
    //tube2.display();
    cephalopod.display();
    
    
    popMatrix();

    pushMatrix();
    translate(0, 0, -65);
    
    rotate(x+=.5, 1, .75, .3);
    
    
    
    
    
    
    verletCube->textureOn();
    verletCube->pulse();
    ProtoGeom3::renderMode modes[] = {SURFACE, SURFACE, WIREFRAME, SURFACE, SURFACE, POINTS};
    float pointSizes[6] = {.2, .8, 15.2, 3, 8, 2};
   //verletCube->display(modes, pointSizes);
    //verletCube->display(modes, pointSizes);
    
    
    
    verletCube2->textureOn();
    verletCube2->pulse();
    //verletCube2->display();
    
    verletCube3->textureOn();
    verletCube3->pulse();
    //verletCube3->display(POINTS, 3);
    //shader.unbind();
    
    //sphere->textureOn();
    glShadeModel(GL_FLAT);
    //sphere->display(SURFACE, .1);
    glShadeModel(GL_SMOOTH);
    //glScalef(20, 20, 20);
    
    //std::cout << "shader.getID() = " << shader.getID() << std::endl;
    //glUseProgram(shader.getID());
   // sphere->textureOn();
    //sphere->display(SURFACE, .1);
    //glutSolidTorus(12, 24, 32, 32);
    //shader.unbind();
    
    
    popMatrix();
    

    
    
    
    // not working
    
    
    
    
    
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
void App01::mouseMoved(int mx, int my){
    //light1->setPosition(Vec3f(0, 0, mx));
    
}
void App01::mouseDragged(){
    
}

void App01::onResized(){
    
}
void App01::onClosed(){
    // std::cout << "in Closed" << std::endl;
}



