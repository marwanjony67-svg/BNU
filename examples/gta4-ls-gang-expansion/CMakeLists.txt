cmake_minimum_required(VERSION 3.16)
project(GTA4LSGangData VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(ls_gang_data
    src/main.cpp
    src/GangConfig.cpp
)

target_include_directories(ls_gang_data PRIVATE src)

if(MSVC)
    target_compile_options(ls_gang_data PRIVATE /W4 /permissive-)
else()
    target_compile_options(ls_gang_data PRIVATE -Wall -Wextra -Wpedantic)
endif()
