#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
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
#include "triangle.h"
#include "shader_path.h"

/**
 * \file
 */

/**
 * defines what should be drawn
 * \param GRID - if defined a grid is drawn.
 * \param TESTLINE - if defined the control line is drawn.
 * \param DOTLINE - if defined the approximated line is drawn as dots.
 */
#define GRID 1
#define TESTTRIANGLE 1
#define DOTTRIANGLE 1
 
/**
 * Global Variables
 * \param xmin - the minimum x-coordinate.
 * \param xmax - the maximum x-coordinate.
 * \param ymin - the minimum y-coordinate.
 * \param ymax - the maximum y-coordinate.
 * \param x_1 - the x-coordinate of the first fixed point of the triangle
 * \param y_1 - the y-coordinate of the first fixed point of the triangle
 * \param x_2 - the x-coordinate of the second fixed point of the triangle
 * \param y_2 - the y-coordinate of the second fixed point of the triangle
 * \param x_3 - the x-coordinate of the varying point of the triangle
 * \param y_3 - the y-coordinate of the varying point of the triangle
 * \param WindowWidth - the current width of the window
 * \param WindowHeight - the current height of the window
 * \param WindowTitle - the current title of the window
 * \param NGridLines - the number of gridlines
 * \param PointSize - the pointsize
 * \param CoordinatesChaged - true if the arrow keya has been pressed, false otherwize
 * \param NeedsUpdate - true if the window needs to be updated - keypress or window resize,
 *                      false otherwize
 */
int xmin = -9;
int xmax =  9;
int ymin = -9;
int ymax =  9;
int x_1  = -5;
int y_1  = -6;
int x_2  =  6;
int y_2  =  4;
int x_3  = -2;
int y_3  =  3;

int WindowWidth  = 500;
int WindowHeight = 500;
std::string WindowTitle("Assignment 2: Scanconvertion of triangles");

int   NGridLines = 21;
float PointSize  = 1.0;

bool CoordinatesChanged = false;
bool NeedsUpdate        = true;

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
    // Set the point size - make the size of the dot be a little smaller than the minimum distance
    // between the grid lines
    WindowWidth  = width;
    WindowHeight = height;
    float dist = std::min(WindowWidth, WindowHeight);
    float pointsize = dist / NGridLines;
    PointSize = pointsize;
    int fwidth, fheight;
    glfwGetFramebufferSize(Window, &fwidth, &fheight);
    glViewport(0, 0, fwidth, fheight);
    NeedsUpdate = true;
}

/**
 * Change the coordinates of a vertex depending on the arrow key and the modifier key
 * \param x - the x-coordinate of the vertex
 * \param y - the y-coordinate of the vertex
 * \param key - the arrow key that was pressed
 * \return x - there is no actual return value but the x-parameter is modified according to the key-value
 * \return y - there is no actual return value but the y-parameter is modified according to the key-value
 */
void ChangeVertex(int& x, int& y, int key)
{
    switch (key) {
        case GLFW_KEY_RIGHT:
            ++x;
            if (x > xmax) x = xmax;
            break;
        case GLFW_KEY_UP:
            ++y;
            if (y > ymax) y = ymax;
            break;
        case GLFW_KEY_LEFT:
            --x;
            if (x < xmin) x = xmin;
            break;
        case GLFW_KEY_DOWN:
            --y;
            if (y < ymin) y = ymin;
    }
    CoordinatesChanged = true;
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
            CoordinatesChanged = false;
        }
        switch (mode) {
            case GLFW_MOD_SHIFT:
                ChangeVertex(x_1, y_1, key);
                break;
            case GLFW_MOD_ALT:
                ChangeVertex(x_2, y_2, key);
                break;
            default:
                ChangeVertex(x_3, y_3, key);
        }
    }
}

/**
 * Initialize GLFW
 */
void InitializeGLFW()
{
    if (!glfwInit()) {
        throw std::runtime_error("Glfw Failed to initialize");
    }

    // Set up some hints for the window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

/**
 * Creates a graphics window and creates two callbacks to Keyboard and Resize.
 * \param WindowWidth - The width of the window.
 * \param WindowHeight - The height of the window.
 * \param WindowTitle - The title of the window.
 * \return An identifier for the window.
 */
GLFWwindow* CreateWindow(int WindowWidth, int WindowHeight,
                         std::string const& WindowTitle)
{
    GLFWwindow* WindowID;

    WindowID = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle.c_str(), NULL, NULL);
    if (!WindowID) {
        throw std::runtime_error("Could not create window");
    }
    if (WindowID != NULL) {
        glfwMakeContextCurrent(WindowID);
    }

    // Setup a callback function for resize of the window
    glfwSetWindowSizeCallback(WindowID, ResizeCallback);

    // Setup a callback function for keyboard input - pres a key
    glfwSetKeyCallback(WindowID, KeyboardCallback);
    
    return WindowID;
}

