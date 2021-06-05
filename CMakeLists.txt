cmake_minimum_required(VERSION 3.0)

project(ili-renderer)

set(SRCS main.cpp)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

add_subdirectory(bcm2835)
add_subdirectory(Graphic)
add_subdirectory(TFT)
add_subdirectory (docs)
include_directories(bcm2835/src)
include_directories(Graphic)
include_directories(TFT)
add_executable(ili-renderer ${SRCS})
target_link_libraries(ili-renderer bcm2835 TFT Graphic)
