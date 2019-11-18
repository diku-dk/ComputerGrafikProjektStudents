#include "windowutils.h"

/*
 * Initializes GLEW.
 */
void InitializeGLEW()
{
    Trace("", "initializeGLEW()");
    
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

/*
 * Initializes OpenGL.
 */
void InitializeOpenGL()
{
    Trace("", "initializeOpenGL()");
    
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glEnable(GL_DEPTH_TEST);
    glClearDepth(-1.0);
    //glDepthFunc(GL_GEQUAL); // You might change this when the transformations are in place!
    glDepthFunc(GL_GREATER);
    glDrawBuffer(GL_BACK);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/*
 * Initialize GLFW
 */
void InitializeGLFW()
{
    Trace("", "initializeGLFW()");
    
    if (!glfwInit()) {
        throw std::runtime_error("Glfw Failed to initialize");
    }

    // Set up some hints for the window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

/*
 * Creates a graphics window and creates two callbacks to Keyboard and Resize.
 * \param WindowWidth - The width of the window.
 * \param WindowHeight - The height of the window.
 * \param WindowTitle - The title of the window.
 * \return An identifier for the window.
 */
GLFWwindow* CreateWindow(int WindowWidth, int WindowHeight,
                         std::string const& WindowTitle)
{
    Trace("", "CreateWindow(int, int, string)");
          
    InitializeGLFW();
    
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
    
    InitializeGLEW();
    InitializeOpenGL();
    
    return WindowID;
}
