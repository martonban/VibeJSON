cmake_minimum_required(VERSION 3.10)
project(NebulaPax)

include(FetchContent)

# Raylib dependences
set(RAYLIB_VERSION 5.0)
FetchContent_Declare(
  raylib
  URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  FIND_PACKAGE_ARGS ${RAYLIB_VERSION}
)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

# Json Dependencies
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)


# Enable testing
enable_testing()

add_subdirectory(game)
add_subdirectory(thirdparty/rlImGui)
add_subdirectory(thirdparty/imgui)
