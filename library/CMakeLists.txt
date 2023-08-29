set(INCROOT ${PROJECT_SOURCE_DIR}/library/include/Core)
set(SRCROOT ${PROJECT_SOURCE_DIR}/library/src/Core)

# all header files
set(LIBRARY_HEADERS
    ${INCROOT}/Camera.hpp
    ${INCROOT}/Shader.hpp
)

# all source files
set(LIBRARY_SOURCES
    ${SRCROOT}/Camera.cpp
    ${SRCROOT}/Shader.cpp
)

# define library
add_library(CoreLibrary STATIC ${LIBRARY_HEADERS} ${LIBRARY_SOURCES})

# we need this directory, and users of our library will need it too
target_include_directories(CoreLibrary PUBLIC ${PROJECT_SOURCE_DIR}/library/include)

# depends on glad
target_link_libraries(CoreLibrary PUBLIC glad::glad)

# depends on glm
target_link_libraries(CoreLibrary PUBLIC glm::glm)

# all users of this library will need at least C++17
target_compile_features(CoreLibrary PUBLIC cxx_std_17)

# IDEs should put the headers and sources in a nice place
source_group(TREE ${INCROOT} PREFIX "Headers" FILES ${LIBRARY_HEADERS})
source_group(TREE ${SRCROOT} PREFIX "Sources" FILES ${LIBRARY_SOURCES})
