/*!  \brief  ProtoCephalopod.cpp: (add brief description)
 ProtoCephalopod.cpp
 Protobyte Library v02
 
 Created by Ira on 12/12/13.
 Copyright (c) 2013 Ira Greenberg. All rights reserved.
 
 Library Usage:
 This work is licensed under the Creative Commons
 Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 To view a copy of this license, visit
 http://creativecommons.org/licenses/by-nc-sa/3.0/
 or send a letter to Creative Commons,
 444 Castro Street, Suite 900,
 Mountain View, California, 94041, USA.
 
 This notice must be retained any source distribution.
 
 \ingroup common
 This class is part of the group common (update)
 \sa NO LINK
 */

#include "ProtoCephalopod.h"

using namespace ijg;

namespace {
    std::vector<ProtoFace3> faces;
}

// default cstr
ProtoCephalopod::ProtoCephalopod() {
    
}

// dstr
ProtoCephalopod::~ProtoCephalopod() {
    
}

ProtoCephalopod::ProtoCephalopod(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
                                 const ProtoColor4f& col4, int tentacleCount):
ProtoShape3(pos, rot, size, col4), tentacleCount(tentacleCount)
{
    init();
    
}


void ProtoCephalopod::init(){
    
    body = std::unique_ptr<ProtoGeoSphere>(new ProtoGeoSphere(Vec3f(0,0,0), Vec3f(0,0,0), Dim3f(7, 7, 7), Col4f(1.0, .3, .05, 1.0), 1, "leather2.jpg"));
    faces = body->getFaces();
    
    for(size_t i=0; i<faces.size(); ++i){
        // for(size_t i=0; i<2; ++i){
        const int pathCount = 30;
        std::vector<Vec3> vecs;
        float _theta = 0.0;
        float _radius = .2;
        float h = 0;
        for(int j=0; j<pathCount; ++j){
            vecs.push_back(Vec3(sin(_theta)*_radius, h+=1.2, cos(_theta)*_radius));
            _theta += ProtoMath::PI/9;
            _radius -=.12;
        }
        ProtoSpline3 path(vecs, 3, 0, .5);
        
        std::unique_ptr<ProtoTentacle> tentacle(new ProtoTentacle(Vec3(), Vec3(), Dim3f(), Col4f(.75, .2, .2, .25), path, 1.6, 16, ProtoTransformFunction(ProtoTransformFunction::LINEAR_INVERSE), false));
        
        
        ProtoMatrix4f mat4(faces.at(i).getTNBFrame(), Vec4((faces.at(i).getCentroid()*.75f), 1));
        tentacle->transform(mat4);
        tentacles.push_back(std::move(tentacle));
    }
}

void ProtoCephalopod::display(){
    
    glShadeModel(GL_FLAT);
    //body->textureOn();
    body->display(SURFACE);
    glShadeModel(GL_SMOOTH);
    // for(size_t i=0; i<2; ++i){
    for(size_t i=0; i<faces.size(); ++i){
        tentacles.at(i)->wave();
        tentacles.at(i)->display(WIREFRAME);
    }
    
}
