/*!  \brief  ProtoWorld.cpp: Top Level Master class
 ProtoWorld.cpp
 Protobyte Library v02
 
 Created by Ira on 7/25/13.
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

#include "ProtoWorld.h"



namespace ijg {
    std::ostream& operator<<(std::ostream& out, const ProtoWorld& protoWorld){
        out << "ijg::protoWorld@"<< &protoWorld;
        return out;
    }
}

using namespace ijg;

//ProtoWorld* ProtoWorld::singletonWorld = nullptr;
//std::once_flag ProtoWorld::protoOnceFlag;

float counter = 0;
// initialize static vars
// cameras
unsigned char ProtoWorld::cameraCount=0;
const unsigned char ProtoWorld::CAMERA_COUNT_MAX=4;

//Lights
unsigned char ProtoWorld::lightCount=0;
const unsigned char ProtoWorld::LIGHT_COUNT_MAX=8;


ProtoBoundsf ProtoWorld::canvasBounds = ProtoBoundsf(0,0,0,0);
// added comment for git test


// cstr
ProtoWorld::ProtoWorld(){
    
    worldRotSpeed = Vec3f(0,0,0);
    worldView = SINGLE_VIEW;
    activeCamera = 0;
    
    
    setDefaultProjection();
    init();
}

// cstr
ProtoWorld::ProtoWorld(float canvasWidth, float canvasHeight):
canvasWidth(canvasWidth), canvasHeight(canvasHeight){
    worldRotSpeed = Vec3f(0,0,0);
    //
    //    lights.resize(8);
    //    lights[0] = ProtoLight();
    //    std::cout << "lights.size() = " << lights.size() << std::endl;
    // canvasWidth = 23;
    
    init();
}

// dstr
//ProtoWorld::~ProtoWorld() {
//
//}

//ProtoWorld& ProtoWorld::operator=(const ProtoWorld& world) {
//    return *this;
//}


//ProtoWorld& ProtoWorld::getInstance(float canvasWidth, float canvasHeight) {
//
//    //    std::cout<<" canvasWidth = " <<  canvasWidth << std::endl;
//    //    std::cout<<" canvasHeight = " <<  canvasHeight << std::endl;
//
//    ProtoWorld::canvasWidth = canvasWidth;
//    ProtoWorld::canvasHeight = canvasHeight;
//
//    // allocation hasn't happened yet, so do it
//    if(singletonWorld == nullptr)
//    {
//        std::cout<<"Singleton ProtoWorld obj created"<<std::endl;
//
//        std::call_once(protoOnceFlag,
//                       [] {singletonWorld.reset(new ProtoWorld);
//                       });
//        return *singletonWorld.get();
//
//    }
//    // pointer to object already exists just return it
//    else
//    {
//        std::cout<<"Pointer to existing Singleton ProtoWorld obj returned"<<std::endl;
//        return *singletonWorld.get();
//    }
//}
//
//ProtoWorld& ProtoWorld::getInstance(float canvasWidth, float canvasHeight) {
//
//    //    std::cout<<" canvasWidth = " <<  canvasWidth << std::endl;
//    //    std::cout<<" canvasHeight = " <<  canvasHeight << std::endl;
//
//    ProtoWorld::canvasWidth = canvasWidth;
//    ProtoWorld::canvasHeight = canvasHeight;
//
//    // allocation hasn't happened yet, so do it
//    if(singletonWorld == nullptr)
//    {
//        std::cout<<"Singleton ProtoWorld obj created"<<std::endl;
//
//        std::call_once(protoOnceFlag,
//                       [] {singletonWorld.reset(new ProtoWorld);
//                       });
//        return *singletonWorld.get();
//
//    }
//    // pointer to object already exists just return it
//    else
//    {
//        std::cout<<"Pointer to existing Singleton ProtoWorld obj returned"<<std::endl;
//        return *singletonWorld.get();
//    }
//}



//ProtoWorld* ProtoWorld::getInstance() {
//
//    std::cout << "singletonWorld = " << singletonWorld << std::endl;
//
//    // allocation hasn't happened yet, so do it
//    if(singletonWorld == nullptr)
//    {
//        std::cout<<"Singleton ProtoWorld obj created"<<std::endl;
//
//        singletonWorld = new ProtoWorld;
//        return singletonWorld;
//
//    }
//    // pointer to object already exists just return it
//    else
//    {
//        std::cout<<"Pointer to existing Singleton ProtoWorld obj returned"<<std::endl;
//        return singletonWorld;
//    }
//}
//
//
//ProtoWorld* ProtoWorld::getInstance(float width, float height) {
//    std::cout << "singletonWorld = " << singletonWorld << std::endl;
//
//    // allocation hasn't happened yet, so do it
//    if(singletonWorld == nullptr)
//    {
//        canvasWidth = width;
//        canvasHeight = height;
//        std::cout<<"Singleton ProtoWorld obj created"<<std::endl;
//
//        singletonWorld = new ProtoWorld();
//        return singletonWorld;
//
//    }
//    // pointer to object already exists just return it
//    else
//    {
//        std::cout<<"Pointer to existing Singleton ProtoWorld obj returned"<<std::endl;
//        return singletonWorld;
//    }
//}

void ProtoWorld::init(){;
//    glEnable(GL_LIGHTING);
//    glFrontFace(GL_CCW); // default
//    glEnable(GL_CULL_FACE);
//    //glCullFace(GL_BACK);
//    //glDisable(GL_CULL_FACE);
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//    //glShadeModel(GL_FLAT); // option
//    glEnable(GL_COLOR_MATERIAL); // incorporates per vertex color with lights
//    // let glColor contorl diffues and ambient material values
//    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
//    
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glEnable(GL_BLEND);
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_NORMALIZE); //  good for uniform scaling
//    
//    
//    glClearStencil(0); // clear stencil buffer
//    glClearDepth(1.0f); // 0 is near, 1 is far
//    glDepthFunc(GL_LEQUAL);
    
    
    // CREATE DEFAULT CAMERA
    //    std::unique_ptr<ProtoCamera> camera1(new ProtoCamera(ProtoWorld::canvasBounds));
    //    add(std::move(camera1));
    
    
    // CREATE DEFAULT RENDERER
    // enable renderer and animator
    renderer = ProtoRenderer::getInstance();
    
    // CREATE DEFAULT ANIMATOR
    //    animator = ProtoAnimator::getInstance();
    
    //create default shader
    //const char* vert = "resources/defaultShader.vert";
    //const char* frag = "resources/defaultShader.frag";
    // shader.init(vert, frag);
}


//void ProtoWorld::add(ProtoGeomComposite* geomObj){
//    // TO DO
//}
//

void ProtoWorld::add(std::unique_ptr<ProtoCamera> camera){
    
    assert(static_cast<int>(ProtoWorld::cameraCount)<= 4);
    
    if(ProtoWorld::cameraCount < ProtoWorld::CAMERA_COUNT_MAX){
        camera->setName("cam_"+ std::to_string(ProtoWorld::cameraCount));
        cameras.push_back(std::move(camera)); // change ownership
        ProtoWorld::cameraCount++;
    }
    for(int i=0; i<cameras.size(); ++i){
        //std::cout << "cameras.at("<<i<<")->getName() = " << cameras.at(i)->getName() << std::endl;
    }
    //std::cout << "ProtoWorld::cameraCount = "<< static_cast<int>(ProtoWorld::cameraCount) << std::endl;
}


void ProtoWorld::add(std::unique_ptr<ProtoGeom3> geomObj) {
    geoms.push_back(std::move(geomObj)); // change ownership
    //std::cout << " geomObj added @ " << &geomObj << std::endl;
}

void ProtoWorld::add(std::shared_ptr<ProtoGeom3> geomObj) {
    // std::cout << " geomObj added @ " << &geomObj << std::endl;
    sharedGeoms.push_back(geomObj); // change ownership
}

// not sure this is a good idea
void ProtoWorld::add(const ProtoGeom3* geomObj) {
}


//void ProtoWorld::remove(ProtoCamera* camera){
//    if(cameras.size()>0){
//        for(cameraObjsIter=cameras.begin(); cameraObjsIter < cameras.end(); ++cameraObjsIter){
//            if( (*cameraObjsIter)->getUniqueID() == camera->getUniqueID()){
//                cameras.erase(cameraObjsIter);
//
//            }
//        }
//    }
//    std::cout << "cameras.size() = " << cameras.size() << std::endl;
//}


// Lighting handled through world
void ProtoWorld::setDiffuse(Light lightID, const ProtoColor4f& color, const ProtoColor4f& material){
    // glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
    // glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    
}
void ProtoWorld::setSpecular(Light lightID, const ProtoColor4f& color, const ProtoColor4f& material, float shininess){
    
}
void ProtoWorld::setShininess(float shininess){
    
}
void ProtoWorld::setAmbient(Light lightID, const ProtoColor4f& color, const ProtoColor4f& material){
    
}
void ProtoWorld::setEmission(Light lightID, const ProtoColor4f& color, const ProtoColor4f& material){
    
}


// add Shared pointer lights
void ProtoWorld::add(std::shared_ptr<ProtoLight> light){
    
    if (lights.size() < LIGHT_COUNT_MAX){
        lights.push_back(light);
    } else {
        std::cout << "WARNING: ProtoWorld includes 8 lights, wthe maximum number allowed.\n";
    }
}


// run world
void ProtoWorld::run() {
    
    //std::cout << "in ProtoWorld.run()" << std::endl;
    // if animated
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    
    float globalAmbient[4] = {.2, .2, .2, 1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,  globalAmbient);
    /**************************************************
     *                   LIGHTING                     *
     *************************************************/
    for(std::size_t i=0; i<lights.size(); ++i){
        switch(i){
            case 0:
                if(lights.at(i)->getIsOn()){
                    glEnable(GL_LIGHT0);
                    
                    // set Lights
                    float position[4] = {
                        lights.at(i)->getPosition().x,
                        lights.at(i)->getPosition().y,
                        lights.at(i)->getPosition().z,
                        1
                    };
                    
                    float diffuse[4] = {
                        lights.at(i)->getDiffuse().getR(),
                        lights.at(i)->getDiffuse().getG(),
                        lights.at(i)->getDiffuse().getB(),
                        lights.at(i)->getDiffuse().getA()
                    };
                    
                    float ambient[4] = {
                        lights.at(i)->getAmbient().getR(),
                        lights.at(i)->getAmbient().getG(),
                        lights.at(i)->getAmbient().getB(),
                        lights.at(i)->getAmbient().getA()
                    };
                    
                    float specular[4] = {
                        lights.at(i)->getSpecular().getR(),
                        lights.at(i)->getSpecular().getG(),
                        lights.at(i)->getSpecular().getB(),
                        lights.at(i)->getSpecular().getA()
                    };
                    
                    
                    // materials
//                    float materialDiffuse[4] = {
//                        lights.at(i)->getDiffuseMaterial().getR(),
//                        lights.at(i)->getDiffuseMaterial().getG(),
//                        lights.at(i)->getDiffuseMaterial().getB(),
//                        lights.at(i)->getDiffuseMaterial().getA()
//                    };
//                    
//                    float materialSpecularity[4] = {
//                        lights.at(i)->getSpecularMaterial().getR(),
//                        lights.at(i)->getSpecularMaterial().getG(),
//                        lights.at(i)->getSpecularMaterial().getB(),
//                        lights.at(i)->getSpecularMaterial().getA()
//                    };
//                    
//                    float materialAmbient[4] = {
//                        lights.at(i)->getAmbientMaterial().getR(),
//                        lights.at(i)->getAmbientMaterial().getG(),
//                        lights.at(i)->getAmbientMaterial().getB(),
//                        lights.at(i)->getAmbientMaterial().getA()
//                    };
//                    
//                    float materialEmissive[4] = {
//                        lights.at(i)->getEmissiveMaterial().getR(),
//                        lights.at(i)->getEmissiveMaterial().getG(),
//                        lights.at(i)->getEmissiveMaterial().getB(),
//                        lights.at(i)->getEmissiveMaterial().getA()
//                    };
                    
                    //GLfloat shininess[] = {lights.at(i)->getShinines()}; // max 128
                    
                    //glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecularity);
                    //glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
                    glLightfv(GL_LIGHT0, GL_POSITION, position);
                    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
                    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
                    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
                    
                } else {
                    glDisable(GL_LIGHT0);
                }
                break;
            case 1:
                if(lights.at(i)->getIsOn()){
                    glEnable(GL_LIGHT1);
                    // set Lights
                    float position[4] = {
                        lights.at(i)->getPosition().x,
                        lights.at(i)->getPosition().y,
                        lights.at(i)->getPosition().z,
                        1
                    };
                    
                    float diffuse[4] = {
                        lights.at(i)->getDiffuse().getR(),
                        lights.at(i)->getDiffuse().getG(),
                        lights.at(i)->getDiffuse().getB(),
                        lights.at(i)->getDiffuse().getA()
                    };
                    
                    float ambient[4] = {
                        lights.at(i)->getAmbient().getR(),
                        lights.at(i)->getAmbient().getG(),
                        lights.at(i)->getAmbient().getB(),
                        lights.at(i)->getAmbient().getA()
                    };
                    
                    float specular[4] = {
                        lights.at(i)->getSpecular().getR(),
                        lights.at(i)->getSpecular().getG(),
                        lights.at(i)->getSpecular().getB(),
                        lights.at(i)->getSpecular().getA()
                    };
                    
                    
                    // materials
//                    float materialDiffuse[4] = {
//                        lights.at(i)->getDiffuseMaterial().getR(),
//                        lights.at(i)->getDiffuseMaterial().getG(),
//                        lights.at(i)->getDiffuseMaterial().getB(),
//                        lights.at(i)->getDiffuseMaterial().getA()
//                    };
//                    
//                    float materialSpecularity[4] = {
//                        lights.at(i)->getSpecularMaterial().getR(),
//                        lights.at(i)->getSpecularMaterial().getG(),
//                        lights.at(i)->getSpecularMaterial().getB(),
//                        lights.at(i)->getSpecularMaterial().getA()
//                    };
//                    
//                    float materialAmbient[4] = {
//                        lights.at(i)->getAmbientMaterial().getR(),
//                        lights.at(i)->getAmbientMaterial().getG(),
//                        lights.at(i)->getAmbientMaterial().getB(),
//                        lights.at(i)->getAmbientMaterial().getA()
//                    };
//                    
//                    float materialEmissive[4] = {
//                        lights.at(i)->getEmissiveMaterial().getR(),
//                        lights.at(i)->getEmissiveMaterial().getG(),
//                        lights.at(i)->getEmissiveMaterial().getB(),
//                        lights.at(i)->getEmissiveMaterial().getA()
//                    };
                    
                    //GLfloat shininess[] = {lights.at(i)->getShinines()}; // max 128
                    
                    //glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecularity);
                    //glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
                    glLightfv(GL_LIGHT1, GL_POSITION, position);
                    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
                    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
                    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
                    
                } else {
                    glDisable(GL_LIGHT1);
                }
                
                break;
            case 2:
                if(lights.at(i)->getIsOn()){
                    glEnable(GL_LIGHT2);
                    // set Lights
                    float position[4] = {
                        lights.at(i)->getPosition().x,
                        lights.at(i)->getPosition().y,
                        lights.at(i)->getPosition().z,
                        1
                    };
                    
                    float diffuse[4] = {
                        lights.at(i)->getDiffuse().getR(),
                        lights.at(i)->getDiffuse().getG(),
                        lights.at(i)->getDiffuse().getB(),
                        lights.at(i)->getDiffuse().getA()
                    };
                    
                    float ambient[4] = {
                        lights.at(i)->getAmbient().getR(),
                        lights.at(i)->getAmbient().getG(),
                        lights.at(i)->getAmbient().getB(),
                        lights.at(i)->getAmbient().getA()
                    };
                    
                    float specular[4] = {
                        lights.at(i)->getSpecular().getR(),
                        lights.at(i)->getSpecular().getG(),
                        lights.at(i)->getSpecular().getB(),
                        lights.at(i)->getSpecular().getA()
                    };
                    
                    
                    // materials
//                    float materialDiffuse[4] = {
//                        lights.at(i)->getDiffuseMaterial().getR(),
//                        lights.at(i)->getDiffuseMaterial().getG(),
//                        lights.at(i)->getDiffuseMaterial().getB(),
//                        lights.at(i)->getDiffuseMaterial().getA()
//                    };
//                    
//                    float materialSpecularity[4] = {
//                        lights.at(i)->getSpecularMaterial().getR(),
//                        lights.at(i)->getSpecularMaterial().getG(),
//                        lights.at(i)->getSpecularMaterial().getB(),
//                        lights.at(i)->getSpecularMaterial().getA()
//                    };
//                    
//                    float materialAmbient[4] = {
//                        lights.at(i)->getAmbientMaterial().getR(),
//                        lights.at(i)->getAmbientMaterial().getG(),
//                        lights.at(i)->getAmbientMaterial().getB(),
//                        lights.at(i)->getAmbientMaterial().getA()
//                    };
//                    
//                    float materialEmissive[4] = {
//                        lights.at(i)->getEmissiveMaterial().getR(),
//                        lights.at(i)->getEmissiveMaterial().getG(),
//                        lights.at(i)->getEmissiveMaterial().getB(),
//                        lights.at(i)->getEmissiveMaterial().getA()
//                    };
                    
//                    GLfloat shininess[] = {lights.at(i)->getShinines()}; // max 128
                    
//                    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecularity);
//                    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
                    glLightfv(GL_LIGHT2, GL_POSITION, position);
                    glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
                    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
                    glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
                    
                } else {
                    glDisable(GL_LIGHT2);
                }
                
                break;
                
            case 3:
                if(lights.at(i)->getIsOn()){
                    glEnable(GL_LIGHT3);
                    // set Lights
                    float position[4] = {
                        lights.at(i)->getPosition().x,
                        lights.at(i)->getPosition().y,
                        lights.at(i)->getPosition().z,
                        1
                    };
                    
                    float diffuse[4] = {
                        lights.at(i)->getDiffuse().getR(),
                        lights.at(i)->getDiffuse().getG(),
                        lights.at(i)->getDiffuse().getB(),
                        lights.at(i)->getDiffuse().getA()
                    };
                    
                    float ambient[4] = {
                        lights.at(i)->getAmbient().getR(),
                        lights.at(i)->getAmbient().getG(),
                        lights.at(i)->getAmbient().getB(),
                        lights.at(i)->getAmbient().getA()
                    };
                    
                    float specular[4] = {
                        lights.at(i)->getSpecular().getR(),
                        lights.at(i)->getSpecular().getG(),
                        lights.at(i)->getSpecular().getB(),
                        lights.at(i)->getSpecular().getA()
                    };
                    
                    
                    // materials
//                    float materialDiffuse[4] = {
//                        lights.at(i)->getDiffuseMaterial().getR(),
//                        lights.at(i)->getDiffuseMaterial().getG(),
//                        lights.at(i)->getDiffuseMaterial().getB(),
//                        lights.at(i)->getDiffuseMaterial().getA()
//                    };
//                    
//                    float materialSpecularity[4] = {
//                        lights.at(i)->getSpecularMaterial().getR(),
//                        lights.at(i)->getSpecularMaterial().getG(),
//                        lights.at(i)->getSpecularMaterial().getB(),
//                        lights.at(i)->getSpecularMaterial().getA()
//                    };
//                    
//                    float materialAmbient[4] = {
//                        lights.at(i)->getAmbientMaterial().getR(),
//                        lights.at(i)->getAmbientMaterial().getG(),
//                        lights.at(i)->getAmbientMaterial().getB(),
//                        lights.at(i)->getAmbientMaterial().getA()
//                    };
//                    
//                    float materialEmissive[4] = {
//                        lights.at(i)->getEmissiveMaterial().getR(),
//                        lights.at(i)->getEmissiveMaterial().getG(),
//                        lights.at(i)->getEmissiveMaterial().getB(),
//                        lights.at(i)->getEmissiveMaterial().getA()
//                    };
                    
//                    GLfloat shininess[] = {lights.at(i)->getShinines()}; // max 128
//                    
//                    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecularity);
//                    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
                    glLightfv(GL_LIGHT3, GL_POSITION, position);
                    glLightfv(GL_LIGHT3, GL_AMBIENT, ambient);
                    glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);
                    glLightfv(GL_LIGHT3, GL_SPECULAR, specular);
                    
                } else {
                    glDisable(GL_LIGHT3);
                }
                
                break;
                
            case 4:
                if(lights.at(i)->getIsOn()){
                    glEnable(GL_LIGHT4);
                    // set Lights
                    float position[4] = {
                        lights.at(i)->getPosition().x,
                        lights.at(i)->getPosition().y,
                        lights.at(i)->getPosition().z,
                        1
                    };
                    
                    float diffuse[4] = {
                        lights.at(i)->getDiffuse().getR(),
                        lights.at(i)->getDiffuse().getG(),
                        lights.at(i)->getDiffuse().getB(),
                        lights.at(i)->getDiffuse().getA()
                    };
                    
                    float ambient[4] = {
                        lights.at(i)->getAmbient().getR(),
                        lights.at(i)->getAmbient().getG(),
                        lights.at(i)->getAmbient().getB(),
                        lights.at(i)->getAmbient().getA()
                    };
                    
                    float specular[4] = {
                        lights.at(i)->getSpecular().getR(),
                        lights.at(i)->getSpecular().getG(),
                        lights.at(i)->getSpecular().getB(),
                        lights.at(i)->getSpecular().getA()
                    };
                    
                    
                    // materials
//                    float materialDiffuse[4] = {
//                        lights.at(i)->getDiffuseMaterial().getR(),
//                        lights.at(i)->getDiffuseMaterial().getG(),
//                        lights.at(i)->getDiffuseMaterial().getB(),
//                        lights.at(i)->getDiffuseMaterial().getA()
//                    };
//                    
//                    float materialSpecularity[4] = {
//                        lights.at(i)->getSpecularMaterial().getR(),
//                        lights.at(i)->getSpecularMaterial().getG(),
//                        lights.at(i)->getSpecularMaterial().getB(),
//                        lights.at(i)->getSpecularMaterial().getA()
//                    };
//                    
//                    float materialAmbient[4] = {
//                        lights.at(i)->getAmbientMaterial().getR(),
//                        lights.at(i)->getAmbientMaterial().getG(),
//                        lights.at(i)->getAmbientMaterial().getB(),
//                        lights.at(i)->getAmbientMaterial().getA()
//                    };
//                    
//                    float materialEmissive[4] = {
//                        lights.at(i)->getEmissiveMaterial().getR(),
//                        lights.at(i)->getEmissiveMaterial().getG(),
//                        lights.at(i)->getEmissiveMaterial().getB(),
//                        lights.at(i)->getEmissiveMaterial().getA()
//                    };
//                    
//                    GLfloat shininess[] = {lights.at(i)->getShinines()}; // max 128
//                    
//                    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecularity);
//                    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
                    glLightfv(GL_LIGHT4, GL_POSITION, position);
                    glLightfv(GL_LIGHT4, GL_AMBIENT, ambient);
                    glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse);
                    glLightfv(GL_LIGHT4, GL_SPECULAR, specular);
                    
                } else {
                    glDisable(GL_LIGHT4);
                }
                
                break;
                
            case 5:
                if(lights.at(i)->getIsOn()){
                    glEnable(GL_LIGHT5);
                    // set Lights
                    float position[4] = {
                        lights.at(i)->getPosition().x,
                        lights.at(i)->getPosition().y,
                        lights.at(i)->getPosition().z,
                        1
                    };
                    
                    float diffuse[4] = {
                        lights.at(i)->getDiffuse().getR(),
                        lights.at(i)->getDiffuse().getG(),
                        lights.at(i)->getDiffuse().getB(),
                        lights.at(i)->getDiffuse().getA()
                    };
                    
                    float ambient[4] = {
                        lights.at(i)->getAmbient().getR(),
                        lights.at(i)->getAmbient().getG(),
                        lights.at(i)->getAmbient().getB(),
                        lights.at(i)->getAmbient().getA()
                    };
                    
                    float specular[4] = {
                        lights.at(i)->getSpecular().getR(),
                        lights.at(i)->getSpecular().getG(),
                        lights.at(i)->getSpecular().getB(),
                        lights.at(i)->getSpecular().getA()
                    };
                    
                    
//                    // materials
//                    float materialDiffuse[4] = {
//                        lights.at(i)->getDiffuseMaterial().getR(),
//                        lights.at(i)->getDiffuseMaterial().getG(),
//                        lights.at(i)->getDiffuseMaterial().getB(),
//                        lights.at(i)->getDiffuseMaterial().getA()
//                    };
//                    
//                    float materialSpecularity[4] = {
//                        lights.at(i)->getSpecularMaterial().getR(),
//                        lights.at(i)->getSpecularMaterial().getG(),
//                        lights.at(i)->getSpecularMaterial().getB(),
//                        lights.at(i)->getSpecularMaterial().getA()
//                    };
//                    
//                    float materialAmbient[4] = {
//                        lights.at(i)->getAmbientMaterial().getR(),
//                        lights.at(i)->getAmbientMaterial().getG(),
//                        lights.at(i)->getAmbientMaterial().getB(),
//                        lights.at(i)->getAmbientMaterial().getA()
//                    };
//                    
//                    float materialEmissive[4] = {
//                        lights.at(i)->getEmissiveMaterial().getR(),
//                        lights.at(i)->getEmissiveMaterial().getG(),
//                        lights.at(i)->getEmissiveMaterial().getB(),
//                        lights.at(i)->getEmissiveMaterial().getA()
//                    };
//                    
//                    GLfloat shininess[] = {lights.at(i)->getShinines()}; // max 128
//                    
//                    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecularity);
//                    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
                    glLightfv(GL_LIGHT5, GL_POSITION, position);
                    glLightfv(GL_LIGHT5, GL_AMBIENT, ambient);
                    glLightfv(GL_LIGHT5, GL_DIFFUSE, diffuse);
                    glLightfv(GL_LIGHT5, GL_SPECULAR, specular);
                    
                } else {
                    glDisable(GL_LIGHT5);
                }

                
                break;
                
            case 6:
                if(lights.at(i)->getIsOn()){
                    glEnable(GL_LIGHT6);
                    // set Lights
                    float position[4] = {
                        lights.at(i)->getPosition().x,
                        lights.at(i)->getPosition().y,
                        lights.at(i)->getPosition().z,
                        1
                    };
                    
                    float diffuse[4] = {
                        lights.at(i)->getDiffuse().getR(),
                        lights.at(i)->getDiffuse().getG(),
                        lights.at(i)->getDiffuse().getB(),
                        lights.at(i)->getDiffuse().getA()
                    };
                    
                    float ambient[4] = {
                        lights.at(i)->getAmbient().getR(),
                        lights.at(i)->getAmbient().getG(),
                        lights.at(i)->getAmbient().getB(),
                        lights.at(i)->getAmbient().getA()
                    };
                    
                    float specular[4] = {
                        lights.at(i)->getSpecular().getR(),
                        lights.at(i)->getSpecular().getG(),
                        lights.at(i)->getSpecular().getB(),
                        lights.at(i)->getSpecular().getA()
                    };
                    
                    
                    // materials
//                    float materialDiffuse[4] = {
//                        lights.at(i)->getDiffuseMaterial().getR(),
//                        lights.at(i)->getDiffuseMaterial().getG(),
//                        lights.at(i)->getDiffuseMaterial().getB(),
//                        lights.at(i)->getDiffuseMaterial().getA()
//                    };
//                    
//                    float materialSpecularity[4] = {
//                        lights.at(i)->getSpecularMaterial().getR(),
//                        lights.at(i)->getSpecularMaterial().getG(),
//                        lights.at(i)->getSpecularMaterial().getB(),
//                        lights.at(i)->getSpecularMaterial().getA()
//                    };
//                    
//                    float materialAmbient[4] = {
//                        lights.at(i)->getAmbientMaterial().getR(),
//                        lights.at(i)->getAmbientMaterial().getG(),
//                        lights.at(i)->getAmbientMaterial().getB(),
//                        lights.at(i)->getAmbientMaterial().getA()
//                    };
//                    
//                    float materialEmissive[4] = {
//                        lights.at(i)->getEmissiveMaterial().getR(),
//                        lights.at(i)->getEmissiveMaterial().getG(),
//                        lights.at(i)->getEmissiveMaterial().getB(),
//                        lights.at(i)->getEmissiveMaterial().getA()
//                    };
//                    
//                    GLfloat shininess[] = {lights.at(i)->getShinines()}; // max 128
//                    
//                    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecularity);
//                    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
                    glLightfv(GL_LIGHT6, GL_POSITION, position);
                    glLightfv(GL_LIGHT6, GL_AMBIENT, ambient);
                    glLightfv(GL_LIGHT6, GL_DIFFUSE, diffuse);
                    glLightfv(GL_LIGHT6, GL_SPECULAR, specular);
                    
                } else {
                    glDisable(GL_LIGHT6);
                }
                
                break;
                
            case 7:
                if(lights.at(i)->getIsOn()){
                    glEnable(GL_LIGHT7);
                    // set Lights
                    float position[4] = {
                        lights.at(i)->getPosition().x,
                        lights.at(i)->getPosition().y,
                        lights.at(i)->getPosition().z,
                        1
                    };
                    
                    float diffuse[4] = {
                        lights.at(i)->getDiffuse().getR(),
                        lights.at(i)->getDiffuse().getG(),
                        lights.at(i)->getDiffuse().getB(),
                        lights.at(i)->getDiffuse().getA()
                    };
                    
                    float ambient[4] = {
                        lights.at(i)->getAmbient().getR(),
                        lights.at(i)->getAmbient().getG(),
                        lights.at(i)->getAmbient().getB(),
                        lights.at(i)->getAmbient().getA()
                    };
                    
                    float specular[4] = {
                        lights.at(i)->getSpecular().getR(),
                        lights.at(i)->getSpecular().getG(),
                        lights.at(i)->getSpecular().getB(),
                        lights.at(i)->getSpecular().getA()
                    };
                    
                    
                    // materials
//                    float materialDiffuse[4] = {
//                        lights.at(i)->getDiffuseMaterial().getR(),
//                        lights.at(i)->getDiffuseMaterial().getG(),
//                        lights.at(i)->getDiffuseMaterial().getB(),
//                        lights.at(i)->getDiffuseMaterial().getA()
//                    };
//                    
//                    float materialSpecularity[4] = {
//                        lights.at(i)->getSpecularMaterial().getR(),
//                        lights.at(i)->getSpecularMaterial().getG(),
//                        lights.at(i)->getSpecularMaterial().getB(),
//                        lights.at(i)->getSpecularMaterial().getA()
//                    };
//                    
//                    float materialAmbient[4] = {
//                        lights.at(i)->getAmbientMaterial().getR(),
//                        lights.at(i)->getAmbientMaterial().getG(),
//                        lights.at(i)->getAmbientMaterial().getB(),
//                        lights.at(i)->getAmbientMaterial().getA()
//                    };
//                    
//                    float materialEmissive[4] = {
//                        lights.at(i)->getEmissiveMaterial().getR(),
//                        lights.at(i)->getEmissiveMaterial().getG(),
//                        lights.at(i)->getEmissiveMaterial().getB(),
//                        lights.at(i)->getEmissiveMaterial().getA()
//                    };
//                    
//                    GLfloat shininess[] = {lights.at(i)->getShinines()}; // max 128
//                    
//                    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecularity);
//                    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
                    glLightfv(GL_LIGHT7, GL_POSITION, position);
                    glLightfv(GL_LIGHT7, GL_AMBIENT, ambient);
                    glLightfv(GL_LIGHT7, GL_DIFFUSE, diffuse);
                    glLightfv(GL_LIGHT7, GL_SPECULAR, specular);
                    
                } else {
                    glDisable(GL_LIGHT7);
                }
                
                break;
        }
        
        
        
        
    }
    
    //std::cout << "geoms = " << &geoms << std::endl;
    
    glMatrixMode(GL_MODELVIEW);
    // uncomment glLoadIdentity to allow rotated but not animated state
    // glLoadIdentity();
    // world rot speed
    //    glRotatef(worldRotSpeed.x, 1, 0, 0);
    //    glRotatef(worldRotSpeed.y, 0, 1, 0);
    //    glRotatef(worldRotSpeed.z, 0, 0, 1);
    
    switch(worldView){
            
        case SINGLE_VIEW:
            glPushMatrix();
        {
            if (cameras.size()==0){
                std::unique_ptr<ProtoCamera> camera1(new ProtoCamera());
                add(std::move(camera1));
                cameras.at(0)->setViewPort(0, 0, canvasWidth, canvasHeight);
                cameras.at(0)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(0)->project();
                
                // FIX THIS EVENTUALLY - hard coded 0 instead of using activeCamera ***********************************
            } else {
                cameras.at(0)->setViewPort(0, 0, canvasWidth, canvasHeight);
                cameras.at(0)->project();
            }
            
            
            // draw geometry
            draw();
        }
            glPopMatrix();
            
            break;
        case DOUBLE_VIEW_LANDSCAPE:
            glPushMatrix();
        {
            if (cameras.size()==0){
                std::unique_ptr<ProtoCamera> camera1(new ProtoCamera());
                add(std::move(camera1));
                std::unique_ptr<ProtoCamera> camera2(new ProtoCamera());
                add(std::move(camera2));
                
                // top
                cameras.at(0)->setViewPort(0, canvasHeight/2, canvasWidth, canvasHeight/2);
                cameras.at(0)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(0)->project();
                // draw geometry
                draw();
                
                
                // bottom
                cameras.at(1)->setViewPort(0, 0, canvasWidth, canvasHeight/2);
                cameras.at(1)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(1)->project();
                // draw geometry
                draw();
                
                
            } else if (cameras.size()==1){
                std::unique_ptr<ProtoCamera> camera2(new ProtoCamera());
                add(std::move(camera2));
                
                // top
                cameras.at(0)->setViewPort(0, canvasHeight/2, canvasWidth, canvasHeight/2);
                cameras.at(0)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(0)->project();
                // draw geometry
                draw();
                
                
                // bottom
                cameras.at(1)->setViewPort(0, 0, canvasWidth, canvasHeight/2);
                cameras.at(1)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(1)->project();
                // draw geometry
                draw();
                
            } else {
                
                //cameras.at(0)->setViewPort(0, canvasHeight/2, canvasWidth, canvasHeight/2);
                cameras.at(0)->project();
                // draw geometry
                draw();
                
                //cameras.at(1)->setViewPort(0, 0, canvasWidth, canvasHeight/2);
                cameras.at(1)->project();
                // draw geometry
                draw();
                
            }
        }
            glPopMatrix();
            
            break;
        case DOUBLE_VIEW_PORTRAIT:
            glPushMatrix();
        {
            if (cameras.size()==0){
                std::unique_ptr<ProtoCamera> camera1(new ProtoCamera());
                add(std::move(camera1));
                std::unique_ptr<ProtoCamera> camera2(new ProtoCamera());
                add(std::move(camera2));
                
                // Left
                cameras.at(0)->setViewPort(0, 0, canvasWidth/2, canvasHeight);
                cameras.at(0)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(0)->project();
                // draw geometry
                draw();
                
                
                // Right
                cameras.at(1)->setViewPort(canvasWidth/2, 0, canvasWidth/2, canvasHeight);
                cameras.at(1)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(1)->project();
                // draw geometry
                draw();
                
                
            } else if (cameras.size()==1){
                std::unique_ptr<ProtoCamera> camera2(new ProtoCamera());
                add(std::move(camera2));
                
                // Left
                cameras.at(0)->setViewPort(0, 0, canvasWidth/2, canvasHeight);
                cameras.at(0)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(0)->project();
                // draw geometry
                draw();
                
                
                // Right
                cameras.at(1)->setViewPort(canvasWidth/2, 0, canvasWidth/2, canvasHeight);
                cameras.at(1)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(1)->project();
                // draw geometry
                draw();
                
            } else {
                //cameras.at(0)->setViewPort(0, 0, canvasWidth/2, canvasHeight);
                cameras.at(0)->project();
                // draw geometry
                draw();
                
                //cameras.at(1)->setViewPort(canvasWidth/2, 0, canvasWidth/2, canvasHeight);
                cameras.at(1)->project();
                // draw geometry
                draw();
                
            }
        }
            glPopMatrix();
            
            break;
            
            
            
        case QUAD_VIEW:
            // right now only handle 0 or 4 cameras
            if (cameras.size() == 4){ // cameras are already loaded
                
                // check bottom left camera for viewport
                //                if (cameras.at(0)->getViewPort().x == 0 && cameras.at(0)->getViewPort().y == 0 &&
                //                    cameras.at(0)->getViewPort().w == 0 && cameras.at(0)->getViewPort().h == 0){
                //
                //                    //cameras.at(0)->setViewPort(0, 0, canvasWidth/2, canvasHeight/2);
                //                }
                //
                //                if (cameras.at(1)->getViewPort().x == 0 && cameras.at(0)->getViewPort().y == 0 &&
                //                    cameras.at(1)->getViewPort().w == 0 && cameras.at(0)->getViewPort().h == 0){
                //
                //                    //cameras.at(1)->setViewPort(0, canvasHeight/2, canvasWidth/2, canvasHeight/2); //TL
                //                }
                //
                //                if (cameras.at(2)->getViewPort().x == 0 && cameras.at(0)->getViewPort().y == 0 &&
                //                    cameras.at(2)->getViewPort().w == 0 && cameras.at(0)->getViewPort().h == 0){
                //
                //                    //cameras.at(2)->setViewPort(canvasWidth/2, canvasHeight/2, canvasWidth/2, canvasHeight/2); //TR
                //                }
                //
                //                if (cameras.at(3)->getViewPort().x == 0 && cameras.at(0)->getViewPort().y == 0 &&
                //                    cameras.at(3)->getViewPort().w == 0 && cameras.at(0)->getViewPort().h == 0){
                //
                //                    // cameras.at(3)->setViewPort(canvasWidth/2, 0, canvasWidth/2, canvasHeight/2); //BR
                //                }
                
                cameras.at(0)->project();
                draw();
                cameras.at(1)->project();
                draw();
                cameras.at(2)->project();
                draw();
                cameras.at(3)->project();
                draw();
                
            } else {
                while (cameras.size()<4) { // create camera since none exists
                    std::unique_ptr<ProtoCamera> camera1(new ProtoCamera());
                    add(std::move(camera1));
                    std::cout << "camera size = " << cameras.size() << std::endl;
                }
                
                cameras.at(0)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(0)->setViewPort(0, 0, canvasWidth/2, canvasHeight/2); //BL
                cameras.at(0)->project();
                draw();
                
                cameras.at(1)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(1)->setViewPort(0, canvasHeight/2, canvasWidth/2, canvasHeight/2); //TL
                cameras.at(1)->project();
                draw();
                
                cameras.at(2)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(2)->setViewPort(canvasWidth/2, canvasHeight/2, canvasWidth/2, canvasHeight/2); //TR
                cameras.at(2)->project();
                draw();
                
                cameras.at(3)->setProjection(fovAngle, canvasWidth/canvasHeight, nearClipPlane, farClipPlane);
                cameras.at(3)->setViewPort(canvasWidth/2, 0, canvasWidth/2, canvasHeight/2); //BR
                cameras.at(3)->project();
                draw();
                
            }
            
            
    }
    
    
}

