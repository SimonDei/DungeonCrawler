#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aCol;

uniform mat4x4 projection;
uniform mat4x4 model;

out vec4 vCol;

void main() {
    vCol = vec4(aCol, 1.0);
    gl_Position = projection * model * vec4(aPos, 0.0, 1.0);
}