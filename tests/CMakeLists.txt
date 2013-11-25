CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Copy test date to output directory
FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data
          DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Test to load a tga texture
ADD_EXECUTABLE(test_tga $<TARGET_OBJECTS:mengine_objects>
                        test_tga.cpp)
TARGET_LINK_LIBRARIES(test_tga ${GLFW_LIBRARY}
                               ${OPENGL_LIBRARIES})
ADD_TEST(NAME test_tga
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
         COMMAND ./tests/test_tga)

# ===== Template for adding a new test =====
# Create an executable with mengine object files adding
# a custom entry point
#ADD_EXECUTABLE(test_NAME $<TARGET_OBJECTS:mengine_objects>
#                         test_NAME.cpp)
#TARGET_LINK_LIBRARIES(test_NAME ${GLFW_LIBRARY}
#                                ${OPENGL_LIBRARIES})
