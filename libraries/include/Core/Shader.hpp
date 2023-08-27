#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
    using Path = std::filesystem::path;

public:
    Shader() = default;
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    Shader(Shader&& source) noexcept;
    Shader& operator=(Shader&& source) noexcept;
    ~Shader();

    bool loadFromFile(const Path& vertexShaderFilePath, const Path& fragmentShaderFilePath);

    void use() const;

    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);

    void setVec2(const std::string& name, const glm::vec2& value);
    void setVec2(const std::string& name, float x, float y);

    void setVec3(const std::string& name, const glm::vec3& value);
    void setVec3(const std::string& name, float x, float y, float z);

    void setVec4(const std::string& name, const glm::vec4& value);
    void setVec4(const std::string& name, float x, float y, float z, float w);

    void setMat2(const std::string& name, const glm::mat2& mat);
    void setMat3(const std::string& name, const glm::mat3& mat);
    void setMat4(const std::string& name, const glm::mat4& mat);

private:
    bool compile(const char* vertexShaderCode, const char* fragmentShaderCode);
    GLint getUniformLocation(const std::string& name);

private:
    GLuint m_shaderProgram {};
    std::unordered_map<std::string, GLint> m_uniforms;
};
