cmake_minimum_required(VERSION 3.5)

project(analysis LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(JSON_BuildTests OFF CACHE INTERNAL "")

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(nlohmann_json)

add_subdirectory(src)

install(TARGETS analysis
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
