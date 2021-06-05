project(bcm2835)

set(SRCS 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bcm2835.c
)
include_directories(src)

add_library(bcm2835 ${SRCS})