cmake_minimum_required(VERSION 3.7)

# the project is compiled using the C++17 standard.
set(CMAKE_CXX_STANDARD 17)
message("CMAKE_CXX_STANDARD = ${CMAKE_CXX_STANDARD}")

project(SSD_objectdetection) 

# adds the `-pthread` flag to the compiler flags. 
set(CMAKE_CXX_FLAGS "-pthread")

# config OpenCV 4.1 package
find_package(OpenCV 4.1 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

# create a list of source files
file(GLOB project_SRCS src/*.cpp) #src/*.h
# adds an executable using the source files in the list
add_executable(detect ${project_SRCS})
# links the executable "detect" with the OpenCV libraries 
target_link_libraries(detect ${OpenCV_LIBRARIES})

