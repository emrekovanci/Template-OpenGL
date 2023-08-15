cmake_minimum_required(VERSION 3.2)

project(Template_OpenGL)

# custom compiler warnings configuration
include("cmake/CompilerWarnings.cmake")

add_executable(${PROJECT_NAME}
    "src/Shader.cpp"
    "src/Camera.cpp"
    "Main.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

# c++ standard
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# apply custom compiler warnings
set(WARNINGS_AS_ERRORS TRUE)
set_target_warnings(${PROJECT_NAME})

find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

# set the output directory for the executable
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

# copy resources directory after build
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)