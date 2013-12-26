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
    
    body = std::unique_ptr<ProtoGeoSphere>(new ProtoGeoSphere(Vec3f(0,0,0), Vec3f(0,0,0), Dim3f(7, 7, 7), Col4f(.7, .3, .2, 1), 1, "shipPlate.jpg"));
    
    faces =  body->getFaces();
    
    
    for(size_t i=0; i<faces.size(); ++i){
        const int pathCount = 30;
        std::vector<Vec3> vecs;
        float _theta = 0.0;
        float _radius = .2;
        float h = 0;
        for(int j=0; j<pathCount; ++j){
            vecs.push_back(Vec3(sin(_theta)*_radius, h+=1.2, cos(_theta)*_radius));
            //vecs.push_back(Vec3(0, h+=1.2, 0));
            _theta += ProtoMath::PI/9;
            _radius -=.12;
        }
        //const std::vector<Vec3f>& controlPts, int interpDetail, bool isCurveClosed, float smoothness
        ProtoSpline3 path(vecs, 3, 0, .5);
        //const ProtoSpline3& path, float radius, int crossSectionDetail, bool isClosed
        
        //const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4,
        ProtoTube pt = ProtoTube(Vec3(), Vec3(), Dim3f(), Col4f(.75, .2, .2, 1.0), path, 1, 12, ProtoTransformFunction(ProtoTransformFunction::LINEAR_INVERSE), false);
//        if(i==0){
//            trace("pos = ", pt.getVertices().at(0).pos);
//        }
        ProtoMatrix4f mat4(faces.at(i).getTNBFrame(), Vec4((faces.at(i).getCentroid()*.75f), 1));
        pt.transform(mat4);
        tentacles.push_back(pt);
    }
}

void ProtoCephalopod::display(){
    
    glShadeModel(GL_FLAT);
    body->display(SURFACE);
    glShadeModel(GL_SMOOTH);
    for(size_t i=0; i<faces.size(); ++i){
        tentacles.at(i).display(SURFACE);
    }
    
}
