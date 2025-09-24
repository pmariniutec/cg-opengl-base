#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void Use() const;
    void Delete() const;

    // Utility uniform functions
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec3(const std::string& name, const glm::vec3& value) const;
    void SetMat4(const std::string& name, const glm::mat4& value) const;
    void SetMat4(const std::string& name, const float* value) const;

    GLuint GetID() const { return m_program; }

private:
    GLuint CompileShader(const std::string& source, GLenum type) const;
    std::string ReadFile(const std::string& filePath) const;
    void CheckCompileErrors(GLuint shader, const std::string& type) const;

    GLuint m_program;
};
