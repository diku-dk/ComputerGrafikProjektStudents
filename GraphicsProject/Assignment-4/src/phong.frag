#version 330 core

uniform vec3 AmbientLightColor;
uniform vec3 LightPosition;
uniform vec3 LightColor;

uniform vec3 EyePosition;

uniform vec3  AmbientColor;
uniform vec3  DiffuseColor;
uniform vec3  SpecularColor;
uniform float Shininess;

in vec3 WorldVertex;
in vec3 WorldNormal;

out vec4 FragColor;

void main() {
    vec3 color = vec3(0.0f, 0.0f, 0.0f);

    // Implement your phong shader program here.


    FragColor = vec4(color, 1.0f);
}
