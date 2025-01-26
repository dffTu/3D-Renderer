cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(LIBRARY_NAME renderer)

project(${LIBRARY_NAME})

set(LIBRARY_SOURCES
    ${PROJECT_SOURCE_DIR}/src/renderer/camera/camera.h
    ${PROJECT_SOURCE_DIR}/src/renderer/object/object.h
    ${PROJECT_SOURCE_DIR}/src/renderer/rasterizer/rasterizer.h
    ${PROJECT_SOURCE_DIR}/src/renderer/world/world.h
)

add_library(${LIBRARY_NAME} ${LIBRARY_SOURCES})
include_directories(${LIBRARY_NAME} ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(${LIBRARY_NAME} camera object rasterizer world)
set_target_properties(${LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(contrib)
add_subdirectory(src/renderer)
add_subdirectory(example)