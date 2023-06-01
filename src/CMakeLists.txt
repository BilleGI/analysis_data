cmake_minimum_required(VERSION 3.5)

add_executable(analysis main.cpp film.cpp  ${MY_INCLUDE_DIR}/film.h)

target_include_directories(analysis PRIVATE ${MY_INCLUDE_DIR})

target_link_libraries(analysis PRIVATE nlohmann_json::nlohmann_json)
