//
//  ProtoIcosahedron.cpp
//  3DSHAPE
//
//  Created by Aurora Havens on 11/20/13.
//
//http://www.openframeworks.cc/documentation/gl/ofVbo.html
//

#include "ProtoIcosahedron.h"
using namespace ijg;


ProtoIcosahedron::ProtoIcosahedron(){}

ProtoIcosahedron::ProtoIcosahedron(const ofVec3f& pos, const ofVec3f&  rot, const ofVec3f&  dim,
                               const ofColor& fillCol, const ofColor& strokeCol,
                               std::string name):
BaseShape(pos, rot, dim, fillCol, strokeCol), name(name)
{
    init();
}

void ProtoIcosahedron::init(){
    vecs.push_back(ofVec3f(0.000*dim.x, 0.000*dim.y, 1.000*dim.z));
    vecs.push_back(ofVec3f(.894*dim.x, 0.000*dim.y, 0.447*dim.z));
    vecs.push_back(ofVec3f(0.276*dim.x, 0.851*dim.y, 0.447*dim.z));
    vecs.push_back(ofVec3f(-0.724*dim.x, 0.526*dim.y, 0.447*dim.z));
    vecs.push_back(ofVec3f(-0.724*dim.x, -0.526*dim.y, 0.447*dim.z));
    vecs.push_back(ofVec3f(0.276*dim.x, -0.851*dim.y, 0.447*dim.z));
    vecs.push_back(ofVec3f(0.724*dim.x, 0.526*dim.y, -0.447*dim.z));
    vecs.push_back(ofVec3f(-0.276*dim.x, 0.851*dim.y, -0.447*dim.z));
    vecs.push_back(ofVec3f(-0.894*dim.x, 0.000*dim.y, -0.447*dim.z));
    vecs.push_back(ofVec3f(-0.276*dim.x, -0.851*dim.y, -0.447*dim.z));
    vecs.push_back(ofVec3f(0.724*dim.x, -0.526*dim.y, -0.447*dim.z));
    vecs.push_back(ofVec3f(0.000*dim.x, 0.000*dim.y, -1.000*dim.z));
    
    mesh.addVertices(vecs);
    
    inds.push_back(ofTup3i(2,1,0));
    inds.push_back(ofTup3i(3,2,0));
    inds.push_back(ofTup3i(4,3,0));
    inds.push_back(ofTup3i(5,4,0));
    inds.push_back(ofTup3i(1,5,0));
    inds.push_back(ofTup3i(11,6,7));
    inds.push_back(ofTup3i(11,7,8));
    inds.push_back(ofTup3i(11,8,9));
    inds.push_back(ofTup3i(11,9,10));
    inds.push_back(ofTup3i(11,10,6));
    inds.push_back(ofTup3i(1,2,6));
    inds.push_back(ofTup3i(2,3,7));
    inds.push_back(ofTup3i(3,4,8));
    inds.push_back(ofTup3i(4,5,9));
    inds.push_back(ofTup3i(5,1,10));
    inds.push_back(ofTup3i(2,7,6));
    inds.push_back(ofTup3i(3,8,7));
    inds.push_back(ofTup3i(4,9,8));
    inds.push_back(ofTup3i(5,10,9));
    inds.push_back(ofTup3i(1,6,10));
    
    
    for(int i=0; i<inds.size(); ++i){
        mesh.addIndex(inds.at(i).elem0);
        mesh.addIndex(inds.at(i).elem1);
        mesh.addIndex(inds.at(i).elem2);
    }
    
    for(int i=0; i<inds.size(); ++i){
        faces.push_back(Face3(&vecs.at(inds.at(i).elem0), &vecs.at(inds.at(i).elem1), &vecs.at(inds.at(i).elem2)));
    }
    
    for(int i=0; i<faces.size(); ++i){
        std::cout << "normals = " << faces.at(i).getNorm() << std::endl;
        mesh.addNormal(faces.at(i).getNorm());
    }
    
}


void ProtoIcosahedron::display(){
    ofSetColor(fillCol);
    ofFill();
    //ofSetColor(strokeCol);
    //mesh.drawWireframe();
    mesh.drawFaces();
}

void ProtoIcosahedron::displayNorms(float len){
    ofSetColor(255, 127, 0, 255);
    
    for(int i=0; i<faces.size(); ++i){
        ofLine(faces.at(i).getCentroid().x, faces.at(i).getCentroid().y, faces.at(i).getCentroid().z,
               faces.at(i).getCentroid().x + faces.at(i).getNorm().x*len, faces.at(i).getCentroid().y + faces.at(i).getNorm().y*len, faces.at(i).getCentroid().z + faces.at(i).getNorm().z*len);
    }
}
