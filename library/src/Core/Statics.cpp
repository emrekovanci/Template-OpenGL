#include <Core/Statics.hpp>

#include <glad/glad.h>

#include <iostream>

void Statics::displayGpuInfo()
{
    // clang-format off
    std::cout
        << "---------------------------------------------\n"
        << "Vendor:  \t" << glGetString(GL_VENDOR) <<   '\n'
        << "Version: \t" << glGetString(GL_VERSION) <<  '\n'
        << "Renderer:\t" << glGetString(GL_RENDERER) << '\n'
        << "---------------------------------------------\n";
    // clang-format on
}
