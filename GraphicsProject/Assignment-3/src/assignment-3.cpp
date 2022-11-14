#define _USE_MATH_DEFINES
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


/**
 * \file
 */

glm::vec3 housecolor(1.0f, 1.0f, 1.0f);

/**
 * Global Variables
 * \param WindowWidth - the current width of the window
 * \param WindowHeight - the current height of the window
 * \param WindowTitle - the current title of the window
 * \param NFigure - the current figure that should be shown
 * \param HouseVertices - the vertices of the house model
 * \param NHouseVertices - the number of entries of the house model
 * \param NeedsUpdate - true if the window needs to be updated
 */
int WindowWidth  = 500;
int WindowHeight = 500;
std::string WindowTitle("Assignment 3: Projection of a House");

int NFigure = 0;

glm::vec3 HouseVertices[] = {
    //Front wall
    glm::vec3( 0.0f,  0.0f, 54.0f),
    glm::vec3(16.0f,  0.0f, 54.0f),
    glm::vec3(16.0f,  0.0f, 54.0f),
    glm::vec3(16.0f, 10.0f, 54.0f),
    glm::vec3(16.0f, 10.0f, 54.0f),
    glm::vec3( 8.0f, 16.0f, 54.0f),
    glm::vec3( 8.0f, 16.0f, 54.0f),
    glm::vec3( 0.0f, 10.0f, 54.0f),
    glm::vec3( 0.0f, 10.0f, 54.0f),
    glm::vec3( 0.0f,  0.0f, 54.0f),
    //Back Wall
    glm::vec3( 0.0f,  0.0f, 30.0f),
    glm::vec3(16.0f,  0.0f, 30.0f),
    glm::vec3(16.0f,  0.0f, 30.0f),
    glm::vec3(16.0f, 10.0f, 30.0f),
    glm::vec3(16.0f, 10.0f, 30.0f),
    glm::vec3( 8.0f, 16.0f, 30.0f),
    glm::vec3( 8.0f, 16.0f, 30.0f),
    glm::vec3( 0.0f, 10.0f, 30.0f),
    glm::vec3( 0.0f, 10.0f, 30.0f),
    glm::vec3( 0.0f,  0.0f, 30.0f),
    //Sides
    glm::vec3( 0.0f,  0.0f, 54.0f),
    glm::vec3( 0.0f,  0.0f, 30.0f),
    glm::vec3(16.0f,  0.0f, 54.0f),
    glm::vec3(16.0f,  0.0f, 30.0f),
    glm::vec3(16.0f, 10.0f, 54.0f),
    glm::vec3(16.0f, 10.0f, 30.0f),
    glm::vec3( 8.0f, 16.0f, 54.0f),
    glm::vec3( 8.0f, 16.0f, 30.0f),
    glm::vec3( 0.0f, 10.0f, 54.0f),
    glm::vec3( 0.0f, 10.0f, 30.0f)
};
int NHouseVertices = sizeof(HouseVertices) / sizeof(glm::vec3);

bool NeedsUpdate = true;

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

    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(Window, GL_TRUE);
        }
        else {
            switch (key) {
                case '1':
                    NFigure = 0;
                    break;
                case '2':
                    NFigure = 1;
                    break;
                case '3':
                    NFigure = 2;
                    break;
                case '4':
                    NFigure = 3;
                    break;
                case '5':
                    NFigure = 4;
                    break;
                default:
                    std::cout << "No such figure: choosing figure 1" << std::endl;
                    NFigure = 0;
            }
        }
        NeedsUpdate = true;
    }
}