/**
 * Initializes GLEW.
 */
void InitializeGLEW()
{
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::ostringstream errmess;
        errmess << "GlfwWindow::Initialize(): "
                << "GLEW failed to initialize: "
                << glewGetErrorString(err) << ", (" << err << ") \n"
                << "Status, Using GLEW version: " << glewGetString(GLEW_VERSION)
                << std::endl;
        throw std::runtime_error(errmess.str());
    }

    // Clear any system errors if any
    ErrorClear("Right after glewInit()");
}

/**
 * Initializes OpenGL.
 */
void InitializeOpenGL()
{
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); // You might change this when the transformations are in place!
    glDrawBuffer(GL_BACK);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * Reads the contents of a text file and returns in as a string.
 * \param FileName - A string containing the name of the file to be read.
 * \return A sting containing the contents of the file.
 */
std::string Read(std::string const& FileName)
{
    std::string resultprog;
    InputFile Data(FileName);
    while (!Data.eof()) {
        std::string line;
        std::getline(Data, line);
        if (line.size() > 0) {
            resultprog += line + '\n';
        }
    }
    if (resultprog.size() <= 0) {
        std::ostringstream errormessage;
        errormessage << "No program found in file: " << FileName << std::endl;
        throw std::runtime_error(errormessage.str().c_str());
    }
    return resultprog;
}

/**
 * Creates and compiles a gpu program.
 * \param filename - The name of the file containing the gpu program.
 * \param programtype - The type of the gpu program.
 * \return An identifier for the gpu program.
 */
GLuint CreateGpuProgram(std::string const& filename, GLenum programtype)
{
    GLuint gpuprogID;

    std::string gpuprogram = Read(filename);
    gpuprogID = glCreateShader(programtype);
    if (gpuprogID == 0) {
        std::ostringstream errormessage;
        errormessage << "The gpu program could not be created" << std::endl;
        throw std::runtime_error(errormessage.str().c_str());
    }

    GLchar const* gpuprogramsrc[1];
    gpuprogramsrc[0] = gpuprogram.c_str();
    GLint gpulengths[1];
    gpulengths[0] = gpuprogram.size();
    
    glShaderSource(gpuprogID, 1, gpuprogramsrc, gpulengths);
    glCompileShader(gpuprogID);
    
    GLint gpusuccess = 0;
    glGetShaderiv(gpuprogID, GL_COMPILE_STATUS, &gpusuccess);

    if (!gpusuccess) {
        GLchar InfoLog[1024] = { 0 };
        glGetShaderInfoLog(gpuprogID, sizeof(InfoLog), NULL, InfoLog);
    
        std::ostringstream errormessage;
        errormessage << "Error compiling gpu program in file: " << filename << ". " << InfoLog << std::endl;
        throw std::runtime_error(errormessage.str().c_str());
    }
    
    return gpuprogID;
}

/**
 * Creates and links a shader program.
 * \param vertexprogID - the ID of a compiled vertex program.
 * \param fragmentprogID - the ID of a compiled fragment program.
 * \return An identifier of the linked shader program.
 */
GLuint CreateShaderProgram(GLuint vertexprogID, GLuint fragmentprogID)
{
    GLuint shaderprogID = glCreateProgram();
    if (shaderprogID == 0) {
        std::ostringstream errormessage;
        errormessage << "Could not create shaderprogram" << std::endl;
        throw std::runtime_error(errormessage.str());
    }
    glAttachShader(shaderprogID, vertexprogID);
    glAttachShader(shaderprogID, fragmentprogID);

    GLint shaderprogsuccess = 0;
    glLinkProgram(shaderprogID);
    glGetProgramiv(shaderprogID, GL_LINK_STATUS, &shaderprogsuccess);
    if (!shaderprogsuccess) {
        GLchar InfoLog[1024] = { 0 };
        glGetProgramInfoLog(shaderprogID, sizeof(InfoLog), NULL, InfoLog);

        std::ostringstream errormessage;
        errormessage << "Error linking shaderprogram: " << InfoLog << std::endl;
        throw std::runtime_error(errormessage.str().c_str());
    }
    glDetachShader(shaderprogID, vertexprogID);
    glDetachShader(shaderprogID, fragmentprogID);
    
    return shaderprogID;
}

