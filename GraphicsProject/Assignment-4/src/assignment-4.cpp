#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "errorcheck.h"
#include "ifile.h"
#include "glmutils.h"
#include "windowutils.h"
#include "shaderutils.h"
#include "camera.h"
#include "shader_path.h"



#define BUFFER_OFFSET(bytes) ((GLvoid*) (bytes))

/**
 * Global Variables
 * \param WindowWidth - the current width of the window
 * \param WindowHeight - the current height of the window
 * \param WindowTitle - the current title of the window
 * \param Vertices - an array containing the vertices of the triangle
 * \param NVertices - the number of vertices of the triangle
 * \param Normals - an array containing the vertex normals of the triangle
 * \param NNormals- the number of normals of the triangle
 */
int WindowWidth  = 500;
int WindowHeight = 500;
std::string WindowTitle("Assignment 4: Shading of a Triangle");

bool NeedsUpdate = true;

glm::vec3 Vertices[] = {
    glm::vec3(-33.978017f, -34.985076f,  50.214926f),
    glm::vec3( 84.192943f, -13.784394f, -50.214926f),
    glm::vec3(-16.236910f,  83.754546f, -50.214926f)
};
int NVertices = sizeof(Vertices) / sizeof(glm::vec3);


glm::vec3 Normals[] = {
    glm::vec3(0.0f),
    glm::vec3(0.0f),
    glm::vec3(0.0f)
};
int NNormals = sizeof(Normals) / sizeof(glm::vec3);

/**
 * Prints out a std::vector<glm::vec3> to an output stream
 * \param s - The output stream that should be printed to
 * \param data - The data that should be printed
 * \return the output stream s
 */
std::ostream& operator<<(std::ostream& s, std::vector<glm::vec3> const& data)
{
    for (int i = 0; i < data.size(); ++i) {
        s << data[i] << std::endl;
    }
    return s;
}

/**
 * Prints the transformed vertices
 * \param Vertices - the virtices (a std::vector) of the figure (here a triangle)
 * \param CTM - the Current Transformation Matrix
 */
void printtransformedvertices(glm::vec3 Vertices[3], glm::mat4x4 const& CTM)
{
    for (int i = 0; i < 3; ++i) {
        std::cout << "point: [" << Vertices[i] << "] transforms to: ";
        glm::vec4 transformedvertex = CTM * glm::vec4(Vertices[i], 1.0f);
        transformedvertex /= transformedvertex.w;
        glm::vec3 eucledian(transformedvertex.x, transformedvertex.y, transformedvertex.z);
        std::cout << "[" << eucledian << "]" << std::endl;
    }
    std::cout << std::endl;
}

/**
 * Callback function for window resize
 * \param Window - A pointer to the window beeing resized
 * \param width - The new width of the window
 * \param height - The new height of the window
 */
void ResizeCallback(GLFWwindow* Window, int width, int height)
{
    WindowWidth  = width;
    WindowHeight = height;
    int fwidth, fheight;
    glfwGetFramebufferSize(Window, &fwidth, &fheight);
    glViewport(0, 0, fwidth, fheight);
    NeedsUpdate = true;
}


/**
 * Callback function for keyboard shortcuts
 * \param Window - the window that created the callback
 * \param key - The key code
 * \param scancode - Don't know right now? It is badly documented in GLFW
 * \param action - Can be any of GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE
 * \param mods - Modifier keys pressed at the same time, like shift etc.
 */
void KeyboardCallback(GLFWwindow* Window, int key, int scancode, int action, int mode)
{
    if (action == GLFW_RELEASE) return;

    //std::cout << "--->KeyboardCallback(...)" << std::endl;

    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(Window, GL_TRUE);
        }
    }

    //std::cout << "<---KeyboardCallback(...)" << std::endl;
}

