/*!  \brief  ProtoProtoTexture.cpp: 2D texture class with w,h fields
 ProtoProtoTexture.cpp
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
 This class is templated to allow for varied single collection types
 This class is part of the group common (update)
 \sa NO LINK
 */

#include "ProtoTexture.h"



namespace ijg {

    std::ostream& operator<<(std::ostream& output, const ProtoTexture& texture) {
        output << "texture2.textureURL: " << texture.textureURL <<
                ", texture2.w: " << texture.w <<
                ", texture2.h: " << texture.h <<
                ", texture2.textureID: " << texture.textureID;
        return output;
    }

}

using namespace ijg;

ProtoTexture::ProtoTexture() {
    textureURL = "";
}

// one being used
ProtoTexture::ProtoTexture(const std::string& textureURL, GLenum image_format, GLint internal_format, GLint level, GLint border):
textureURL(textureURL), image_format(image_format), internal_format(internal_format), level(level), border(border)  {
    std::cout << "texture loading = " <<  init() << std::endl;
}



ProtoTexture::ProtoTexture(const std::string& textureURL, GLuint w, GLuint h, bool isWrap) :
textureURL(textureURL), w(w), h(h), isWrap(isWrap) {

    if (w > 0 && h > 0 && textureURL != "") {
        // texture creation/loading code from: 
        // http://www.nullterminator.net/gltexture.html

        unsigned char* data;
        FILE * file;

        // allocate buffer
        data = new unsigned char[w * h * 3];

        // open texture data
        file = fopen(textureURL.c_str(), "rb");
        if (file == NULL) std::cout << "no file data";

        // read texture data
        fread(data, w * h * 3, 1, file);
        // std::cout << "texture size = " << ftell(file) << std::endl;
        fclose(file);

        // allocate a texture name
        glGenTextures(1, &textureID);

        // select our current texture
        glBindTexture(GL_TEXTURE_2D, textureID);


        // select modulate to mix texture with color for shading
        //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        // when texture area is small, bilinear filter the closest MIP map
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                GL_LINEAR_MIPMAP_NEAREST);
        // when texture area is large, bilinear filter the first MIP map
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // if wrap is true, the texture wraps over at the edges (repeat)
        //       ... false, the texture ends at the edges (clamp)
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                isWrap ? GL_REPEAT : GL_CLAMP);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                isWrap ? GL_REPEAT : GL_CLAMP);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // give opengl the texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        // build our texture mipmaps
        //gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, data);

        // free memory
        delete [] data;
    }
}

ProtoTexture::ProtoTexture(unsigned char*& data, GLuint w, GLuint h, bool isWrap) {
    //Now that we have loaded our texture data from the RAW file, we can call the GLU(OpenGL Utility) function gluBuild2DMipmaps.

    // allocate a texture name
    glGenTextures(1, &textureID);

    // select our current texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // select modulate to mix texture with color for shading
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // when texture area is small, bilinear filter the closest MIP map
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_LINEAR_MIPMAP_NEAREST);
    // when texture area is large, bilinear filter the first MIP map
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            isWrap ? GL_REPEAT : GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
            isWrap ? GL_REPEAT : GL_CLAMP);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // give opengl the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    // build our texture mipmaps
    //gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, data);
}

ProtoTexture::ProtoTexture(std::vector<unsigned char>& data, GLuint w, GLuint h, bool isWrap) {
    //Now that we have loaded our texture data from the RAW file, we can call the GLU(OpenGL Utility) function gluBuild2DMipmaps.

    // allocate a texture name
    glGenTextures(1, &textureID);

    // select our current texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // select modulate to mix texture with color for shading
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // when texture area is small, bilinear filter the closest MIP map
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_LINEAR_MIPMAP_NEAREST);
    // when texture area is large, bilinear filter the first MIP map
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            isWrap ? GL_REPEAT : GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
            isWrap ? GL_REPEAT : GL_CLAMP);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // give opengl the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);

    // build our texture mipmaps
    //gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, data);
}

