#include "shaderutils.h"

/*
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

/*
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
    gpulengths[0] = GLuint(gpuprogram.size());
    
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

/*
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

/*
* Creates and links a shader program.
* \param vertexprogFilename - the name of the file of the vertex program.
* \param fragmentprogFilename - the name of the file of the fragment program.
* \return An identifier for the gpu program.
*/
GLuint CreateShaderProgram(std::string const& vertexprogFilename, std::string const& fragmentprogFilename)
{
    Trace("", "CreateShaderProgram(string&, string&)");

    GLuint vertexShaderID   = CreateGpuProgram(vertexprogFilename, GL_VERTEX_SHADER);
    GLuint fragmentShaderID = CreateGpuProgram(fragmentprogFilename, GL_FRAGMENT_SHADER);
    GLuint shaderprogramID  = CreateShaderProgram(vertexShaderID, fragmentShaderID);

    return shaderprogramID;
}

/*
 * Validates a shader program
 * \param shaderprogID - the ID of the shader program to be valuated
 * \param message - a message to be printed before validation
 */
void ValidateShader(GLuint shaderprogID, std::string message)
{
    if (message.size() > 0) {
        std::clog << message << std::endl;
    }
    
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
