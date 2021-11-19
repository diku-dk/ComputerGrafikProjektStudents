IF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    MESSAGE(
        FATAL_ERROR 
            "CMake generation is not allowed within the source directory!"
    )
ENDIF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})

CMAKE_MINIMUM_REQUIRED (VERSION 3.21 FATAL_ERROR)

PROJECT(GRAPHICS_PROJECT)

SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

IF (MSVC)
    ADD_DEFINITIONS(-D_SCL_SECURE_NO_WARNINGS)
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS) 
ENDIF()

# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/Include")
# FIND_PACKAGE (glm REQUIRED PATHS "/usr/local/include")
FIND_PACKAGE (GLM REQUIRED)
IF(GLM_FOUND) 
    # MESSAGE("Found GLM: ${GLM_DIR}")
ELSE(GLM_FOUND)
    MESSAGE(FATAL_ERROR, "Could not find GLM. We recommend using MacPort installation of GLM on Apple. If not possible then try set GLM_DIR to the location where you have installed GLM on your platform.")
ENDIF(GLM_FOUND)
FIND_PACKAGE (GLEW  REQUIRED)
FIND_PACKAGE (OpenGL REQUIRED)

IF(APPLE)    
    FIND_LIBRARY(COCOA_LIBRARY Cocoa REQUIRED)
    FIND_LIBRARY (IOKIT_LIBRARY IOKit REQUIRED)
    FIND_LIBRARY (COREVID_LIBRARY CoreVideo REQUIRED)
  
    # Try to do CMake assumping GLFW is from source installation.
    # You might have to set GLFW3_DIR in CMake gui to point
    # to you specific installation path.
    #SET( GLFW3_DIR "my/path/to/glfw3")
    FIND_PACKAGE (GLFW3 REQUIRED)
    IF(GLFW3_FOUND AND NOT GLFW_LIBRARIES)
        SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/usr/local/lib"  CACHE STRING "" FORCE)
        SET(GLFW_LIBRARIES "glfw3"  CACHE STRING "" FORCE)
    ELSE()    
        # Now try CMake way of getting GLFW if it was installed with Macport
        FIND_PACKAGE(PkgConfig REQUIRED)
        PKG_SEARCH_MODULE(GLFW glfw3)    
        IF( GLFW_LIBRARIES)
            SET(
            CMAKE_EXE_LINKER_FLAGS
            "${CMAKE_EXE_LINKER_FLAGS} -L/opt/local/lib"
            CACHE STRING "" FORCE
        )  
        ELSE()
            MESSAGE(FATAL_ERROR, "Could not find GLFW. We recommend using MacPort installation of GLFW")
    ENDIF()
ENDIF()
ELSE(APPLE)
    # Non Apple Platform. This means Windows or Linux. 
    #SET( GLFW3_DIR "my/path/to/glfw3")
    FIND_PACKAGE (glfw3 REQUIRED)
        IF(MSVC)
            file(GLOB GLFW_DLL  "${glfw3_DIR}/../../glfw3.dll")
            file(GLOB GLEW_DLL  "${GLEW_INCLUDE_DIR}/../bin/Release/Win32/glew32.dll")
        ENDIF()
    IF(NOT glfw3_FOUND)
        MESSAGE(FATAL_ERROR, "Could not find GLFW. Try setting GLFW3_DIR in CMake gui to point to your specific installation path")      
    ENDIF()
ENDIF()

ADD_SUBDIRECTORY (DIKUgraphics)
ADD_SUBDIRECTORY (Assignment-1)
ADD_SUBDIRECTORY (Assignment-2)
ADD_SUBDIRECTORY (Assignment-3)
ADD_SUBDIRECTORY (Assignment-4)
ADD_SUBDIRECTORY (Assignment-5)
ADD_SUBDIRECTORY (Assignment-6)
