#ifdef _WIN32
#include <GL/glew.h>
#endif

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <unistd.h> // for cCurrentPath
#define GetCurrentDir getcwd

//#include <iostream>
#include "ProtoPlasm.h"
#include "../../Protobyte_v02/ProtoDimension2.h"
#include "../../Protobyte_v02/ProtoWorld.h"
#include "../../Protobyte_v02/ProtoColor3.h"
#include "../../Protobyte_v02/ProtoColor4.h"
#include "../../Protobyte_v02/ProtoMath.h"
#include "../../Protobyte_v02/ProtoVector2.h"
#include "../../Protobyte_v02/ProtoVector3.h"
#include "../../Protobyte_v02/ProtoToroid.h"
#include "../../Protobyte_v02/ProtoSpline3.h"
#include "../../Protobyte_v02/ProtoSphere.h"
#include "../../Protobyte_v02/ProtoTube.h"
#include "../../Protobyte_v02/ProtoLight.h"

// preproc dir for relative resource loading
// from http://stackoverflow.com/questions/143174/how-do-i-get-the-directory-that-a-program-is-running-from
#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
// end relative loading proproc dir


#ifndef PROTO_BASEAPP_H
#define PROTO_BASEAPP_H

#include <iostream>

namespace ijg {
    
    class ProtoBaseApp {
        
        friend class ProtoPlasm;
        
    public:
        ProtoBaseApp();
        
       // void setAppWindowDetails(int appWidth, int appHeight, std::string appTitle);
        
        
    private:
        // only needed to be called by ProtoPlasm class - a friend
        void setWorld(std::unique_ptr<ProtoWorld> world);
        void runWorld();
        // don't let users touch this after context is created
        void setWidth(int canvasWidth);
        void setHeight(int canvasHeight);
        void setSize(const Dim2i& canvasSize);
        
    protected:
        // pure virtual funcs require override
        virtual void init()=0;
        virtual void run()=0;
        
        // mouse/key events
        virtual void keyPressed();
        virtual void mousePressed();
        virtual void mouseRightPressed();
        virtual void mouseReleased();
        virtual void mouseRightReleased();
        virtual void mouseMoved();
        virtual void mouseDragged();
        
        // window events
        virtual void onResized();
        virtual void onClosed();
        
        
        // Add content to world
        void add(std::unique_ptr<ProtoGeom3> geom);
        void add(std::unique_ptr<ProtoLight> lt);
        void add(std::unique_ptr<ProtoCamera> cam);
        //void initWorld();

        
        std::unique_ptr<ProtoWorld> world;
        int appWidth;
        int appHeight;
        std::string appTitle;
        int canvasWidth;
        int canvasHeight;
        Dim2i canvasSize;
        
        // background color
        Col3f bgColor;
        void setBackground(float r, float g, float b);
        void setBackground(float c);
        void setBackground(const Col3f& col);
        void setBackground(const Col4f& col);
        
        // window properties **READ ONLY**
        int getWidth()const;
        int getHeight()const;
        Dim2i getSize()const;
        
        // image loading using SFML
        void loadImage(std::string url);
       
        
    
        
        
       
        
        
    };
    
}

#endif /* defined(PROTO_BASEAPP_H) */
