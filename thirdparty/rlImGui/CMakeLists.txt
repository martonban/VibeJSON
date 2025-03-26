cmake_minimum_required(VERSION 3.10)
project(rlImGui)

add_library(rlImGui STATIC
    src/rlImGui.cpp
)

target_include_directories(rlImGui 
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(rlImGui
    PUBLIC
        raylib
        ImGui
)


add_executable(rlImGui_binary
    src/main.cpp
)

target_link_libraries(rlImGui_binary
    PRIVATE 
        rlImGui
        raylib
        ImGui
)