// brings in packed 32 bit packed int array of color values
ProtoTexture::ProtoTexture(const int* packedData32, GLuint w, GLuint h, bool isWrap) {
    // packedData32 stored as ABGR 
    int len = w*h;
    std::vector<unsigned char> data;
    data.resize(len * 3);

    int k = 0;
    for (int i = 0; i < len; ++i) {
        // shift desired bits to right and bitwise "AND" them.
        data.at(k++) = packedData32[i] & 0xFF; // get r
        data.at(k++) = packedData32[i] >> 8 & 0xFF; // get g
        data.at(k++) = packedData32[i] >> 16 & 0xFF; // get b
    }

    // allocate a texture name
    glGenTextures(1, &textureID);

    // select our current texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // select modulate to mix texture with color for shading
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // when texture area is small, bilinear filter the closest MIP map
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_LINEAR_MIPMAP_NEAREST);
    // when texture area is large, bilinear filter the first MIP map
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
            isWrap ? GL_REPEAT : GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
            isWrap ? GL_REPEAT : GL_CLAMP);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // give opengl the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);

    // build our texture mipmaps
    //gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, data);
}

bool ProtoTexture::init() {
    if (textureURL != "") {
        
        // FreeImage implementaiont from:
        //Singleton Texture Manager class
        //Written by Ben English
        //benjamin.english@oit.edu
        
        //image format
        FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
        //pointer to the image, once loaded
        FIBITMAP *dib(0);
        //pointer to the image data
        BYTE* imageData(0);
        //image width and height
        unsigned int width(0), height(0);
        //OpenGL's image ID to map to
        GLuint gl_texID;
        
        //check the file signature and deduce its format
        const char* fileURL = textureURL.c_str();
        fif = FreeImage_GetFileType(fileURL, 0);
        //if still unknown, try to guess the file format from the file extension
        if(fif == FIF_UNKNOWN)
            fif = FreeImage_GetFIFFromFilename(fileURL);
        //if still unkown, return failure
        if(fif == FIF_UNKNOWN)
            return false;
        
        //check that the plugin has reading capabilities and load the file
        if(FreeImage_FIFSupportsReading(fif))
            dib = FreeImage_Load(fif, fileURL);
        //if the image failed to load, return failure
        if(!dib)
            return false;
        
        //retrieve the image data
        imageData = FreeImage_GetBits(dib);
        //get the image width and height
        width = FreeImage_GetWidth(dib);
        height = FreeImage_GetHeight(dib);
        std::cout << "image width = " << width << std::endl;
        std::cout << "image height = " << height << std::endl;
        //if this somehow one of these failed (they shouldn't), return failure
        if((imageData == 0) || (width == 0) || (height == 0))
            return false;
        
        
        // texture creation/loading code from:
        // http://www.nullterminator.net/gltexture.html
        
//        unsigned char* data;
//        FILE * file;
//        
//        // allocate buffer
//        data = new unsigned char[w * h * 3];
//        
//        // open texture data
//        file = fopen(textureURL.c_str(), "rb");
//        if (file == NULL) std::cout << "no file data";
//        
//        // read texture data
//        fread(data, w * h * 3, 1, file);
//        // std::cout << "texture size = " << ftell(file) << std::endl;
//        fclose(file);
        
        // allocate a texture name
        glGenTextures(1, &textureID);
        
        // select our current texture
        glBindTexture(GL_TEXTURE_2D, textureID);
        
        
        // select modulate to mix texture with color for shading
        //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        
        // when texture area is small, bilinear filter the closest MIP map
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR_MIPMAP_NEAREST);
        // when texture area is large, bilinear filter the first MIP map
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        // if wrap is true, the texture wraps over at the edges (repeat)
        //       ... false, the texture ends at the edges (clamp)
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                        isWrap ? GL_REPEAT : GL_CLAMP);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                        isWrap ? GL_REPEAT : GL_CLAMP);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        
        // give opengl the texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
        
        // build our texture mipmaps
        //gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_RGB, GL_UNSIGNED_BYTE, data);
        
        // free memory
        //delete [] data;
        
        //Free FreeImage's copy of the data
        FreeImage_Unload(dib);
        
        //return success
        return true;
    }


}



