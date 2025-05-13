set(LIBRARY_NAME renderer)
set(LIBRARY_SOURCES renderer.cpp)

add_library(${LIBRARY_NAME} ${LIBRARY_SOURCES})

target_link_libraries(${LIBRARY_NAME} world camera screen utils)
