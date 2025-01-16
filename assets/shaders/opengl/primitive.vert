#version 450 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;
uniform mat4 mp;
out vec4 fragColor;

void main(){
    gl_Position = mp * vec4(aPos, 0, 1);
    fragColor = aColor;
}