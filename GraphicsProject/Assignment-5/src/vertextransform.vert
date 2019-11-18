#version 330 core

uniform mat4x4 CTM;
in vec3 VertexPosition;

void main() {
    gl_Position = CTM * vec4(VertexPosition, 1.0f);
}
