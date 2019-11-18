#include "errorcheck.h"

/*
 * Converts an OpenGL error code to a human readable text string
 * \param ErrorCode - the error code from the OpenGL system
 * \param Verbose - if false return a short error message, 
 *                  else if true return a more verbose error message 
 * \return - a human readable error message
 */
std::string ErrorMessage(GLenum ErrorCode, bool Verbose)
{
    Trace("", "ErrorMessage(GLenum, bool)");

    std::ostringstream errMessage;
    switch (ErrorCode) {
        case GL_NO_ERROR:
            errMessage << "no error";
            if (Verbose) {
                errMessage << "\nGlfwWindow: Error Code " << ErrorCode << ":" << std::endl
                           << "\tNo error has been recorded.";
            }
            break;
        case GL_INVALID_ENUM:
            errMessage << "invalid enumerant";
            if (Verbose) {
                errMessage << "\nGlfwWindow: Error Code " << ErrorCode << ":" << std::endl
                           << "\tAn unacceptable value is specified for an enumerated argument.";
                errMessage << "\n\tThe offending command is ignored and has no "
                           << "other side effect than to set the error flag.";
            }
            break;
        case GL_INVALID_VALUE:
            errMessage << "invalid value";
            if (Verbose) {
                errMessage << "\nGlfwWindow: Error Code " << ErrorCode << ":" << std::endl
                           << "\tA numeric argument is out of range.";
                errMessage << "\n\tThe offending command is ignored and has no "
                           << "other side effect than to set the error flag.";
            }
            break;
        case GL_INVALID_OPERATION:
            errMessage << "invalid operation";
            if (Verbose) {
                errMessage << "\nGlfwWindow: Error Code " << ErrorCode << ":" << std::endl
                           << "\tThe specified operation is not allowed in the current state.";
                errMessage << "\n\tThe offending command is ignored and has no "
                           << "other side effect than to set the error flag.";
            }
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            errMessage << "invalid framebuffer operation";
            if (Verbose) {
                errMessage << "\nGlfwWindow: Error Code " << ErrorCode << ":" << std::endl
                           << "\tThe framebuffer object is not complete.";
                errMessage << "\n\tThe offending command is ignored and has no "
                           << "other side effect than to set the error flag.";
            }
            break;
        case GL_OUT_OF_MEMORY:
            errMessage << "out of memory";
            if (Verbose) {
                errMessage << "\nGlfwWindow: Error Code " << ErrorCode << ":" << std::endl
                           << "\tThere is not enough memory left to execute the command.";
                errMessage << "\n\tThe state of the GL is undefined, "
                           << "except for the state of the error flags, after this error is recorded.";
            }
            break;
        case GL_STACK_UNDERFLOW:
            errMessage << "stack underflow";
            if (Verbose) {
                errMessage  << "\nGlfwWindow: Error Code " << ErrorCode << ":" << std::endl
                            << "\tAn attempt has been made to perform an operation that "
                            << "would cause an internal stack to underflow.";
            }
            break;
        case GL_STACK_OVERFLOW:
            errMessage << "stack overflow";
            if (Verbose) {
                errMessage << "\nGlfwWindow: Error Code " << ErrorCode << ":" << std::endl
                           << "\tAn attempt has been made to perform an operation that "
                           << "would cause an internal stack to overflow.";
            }
            break;
        default:
            errMessage << "GlfwWindow: Error Code " << ErrorCode << ": Unknown Error Code";
    }
    return errMessage.str();
}


/*
 * Clears any OpenGL errors.
 * \param Message - a string which should be written if any errors messages.
 * \param BeQuiet - if true no message is output, else an error message is output.
 */
void ErrorClear(std::string Message, bool BeQuiet)
{
    bool AnyErrors = false;
    GLenum ErrorCode = GL_NO_ERROR;
    std::ostringstream errormessage;
    errormessage << "ErrorClear(): " << Message << ": ";
    while ((ErrorCode = glGetError()) != GL_NO_ERROR) {
        AnyErrors = true;
        errormessage << ErrorMessage(ErrorCode);
    }
    if (AnyErrors) {
        if (!BeQuiet) {
            std::cerr << errormessage.str() << ": cleared" << std::endl;
        }
    }
}

/*
 * Checks if any errors occurred during processing of OpenGL requests
 * If an error has occurred an exception is thown.
 * \param Message - a message which is output before the actual error message.
 */
void ErrorCheck(std::string Message)
{
    bool AnyErrors = false;
    GLenum ErrorCode = GL_NO_ERROR;
    std::ostringstream errormessage;
    errormessage << "ErrorCheck(): " << Message << ": ";
    while ((ErrorCode = glGetError()) != GL_NO_ERROR) {
    AnyErrors = true;
    errormessage << ErrorMessage(ErrorCode);
    }
    if (AnyErrors) {
    throw std::runtime_error(errormessage.str());
    }
}
