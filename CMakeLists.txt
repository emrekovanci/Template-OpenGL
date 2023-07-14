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

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glfw)

find_package(Stb REQUIRED)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})

find_package(glm CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glm::glm)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE imgui::imgui)

file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})