cmake_minimum_required(VERSION 3.8)

project(Template_OpenGL)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(${CMAKE_PROJECT_NAME}
	"src/Shader.cpp"
	"src/Camera.cpp"
	Main.cpp
)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glad::glad)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glm::glm)

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})