/*!  \brief  ProtoShader.cpp: class for managing shaders
ProtoShader.cpp
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


#include "ProtoShader.h"
#include <string.h>
#include <iostream>

using namespace ijg;

ProtoShader::ProtoShader() {
}

ProtoShader::ProtoShader(const std::string& vShader, const std::string& fShader):
vShader(vShader), fShader(fShader){
	init();
}

void ProtoShader::init() {

	// initialize glew for Windows
#if defined(_WIN32) || defined(__linux__)
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif
	
    
    std::string url = ProtoUtility::getBuildPath();
    std::string vShaderURL = url+"/resources/shaders/"+vShader;
    std::string fShaderURL = url+"/resources/shaders/"+fShader;
    //std::cout << "vShaderURL = " << vShaderURL << std::endl;
    //std::cout << "fShaderURL = " << fShaderURL << std::endl;
    //std::string vShaderCodeStr = ProtoUtility::load(vShaderURL);
	std::string fShaderCodeStr = ProtoUtility::load(fShaderURL);
    
    
    std::string vShaderCodeStr = "#version 400 in vec3 VertexPosition; in vec3 VertexColor; out vec3 Color; void main() { Color = VertexColor; GL_Position = vec4(VertexPosition, 1.0); }";
    
	const GLchar* vShaderCode = vShaderCodeStr.c_str();
	const GLchar* fShaderCode = fShaderCodeStr.c_str();
	//std::cout << "vShaderCode = " << vShaderCode << std::endl;
	//std::cout << "fShaderCode = " << fShaderCode << std::endl;
    
	if (vShaderCode == NULL || fShaderCode == NULL) {
		std::cerr << "Either vertex shader or fragment shader file not found." << std::endl;
		return;
	}
    
    
    const char* vShaderCode2 = "uniform mat4 u_mvpMatrix;attribute vec4 a_position;attribute vec4 a_color;varying vec4 v_color;void main(){   gl_Position = u_mvpMatrix * a_position;   v_color = a_color;}";
    
    const char* fShaderCode2 = "varying vec4 v_color;void main() {	gl_FragColor = v_color;}";
    

	shader_vp = glCreateShader(GL_VERTEX_SHADER);
    if(0==shader_vp){
        std::cerr << "Error creating vertex shader"<< std::endl;
        return;
    }
    
	shader_fp = glCreateShader(GL_FRAGMENT_SHADER);
    if(0==shader_fp){
        std::cerr << "Error creating fragment shader"<< std::endl;
        return;
    }
    
    glShaderSource(shader_vp, 1, (const GLchar**)&vShaderCode2, 0);
	glShaderSource(shader_fp, 1, (const GLchar**)&fShaderCode2, 0);

	glCompileShader(shader_vp);
	glCompileShader(shader_fp);
    
    //Check shader for errors
    GLint shaderCompiled = GL_FALSE;
    glGetShaderiv( shader_vp, GL_COMPILE_STATUS, &shaderCompiled );
    if( shaderCompiled != GL_TRUE )
    {
        printf( "Unable to compile Vertex shader %d!\n\nSource:\n%s\n", shader_vp, vShaderCode );
        //printShaderLog( shader_vp );
        glDeleteShader( shader_vp );
        shader_vp = 0;
    }

    glGetShaderiv( shader_fp, GL_COMPILE_STATUS, &shaderCompiled );
    if( shaderCompiled != GL_TRUE )
    {
        printf( "Unable to compile fragment shader %d!\n\nSource:\n%s\n", shader_fp, fShaderCode );
        //printShaderLog( shader_vp );
        glDeleteShader( shader_fp );
        shader_fp = 0;
    }

    
    

	shader_id = glCreateProgram();
	glAttachShader(shader_id, shader_vp);
	glAttachShader(shader_id, shader_fp);

	glLinkProgram(shader_id);

}

ProtoShader::~ProtoShader() {
	glDetachShader(shader_id, shader_fp);
	glDetachShader(shader_id, shader_vp);

	glDeleteShader(shader_fp);
	glDeleteShader(shader_vp);
	glDeleteProgram(shader_id);
}

unsigned int ProtoShader::getID() {
	return shader_id;
}

void ProtoShader::bind() {
	glUseProgram(shader_id);
}

void ProtoShader::unbind() {
	glUseProgram(0);
}