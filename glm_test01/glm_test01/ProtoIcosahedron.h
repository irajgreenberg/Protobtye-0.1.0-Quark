//
//  ProtoIcosahedron.h
//  glm_test01
//
//  Created by iragreenberg on 12/10/13.
//  Copyright (c) 2013 Ira Greenberg. All rights reserved.
//

#ifndef __glm_test01__ProtoIcosahedron__
#define __glm_test01__ProtoIcosahedron__

#include <iostream>

namespace ijg{
    
    class ProtoIcosahedron{
        
    public:
        ProtoIcosahedron();
        
        ProtoIcosahedron(const ofVec3f& pos, const ofVec3f&  rot, const ofVec3f&  dim, const ofColor& fillCol, const ofColor& strokeCol, std::string name);
        
        void display();
        void displayNorms(float len = 3);
        
    private:
        // use of mesh class for simplicity (for now)
        ofMesh mesh;
        
        std::string name;
        void init();
        
    };
    
#endif /* defined(___DSHAPE__ProtoIcosahedron__) */

    
}

#endif /* defined(__glm_test01__ProtoIcosahedron__) */
