set(LIBRARY_NAME world)
set(LIBRARY_SOURCES world.cpp)

add_library(${LIBRARY_NAME} ${LIBRARY_SOURCES})

target_link_libraries(${LIBRARY_NAME} sfml-graphics utils)