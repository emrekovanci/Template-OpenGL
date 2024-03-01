cmake_minimum_required(VERSION 3.26)

project(
	Template-OpenGL
	VERSION 0.1.0
	DESCRIPTION "Template project for developing OpenGL applications"
	HOMEPAGE_URL "https://github.com/emrekovanci/Template-OpenGL"
	LANGUAGES CXX
)

find_package(glad CONFIG REQUIRED)
find_package(SFML COMPONENTS window CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_subdirectory(library)
add_subdirectory(app)
