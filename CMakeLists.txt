cmake_minimum_required(VERSION 3.11)

project(potato C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(thirdparty/glfw)

add_library(glad STATIC thirdparty/glad/src/glad.c)
target_include_directories(glad PUBLIC "thirdparty/glad/include")
target_link_libraries(glad PUBLIC OpenGL::GL)

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
    thirdparty/imgui/backends/imgui_impl_opengl3.cpp

    thirdparty/imgui/imgui_demo.cpp
)

target_include_directories(imgui_lib PUBLIC
    thirdparty/imgui
    thirdparty/imgui/backends
)

target_link_libraries(imgui_lib PUBLIC glfw OpenGL::GL)

add_subdirectory(thirdparty/lua)

add_library(sol2 INTERFACE)
target_include_directories(sol2 INTERFACE thirdparty/sol2/include)
target_link_libraries(sol2 INTERFACE lua_static)

add_library(sol2_ImGui_Bindings STATIC
    thirdparty/sol2_ImGui_Bindings/sol_ImGui.cpp
    thirdparty/sol2_ImGui_Bindings/generated/sol_ImGui_Enums_gen.cpp
    thirdparty/sol2_ImGui_Bindings/generated/sol_ImGui_gen_0.cpp
    thirdparty/sol2_ImGui_Bindings/generated/sol_ImGui_gen_1.cpp
    thirdparty/sol2_ImGui_Bindings/generated/sol_ImGui_gen_2.cpp

    thirdparty/sol2_ImGui_Bindings/manual/sol_ImGui_Manual.cpp
)

target_include_directories(sol2_ImGui_Bindings PUBLIC
    thirdparty/sol2/include
)

target_link_libraries(sol2_ImGui_Bindings PUBLIC
    sol2
    imgui_lib
)

file(GLOB_RECURSE POTATO_CORE_SOURCES CONFIGURE_DEPENDS
    "src/core/*.cpp"
)

add_library(potato_core STATIC ${POTATO_CORE_SOURCES})

target_include_directories(potato_core PUBLIC
    "src/core"
    "src/"
    "thirdparty/meb"
    "thirdparty/sol2/include"
    "thirdparty/nlohmann_json/include"
    "thirdparty/"
)

target_link_libraries(potato_core PUBLIC
    glfw
    glad
    glm::glm
    stb_image
    imgui_lib
    sol2
    sol2_ImGui_Bindings
)

file(GLOB_RECURSE POTATO_EDITOR_SOURCES CONFIGURE_DEPENDS
    "src/editor/*.cpp"
    "src/editor/plugins/*.cpp"
)

add_library(potato_editor STATIC ${POTATO_EDITOR_SOURCES})

target_include_directories(potato_editor PUBLIC
    "src/core"
    "src/"
    "thirdparty/meb"
    "thirdparty/sol2/include"
    "thirdparty/nlohmann_json/include"
    "thirdparty/portable-file-dialogs/"
)

target_link_libraries(potato_editor PUBLIC
    potato_core
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    file(GLOB PLATFORM_SOURCES CONFIGURE_DEPENDS
        "src/platform/*.cpp"
        "src/platform/linux/*.cpp"
    )
else()
    file(GLOB PLATFORM_SOURCES CONFIGURE_DEPENDS
        "src/platform/*.cpp"
        "src/platform/windows/*.cpp"
    )
endif()

add_executable(potato
    src/main.cpp
    ${PLATFORM_SOURCES}
)

target_link_libraries(potato PRIVATE
    potato_core
    potato_editor
)

