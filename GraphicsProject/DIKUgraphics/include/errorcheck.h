#ifndef __ERROR_CHECK__
#define __ERROR_CHECK__

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <sstream>
#include <string>

#include "GL/glew.h"

#include "traceinfo.h"

/**
 * \file errorcheck.h
 */

/**
 * Converts an OpenGL error code to a human readable text string
 * \param ErrorCode - the error code from the OpenGL system
 * \param Verbose - if false return a short error message, 
 *                  else if true return a more verbose error message 
 * \return - a human readable error message
 */
std::string ErrorMessage(GLenum ErrorCode, bool Verbose = false);

/**
 * Clears any OpenGL errors
 * \param Message - a string which should be written if any errors messages.
 * \param BeQuiet - if true no message is output, else an error message is output.
 */
void ErrorClear(std::string Message = "", bool BeQuiet = true);

/**
 * Checks if any errors occurred during processing of OpenGL requests
 * If an error has occurred an exception is thown.
 * \param Message - a message which is output before the actual error message.
 */
void ErrorCheck(std::string Message = "");

#endif