// stop world
void ProtoWorld::stop(){
}

void ProtoWorld::draw() {
    
    
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //std::cout << "in world draw" << std::endl;
    // utlize shader
    //shader.bind();
    for(int i=0; i<geoms.size(); ++i){
        //std::cout << "geoms.size() = " << geoms.size() << std::endl;
        renderer->draw(geoms.at(i));
        //geoms.at(i)->display(ProtoGeom3::VERTEX_BUFFER_OBJECT, ProtoGeom3::SURFACE);
    }
    
    
    
    for(int i=0; i<sharedGeoms.size(); ++i){
        //sharedGeoms.at(i)->display(ProtoGeom3::VERTEX_BUFFER_OBJECT, ProtoGeom3::SURFACE);
    }
    // shader.unbind();
}

void ProtoWorld::rotate(const Vec3f& worldRot) {
    
}

void ProtoWorld::setWorldRotSpeed(const Vec3f& worldRotSpeed){
    this->worldRotSpeed = worldRotSpeed;
}

void ProtoWorld::setDefaultProjection(float fovAngle, float nearClipPlane, float farClipPlane) {
    this->fovAngle = fovAngle;
    this->nearClipPlane = nearClipPlane;
    this->farClipPlane = farClipPlane;
}

void ProtoWorld::setWorldView(WorldView worldView){
    this->worldView = worldView;
    
}

