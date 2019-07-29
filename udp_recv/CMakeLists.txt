cmake_minimum_required(VERSION 2.8.3)
project(udp_socket)

## Add support for C++11
add_definitions(-std=c++11)
set(CMAKE_BUILD_TYPE Release)

## Your package locations should be listed before other locations
include_directories(
  include
  src
)

#link_directories( ${TFS_SERVER_DIR}/lib )


######################################
add_executable ( server   src/server.cpp )



######################################
