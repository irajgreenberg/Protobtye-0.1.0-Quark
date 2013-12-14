#ifdef _WIN32
#include <GL/glew.h>
#endif

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>


//#include <iostream>
#include "ProtoPlasm.h"
#include "../../libProtobyte/ProtoDimension2.h"
#include "../../libProtobyte/ProtoWorld.h"
#include "../../libProtobyte/ProtoColor3.h"
#include "../../libProtobyte/ProtoColor4.h"
#include "../../libProtobyte/ProtoMath.h"
#include "../../libProtobyte/ProtoVector2.h"
#include "../../libProtobyte/ProtoVector3.h"
#include "../../libProtobyte/ProtoToroid.h"
#include "../../libProtobyte/ProtoSpline3.h"
#include "../../libProtobyte/ProtoSphere.h"
#include "../../libProtobyte/ProtoTube.h"
#include "../../libProtobyte/ProtoLight.h"

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

#define PI ProtoMath::PI
#define TWO_PI ProtoMath::TWO_PI

#include <iostream>

namespace ijg {
    
    class ProtoBaseApp {
        
        // enable Protoplasm private access
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
        /************************************
         **********     FIELDS     **********
         ***********************************/
        
        std::unique_ptr<ProtoWorld> world;
        int appWidth;
        int appHeight;
        std::string appTitle;
        int canvasWidth;
        int canvasHeight;
        Dim2i canvasSize;
        
        // background color
        Col3f bgColor;
        
        // CAMERAS
        // 5 cameras (for now) accessible in world
        ProtoCamera camera0, camera1, camera2, camera3, camera4;
        
        // LIGHTS
        // per GL limits 8 lights accessible in world
        // light0 enabled by default
        std::shared_ptr<ProtoLight> light0, light1, light2, light3, light4, light5, light6, light7;
        //std::shared_ptr<ProtoLight> lights[8];
        
        
        enum Matrix {
            MODEL_VIEW,
            PROJECTION
        };
        
        
        /************************************
         **********   FUNCTIONS   ***********
         ***********************************/
        
        
        
        // pure virtual funcs require override
        virtual void init()=0;
        virtual void run()=0;
        
        // mouse/key events
        virtual void keyPressed();
        virtual void mousePressed();
        virtual void mouseRightPressed();
        virtual void mouseReleased();
        virtual void mouseRightReleased();
        virtual void mouseMoved(int mx, int my);
        virtual void mouseDragged();
        
        // window events
        virtual void onResized();
        virtual void onClosed();
        
        
        // Add content to world
        void add(std::unique_ptr<ProtoGeom3> geom);
        //void add(std::unique_ptr<ProtoLight> lt);
        //void add(std::shared_ptr<ProtoLight> lt);
        void add(std::unique_ptr<ProtoCamera> cam);
        //void initWorld();
        
        
        // set background color
        void setBackground(float r, float g, float b);
        void setBackground(float c);
        void setBackground(const Col3f& col);
        void setBackground(const Col4f& col);
        
        // get window properties **READ ONLY**
        int getWidth()const;
        int getHeight()const;
        Dim2i getSize()const;
        
        // image loading using SFML
        void loadImage(std::string url);
        
        // LIGHTS
        void lightsOn();
        void lightsOff();
        
        
        // CAMERAS
        
        // WORLD
        void printMatrix(Matrix m=MODEL_VIEW);
        
        
        
        
    };
#define POINTS ProtoGeom3::POINTS
#define WIREFRAME ProtoGeom3::WIREFRAME
#define SURFACE ProtoGeom3::SURFACE
    
#define pushMatrix glPushMatrix
#define popMatrix glPopMatrix
    
#define translate glTranslatef
#define rotate glRotatef
    
}

#endif /* defined(PROTO_BASEAPP_H) */
