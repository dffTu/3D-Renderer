set(LIBRARY_NAME object)
set(LIBRARY_SOURCES object.cpp vertex.cpp)

add_library(${LIBRARY_NAME} ${LIBRARY_SOURCES})

target_link_libraries(${LIBRARY_NAME} utils)