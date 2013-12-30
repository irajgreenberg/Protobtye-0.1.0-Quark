/*!  \brief  ProtoVerletPath.h: (add brief description)
 ProtoVerletPath.h
 Protobyte Library v02
 
 Created by Ira on 12/26/13.
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

#ifndef Protobyte_dev_ProtoVerletPath_cpp
#define Protobyte_dev_ProtoVerletPath_cpp

#include <iostream>
#include "ProtoCore.h"
#include "ProtoSpline3.h"
#include "ProtoVerletStick.h"

namespace ijg {
    
    class ProtoVerletPath;
    typedef ProtoVerletPath VerletPath;
    
    class ProtoVerletPath {
    
    public:
        
        friend std::ostream& operator<<(std::ostream& out, const VerletPath& path);
        
        enum AnchorMode {
            LEFT,
            RIGHT,
            CENTER,
            ENDS,
            RANDOM,
            ALTERNATING,
            ALL,
            NONE
        };
        
        
        ProtoVerletPath();
        ProtoVerletPath(float tension, AnchorMode anchorMode); // no coords
        
        ProtoVerletPath(const Spline3& spline, float tension, AnchorMode anchorMode=LEFT); // Spline3
        
        ProtoVerletPath(const Spline3& spline, float tensionMin, float tensionMax, AnchorMode anchorMode=LEFT); // Spline3
        
        ProtoVerletPath(const Spline3& spline, const Tup2& edgeTensions, AnchorMode anchorMode=LEFT); // Spline3
        ~ProtoVerletPath();
        
        
        
        std::vector<Vec3>& getPath();
        
        float getTension(); // get single tension for entire path
        void setTension(float tension); // set single tension for entire path
        float getTension(int node); // get tension for individual node on path
        void setTension(int node, float tension); // set tension for individual node on path
        Tup2 getEdgeTensions(); // tensions at path ends
        void setEdgeTensions(const Tup2& edgeTensions); // tensions at path ends
        std::vector<float>& getTensions(); // get unique tensions along path
        void setTensions(const std::vector<float>& tensions); // set unique tensions along path
        AnchorMode getAnchorMode();
        void setAnchorMode(const AnchorMode& anchorMode);
        
        void setVecs(std::vector<Vec3> vecs);
        
        // Start Verlet Integration
        void run();
        void push(const Vec3& nudge);
        
    private:
        Spline3 spline;
        
        std::vector<Vec3> vecs;
        float tension; // tension for entire path
        float tensionMin, tensionMax; // tension for entire path
        Tup2 edgeTensions; // tensions at path ends
        std::vector<float> tensions; // all tensions along path
        AnchorMode anchorMode;
        
        // implementation guts
        // don't leave these shared - unnecessary and inefficient
        // Possible fix use unique or raw and make all control through sticks
        
        // hope this can work
        std::vector<std::shared_ptr<ProtoVerletBall>> balls;
        std::vector<std::unique_ptr<ProtoVerletStick>> sticks;
        
        void init();
    
    };
    
    // add more useful output to this eventually
    inline std::ostream& operator<<(std::ostream& out, const VerletPath& path){
        out << "address@"<< &path;
        return out;
    }
    
    inline std::vector<Vec3>& ProtoVerletPath::getPath(){
        return vecs;
    }
    
    inline float ProtoVerletPath::getTension(){
        return tension;
    }
    
    inline void ProtoVerletPath::setTension(float tension){
        this->tension = tension;
    }
    
    inline float ProtoVerletPath::getTension(int node){
        return tensions.at(node);
    }
    
    inline void ProtoVerletPath::setTension(int node, float tension){
        tensions.at(node) = tension;
    }
    
    inline Tup2 ProtoVerletPath::getEdgeTensions(){
        return edgeTensions;
    }
    
    inline void ProtoVerletPath::setEdgeTensions(const Tup2& edgeTensions){
        this->edgeTensions = edgeTensions;
    }
    inline std::vector<float>& ProtoVerletPath::getTensions(){
        return tensions;
    }
    
    inline void ProtoVerletPath::setTensions(const std::vector<float>& tensions){
        
    }
    inline ProtoVerletPath::AnchorMode ProtoVerletPath::getAnchorMode(){
        return anchorMode;
    }
    inline void ProtoVerletPath::setAnchorMode(const AnchorMode& anchorMode){
        this->anchorMode = anchorMode;
    }
}

#endif // Protobyte_dev_ProtoVerletPath_cpp
