cmake_minimum_required(VERSION 3.31)
project(black)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
if(MSVC)
    foreach(flag_var
            CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_DEBUG
            CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_DEBUG)
        string(REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
    endforeach()
endif()

include(FetchContent)

set(BUILD_SHARED_LIBS ON)

file(GLOB_RECURSE SOURCES src/*.*)
file(GLOB_RECURSE IMGUI_SOURCES includes/imgui/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${IMGUI_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
  PREFIX ""
  OUTPUT_NAME "black"
)

target_include_directories(${PROJECT_NAME} PRIVATE
  "includes/"
  "src/"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  "${CMAKE_SOURCE_DIR}/libs/sigscanner.lib"
  "${CMAKE_SOURCE_DIR}/libs/libMinHook.x64.lib"
)
