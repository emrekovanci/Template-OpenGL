# Define executable and its properties
add_executable(${PROJECT_NAME} App.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE Core)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-window)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

# Copy resources directory after build
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)
