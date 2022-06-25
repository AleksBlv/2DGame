#pragma once
#include <glad/glad.h>
#include <vector>
#include <string> 
#include <glm/glm.hpp>

namespace Renderer{
    class ShaderProgram{
        public:
            ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
            ShaderProgram() = delete;
            ShaderProgram(ShaderProgram&) = delete;
            ShaderProgram& operator=(const ShaderProgram&) = delete;
            ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
            ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;

            void setUniformLocation3f(glm::vec3 data, const std::string& location);
            void setUniformLocation1f(float data, const std::string& location);
            void setUniformLocationMat4fv(glm::mat4 data, const std::string& location);
            void setUniformLocationInt(int data, const std::string& location);

            ~ShaderProgram();
            bool getCompiledStatus() const {return isCompiled; }
            std::string loadShader(const GLchar* path);

            void use() const;

            inline GLuint getProgramID(){return programID;}
        private:
            bool createShader(GLenum shaderType,const std::string& shaderSrc, GLuint& shaderId);
            
            bool isCompiled = false;
            GLuint programID = 0;
    };
}