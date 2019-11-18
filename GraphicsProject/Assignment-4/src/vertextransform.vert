#version 330 core

uniform mat4x4 CTM;

in vec3 Vertex;
in vec3 Normal;

out vec3 WorldVertex;
out vec3 WorldNormal;

void main() {
    WorldVertex = Vertex;
    WorldNormal = Normal;
    
    // Implement your vertex program here - it must have CTM from the camera.
  
    gl_Position = vec4(0.0f, 0.0f, 0.0f, 1.0f); 	
}
