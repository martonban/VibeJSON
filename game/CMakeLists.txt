cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(SpaceOS "${MY_SOURCES}")
target_include_directories(SpaceOS PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SpaceOS PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(SpaceOS PRIVATE raylib nlohmann_json::nlohmann_json ImGui rlImGui)