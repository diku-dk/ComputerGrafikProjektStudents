#ifndef __WINDOWUTILS_H__
#define __WINDOWUTILS_H__


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

#include "traceinfo.h"
#include "errorcheck.h"

/**
 * \file windowutils.h
 */

/**
 * ResizeCallback - function pointer declared in main program
 */
extern void ResizeCallback(GLFWwindow*, int, int);

/**
 * KeyboardCallback - function pointer declared in main program
 */
extern void KeyboardCallback(GLFWwindow*, int, int, int, int);

/**
 * Initializes GLEW.
 */
void InitializeGLEW();

/**
 * Initializes OpenGL.
 */
void InitializeOpenGL();

/**
 * Initialize GLFW
 */
void InitializeGLFW();

/**
 * Creates a graphics window and creates two callbacks to Keyboard and Resize.
 * \param WindowWidth - The width of the window.
 * \param WindowHeight - The height of the window.
 * \param WindowTitle - The title of the window.
 * \return An identifier for the window.
 */
GLFWwindow* CreateWindow(int WindowWidth, int WindowHeight,
                         std::string const& WindowTitle);

#endif
