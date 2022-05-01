#pragma once
#include <glad/glad.h>
#include <vector>
#include <string> 

namespace Renderer{
    class ShaderProgram{
        public:
            ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
            ShaderProgram() = delete;
            ShaderProgram(ShaderProgram&) = delete;
            ShaderProgram& operator=(const ShaderProgram&) = delete;
            ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
            ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;

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