INCLUDE_DIRECTORIES (
    ${OPENGL_INCLUDE_DIR}
    ${GLM_INCLUDE_DIR}
    ${GLM_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIRS}            
    ${PROJECT_SOURCE_DIR}/DIKUgraphics/include
    ${PROJECT_SOURCE_DIR}/Assignment-2/include
)

FILE(
    GLOB
    ASSIGNMENT2_HEADERS
    include/*.h
)

FILE(
    GLOB
    ASSIGNMENT2_SOURCES
    src/*.cpp
)


CONFIGURE_FILE(
    "${PROJECT_SOURCE_DIR}/Assignment-2/include/shader_path.h.in"
    "${PROJECT_SOURCE_DIR}/Assignment-2/include/shader_path.h"
    @ONLY
)

ADD_EXECUTABLE (
    assignment-2
    ${ASSIGNMENT2_HEADERS}
    ${ASSIGNMENT2_SOURCES}
)

IF(APPLE)
    TARGET_LINK_LIBRARIES (
        assignment-2
        DIKUgraphics
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLFW_LIBRARIES}
        ${COCOA_LIBRARY}
        ${COREVID_LIBRARY}
        ${IOKIT_LIBRARY}
)
ELSE()
    TARGET_LINK_LIBRARIES (
         assignment-2
         DIKUgraphics
         ${OPENGL_LIBRARIES}
         ${GLEW_LIBRARIES}
         glfw  
    )
ENDIF()

SET_TARGET_PROPERTIES(assignment-2 PROPERTIES DEBUG_POSTFIX "D" )
SET_TARGET_PROPERTIES(assignment-2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY                             "${PROJECT_SOURCE_DIR}/bin")
SET_TARGET_PROPERTIES(assignment-2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG                 "${PROJECT_SOURCE_DIR}/bin")
SET_TARGET_PROPERTIES(assignment-2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE               "${PROJECT_SOURCE_DIR}/bin")
SET_TARGET_PROPERTIES(assignment-2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL          "${PROJECT_SOURCE_DIR}/bin")
SET_TARGET_PROPERTIES(assignment-2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${PROJECT_SOURCE_DIR}/bin")
IF(MSVC)
        file(COPY ${GLFW_DLL} DESTINATION ${PROJECT_SOURCE_DIR}/bin)
        file(COPY ${GLEW_DLL} DESTINATION ${PROJECT_SOURCE_DIR}/bin)
ENDIF()
