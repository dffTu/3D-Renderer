set(LIBRARY_NAME rasterizer)
set(LIBRARY_SOURCES rasterizer.cpp)

add_library(${LIBRARY_NAME} ${LIBRARY_SOURCES})

target_link_libraries(${LIBRARY_NAME} sfml-graphics)