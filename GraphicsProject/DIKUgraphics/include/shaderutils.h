#ifndef __SHADERUTILS_H__
#define __SHADERUTILS_H__

#define TRACE 1

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
#include "ifile.h"

/**
 * \file shaderutils.h
 */

/**
 * Reads the contents of a text file and returns in as a string.
 * \param FileName - A string containing the name of the file to be read.
 * \return A sting containing the contents of the file.
 */
std::string Read(std::string const& FileName);

/**
 * Creates and compiles a gpu program.
 * \param filename - The name of the file containing the gpu program.
 * \param programtype - The type of the gpu program.
 * \return An identifier for the gpu program.
 */
GLuint CreateGpuProgram(std::string const& filename, GLenum programtype);

/**
 * Creates and links a shader program.
 * \param vertexprogID - the ID of a compiled vertex program.
 * \param fragmentprogID - the ID of a compiled fragment program.
 * \return An identifier of the linked shader program.
 */
GLuint CreateShaderProgram(GLuint vertexprogID, GLuint fragmentprogID);

/**
 * Creates and links a shader program.
 * \param vertexprogFilename - the name of the file of the vertex program.
 * \param fragmentprogFilename - the name of the file of the fragment program.
 * \return An identifier for the gpu program.
 */
GLuint CreateShaderProgram(std::string const& vertexprogFilename, std::string const& fragmentprogFilename);

/**
 * Validates a shader program
 * \param shaderprogID - the ID of the shader program to be valuated
 * \param message - a message to be printed before validation
 */
void ValidateShader(GLuint shaderprogID, std::string message = "");

#endif
