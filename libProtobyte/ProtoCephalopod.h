/*!  \brief  ProtoCephalopod.h: (add brief description)
 ProtoCephalopod.h
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

#ifndef Protobyte_dev_ProtoCephalopod_cpp
#define Protobyte_dev_ProtoCephalopod_cpp

#include <iostream>
#include "ProtoShape3.h"
#include "ProtoGeom3.h"
#include "ProtoGeoSphere.h"

#include "ProtoTube.h"

namespace ijg {
    
    class ProtoCephalopod;
    typedef ProtoCephalopod Cephalopod;
    
    class ProtoCephalopod: public ProtoShape3{
        
    public:
        ProtoCephalopod();
        ProtoCephalopod(const Vec3f& pos, const Vec3f& rot, const Dim3f& size,
                        const ProtoColor4f& col4, int tentacleCount=8);
        ~ProtoCephalopod();
        
        const std::vector<ProtoTube>& getTentacles() const;
        void display();
        
        
        const GeoSphere& getBody() const;
        
    private:
        int tentacleCount;
        std::unique_ptr<GeoSphere> body;
        std::vector<ProtoTube> tentacles;
        std::vector<Vec3> offsets; // testing only
        void init();
        
    };
    
    inline const std::vector<ProtoTube>& ProtoCephalopod::getTentacles() const
    {
        return tentacles;
    }
    
    inline const ProtoGeoSphere& ProtoCephalopod::getBody() const{
        return *body;
    }
}

#endif // Protobyte_dev_ProtoCephalopod_cpp
