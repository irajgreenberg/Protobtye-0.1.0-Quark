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
    for(int i=0; i<6; ++i) {
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(pos, rot, size, col4, textureImageURL, subdivision.elem0, subdivision.elem1, springTension, anchorMode));
    }
}

// 6 subdivisions, 1 texture, 1 tension
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivisions[6], float springTension, const std::string& textureImageURL, ProtoVerletSurface::AnchorModeEnum anchorMode)
{
    for(int i=0; i<6; ++i) {
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(pos, rot, size, col4, textureImageURL, subdivisions[i].elem0, subdivisions[i].elem1, springTension, anchorMode));
    }
}

// 1 subdivisions, 6 textures, 1 tension
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivision, float springTension, const std::string textureImageURLs[6], ProtoVerletSurface::AnchorModeEnum anchorMode)
{
    for(int i=0; i<6; ++i) {
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(pos, rot, size, col4, textureImageURLs[i], subdivision.elem0, subdivision.elem1, springTension, anchorMode));
    }
}

// 6 subdivisions, 6 textures, 1 tension
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivisions[6], float springTension, const std::string textureImageURLs[6], ProtoVerletSurface::AnchorModeEnum anchorMode)
{
    for(int i=0; i<6; ++i) {
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(pos, rot, size, col4, textureImageURLs[i], subdivisions[i].elem0, subdivisions[i].elem1, springTension, anchorMode));
    }
}

// 1 subdivision, 1 texture, 6 tensions
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivision, float springTensions[6], const std::string& textureImageURL, ProtoVerletSurface::AnchorModeEnum anchorMode)
{
    for(int i=0; i<6; ++i) {
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(pos, rot, size, col4, textureImageURL, subdivision.elem0, subdivision.elem1, springTensions[i], anchorMode));
    }
}

// 6 subdivisions, 1 texture, 6 tensions
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivisions[6], float springTensions[6], const std::string& textureImageURL, ProtoVerletSurface::AnchorModeEnum anchorMode)
{
    for(int i=0; i<6; ++i) {
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(pos, rot, size, col4, textureImageURL, subdivisions[i].elem0, subdivisions[i].elem1, springTensions[i], anchorMode));
    }
}

// 1 subdivisions, 6 textures, 6 tensions
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivision, float springTensions[6], const std::string textureImageURLs[6], ProtoVerletSurface::AnchorModeEnum anchorMode)
{
    for(int i=0; i<6; ++i) {
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(pos, rot, size, col4, textureImageURLs[i], subdivision.elem0, subdivision.elem1, springTensions[i], anchorMode));
    }
}

// 6 subdivisions, 6 textures, 6 tensions
ProtoVerletCube::ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivisions[6], float springTensions[6], const std::string textureImageURLs[6], ProtoVerletSurface::AnchorModeEnum anchorMode)
{
    for(int i=0; i<6; ++i) {
        verletSurfs[i] = std::unique_ptr<ProtoVerletSurface> (new ProtoVerletSurface(pos, rot, size, col4, textureImageURLs[i], subdivisions[i].elem0, subdivisions[i].elem1, springTensions[i], anchorMode));
    }
}

void ProtoVerletCube::display(){

}
