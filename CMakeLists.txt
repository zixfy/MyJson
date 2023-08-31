cmake_minimum_required(VERSION 3.22)
project(my_json)

set(CMAKE_CXX_STANDARD 17)

add_library(json_lib STATIC Json.cpp JsonParser.cpp)
target_include_directories(json_lib PUBLIC ./include)

add_executable(demo demo.cpp)
target_link_libraries(demo  PRIVATE json_lib )
# default release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE release CACHE STRING "Build Type" FORCE)
endif()

file(GLOB test_src "./test/*.cpp")
foreach(source ${test_src})
    message(STATUS "using test file: ${source}")
    get_filename_component(filename ${source} NAME)
    add_executable(${filename} ${source})
endforeach()