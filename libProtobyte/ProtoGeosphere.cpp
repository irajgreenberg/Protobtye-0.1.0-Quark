/*!  \brief  ProtoGeoSphere.h: Geodesic Sphere implementation
 Subdivided Icoshahedron
 ProtoGeoSphere.h
 Protobyte Library v02
 
 Created by Ira on 7/23/13.
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

#include "ProtoGeosphere.h"
using namespace ijg;


ProtoGeoSphere::ProtoGeoSphere(){
}

ProtoGeoSphere::ProtoGeoSphere(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, int subdivisionLevel):
ProtoGeom3(pos, rot, size, col4), subdivisionLevel(subdivisionLevel)
{
    init();
}

ProtoGeoSphere::ProtoGeoSphere(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, int subdivisionLevel, const std::string& textureImageURL):
ProtoGeom3(pos, rot, size, col4, textureImageURL), subdivisionLevel(subdivisionLevel)
{
    init();
}



void ProtoGeoSphere::calcVerts() {
    // coords and indices form: http://www.csee.umbc.edu/~squire/reference/polyhedra.shtml

    /*
     0,  x= 0.000, y= 0.000, z= 1.000
     1,  x= 0.894, y= 0.000, z= 0.447
     2,  x= 0.276, y= 0.851, z= 0.447
     3,  x=-0.724, y= 0.526, z= 0.447
     4,  x=-0.724, y=-0.526, z= 0.447
     5,  x= 0.276, y=-0.851, z= 0.447
     6,  x= 0.724, y= 0.526, z=-0.447
     7,  x=-0.276, y= 0.851, z=-0.447
     8,  x=-0.894, y= 0.000, z=-0.447
     9,  x=-0.276, y=-0.851, z=-0.447
     10,  x= 0.724, y=-0.526, z=-0.447
     11,  x= 0.000, y= 0.000, z=-1.000
     */
    
    verts.push_back(ProtoVertex3(Vec3f(0.000*size.w, 0.000*size.h, 1.000*size.d), ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0.000, 0.000)));
    verts.push_back(ProtoVertex3(Vec3f(0.894*size.w, 0.000*size.h, 0.447*size.d), ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0.894, 0.000)));
    verts.push_back(ProtoVertex3(Vec3f(0.276*size.w, 0.851*size.h, 0.447*size.d), ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0.276, 0.851)));
    verts.push_back(ProtoVertex3(Vec3f(-0.724*size.w, 0.526*size.h, 0.447*size.d), ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(-0.724, 0.526)));
    verts.push_back(ProtoVertex3(Vec3f(-0.724*size.w, -0.526*size.h, 0.447*size.d), ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(-0.724, -0.526)));
    verts.push_back(ProtoVertex3(Vec3f(0.276*size.w, -0.851*size.h, 0.447*size.d), ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0.276, -0.851)));
    verts.push_back(ProtoVertex3(Vec3f(0.724*size.w, 0.526*size.h, -0.447*size.d), ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0.724, 0.526)));
    verts.push_back(ProtoVertex3(Vec3f(-0.276*size.w, 0.851*size.h, -0.447*size.d), ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(-0.276, 0.851)));
    verts.push_back(ProtoVertex3(Vec3f(-0.894*size.w, 0.000*size.h, -0.447*size.d), ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(-0.894, 0.000)));
    verts.push_back(ProtoVertex3(Vec3f(-0.276*size.w, -0.851*size.h, -0.447*size.d), ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(-0.276, -0.851)));
    verts.push_back(ProtoVertex3(Vec3f(0.724*size.w, -0.526*size.h, -0.447*size.d), ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0.724, -0.526)));
    verts.push_back(ProtoVertex3(Vec3f(0.000*size.w, 0.000*size.h, -1.000*size.d), ProtoColor4f(col4.getR(), col4.getG(), col4.getB(), col4.getA()), ProtoTuple2f(0.000, 0.000)));
    
}
void ProtoGeoSphere::calcInds() {
     inds.push_back(ProtoTuple3i(0,1,2));
     inds.push_back(ProtoTuple3i(0,2,3));
     inds.push_back(ProtoTuple3i(0,3,4));
     inds.push_back(ProtoTuple3i(0,4,5));
     inds.push_back(ProtoTuple3i(0,5,1));
     inds.push_back(ProtoTuple3i(11,6,7));
     inds.push_back(ProtoTuple3i(11,7,8));
     inds.push_back(ProtoTuple3i(11,8,9));
     inds.push_back(ProtoTuple3i(11,9,10));
     inds.push_back(ProtoTuple3i(11,10,6));
     inds.push_back(ProtoTuple3i(1,2,6));
     inds.push_back(ProtoTuple3i(2,3,7));
     inds.push_back(ProtoTuple3i(3,4,8));
     inds.push_back(ProtoTuple3i(4,5,9));
     inds.push_back(ProtoTuple3i(5,1,10));
     inds.push_back(ProtoTuple3i(6,7,2));
     inds.push_back(ProtoTuple3i(7,8,3));
     inds.push_back(ProtoTuple3i(8,9,4));
     inds.push_back(ProtoTuple3i(9,10,5));
     inds.push_back(ProtoTuple3i(10,6,1));
    
}