set(LIBRARY_NAME screen)
set(LIBRARY_SOURCES screen.cpp)

add_library(${LIBRARY_NAME} ${LIBRARY_SOURCES})

target_link_libraries(${LIBRARY_NAME} sfml-graphics)
