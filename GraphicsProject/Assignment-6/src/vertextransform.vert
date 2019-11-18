#version 330 core

uniform mat4x4 CTM;
uniform mat4x4 invCTMtranspose;
uniform mat4x4 VertexTransformation;
uniform mat4x4 NormalTransformation;

in vec3 Vertex;
in vec3 Normal;

out vec3 WorldVertex;
out vec3 WorldNormal;

void main() {
    vec4 worldvertex = VertexTransformation * vec4(Vertex, 1.0f);
    if (worldvertex.w != 0.0f) {
	worldvertex /= worldvertex.w;
    }
    WorldVertex = worldvertex.xyz;

    vec4 worldnormal = NormalTransformation * vec4(Normal, 0.0f);
    if (worldnormal.w != 0.0f) {
	worldnormal /= worldnormal.w;
    }
    WorldNormal = worldnormal.xyz;

    gl_Position = CTM * VertexTransformation * vec4(Vertex, 1.0f);	
}