void ProtoWorld::setActiveCamera(int activeCamera){
    this->activeCamera = activeCamera;
}

// set states
//void setRenderState(ProtoRenderer::RenderModeEnum renderMode, float pointSize) {
//   // this->renderMode = renderMode;
//}

void ProtoWorld::setLights() {
    
    /**********************************
     *           LIGHTING             *
     *********************************/
    // Light01
    GLfloat light01_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat light01_diffuse[] = {.65, .65, .65, 1.0};
    GLfloat light01_specular[] = {.8, .8, .8, 1.0};
    GLfloat light01_position[] = {-20, 10, 5.0, 0.0};
    
    //materials
    GLfloat light01_mat_specular[] = {.85, .8, .92, 1.0};
    GLfloat light01_mat_shininess[] = {18}; // max 128
    
    
    // light 01
    glMaterialfv(GL_FRONT, GL_SPECULAR, light01_mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, light01_mat_shininess);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light01_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light01_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light01_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light01_position);
    
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void ProtoWorld::updateCanvasSize(float canvasWidth, float canvasHeight){
    this->canvasWidth = canvasWidth;
    this->canvasHeight = canvasHeight;
    //std::cout << "cameras.size() = " << cameras.size() << std::endl;
    
    
    if(ProtoWorld::QUAD_VIEW){
        if(cameras.size()==4){
            cameras.at(0)->setAspectRatio(canvasWidth/canvasHeight);
            cameras.at(1)->setAspectRatio(canvasWidth/canvasHeight);
            cameras.at(2)->setAspectRatio(canvasWidth/canvasHeight);
            cameras.at(3)->setAspectRatio(canvasWidth/canvasHeight);
            
            cameras.at(0)->setViewPort(0, 0, canvasWidth/2,canvasHeight/2);
            cameras.at(1)->setViewPort(0, canvasHeight/2, canvasWidth/2, canvasHeight/2);
            cameras.at(2)->setViewPort(canvasWidth/2, canvasHeight/2, canvasWidth/2, canvasHeight/2);
            cameras.at(3)->setViewPort(canvasWidth/2, 0, canvasWidth/2, canvasHeight/2);
        }
    }
}

int ProtoWorld::getGeomCount() {
    return static_cast<int>(geoms.size());
}




/****************************************************
 *** global convenience functions Implementations ***
 ***************************************************/

namespace ijg {
    // single geometric obj
    //    void add(ProtoGeom3* geomObj){
    //        ProtoWorld* w = ProtoWorld::getInstance();
    //        w->add(geomObj);
    //    }
    
    // ADD ProtoGeomComposite pointers
    //void add(ProtoGeomComposite* compositeObj); // composite geometric obj
    
    // ADD shared pointer
    void add(std::shared_ptr<ProtoGeom3> geomObj){}
    
    // ADD raw pointer
    void add(const ProtoGeom3* geomObj){}
    
    //+++++ CAMERA +++++
    // ADD camera obs
    void add(std::unique_ptr<ProtoCamera> camera){}
    
    //+++++ LIGHTS +++++
    void add(std::unique_ptr<ProtoLight> light){}
    
    void add(ProtoLight* light){}
}

/************************************
 *** END function implementations ***
 ***********************************/





