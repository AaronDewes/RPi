project(Graphic)

set(SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/ascii.c  
    ${CMAKE_CURRENT_SOURCE_DIR}/basic.cpp  
    ${CMAKE_CURRENT_SOURCE_DIR}/scrbuff.cpp
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(Graphic ${SRCS})