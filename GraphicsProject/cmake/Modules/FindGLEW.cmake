#
# Try to find imgui library and include path.
# Once done this will define
#
# GLEW_FOUND
# GLEW_INCLUDE_DIR
# GLEW_INCLUDE_DIRS
# GLEW_LIBRARY
# GLEW_LIBRARIES
# 

# message("FindGLEW running")

# Additional modules
include(FindPackageHandleStandardArgs)

set(GLEW_SEARCH_PATHS
	$ENV{GLEW_ROOT}
	${DEPENDENCIES_ROOT}
	/usr/local
	/usr)

find_path(GLEW_INCLUDE_DIR
    NAMES
        GL/glew.h
    PATHS
        ${GLEW_SEARCH_PATHS}
    PATH_SUFFIXES
        include
    DOC
        "The directory where imgui/imgui.h resides"
)

# message("GLEW_INCLUDE_DIR: ${GLEW_INCLUDE_DIR}")
# message("GLEW_SEARCH_PATHS: ${GLEW_SEARCH_PATHS}")

find_library(GLEW_LIBRARY
    NAMES
       GLEW
    PATHS
        ${GLEW_SEARCH_PATHS}
    PATH_SUFFIXES
        lib
    DOC
        "The directory where imgui.lib resides"
)

set(GLEW_FOUND "NO")
if (GLEW_INCLUDE_DIR AND GLEW_LIBRARY)
    set(GLEW_FOUND "YES")
    set(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})
    set(GLEW_LIBRARIES ${GLEW_LIBRARY})

    # message("EXTERNAL LIBRARY 'GLEW' FOUND")
    # message("GLEW_LIBRARY: ${GLEW_LIBRARY}")
    # message("GLEW_LIBRARIES: ${GLEW_LIBRARIES}")
else (GLEW_INCLUDE_DIR AND GLEW_LIBRARY)
    message("ERROR: EXTERNAL LIBRARY 'GLEW' NOT FOUND")
endif (GLEW_INCLUDE_DIR AND GLEW_LIBRARY)

# Handle REQUIRD argument, define *_FOUND variable
find_package_handle_standard_args(GLEW DEFAULT_MSG GLEW_INCLUDE_DIR)