int main() 
{
    try {
        /*
         * Compute the normals of the triangle
         */
        glm::vec3 normal = glm::normalize(glm::cross(Vertices[1] - Vertices[0], Vertices[2] - Vertices[0]));

        Normals[0] = normal;
        Normals[1] = normal;
        Normals[2] = normal;

        /*
         * Viewing parameters
         */
        glm::vec3 vrp(0.0f, 0.0f, 125.0f);
        glm::vec3 vpn(0.0f, 0.0f, 1.0f);
        glm::vec3 vup(0.0f, 1.0f, 0.0f);
        glm::vec3 prp(0.0f, 0.0f, 50.0f);
        float F =   10.0f;
        float B = -800.0f;
        glm::vec2 lower_left(-25.0f, -25.0f);
        glm::vec2 upper_right(25.0f,  25.0f);

        Camera camera(vrp, vpn, vup, prp, lower_left, upper_right, F, B);
    
        glm::mat4x4 CTM = camera.CurrentTransformationMatrix();
        //std::cout << "CTM = " << std::endl << CTM << std::endl;

        // glm::mat4x4 invCTMtranspose = glm::transpose(camera.InvCurrentTransformationMatrix());
        //std::cout << "invCTMtranspose = " << std::endl << invCTMtranspose << std::endl;

        // glm::mat4x4 VertexTransformation = camera.ViewOrientation();
        // glm::mat4x4 NormalTransformation = glm::transpose(camera.InvViewOrientation());
    
        glm::vec3 AmbientLightColor(0.5f, 0.5f, 0.5f);
        glm::vec3 LightPosition(266.395325f, 274.291267f, -43.696048f);
        glm::vec3 LightColor(1.0f, 1.0f, 1.0f);

        glm::vec4 TmpEyePosition = camera.InvViewOrientation() * glm::vec4(camera.PRP(), 1.0f);
        TmpEyePosition = TmpEyePosition / TmpEyePosition.w;
        glm::vec3 EyePosition = glm::vec3(TmpEyePosition.x, TmpEyePosition.y, TmpEyePosition.z);

        float     Ka = 0.5f;
        // float     Ka = 0.0f;
        glm::vec3 Oa(0.0f, 1.0f, 0.0f);
        glm::vec3 AmbientColor(Ka * Oa);

        float     Kd = 0.75f;
        // float     Kd = 0.3f;
        glm::vec3 Od(0.0f, 1.0f, 0.0f);
        glm::vec3 DiffuseColor(Kd * Od);

        float     Ks = 0.9f;
        // float     Ks = 0.7f;
        glm::vec3 Os(1.0f, 1.0f, 1.0f);
        glm::vec3 SpecularColor(Ks * Os);

        float Shininess = 20.0f;
        // float Shininess = 50.0f;

        // GLenum Error = GL_NO_ERROR;

        // Initialize graphics
        InitializeGLFW();
        GLFWwindow* Window = CreateWindow(WindowWidth, WindowHeight, WindowTitle.c_str());
        if (!Window) {
            throw std::runtime_error("Could not create window");
        }
        if (Window != NULL) {
            glfwMakeContextCurrent(Window);
        }
        InitializeGLEW();
        InitializeOpenGL();
        glfwSwapBuffers(Window);

        // Setup a callback function for resize of the window
        glfwSetWindowSizeCallback(Window, ResizeCallback);

            // Setup a callback function for keyboard input - pres a key
        glfwSetKeyCallback(Window, KeyboardCallback);

        // Read and Compile the vertex program vertextransform.vert
        GLuint vertexprogID = CreateGpuProgram(shader_path + "vertextransform.vert", GL_VERTEX_SHADER);

        // Read and Compile the fragment program phong.frag
        GLuint fragmentprogID = CreateGpuProgram(shader_path + "phong.frag", GL_FRAGMENT_SHADER);

        // Create a triangleshader program and Link it with the vertex and fragment programs
        GLuint triangleshaderID = CreateShaderProgram(vertexprogID, fragmentprogID);

        // Now comes the OpenGL core part

        // This is where the triangle is initialized
        // User data is in the global variable Vertices, and the number of entries is in NVertices

        // Make a VertexArrayObject - it is used by the VertexBufferObjects, and it must be declared!
        GLuint TriangleArrayID;
        glGenVertexArrays(1, &TriangleArrayID);
        if (TriangleArrayID == 0) {
            throw std::runtime_error("Could not create VertexArray");
        }
        glBindVertexArray(TriangleArrayID);

        // Make a VertexbufferObject for the triangle vertices - it uses the previous VertexArrayBuffer!
        GLuint vertexbuffer;
        glGenBuffers(1, &vertexbuffer);
        if (vertexbuffer == 0) {
            throw std::runtime_error("Could not create VertexBuffer");
        }
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    
        // Give our vertices to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, NVertices * 3 * sizeof(float), glm::value_ptr(Vertices[0]), GL_STATIC_DRAW);

        // Initialize triangle vertex Attributes
        GLuint vertexattribute = glGetAttribLocation(triangleshaderID, "Vertex");
        glEnableVertexAttribArray(vertexattribute);
        glVertexAttribPointer(vertexattribute, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    
        // Make a VertexbufferObject for the triangle normals - it uses the previous VertexArrayBuffer!
        GLuint normalbuffer;
        glGenBuffers(1, &normalbuffer);
        if (normalbuffer == 0) {
            throw std::runtime_error("Could not create NormalBuffer");
        }
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    
        // Give our normals to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, NNormals * 3 * sizeof(float), glm::value_ptr(Normals[0]), GL_STATIC_DRAW);

        // Initialize triangle normal Attributes
        GLuint normalattribute = glGetAttribLocation(triangleshaderID, "Normal");
        glEnableVertexAttribArray(normalattribute);
        glVertexAttribPointer(normalattribute, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    
        // Validate the triangle shader program
        ValidateShader(triangleshaderID);

        glBindVertexArray(0);
    
        // Get locations of Uniforms
        GLuint ctm               = glGetUniformLocation(triangleshaderID, "CTM");
        GLuint ambientlightcolor = glGetUniformLocation(triangleshaderID, "AmbientLightColor");
        GLuint lightposition     = glGetUniformLocation(triangleshaderID, "LightPosition");
        GLuint lightcolor        = glGetUniformLocation(triangleshaderID, "LightColor");
        GLuint eyeposition       = glGetUniformLocation(triangleshaderID, "EyePosition");
        GLuint ambientcolor      = glGetUniformLocation(triangleshaderID, "AmbientColor");
        GLuint diffusecolor      = glGetUniformLocation(triangleshaderID, "DiffuseColor");
        GLuint specularcolor     = glGetUniformLocation(triangleshaderID, "SpecularColor");
        GLuint shininess         = glGetUniformLocation(triangleshaderID, "Shininess");

        // The main loop
        std::cout << std::endl;
        std::cout << "*****************************************************************" << std::endl;
        std::cout << "* Press ESC to finish the program                               *" << std::endl;
        std::cout << "*****************************************************************" << std::endl;
        std::cout << std::endl;

        while (!glfwWindowShouldClose(Window)) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Use TriangleArray
            glBindVertexArray(TriangleArrayID);
            
                // Use the Triangleshader
                glUseProgram(triangleshaderID);

                // Bind the underlying VertexArrayObject
                //glBindVertexArray(TriangleArrayID);   // It is very important to bind the Vertex Array Object!

                // Assign values to the uniforms
                glUniformMatrix4fv(ctm, 1, GL_FALSE, glm::value_ptr(CTM));
                glUniform3fv(ambientlightcolor, 1, glm::value_ptr(AmbientLightColor));
                glUniform3fv(lightposition,     1, glm::value_ptr(LightPosition));
                glUniform3fv(lightcolor,        1, glm::value_ptr(LightColor));
                glUniform3fv(eyeposition,       1, glm::value_ptr(EyePosition));
                glUniform3fv(ambientcolor,      1, glm::value_ptr(AmbientColor));
                glUniform3fv(diffusecolor,      1, glm::value_ptr(DiffuseColor));
                glUniform3fv(specularcolor,     1, glm::value_ptr(SpecularColor));
                glUniform1f(shininess, Shininess);
                if (NVertices > 0) {
                    glDrawArrays(GL_TRIANGLES, 0, NVertices);
                }
                glBindVertexArray(0);
            glUseProgram(0);
        
            glfwSwapBuffers(Window);

            std::stringstream errormessage;
            errormessage << "End of loop: " << "assignment-4.cpp" << ": " << __LINE__ << ": ";
            ErrorCheck(errormessage.str());

            glfwPollEvents();
        }
    }
    catch (std::exception const& exception) {
        std::cerr << "Exception: " << exception.what() << std::endl;
    }

    glfwTerminate();

    return 0;
}

