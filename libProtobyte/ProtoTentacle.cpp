/*!  \brief  Tentacle.cpp:
 Derived from Tube class with Verlet waving
 
 Utilizes Tube geometry algoirthms and functions
 to change this implementation declare
 calcVerts() and calcInds();
 
 ProtoTentacle.cpp
 Protobyte Library v02
 
 Created by Ira on 12/27/13.
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

#include "ProtoTentacle.h"


namespace ijg {

    
    std::ostream& operator<<(std::ostream& out, const ProtoTentacle& tentacle) {
        out << "\n\tpos = " << tentacle.pos << "\n" << ""
        "\trot = " << tentacle.rot << "\n" <<
        "\tsize = " << tentacle.size << "\n" <<
        "\tcol4 = " << tentacle.col4 << "\n" <<
        "\tradius = " << tentacle.radius << "\n" <<
        "\tcrossSectionDetail = " << tentacle.crossSectionDetail << "\n" <<
        "\tisClosed = " << tentacle.isClosed << "\n" <<
        "\tfrenetFrameLength = " << tentacle.frenetFrameLength << "\n" <<
        "\tspd = " << tentacle.spd << "\n" <<
        "\trotSpd = " << tentacle.rotSpd << "\n" <<
        "\tisTransformFunction = " << tentacle.isTransformFunction;
        
        return out;
    }
}

using namespace ijg;

// default cstr

ProtoTentacle::ProtoTentacle() {
    std::cout << "ProtoTentacle CSTR default" << std::endl;
}

// overloaded cstr 1
ProtoTentacle::ProtoTentacle(const ProtoSpline3& path, float radius, int crossSectionDetail, bool isClosed) :
Tube(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), ProtoColor4f(.5, .5, .5, 1.0), path, radius, crossSectionDetail, isClosed) {
    init();
}

/*!
 * Constructor 02
 * with TransformFunction object*/
ProtoTentacle::ProtoTentacle(const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, bool isClosed) :
Tube(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), ProtoColor4f(.5, .5, .5, 1.0), path, radius, crossSectionDetail, transFuncObj, isClosed) {
    init();
}

// Constructor 03 (calls Tube cstr 14)
ProtoTentacle::ProtoTentacle(const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, bool isClosed) :
Tube(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), ProtoColor4f(.5, .5, .5, 1.0), path, radii, crossSectionDetail, transFuncObj, isClosed) {
    init();
}

/*!
 * Constructor 04
 * varied thickness*/
ProtoTentacle::ProtoTentacle(const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, bool isClosed) :
Tube(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), ProtoColor4f(.5, .5, .5, 1.0), path, radii, crossSectionDetail, isClosed) {
    init();
}

/*!
 * Constructor 05
 * varied color*/
ProtoTentacle::ProtoTentacle(const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, float radius, int crossSectionDetail, bool isClosed) :
Tube(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), col4s, path, radius, crossSectionDetail, isClosed) {
    init();
}

/*!
 * Constructor 06
 * varied color and TransformFunction object*/
ProtoTentacle::ProtoTentacle(const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, bool isClosed) :
Tube(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), col4s, path, radius, crossSectionDetail, transFuncObj, isClosed) {
    init();
}

/*!
 * Constructor 07
 * varied thickness and color */
ProtoTentacle::ProtoTentacle(const std::vector< ProtoColor4f >& col4s, const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, bool isClosed) :
Tube(Vec3f(0, 0, 0), Vec3f(0, 0, 0), ProtoDimension3f(1, 1, 1), col4s, path, radii, crossSectionDetail, isClosed) {
    init();
}

/*!
 * Constructor 08
 * All */
ProtoTentacle::ProtoTentacle(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, float radius, int crossSectionDetail, bool isClosed) :
Tube(pos, rot, size, col4, path, radius, crossSectionDetail, isClosed) {
    init();
}

/*!
 * Constructor 09
 * varied thickness */
ProtoTentacle::ProtoTentacle(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, std::vector<float>& radii, int crossSectionDetail, bool isClosed) : // varied thickness
Tube(pos, rot, size, col4, path, radii, crossSectionDetail, isClosed) {
    init();
}

/*!
 * Constructor 10
 * varied color */
ProtoTentacle::ProtoTentacle(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size,
                             const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, float radius, int crossSectionDetail, bool isClosed) : // varied color
Tube(pos, rot, size, col4s, path, radius, crossSectionDetail, isClosed) {
    init();
}

/*!
 * Constructor 11
 * varied thickness and color */
ProtoTentacle::ProtoTentacle(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size,
                             const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, std::vector<float>& radii,
                             int crossSectionDetail, bool isClosed) : // varied thickness & color
Tube(pos, rot, size, col4s, path, radii, crossSectionDetail, isClosed) {
    init();
}

/*!
 * Constructor 12
 * All with TransformFunction obj*/
ProtoTentacle::ProtoTentacle(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const ProtoColor4f& col4, const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, bool isClosed) : Tube(pos, rot, size, col4, path, radius, crossSectionDetail, transFuncObj, isClosed) {
    init();
}

/*!
 * Constructor 13
 * all with varied color and TransformFunction obj */
