//
//  ProtoVerletCube.h
//  Protobyte_dev
//
//  Created by Ira on 11/11/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//

#ifndef PROTO_VERLETCUBE_H
#define PROTO_VERLETCUBE_H

#include <iostream>
#include "ProtoVerletSurface.h"
#include "ProtoTuple2.h"
#include "ProtoShape3.h"

namespace ijg {
    
    class ProtoVerletCube: public ProtoShape3 {
        
    public:
        // deafult
        ProtoVerletCube();
        
        // 1 subdivision, 1 texture, 1 tension
        ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivision, float springTension, const std::string& textureImageURL, ProtoVerletSurface::AnchorModeEnum anchorMode=ProtoVerletSurface::ALL_EDGES);
        
        // 6 subdivisions, 1 texture, 1 tension
        ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivisions[6], float springTension, const std::string& textureImageURL, ProtoVerletSurface::AnchorModeEnum anchorMode=ProtoVerletSurface::ALL_EDGES);
        
         // 1 subdivisions, 6 textures, 1 tension
        ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivision, float springTension, const std::string textureImageURLs[6], ProtoVerletSurface::AnchorModeEnum anchorMode=ProtoVerletSurface::ALL_EDGES);
        
        // 6 subdivisions, 6 textures, 1 tension
        ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivisions[6], float springTension, const std::string textureImageURLs[6], ProtoVerletSurface::AnchorModeEnum anchorMode=ProtoVerletSurface::ALL_EDGES);
        
        // 1 subdivision, 1 texture, 6 tensions
        ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivision, float springTensions[6], const std::string& textureImageURL, ProtoVerletSurface::AnchorModeEnum anchorMode=ProtoVerletSurface::ALL_EDGES);
        
        // 6 subdivisions, 1 texture, 6 tensions
        ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivisions[6], float springTensions[6], const std::string& textureImageURL, ProtoVerletSurface::AnchorModeEnum anchorMode=ProtoVerletSurface::ALL_EDGES);
        
        // 1 subdivisions, 6 textures, 6 tensions
        ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivision, float springTensions[6], const std::string textureImageURLs[6], ProtoVerletSurface::AnchorModeEnum anchorMode=ProtoVerletSurface::ALL_EDGES);
        
        // 6 subdivisions, 6 textures, 6 tensions
        ProtoVerletCube(const Vec3f& pos, const Vec3f& rot, const ProtoDimension3<float>& size, const ProtoColor4<float>& col4, Tup2i subdivisions[6], float springTensions[6], const std::string textureImageURLs[6], ProtoVerletSurface::AnchorModeEnum anchorMode=ProtoVerletSurface::ALL_EDGES);
        
        void pulse(float amp = 1, float freq = Math::PI/180.0);
        void pulse(float amps[6], float freq[6]);
        
        void display(ProtoGeom3::renderMode mode=ProtoVerletSurface::SURFACE, float pointSize = .5);
        void display(ProtoGeom3::renderMode mode0, ProtoGeom3::renderMode mode1, ProtoGeom3::renderMode mode2, ProtoGeom3::renderMode mode3, ProtoGeom3::renderMode mode4, ProtoGeom3::renderMode mode5, float pointSize = .5);
        void display(ProtoGeom3::renderMode modes[6], float pointSize = .5);
        void display(ProtoGeom3::renderMode modes[6], float pointSizes[6]);

        
        void textureOn();
        void textureOff();

    
    private:
        
        void init();
        std::unique_ptr<ProtoVerletSurface> verletSurfs[6];
        
        
        Tup2i subdivision;
        Tup2i subdivisions[6];
        float springTension;
        float springTensions[6];
        const std::string textureImageURL;
        const std::string textureImageURLs[6];
        ProtoVerletSurface::AnchorModeEnum anchorMode;
        

        
        
    };
}

#endif /* defined(PROTO_VERLETCUBE_H) */