/**
 * Validates a shader program
 * \param shaderprogID - the ID of the shader program to be valuated
 * \param message - a message to be printed before validation
 */
void ValidateShader(GLuint shaderprogID, std::string message = "")
{
    std::clog << message << std::endl;
    
    GLint gridvalidationsuccess = 0;
    glValidateProgram(shaderprogID);
    glGetProgramiv(shaderprogID, GL_VALIDATE_STATUS, &gridvalidationsuccess);
    if (!gridvalidationsuccess) {
        GLchar InfoLog[1024] = { 0 };
        glGetProgramInfoLog(shaderprogID, sizeof(InfoLog), NULL, InfoLog);

        std::ostringstream errormessage;
        errormessage << "Error validating shader program failed: "  << InfoLog << std::endl;
        throw std::runtime_error(errormessage.str().c_str());
    }
}

/**
 * Generates quadratic grid
 */
std::vector<glm::vec3> GenerateGridLines()
{
    std::vector<glm::vec3> lines;

    for (float i = xmin; i <= xmax; i += 1.0f) {
        lines.push_back(glm::vec3(xmin, i, -0.05f));
        lines.push_back(glm::vec3(xmax, i, -0.05f));

        lines.push_back(glm::vec3(i, ymin, -0.05f));
        lines.push_back(glm::vec3(i, ymax, -0.05f));
    }
    return lines;
}

/**
 * Creates the a buffer containing the vertices of the ideal triangle
 * \param x_1 - the x-coordinate of the first fixed point of the triangle
 * \param y_1 - the y-coordinate of the first fixed point of the triangle
 * \param x_2 - the x-coordinate of the second fixed point of the triangle
 * \param y_2 - the y-coordinate of the second fixed point of the triangle
 * \param x_3 - the x-coordinate of the varying point of the triangle
 * \param y_3 - the y-coordinate of the varying point of the triangle
 * \return A std::vector which contains the coordinates of the vertices of the triangle
 */
std::vector<glm::vec3> GenererateTestTriangle(int x_1, int y_1, int x_2, int y_2, int x_3, int y_3)
{
    std::vector<glm::vec3> vertices;
    
    vertices.push_back(glm::vec3(float(x_1), float(y_1), -0.1f));
    vertices.push_back(glm::vec3(float(x_2), float(y_2), -0.1f));
    vertices.push_back(glm::vec3(float(x_3), float(y_3), -0.1f));
    
    return vertices;
}

/**
 * Scanconverts a triangle, i.e. computes the pixels that represents the approximated triangle.
 * \param x_1 - the x-coordinate of the first vertex.
 * \param y_1 - the y-coordinate of the first vertex.
 * \param x_2 - the x-coordinate of the second vertex.
 * \param y_2 - the y-coordinate of the second vertex.
 * \param x_3 - the x-coordinate of the third vertex.
 * \param y_3 - the y-coordinate of the third vertex.
 * \return A std::vector which contains the coordinates of the pixels of the triangle.
 */
std::vector<glm::vec3> GenerateTrianglePixels(int x_1, int y_1, int x_2, int y_2, int x_3, int y_3)
{
    std::vector<glm::vec3> pixels;

    triangle_rasterizer triangle(x_1, y_1, x_2, y_2, x_3, y_3);

    pixels = triangle.all_pixels();

    CoordinatesChanged = false;

    return pixels;
}


