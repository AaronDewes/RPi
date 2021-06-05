project(TFT)

set(SRCS 
    ${CMAKE_CURRENT_SOURCE_DIR}/ascii.c
    ${CMAKE_CURRENT_SOURCE_DIR}/gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/tft.cpp
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../bcm2835/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

add_library(TFT ${SRCS})
target_link_libraries(TFT bcm2835 pthread)