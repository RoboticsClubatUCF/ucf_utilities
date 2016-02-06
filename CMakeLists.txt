cmake_minimum_required(VERSION 2.8)
project(ucf_utilities)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set(SOURCE_FILES src/i2c_interface.cpp src/byte_buffer.cpp)
set(LIBRARY_NAME ucfutilities)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/ucf_utilities)

add_library(${LIBRARY_NAME} SHARED ${SOURCE_FILES})

install(TARGETS ${LIBRARY_NAME} DESTINATION /usr/local/lib)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ucf_utilities DESTINATION /usr/local/include)
