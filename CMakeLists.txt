CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(mengine)

SET(MENGINE_VERSION_MAJOR 0)
SET(MENGINE_VERSION_MINOR 0)
SET(MENGINE_VERSION_PATCH 1)

# ============= FIND EXTERNAL LIBRARIES ==========
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

FIND_PACKAGE(GLFW   REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)

# =============== INCLUDES =======================
# Create directory for the resulting config.h
FILE(MAKE_DIRECTORY include/mengine)
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/include/mengine/config.h.in
    ${CMAKE_BINARY_DIR}/include/mengine/config.h)

INCLUDE_DIRECTORIES(include)
INCLUDE_DIRECTORIES(${GLFW_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/include)

# =============== MAIN OBJECTS ===================
# Enable C++11 support
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    SET(CMAKE_CXX_FLAGS "-std=c++11")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

# Match everything except the entry point
FILE(GLOB_RECURSE MENGINE_SOURCES src/*/*.cpp)

# Just build the object files, so that we could reuse them
# apart from the main executable (e.g. in test)
ADD_LIBRARY(mengine_objects OBJECT ${MENGINE_SOURCES})

# Create an executable by just adding the main entry point
ADD_EXECUTABLE(mengine $<TARGET_OBJECTS:mengine_objects>
                            src/main.cpp)

# =============== LINK LIBRARIES =================
TARGET_LINK_LIBRARIES(mengine ${GLFW_LIBRARY}
                                   ${OPENGL_LIBRARIES})

# =============== TESTS ==========================
ADD_SUBDIRECTORY(examples)

# =============== TESTS ==========================
ENABLE_TESTING()
ADD_SUBDIRECTORY(tests)

# =============== PYTHON BINDINGS ================
OPTION(BUILD_PYTHON "Build Python 3 bindings" OFF)

IF (BUILD_PYTHON)
    FIND_PACKAGE(PYTHON3 3.3 REQUIRED)

    SET(PYMENGINE_SOURCES python/mengine.cpp)

    INCLUDE_DIRECTORIES(${PYTHON3_INCLUDE_DIRS})

    ADD_LIBRARY(pymengine SHARED $<TARGET_OBJECTS:mengine_objects>
                                      ${PYMENGINE_SOURCES})

    TARGET_LINK_LIBRARIES(pymengine ${PYTHON3_LDFLAGS}
                                         ${GLFW_LIBRARY}
                                         ${OPENGL_LIBRARIES})
    IF(APPLE OR LINUX)
        SET_PROPERTY(TARGET pymengine PROPERTY PREFIX "_")
        SET_PROPERTY(TARGET pymengine PROPERTY SUFFIX ".so")
    ENDIF()
ENDIF(BUILD_PYTHON)

