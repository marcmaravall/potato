cmake_minimum_required(VERSION 3.11)
 
project(potato C CXX)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/glfw)

add_library(glad STATIC thirdparty/glad/src/glad.c )
target_include_directories(glad PUBLIC "thirdparty/glad/include")

add_subdirectory(thirdparty/glm)

add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE thirdparty/stb)

add_library(imgui_lib STATIC
    thirdparty/imgui/imgui.cpp
    thirdparty/imgui/imgui_draw.cpp
    thirdparty/imgui/imgui_tables.cpp
    thirdparty/imgui/imgui_widgets.cpp
    thirdparty/imgui/backends/imgui_impl_glfw.cpp
    thirdparty/imgui/misc/cpp/imgui_stdlib.cpp
    thirdparty/imgui/backends/imgui_impl_opengl3.cpp )

target_include_directories(imgui_lib PUBLIC
    thirdparty/imgui
    thirdparty/imgui/backends
)

target_link_libraries(imgui_lib PUBLIC glfw)

file(GLOB ENGINE_SOURCES CONFIGURE_DEPENDS "src/core/*.cpp" "src/editor/*.cpp" 
    "src/core/rendering/*.cpp" "src/core/rendering/opengl/*.cpp" "src/core/logging/*.cpp" 
    "src/platform/linux/*.cpp"
    "src/platform/*.cpp"
    "src/core/assets_manager/*.cpp"
    "src/core/systems/*.cpp"
    "src/core/components/*.cpp"
)

include_directories(potato PUBLIC "src/core" "src/"
    "thirdparty/meb"
)

add_executable(potato
    "src/main.cpp"
    ${ENGINE_SOURCES}
 )
 
target_link_libraries(potato PRIVATE
    glfw
    glad
    glm::glm
    stb_image
    imgui_lib
)
 