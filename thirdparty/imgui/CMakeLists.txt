cmake_minimum_required(VERSION 3.10)
project(ImGui)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(ImGui "${MY_SOURCES}")


target_include_directories(ImGui 
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)



add_executable(ImGui_binary
    src/main.cpp
)

target_link_libraries(ImGui_binary
    PRIVATE 
        ImGui
)