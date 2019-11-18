#version 330 core

uniform vec3  Color;

uniform vec3  AmbientLightColor;
uniform vec3  LightPosition;
uniform vec3  LightColor;

uniform vec3  EyePosition;

uniform vec3  FrontAmbientColor;
uniform vec3  FrontDiffuseColor;
uniform vec3  FrontSpecularColor;
uniform float FrontShininess;

uniform vec3  BackAmbientColor;
uniform vec3  BackDiffuseColor;
uniform vec3  BackSpecularColor;
uniform float BackShininess;

in vec3 WorldVertex;
in vec3 WorldNormal;

out vec4 FragColor;

vec3 computeambientcolor(in vec3 lightcolor, in vec3 ambientcolor)
{
    vec3 color = lightcolor * ambientcolor;
    return color;
}

vec3 computediffusecolor(in vec3 lightcolor, in vec3 diffusecolor, in float dotLN)
{
    vec3 color = lightcolor * diffusecolor * max(0.0f, dotLN);
    //vec3 color = lightcolor * diffusecolor * dotLN;
    return color;
}

vec3 computespecularcolor(in vec3 lightcolor, in vec3 specularcolor, in float dotRV, in float shininess)
{
    vec3 color = lightcolor * specularcolor * pow(max(0.0f, dotRV), shininess);
    //vec3 color = lightcolor * specularcolor * pow(dotRV, shininess);
    return color;
}


void main() {
    vec3 color = vec3(0.0f, 0.0f, 0.0f);

    vec3 N = normalize(WorldNormal);
    vec3 L = normalize(LightPosition - WorldVertex);
    vec3 V = normalize(EyePosition - WorldVertex);
    vec3 R = normalize((2.0f * dot(N, L)) * N - L);

    float dotLN = dot(L, N);
    float dotVN = dot(V, N);
    float dotVR = dot(V, R);

    if (gl_FrontFacing) {
	color += computeambientcolor(AmbientLightColor, FrontAmbientColor);
	color += computediffusecolor(LightColor, FrontDiffuseColor, dotLN);
	color += computespecularcolor(LightColor, FrontSpecularColor, dotVR, FrontShininess);
    }
    else {
	color += computeambientcolor(AmbientLightColor, BackAmbientColor);
	color += computediffusecolor(LightColor, BackDiffuseColor, -dotLN);
	color += computespecularcolor(LightColor, BackSpecularColor, dotVR, BackShininess);
    }

    FragColor = vec4(color, 1.0f);
}
