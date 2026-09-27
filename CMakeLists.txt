cmake_minimum_required(VERSION 4.3)
project(c-dsa)


# apparently CONFIGURE_DEPENDS is so that you dont need to run 
# cmake everytime a new file is added
file(GLOB SRC CONFIGURE_DEPENDS  "src/*.c" )

add_executable(${PROJECT_NAME} ${SRC})

