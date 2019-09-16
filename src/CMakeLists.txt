# find_package(OpenCV REQUIRED)
# link_directories(${OpenCV_LIB_DIR})

add_library(image image.cpp utils.cpp)
target_link_libraries(image ${OpenCV_LIBS})

add_library(processor processor.cpp utils.cpp image.cpp)
target_link_libraries(processor ${OpenCV_LIBS})

add_executable(${PROJECT_NAME}
    main.cpp
)
target_link_libraries(${PROJECT_NAME} image processor)
