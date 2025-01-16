#version 450 core

layout (location = 0) in vec4 aPosUV; // <vec2 pos, vec2 tex>

out vec2 TexCoords;
uniform mat4 proj;

void main(){
    gl_Position = proj * vec4(aPosUV.xy, 0, 1);
    TexCoords = aPosUV.zw;
}