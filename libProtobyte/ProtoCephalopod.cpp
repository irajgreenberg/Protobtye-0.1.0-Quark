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
    body = ProtoGeoSphere(Vec3f(0,0,0), Vec3f(0,0,0), Dim3f(60, 60, 60), ProtoColor4f(ProtoMath::random(.7, 1.0), ProtoMath::random(.7, 1.0), ProtoMath::random(.7, 1.0), 1), 1, "shipPlate.jpg");
    
    for(size_t i=0; i<tentacleCount; ++i){
        const int pathCount = 30;
        std::vector<Vec3> vecs;
        float _theta = 0.0;
        float _radius = 5;
        float h = 0;
        for(int j=0; j<pathCount; ++j){
            vecs.push_back(Vec3(cos(_theta)*_radius, sin(_theta)*_radius, h+=1.2));
            _theta += ProtoMath::PI/9;
            _radius -=.12;
        }
        //const std::vector<Vec3f>& controlPts, int interpDetail, bool isCurveClosed, float smoothness
        ProtoSpline3 path(vecs, 3, 0, .5);
        //const ProtoSpline3& path, float radius, int crossSectionDetail, bool isClosed
        tentacles.push_back(ProtoTube(path, 2, 12, ProtoTransformFunction(ProtoTransformFunction::LINEAR_INVERSE), false));
        offsets.push_back(Vec3(ProtoMath::random(-30, 30), ProtoMath::random(-30, 30), 0));
    }
}

void ProtoCephalopod::display(){
    //body.display();
    for(size_t i=0; i<tentacleCount; ++i){
        glPushMatrix();
        glTranslatef(offsets.at(i).x, offsets.at(i).y, offsets.at(i).z);
        tentacles.at(i).display();
        glPopMatrix();
    }
    
}
