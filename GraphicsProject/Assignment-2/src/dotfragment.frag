#version 330 core

uniform vec3 Color;

out vec4 FragColor;

void main() {
    if (dot(gl_PointCoord - 0.5, gl_PointCoord - 0.5) > 0.25)
        discard;
    else {
        FragColor = vec4(Color, 1.0f);
    }
}
