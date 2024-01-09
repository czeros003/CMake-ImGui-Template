include(FetchContent)

# Fetch imgui
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG docking
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)
# Fetch glfw
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG master
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glfw
)
# Fetch implot
FetchContent_Declare(
        implot
        GIT_REPOSITORY https://github.com/epezent/implot
        GIT_TAG master
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/implot
)

FetchContent_GetProperties(imgui glfw implot)

# Check if content is populated
if (NOT imgui_PUPULATED)
    FetchContent_Populate(imgui)
endif ()

if (NOT glfw_PUPULATED)
    FetchContent_Populate(glfw)
endif ()

if (NOT implot_PUPULATED)
    FetchContent_Populate(implot)
endif ()


# Add libraries
add_library(
        imgui STATIC
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp

        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_opengl2.cpp
        imgui/backends/imgui_impl_opengl3.cpp
)

add_library(
        implot STATIC
        implot/implot.cpp
        implot/implot_items.cpp
        implot/implot_demo.cpp
)

add_subdirectory(glfw)

# Link libraries together
target_link_libraries(imgui PUBLIC glfw)
target_link_libraries(implot PUBLIC imgui)

# Include directories for executable
target_include_directories(
        imgui PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/imgui>
        $<INSTALL_INTERFACE:imgui>
)

target_include_directories(
        implot PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/implot>
        $<INSTALL_INTERFACE:implot>
)