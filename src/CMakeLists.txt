set(SOURCE_FILES main.cpp)
include_directories(${PROJECT_SOURCE_DIR}/contrib/SFML/include)

add_executable(simple_example ${SOURCE_FILES})
target_link_libraries(simple_example sfml-graphics)