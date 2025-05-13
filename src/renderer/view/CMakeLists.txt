set(LIBRARY_NAME view)
set(LIBRARY_SOURCES view.cpp)

add_library(${LIBRARY_NAME} ${LIBRARY_SOURCES})

target_link_libraries(${LIBRARY_NAME} sfml-graphics screen)
