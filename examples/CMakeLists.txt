CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Copy example data to output directory
FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data
          DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Example to display text on the screen
ADD_EXECUTABLE(example_drawtext $<TARGET_OBJECTS:mengine_objects>
                                example_drawtext.cpp)
TARGET_LINK_LIBRARIES(example_drawtext ${GLFW_LIBRARY}
                                       ${OPENGL_LIBRARIES})

# Example to load a tga texture
ADD_EXECUTABLE(example_tga $<TARGET_OBJECTS:mengine_objects>
                           example_tga.cpp)
TARGET_LINK_LIBRARIES(example_tga ${GLFW_LIBRARY}
                                  ${OPENGL_LIBRARIES})

# Example to trigger a button on the screen
ADD_EXECUTABLE(example_clickable $<TARGET_OBJECTS:mengine_objects>
                                 example_clickable.cpp)
TARGET_LINK_LIBRARIES(example_clickable ${GLFW_LIBRARY}
                                        ${OPENGL_LIBRARIES})

# ===== Template for adding a new example =====
# Create an executable with mengine object files adding
# a custom entry point
#ADD_EXECUTABLE(example_NAME $<TARGET_OBJECTS:mengine_objects>
#                         example_NAME.cpp)
#TARGET_LINK_LIBRARIES(example_NAME ${GLFW_LIBRARY}
#                                ${OPENGL_LIBRARIES})
