add_subdirectory(fmt)
add_subdirectory(glad)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
add_subdirectory(glfw)

add_library(imgui
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui.cpp
    imgui/misc/cpp/imgui_stdlib.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC 
    imgui 
    imgui/backends
    imgui/misc/cpp
)

add_library(implot implot/implot_items.cpp implot/implot.cpp)
target_include_directories(implot PUBLIC implot)
target_link_libraries(implot imgui)