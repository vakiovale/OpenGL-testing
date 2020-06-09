#version 450 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 color;
layout (location = 2) uniform mat4 projection;
out vec4 fColor;

void main() {
    gl_Position = projection * vPosition;
    fColor = color;
}
