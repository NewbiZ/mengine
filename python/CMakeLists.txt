FIND_PACKAGE(PYTHON3 3.3 REQUIRED)

SET(PYMENGINE_SOURCES mengine.cpp)

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

# Copy tests to output directory
#FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests
#          DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Copy examples to output directory
FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/examples
          DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
