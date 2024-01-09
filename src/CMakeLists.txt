add_executable(${PROJECT_NAME} CMakeProject.cpp "Editor.cpp" "Editor.h")

# Link libraries with executable
target_link_libraries(${PROJECT_NAME} PRIVATE imgui implot)

# Add OpenGL
find_package(OpenGL REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_gl_LIBRARY})