project(Panoramic)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED )
#find_package(OpenEXR REQUIRED)
add_library(opencv INTERFACE )

# Set additional flags.
set(CMAKE_CXX_FLAGS "-Wall -Wextra -lstdc++fs")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Tell cmake to output binaries here:
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# Tell cmake where to look for *.h files.
include_directories(${PROJECT_SOURCE_DIR}/include())

# Outsource the actual processing to folders.
add_subdirectory(${PROJECT_SOURCE_DIR}/src)


target_include_directories(opencv INTERFACE "${OpenCV_INCLUDE_DIRS}")
target_link_libraries(opencv INTERFACE "${OpenCV_LIBS}")
