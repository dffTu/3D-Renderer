add_executable(simple_example main.cpp)
target_link_libraries(simple_example 3DRenderer application)
add_custom_command(
        TARGET simple_example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/src/renderer/fonts/arial.ttf
                ${CMAKE_CURRENT_BINARY_DIR}/arial.ttf)