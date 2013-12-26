//
//  Cephalopod01.cpp
//  Protobyte_dev_v02
//
//  Created by iragreenberg on 9/27/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//

#include "Cephalopod01.h"

using namespace ijg;

namespace {
    float rotX = 0.0;
    float rotY = 0.0;
    float rotZ = 0.0;
}



void Cephalopod01::init(){
    setBackground(0);
    isClicked = false;
    
    // light0
    light0->setDiffuse(Col4f(1, 1, 1, 1.0));
    light0->setAmbient(Col4f(.1, .1, .1, 1.0));
    light0->setSpecular(Col4f(1, .6, .6, 1.0));
    light0->on();
    
    cephalopod = new Cephalopod(Vec3f(0,0,0), Vec3f(0,0,0), Dim3f(60, 60, 60),ProtoColor4f(.9, .4, .7, 1), 12);
    
    float vals3[] = {0, .1, .2, .3, .4, .5, .6, .7, .8};
    ProtoMatrix3<float> mat01(vals3);
//    std::cout << "mat01.getRow(0) = " << mat01.getColumn(0) << std::endl;
//    std::cout << "mat01.getRow(1) = " << mat01.getRow(1) << std::endl;
//    std::cout << "mat01.getRow(2) = " << mat01.getRow(2) << std::endl;
//    std::cout << "mat01 = \n" << mat01 << std::endl;
    
    
    float vals4[] = {0.0, 2.1, 2.2, 0.3, 0.4, 3.5, 0.6, 0.7, 0.8 , 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5};
    ProtoMatrix4<float> mat02(vals4);
//    std::cout << "mat02.getRow(0) = " << mat02.getRow(0) << std::endl;
//    std::cout << "mat02.getRow(1) = " << mat02.getRow(1) << std::endl;
//    std::cout << "mat02.getRow(2) = " << mat02.getRow(2) << std::endl;
//    std::cout << "mat02.getRow(3) = " << mat02.getRow(3) << std::endl;
//    std::cout << "mat02 = \n" << mat02 << std::endl;
//    
//    std::cout << "mat02.getColumn(0) = " << mat02.getColumn(0) << std::endl;
//    std::cout << "mat02.getColumn(1) = " << mat02.getColumn(1) << std::endl;
//    std::cout << "mat02.getColumn(2) = " << mat02.getColumn(2) << std::endl;
//    std::cout << "mat02.getColumn(3) = " << mat02.getColumn(3) << std::endl;
//    
//    std::cout << "mat02.determinent = " << mat02.determinent() << std::endl;
    
    mat01.identity();
//    std::cout << "mat01 = \n" << mat01 << std::endl;
    //trace("ira = \n" , mat01);
    
    //const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4,
    //int ringCount, int ringDetail, float ringRadius, float ringThickness
    ProtoToroid t(Vec3f(), Vec3f(), Dim3f(20,20,20), Col4f(1, 1, 1, 1), 12, 12, 15, 35);
    
    geoSphere = cephalopod->getBody();
    
    //cylinder = new ProtoCylinder(Vec3f(), Vec3f(), Dim3f(30, 8, 8), Col4f(.6, .5, .7, 1), 12, ProtoCylinder::LEFT);
    
    
    std::vector<ProtoFace3> faces = geoSphere.getFaces();
    for(size_t i=0; i<faces.size(); ++i){
        ProtoMatrix4f mat4(faces.at(i).getTNBFrame(), Vec4(faces.at(i).getCentroid(), 1));
        //mat4.transpose();
        //trace("mat4:\n", mat4);
        ProtoCylinder c = ProtoCylinder(Vec3f(), Vec3f(), Dim3f(.75, 24, .75), Col4f(.6, .5, .7, 1), 12, ProtoCylinder::LEFT);
        c.transform(mat4);
        cylinders.push_back(c);
        
        if(i==0){
            centroid = faces.at(i).getCentroid();
            frame = faces.at(i).getTNBFrame();
        }
    }



}


void Cephalopod01::run(){
    pushMatrix();
    translate(0, 0, -65);
    rotate(rotX+=.5, 1, .75, .3);
    
    cephalopod->display();
//    std::vector<ProtoFace3> faces = geoSphere.getFaces();
//    geoSphere.display(WIREFRAME);
//
//     for(size_t i=0; i<faces.size(); ++i){
//         cylinders.at(i).display();
//     }
    
   
//
//    for(int i=0; i<faces.size(); ++i){
//        Vec3 n = faces.at(i).getNorm();
//        Vec3 c = faces.at(i).getCentroid();
//        glBegin(GL_LINES);
//        glVertex3f(c.x, c.y, c.z);
//        glVertex3f(c.x+n.x*14, c.y+n.y*14, c.z+n.z*14);
//        glEnd();
//    }

    
    // draw one TNB Frame
//    glBegin(GL_LINES);
//    glVertex3f(centroid.x, centroid.y, centroid.z);
//    glVertex3f(centroid.x+frame.getRow(0).x*20, centroid.y+frame.getRow(0).y*20, centroid.z+frame.getRow(0).z*20);
//    glEnd();
//
//    
//    glBegin(GL_LINES);
//    glVertex3f(centroid.x, centroid.y, centroid.z);
//    glVertex3f(centroid.x+frame.getRow(1).x*20, centroid.y+frame.getRow(1).y*20, centroid.z+frame.getRow(1).z*20);
//    glEnd();
//
//    
//    glBegin(GL_LINES);
//    glVertex3f(centroid.x, centroid.y, centroid.z);
//    glVertex3f(centroid.x+frame.getRow(2).x*20, centroid.y+frame.getRow(2).y*20, centroid.z+frame.getRow(2).z*20);
//    glEnd();
    
    popMatrix();

}

void Cephalopod01::keyPressed(){
    
}


void Cephalopod01::mousePressed(){
    std::cout << "in MousePressed" << std::endl;
    isClicked = true;
    
}
void Cephalopod01::mouseRightPressed(){
    
    
}
void Cephalopod01::mouseReleased(){
    
}
void Cephalopod01::mouseRightReleased(){
    
}
void Cephalopod01::mouseMoved(int mx, int my){
    //light1->setPosition(Vec3f(0, 0, mx));
    
}
void Cephalopod01::mouseDragged(){
    
}

void Cephalopod01::onResized(){
    
}
void Cephalopod01::onClosed(){
    // std::cout << "in Closed" << std::endl;
}



