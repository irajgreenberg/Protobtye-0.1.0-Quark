//
//  ProtoVerletCube.cpp
//  Protobyte_dev
//
//  Created by Ira on 11/11/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//

#include "ProtoVerletCube.h"

using namespace ijg;

// deafult
ProtoVerletCube::ProtoVerletCube(){}

// 1 subdivision, 1 texture, 1 tension
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivision, float springTension, const std::string& textureImageURL, ProtoVerletSurface::AnchorModeEnum anchorMode):
ProtoShape3(pos, rot, size, col4), subdivision(subdivision), springTension(springTension), textureImageURL(textureImageURL), anchorMode(anchorMode)
{
    Vec3f facePos, faceRot;
    for(int i=0; i<6; ++i) {
        switch(i){
          case 0: // FRONT
                facePos = Vec3f(0, 0, size.d/2);
                faceRot = Vec3f(0, 0, 0);
                break;
            case 1: // LEFT
                facePos = Vec3f(-size.w/2, 0, 0);
                faceRot = Vec3f(0, Math::HALF_PI, 0);
                break;
            case 2: // BACK
                facePos = Vec3f(0, 0, -size.d/2);
                faceRot = Vec3f(0, Math::PI, 0);
                break;
            case 3: // RIGHT
                facePos = Vec3f(size.w/2, 0, 0);
                faceRot = Vec3f(0, -Math::HALF_PI, 0);
                break;
            case 4: // TOP
                facePos = Vec3f(0, size.h/2, 0);
                faceRot = Vec3f(-Math::HALF_PI, 0, 0);
                break;
            case 5: // BOTTOM
                facePos = Vec3f(0, -size.h/2, 0);
                faceRot = Vec3f(Math::HALF_PI, 0, 0);
                break;
            }
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(facePos, faceRot, size, col4, textureImageURL, subdivision.elem0, subdivision.elem1, springTension, anchorMode));
    }
   // init();
}

// 6 subdivisions, 1 texture, 1 tension
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivisions[6], float springTension, const std::string& textureImageURL, ProtoVerletSurface::AnchorModeEnum anchorMode)
{
    for(int i=0; i<6; ++i) {
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(pos, rot, size, col4, textureImageURL, subdivisions[i].elem0, subdivisions[i].elem1, springTension, anchorMode));
    }
    init();
}

// 1 subdivisions, 6 textures, 1 tension
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivision, float springTension, const std::string textureImageURLs[6], ProtoVerletSurface::AnchorModeEnum anchorMode)
{
    for(int i=0; i<6; ++i) {
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(pos, rot, size, col4, textureImageURLs[i], subdivision.elem0, subdivision.elem1, springTension, anchorMode));
    }
    init();
}

// 6 subdivisions, 6 textures, 1 tension
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivisions[6], float springTension, const std::string textureImageURLs[6], ProtoVerletSurface::AnchorModeEnum anchorMode)
{
    for(int i=0; i<6; ++i) {
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(pos, rot, size, col4, textureImageURLs[i], subdivisions[i].elem0, subdivisions[i].elem1, springTension, anchorMode));
    }
    init();
}

// 1 subdivision, 1 texture, 6 tensions
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivision, float springTensions[6], const std::string& textureImageURL, ProtoVerletSurface::AnchorModeEnum anchorMode)
{
    for(int i=0; i<6; ++i) {
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(pos, rot, size, col4, textureImageURL, subdivision.elem0, subdivision.elem1, springTensions[i], anchorMode));
    }
    init();
}

// 6 subdivisions, 1 texture, 6 tensions
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivisions[6], float springTensions[6], const std::string& textureImageURL, ProtoVerletSurface::AnchorModeEnum anchorMode)
{
    for(int i=0; i<6; ++i) {
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(pos, rot, size, col4, textureImageURL, subdivisions[i].elem0, subdivisions[i].elem1, springTensions[i], anchorMode));
    }
    init();
}

// 1 subdivisions, 6 textures, 6 tensions
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivision, float springTensions[6], const std::string textureImageURLs[6], ProtoVerletSurface::AnchorModeEnum anchorMode)
{
    for(int i=0; i<6; ++i) {
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(pos, rot, size, col4, textureImageURLs[i], subdivision.elem0, subdivision.elem1, springTensions[i], anchorMode));
    }
    init();
    
}

// 6 subdivisions, 6 textures, 6 tensions
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivisions[6], float springTensions[6], const std::string textureImageURLs[6], ProtoVerletSurface::AnchorModeEnum anchorMode)
{
    for(int i=0; i<6; ++i) {
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(pos, rot, size, col4, textureImageURLs[i], subdivisions[i].elem0, subdivisions[i].elem1, springTensions[i], anchorMode));
    }
    init();
}

void ProtoVerletCube::init(){
}

void ProtoVerletCube::flow(){
    for(int i=0; i<6; ++i) {
        verletSurfs[i]->flow();
    }
    
}

void ProtoVerletCube::display(){
    for(int i=0; i<6; ++i) {
        verletSurfs[i]->display(ProtoGeom3::POINT_CLOUD);
    }
    
}