ProtoTentacle::ProtoTentacle(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3f& size, const std::vector<ProtoColor4f>& col4s, const ProtoSpline3& path, float radius, int crossSectionDetail, const ProtoTransformFunction& transFuncObj, bool isClosed) : Tube(pos, rot, size, col4s, path, radius, crossSectionDetail, transFuncObj, isClosed)     {
    init();
    
}

ProtoTentacle::~ProtoTentacle() {
    //std::cout << "in ProtoTentacle destructor" << std::endl;
}



void ProtoTentacle::init(){
    //trace("In ProtoTentacle::init()");
    // set defaults
    setWaveSpeed();
    setWaveFrequency();
    
    // calculate internal verlet spine
    // get Tube internal Spline3 path
    spine = getPath();
    //balls.clear();
    for(size_t i=0; i<spine.getVerts().size(); ++i){
        balls.push_back(std::shared_ptr<VerletBall>(new VerletBall(&spine.getVerts().at(i))));
    }
    //sticks.clear();
    for(size_t i=1; i<balls.size(); ++i){
        if(i==1){
            sticks.push_back(std::unique_ptr<VerletStick> (new VerletStick(balls.at(i-1), balls.at(i), .876, Tup2f(0, .5))));
        } else {
            sticks.push_back(std::unique_ptr<VerletStick> (new VerletStick(balls.at(i-1), balls.at(i), .876, Tup2f(.5, .5))));
        }
        waveTheta = 0;
    }


}

// transform VBO primitives using glBufferSubData
void ProtoTentacle::transform(const ProtoMatrix4f& mat4){
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    for (int i = 0; i < interleavedPrims.size(); i += 12) {// transform verts
        Vec4 v4(interleavedPrims.at(i), interleavedPrims.at(i+1), interleavedPrims.at(i+2), 1);
        Vec3 v3  = mat4*v4;
        interleavedPrims.at(i) = v3.x;
        interleavedPrims.at(i+1) = v3.y;
        interleavedPrims.at(i+2) = v3.z;
        
        // transform vnorms
        // there's a better way to transform v norms (so fix it eventually!)
        ProtoMatrix4f m = mat4;
        m.transpose();
        Vec4 v4n(interleavedPrims.at(i+3), interleavedPrims.at(i+4), interleavedPrims.at(i+5), 1);
        Vec3 v3n = m*v4n;
        interleavedPrims.at(i+3) = v3n.x;
        interleavedPrims.at(i+4) = v3n.y;
        interleavedPrims.at(i+5) = v3n.z;
        
    }
    int vertsDataSize = sizeof (float) *interleavedPrims.size();
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &interleavedPrims[0]); // upload the data
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // transform spine
    //std::vector<Vec3> tempVecs = spine.getVerts(); //local copy
    for(size_t i=0; i<balls.size(); ++i){
        Vec4 tempV(*balls.at(i)->pos_ptr, 1); //local
        *balls.at(i)->pos_ptr = mat4*tempV;
        balls.at(i)->posOld = *balls.at(i)->pos_ptr; // update
    }
    // update spine and verletPath
    //spine.setVerts(tempVecs); //update member field spine with local vecs
    //verletPath = ProtoVerletPath(spine.getVerts(), .9); // shallow copy with trasnformed spine vecs
    
    // update verletPath spine
    //verletPath.setVecs(tempVecs);
    
    //verletPath.push(Vec3(.02, .01, .01));
    
    // move end
    //*balls.at(balls.size()-1)->pos_ptr += Vec3f(4.02, 4.03, 4.04);
}


void ProtoTentacle::wave(){

    balls.at(balls.size()-1)->pos_ptr->y += cos(waveTheta)*.02;
    waveTheta += Math::PI/720;
    
    
    for(size_t i=0; i<sticks.size(); ++i){
        sticks.at(i)->constrainLen();
        sticks.at(i)->display();
    }
    
    for(size_t i=0; i<balls.size(); ++i){
        balls.at(i)->verlet2();
    }

    // ok below here - simply transforms all Tentacle vertices on GPU
    // spin test of tendrils
//    glBindBuffer(GL_ARRAY_BUFFER, vboID);
//    float t = Math::PI / 360.0;
//    for (int i = 0; i < interleavedPrims.size(); i += 12) {
//        float x = 0;
//        float y = 0;
//        float z = 0;
//        float nx = 0;
//        float ny = 0;
//        float nz = 0;
//        
//        //verts
//        z = cos(t) * interleavedPrims.at(i + 2) - sin(t) * interleavedPrims.at(i);
//        x = sin(t) * interleavedPrims.at(i + 2) + cos(t) * interleavedPrims.at(i);
//        interleavedPrims.at(i + 2) = z;
//        interleavedPrims.at(i) = x;
//        
//        //vnorms
//        nz = cos(t) * interleavedPrims.at(i + 5) - sin(t) * interleavedPrims.at(i + 3);
//        nx = sin(t) * interleavedPrims.at(i + 5) + cos(t) * interleavedPrims.at(i + 3);
//        interleavedPrims.at(i + 5) = nz;
//        interleavedPrims.at(i + 3) = nx;
//        
//    }
//    int vertsDataSize = sizeof (float) *interleavedPrims.size();
//    // upload the data
//    glBufferSubData(GL_ARRAY_BUFFER, 0, vertsDataSize, &interleavedPrims[0]);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
}
