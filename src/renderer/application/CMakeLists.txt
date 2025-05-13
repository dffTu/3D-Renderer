set(LIBRARY_NAME application)
set(LIBRARY_SOURCES application.cpp)

add_library(${LIBRARY_NAME} ${LIBRARY_SOURCES})

target_link_libraries(${LIBRARY_NAME} sfml-graphics utils)