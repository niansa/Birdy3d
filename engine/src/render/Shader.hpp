#ifndef BIRDY3D_SHADER_HPP
#define BIRDY3D_SHADER_HPP

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <unordered_map>
  
class Shader {
public:
    unsigned int ID;
  
    Shader(const std::string &shaderSource);
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const; 
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w);
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    bool checkCompileErrors(GLuint shader, GLenum type);
    std::unordered_map<GLenum, std::string> preprocess(const std::string &shaderSource);
    void compile(std::unordered_map<GLenum, std::string> &shaderSources);
};

#endif
