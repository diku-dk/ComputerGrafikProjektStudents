#version 330 core

uniform float Scale;
uniform float PointSize;

in vec3 VertexPosition;

void main() {
    gl_PointSize = PointSize;
    gl_Position = vec4(Scale * VertexPosition.xy, VertexPosition.z, 1.0);
}