int main() 
{
    try {
        Camera camera[5];
        camera[0] = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                           glm::vec3(8.0f, 6.0f, 84.0f),
                           glm::vec2(-50.0f, -50.0f), glm::vec2(50.0f,  50.0f),
                           60.0f, 25.0f);
        camera[1] = Camera(glm::vec3(0.0f, 0.0f, 54.0f), glm::vec3(0.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f,  0.0f),
                           glm::vec3(8.0f, 6.0f, 30.0f),
                           glm::vec2( -1.0, -1.0), glm::vec2(17.0, 17.0),
                           1.0f, -35.0f);
        camera[2] = Camera(glm::vec3(16.0f, 0.0f, 54.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                           glm::vec3(20.0f, 25.0f, 20.0f),
                           glm::vec2(-20.0, -5.0), glm::vec2(20.0,  35.0),
                           1.0f, -35.0f);
        camera[3] = Camera(glm::vec3(16.0f, 0.0f, 54.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                           glm::vec3(0.0f, 25.0f, 20.0f * sqrt(2.0)),
                           glm::vec2(-20.0, -5.0), glm::vec2(20.0,  35.0),
                           1.0f, -35.0f);
        camera[4] = Camera(glm::vec3(16.0f, 0.0f, 54.0f), glm::vec3(1.0f, 0.0f, 1.0f),
                           glm::vec3( -sin(10.0 * M_PI / 180.0), cos(10.0 * M_PI / 180.0), sin(10.0 * M_PI / 180.0)),
                           glm::vec3( 0.0f, 25.0f, 20.0f * sqrt(2.0)),
                           glm::vec2( -20.0, -5.0), glm::vec2(20.0,  35.0),
                           1.0f, -35.0f);

        // Initialize the graphics
        InitializeGLFW();
        GLFWwindow* Window = CreateWindow(WindowWidth, WindowHeight, WindowTitle.c_str());
        InitializeGLEW();
        InitializeOpenGL();
        glfwSwapBuffers(Window);

        // Read and Compile the vertex program vertextransform.vert
        GLuint vertexprogID = CreateGpuProgram(shader_path + "vertextransform.vert", GL_VERTEX_SHADER);

        // Read and Compile the fragment program linefragment.frag
        GLuint linefragmentprogID = CreateGpuProgram(shader_path + "linefragment.frag", GL_FRAGMENT_SHADER);

        // Create a lineshader program and Link it with the vertex and linefragment programs
        GLuint lineshaderID = CreateShaderProgram(vertexprogID, linefragmentprogID);
    
        // Now comes the OpenGL core part

        // This is where the house is initialized
        // User data is in the global variable HouseVertices, and the number of entries
        // is in NHousevertices

        // Make a VertexArrayObject - it is used by the VertexArrayBuffer, and it must be declared!
        GLuint HouseVertexArrayID;
        glGenVertexArrays(1, &HouseVertexArrayID);
        glBindVertexArray(HouseVertexArrayID);

        // Make a HousevertexbufferObject - it uses the previous VertexArrayBuffer!
        GLuint housevertexbuffer;
        glGenBuffers(1, &housevertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, housevertexbuffer);
    
        // Give our vertices to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, NHouseVertices * 3 * sizeof(float), HouseVertices, GL_STATIC_DRAW);

        // Validate the shader program
        ValidateShader(lineshaderID, "Validating the lineshader");

        // Get locations of Uniforms
        GLuint housevertextransform   = glGetUniformLocation(lineshaderID, "CTM");
        GLuint housefragmentcolor     = glGetUniformLocation(lineshaderID, "Color");


        // Initialize Attributes
        GLuint housevertexattribute = glGetAttribLocation(lineshaderID, "VertexPosition");
        glVertexAttribPointer(housevertexattribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // The main loop
        std::cout << std::endl;
        std::cout << "*****************************************************************" << std::endl;
        std::cout << "* Press the characters: 1, 2, 3, 4, 5                           *" << std::endl;
        std::cout << "* to show the different figures                                 *" << std::endl;
        std::cout << "*                                                               *" << std::endl;
        std::cout << "* The Window can be resized using the mouse                     *" << std::endl;
        std::cout << "*                                                               *" << std::endl;
        std::cout << "* Press ESC to finish the program                               *" << std::endl;
        std::cout << "*****************************************************************" << std::endl;
        std::cout << std::endl;

        while (!glfwWindowShouldClose(Window)) {
            if (NeedsUpdate) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                glUseProgram(lineshaderID);
                if (NFigure < 5) {
                    glm::mat4x4 CTM = camera[NFigure].CurrentTransformationMatrix();
                    glUniformMatrix4fv(housevertextransform, 1, GL_FALSE, &CTM[0][0]);
                    glUniform3f(housefragmentcolor, housecolor.r, housecolor.g, housecolor.b);
                    glEnableVertexAttribArray(housevertexattribute);
                    glBindVertexArray(HouseVertexArrayID);
                    if (NHouseVertices > 0) {
                        glDrawArrays(GL_LINES, 0, NHouseVertices);
                    }
                    glDisableVertexAttribArray(housevertexattribute);
                }
                glUseProgram(0);

                glfwSwapBuffers(Window);
                std::stringstream errormessage;
                errormessage << "End of loop: " << "assignment3.cpp" << ": " << __LINE__ << ": ";
                ErrorCheck(errormessage.str());
                
                NeedsUpdate = false;
            }
            glfwPollEvents();
        }
    }
    catch (std::exception const& exception) {
        std::cerr << "Exception: " << exception.what() << std::endl;
    }

    glfwTerminate();

    return 0;
}