int main() 
{
    try {
    // GLenum Error = GL_NO_ERROR;

        // Initialize the graphics
        InitializeGLFW();
        GLFWwindow* Window = CreateWindow(WindowWidth, WindowHeight, WindowTitle.c_str());
        InitializeGLEW();
        InitializeOpenGL();
        glfwSwapBuffers(Window);

        // Read and Compile the vertex program vertexscale.vert
        GLuint vertexprogID = CreateGpuProgram(shader_path + "vertexscale.vert", GL_VERTEX_SHADER);

        // Read and Compile the fragment program linefragment.frag
        GLuint linefragmentprogID = CreateGpuProgram(shader_path + "linefragment.frag", GL_FRAGMENT_SHADER);

        // Create a lineshader program and Link it with the vertex and linefragment programs
        GLuint lineshaderID = CreateShaderProgram(vertexprogID, linefragmentprogID);

        // Read and Compile the fragment program dotfragment.frag
        GLuint dotfragmentprogID = CreateGpuProgram(shader_path + "dotfragment.frag", GL_FRAGMENT_SHADER);

        // Create dotshader program and Link it with the vertex and dotfragment programs
        GLuint dotshaderID = CreateShaderProgram(vertexprogID, dotfragmentprogID);
    
        // Now comes the OpenGL core part

        // This is where the grid is initialized

        // User data
        std::vector<glm::vec3> GridLines;
        GridLines = GenerateGridLines();
        //std::cout << GridLines << std::endl;

        // Make a VertexArrayObject - it is used by the VertexArrayBuffer, and it must be declared!
        GLuint GridVertexArrayID;
        glGenVertexArrays(1, &GridVertexArrayID);
        glBindVertexArray(GridVertexArrayID);

        // Make a GridvertexbufferObject - it uses the previous VertexArrayBuffer!
        GLuint gridvertexbuffer;
        glGenBuffers(1, &gridvertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, gridvertexbuffer);
    
        // Give our vertices to OpenGL.
        if (GridLines.size() > 0) {
            glBufferData(GL_ARRAY_BUFFER, GridLines.size() * sizeof(float) * 3, &(GridLines[0][0]), GL_STATIC_DRAW);
        }

        // Validate the line shader program
        ValidateShader(lineshaderID, "Validating the lineshader");
    
        // Get locations of Uniforms
        GLuint linevertexscale     = glGetUniformLocation(lineshaderID, "Scale");
        GLuint linevertexpointsize = glGetUniformLocation(lineshaderID, "PointSize");
        GLuint linefragmentcolor   = glGetUniformLocation(lineshaderID, "Color");


        // Initialize grid Attributes
        GLuint linearvertexattribute = glGetAttribLocation(lineshaderID, "VertexPosition");
        glVertexAttribPointer(linearvertexattribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // Unbind the vertex array
        glBindVertexArray(0);


        // This is where the TestLine is initialized

        // User data
        std::vector<glm::vec3> TestTriangle;
        TestTriangle = GenererateTestTriangle(x_1, y_1, x_2, y_2, x_3, y_3);
        //std::cout << TestTriangle << std::endl;

        // Make a VertexArrayObject - it is used by the VertexArrayBuffer, and it must be declared!
        GLuint TestTriangleVertexArrayID;
        glGenVertexArrays(1, &TestTriangleVertexArrayID);
        glBindVertexArray(TestTriangleVertexArrayID);

        // Make a VertexBufferObject - it uses the previous VertexArrayBuffer!
        GLuint testtrianglebuffer;
        glGenBuffers(1, &testtrianglebuffer);
        glBindBuffer(GL_ARRAY_BUFFER, testtrianglebuffer);

        // Supply the data to the GPU
        if (TestTriangle.size() > 0) {
            glBufferData(GL_ARRAY_BUFFER, TestTriangle.size() * sizeof(float) * 3, &(TestTriangle[0][0]), GL_STATIC_DRAW);
        }

        // Initialize grid Attributes
        GLuint testtriangleattribute = glGetAttribLocation(lineshaderID, "VertexPosition");
        glVertexAttribPointer(testtriangleattribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // Unbind the vertex array
        glBindVertexArray(0);


        // This where the dots of the lines initialized

        // User data
        std::vector<glm::vec3> TrianglePixels;
        TrianglePixels = GenerateTrianglePixels(x_1, y_1, x_2, y_2, x_3, y_3);
        //std::cout << TrianglePixels << std::endl;

        // Make a VertexArrayObject - it is used by the VertexArrayBuffer, and it must be declared!
        GLuint PixelVertexArrayID;
        glGenVertexArrays(1, &PixelVertexArrayID);
        glBindVertexArray(PixelVertexArrayID);

        // Make a VertexBufferObject - it uses the previous VertexArrayBuffer!
        GLuint dotvertexbuffer;
        glGenBuffers(1, &dotvertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, dotvertexbuffer);

        // Give our vertices to OpenGL.
        if (TrianglePixels.size() > 0) {
            glBufferData(GL_ARRAY_BUFFER, TrianglePixels.size() * sizeof(float) * 3, &(TrianglePixels[0][0]), GL_STATIC_DRAW);
        }
        
        // Validate the dot shader program
        ValidateShader(dotshaderID, "Validating the dotshader");
    
        // Get locations of Dot Uniforms
        GLuint dotvertexscale     = glGetUniformLocation(dotshaderID, "Scale");
        GLuint dotvertexpointsize = glGetUniformLocation(dotshaderID, "PointSize");
        GLuint dotfragmentcolor   = glGetUniformLocation(dotshaderID, "Color");

        // Initialize dot Attributes
        GLuint dotvertexattribute = glGetAttribLocation(dotshaderID, "VertexPosition");
        glVertexAttribPointer(dotvertexattribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // Unbind the vertex array
        glBindVertexArray(0);

        
        // Set the point size - make the size of the dot be a little smaller than the minimum distance
        // between the grid lines
        glEnable(GL_PROGRAM_POINT_SIZE);
        float dist = std::min(WindowWidth, WindowHeight);
        float pointsize = dist / NGridLines;
        //glPointSize(pointsize);
        PointSize = pointsize;
        // std::cout << "PointSize = " << PointSize << std::endl;

        // The main loop
        std::cout << std::endl;
        std::cout << "*****************************************************************" << std::endl;
        std::cout << "* Use the arrow keys to manipulate the vertices of the triangle *" << std::endl;
        std::cout << "* All three vertices can be modified.                           *" << std::endl;
        std::cout << "* It is done with the arrow straitht arrow keys, and also by    *" << std::endl;
        std::cout << "* simultaneously pressing one of the modifier keys:             *" << std::endl;
        std::cout << "* Shift or Alt                                                  *" << std::endl;
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
                glUniform1f(linevertexscale, 0.1f);
                glUniform1f(linevertexpointsize, PointSize);
                glUniform3f(linefragmentcolor, 0.0f, 0.0f, 1.0f);

                glBindVertexArray(GridVertexArrayID);
                glEnableVertexAttribArray(linearvertexattribute);
                if (GridLines.size() > 0) {
                    glDrawArrays(GL_LINES, 0, GridLines.size());
                }
                glDisableVertexAttribArray(linearvertexattribute);
                glUseProgram(0);


                glUseProgram(lineshaderID);
                glUniform1f(linevertexscale, 0.1f);
                glUniform1f(linevertexpointsize, PointSize);
                glUniform3f(linefragmentcolor, 1.0f, 1.0f, 1.0f);

                glBindVertexArray(TestTriangleVertexArrayID);
                glEnableVertexAttribArray(testtriangleattribute);
                if (CoordinatesChanged) {
                    TestTriangle = GenererateTestTriangle(x_1, y_1, x_2, y_2, x_3, y_3);
                    glBindBuffer(GL_ARRAY_BUFFER, testtrianglebuffer);
                    if (TestTriangle.size() > 0) {
                        glBufferData(GL_ARRAY_BUFFER, TestTriangle.size() * sizeof(float) * 3, &(TestTriangle[0][0]),
                                     GL_STATIC_DRAW);
                    }
                }
                if (TestTriangle.size() > 0) {
                    glDrawArrays(GL_LINE_LOOP, 0, TestTriangle.size());
                }
                glDisableVertexAttribArray(testtriangleattribute);
                glUseProgram(0);


                glUseProgram(dotshaderID);
                glUniform1f(dotvertexscale, 0.1f);
                // glUniform1f(dotvertexpointsize, 2.0f * PointSize);
                glUniform1f(dotvertexpointsize, PointSize);
                glUniform3f(dotfragmentcolor, 0.0f, 0.0f, 0.0f);

                glBindVertexArray(PixelVertexArrayID);
                glEnableVertexAttribArray(dotvertexattribute);
                if (CoordinatesChanged) {
                    TrianglePixels = GenerateTrianglePixels(x_1, y_1, x_2, y_2, x_3, y_3);
                    glBindBuffer(GL_ARRAY_BUFFER, dotvertexbuffer);
                    if (TrianglePixels.size() > 0) {
                        glBufferData(GL_ARRAY_BUFFER, TrianglePixels.size() * sizeof(float) * 3, &(TrianglePixels[0][0]),
                                     GL_STATIC_DRAW);
                    }
                }
                if (TrianglePixels.size() > 0) {
                    glDrawArrays(GL_POINTS, 0, TrianglePixels.size());
                }
                glDisableVertexAttribArray(dotvertexattribute);
                glUseProgram(0);

                glfwSwapBuffers(Window);
                std::stringstream errormessage;
                errormessage << "End of loop: " << "assignment2.cpp" << ": " << __LINE__ << ": ";
                ErrorCheck(errormessage.str());
                CoordinatesChanged = false;
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

