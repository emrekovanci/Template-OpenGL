#include <Core/Shader.hpp>

#include <iostream>
#include <fstream>
#include <iterator>

#include <glm/gtc/type_ptr.hpp>

namespace
{
    bool isShaderCompiled(GLuint shader)
    {
        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        return success == GL_TRUE;
    }

    std::string getShaderLog(GLuint shader)
    {
        std::string infoLog;
        infoLog.resize(1024);
        glGetShaderInfoLog(shader, static_cast<GLsizei>(infoLog.size()), nullptr, infoLog.data());

        return infoLog;
    }

    bool isShaderProgramLinked(GLuint shaderProgram)
    {
        GLint success;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

        return success == GL_TRUE;
    }

    std::string getShaderProgramLog(GLuint shaderProgram)
    {
        std::string infoLog;
        infoLog.resize(1024);
        glGetProgramInfoLog(shaderProgram, static_cast<GLsizei>(infoLog.size()), nullptr, infoLog.data());

        return infoLog;
    }

    bool loadFileContents(const std::filesystem::path& sourcefilePath, std::string& destination)
    {
        std::ifstream file { sourcefilePath };
        if (file)
        {
            destination = { std::istreambuf_iterator<char> { file }, std::istreambuf_iterator<char> {} };
        }

        return file.is_open();
    }
} // namespace

Shader::Shader(Shader&& source) noexcept :
    _shaderProgram { std::exchange(source._shaderProgram, 0U) },
    _uniforms { std::move(source._uniforms) }
{
}

Shader& Shader::operator=(Shader&& source) noexcept
{
    // make sure we aren't moving ourselves
    if (&source == this)
    {
        return *this;
    }

    // destroy current program
    if (_shaderProgram)
    {
        glDeleteProgram(_shaderProgram);
    }

    _shaderProgram = std::exchange(source._shaderProgram, 0U);
    _uniforms = std::move(source._uniforms);

    return *this;
}

Shader::~Shader()
{
    if (_shaderProgram)
    {
        glDeleteProgram(_shaderProgram);
    }
}

bool Shader::loadFromFile(const Path& vertexShaderFilePath, const Path& fragmentShaderFilePath)
{
    std::string vertexShaderCode;
    if (!loadFileContents(vertexShaderFilePath, vertexShaderCode))
    {
        std::cerr << "Failed to open Vertex Shader: " << std::quoted(vertexShaderFilePath.string()) << '\n';
        return false;
    }

    std::string fragmentShaderCode;
    if (!loadFileContents(fragmentShaderFilePath, fragmentShaderCode))
    {
        std::cerr << "Failed to open Fragment Shader: " << std::quoted(fragmentShaderFilePath.string()) << '\n';
        return false;
    }

    return compile(vertexShaderCode.c_str(), fragmentShaderCode.c_str());
}

void Shader::use() const
{
    glUseProgram(_shaderProgram);
}

void Shader::setBool(const std::string& name, bool value)
{
    glUniform1i(getUniformLocation(name), static_cast<int>(value));
}

void Shader::setInt(const std::string& name, int value)
{
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setFloat(const std::string& name, float value)
{
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value)
{
    glUniform2fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::setVec2(const std::string& name, float x, float y)
{
    glUniform2f(getUniformLocation(name), x, y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value)
{
    glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, float x, float y, float z)
{
    glUniform3f(getUniformLocation(name), x, y, z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value)
{
    glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w)
{
    glUniform4f(getUniformLocation(name), x, y, z, w);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat)
{
    glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat)
{
    glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

bool Shader::compile(const char* vertexShaderCode, const char* fragmentShaderCode)
{
    // destroy the shader if it was already created
    if (_shaderProgram)
    {
        glDeleteShader(_shaderProgram);
        _shaderProgram = 0;
        _uniforms.clear();
    }

    _shaderProgram = glCreateProgram();

    // create, compile and attach
    auto createShader = [this](const char* shaderCode, GLenum shaderType) -> bool
    {
        const GLuint shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &shaderCode, nullptr);
        glCompileShader(shader);

        if (!isShaderCompiled(shader))
        {
            std::cerr << "Failed to compile shader!\n" << getShaderLog(shader);
            glDeleteShader(shader);
            glDeleteProgram(_shaderProgram);
            return false;
        }

        glAttachShader(_shaderProgram, shader);
        glDeleteShader(shader);
        return true;
    };

    if (!createShader(vertexShaderCode, GL_VERTEX_SHADER) || !createShader(fragmentShaderCode, GL_FRAGMENT_SHADER))
    {
        return false;
    }

    glLinkProgram(_shaderProgram);
    if (!isShaderProgramLinked(_shaderProgram))
    {
        std::cerr << "Failed to link shader!\n" << getShaderProgramLog(_shaderProgram);
        glDeleteProgram(_shaderProgram);
        return false;
    }

    return true;
}

GLint Shader::getUniformLocation(const std::string& name)
{
    // check the cache
    if (const auto it = _uniforms.find(name); it != _uniforms.end())
    {
        return it->second;
    }

    // uniform not in cache, request the location from OpenGL
    const GLint location = glGetUniformLocation(_shaderProgram, name.c_str());
    _uniforms.emplace(name, location);

    if (location == -1)
    {
        std::cerr << "Uniform " << std::quoted(name) << " not found in shader!\n";
    }

    return location;
}
