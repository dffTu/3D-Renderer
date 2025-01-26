set(LIBRARY_NAME projector)
set(LIBRARY_SOURCES projector.cpp)

add_library(${LIBRARY_NAME} ${LIBRARY_SOURCES})

target_link_libraries(${LIBRARY_NAME} sfml-graphics world camera utils)