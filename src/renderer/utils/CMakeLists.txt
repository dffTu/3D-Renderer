set(LIBRARY_NAME utils)
set(LIBRARY_SOURCES linalg.cpp)

add_library(${LIBRARY_NAME} ${LIBRARY_SOURCES})

target_link_libraries(${LIBRARY_NAME} eigen)