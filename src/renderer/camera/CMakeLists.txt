set(LIBRARY_NAME camera)
set(LIBRARY_SOURCES camera.cpp)

add_library(${LIBRARY_NAME} ${LIBRARY_SOURCES})

target_link_libraries(${LIBRARY_NAME} sfml-graphics utils)