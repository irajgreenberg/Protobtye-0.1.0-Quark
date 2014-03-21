#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec3 VertexColor;

out vec3 Color;
out vec3 LightIntensity;

uniform vec4 light0Position;
uniform vec3 light0ReflectionConstant; // fraction of light scattering
uniform vec3 light0Intensity;


uniform mat4 gl_modelViewProjectionMatrix;
uniform mat4 RotationMatrix;


void main(){
    gl_Position = gl_modelViewProjectionMatrix * RotationMatrix * vec4(VertexPosition, 1.0);
    Color = VertexColor;
}