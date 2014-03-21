#version 400

in vec3 Color;

// no more gl_FragColor, so we need to declare ourself
layout (location = 0) out vec4 FragColor;

void main(){
    FragColor = vec4(Color, 1.0);
}