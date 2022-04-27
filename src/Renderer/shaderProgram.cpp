#include "shaderProgram.h"
#include <iostream>

namespace Renderer{
    ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader){
        GLuint vertexShaderID;
        if(!createShader(GL_VERTEX_SHADER, vertexShader, vertexShaderID)){
            std::cerr << "Vertex shader compile error" <<std::endl;
            glDeleteShader(vertexShaderID);
            return;
        }
        GLuint fragmentShaderID;
        if(!createShader(GL_FRAGMENT_SHADER, fragmentShader, fragmentShaderID)){
            std::cerr << "Fragment shader compile error" <<std::endl;
            glDeleteShader(fragmentShaderID);
            return;
        }
        programID = glCreateProgram();
        glAttachShader(programID, vertexShaderID);
        glAttachShader(programID, fragmentShaderID);
        glLinkProgram(programID);

        GLint success;
        glGetProgramiv(programID, GL_LINK_STATUS, &success);
        if(!success){
            GLchar infolog[1024];
            glGetShaderInfoLog(programID, 1024, nullptr, infolog);
            std::cerr << "ERROR::SHADER: Link time error\n" << infolog << std::endl;
            return;
        }else{
            isCompiled = true;
        }

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }

    void ShaderProgram::use() const {
        glUseProgram(programID);
    }

    bool ShaderProgram::createShader(GLenum shaderType,const std::string& shaderSrc, GLuint& shaderId){
        shaderId = glCreateShader(shaderType);
        const char* code = shaderSrc.c_str();
        glShaderSource(shaderId, 1, &code, nullptr);
        glCompileShader(shaderId);

        GLint success;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
        if(!success){
            GLchar infolog[1024];
            glGetShaderInfoLog(shaderId, 1024, nullptr, infolog);
            std::cerr << "ERROR::SHADER: Compile time error\n" << infolog << std::endl;
            return false;
        }
        return true;
    }

    ShaderProgram::~ShaderProgram(){
        glDeleteProgram(programID);
    }

    ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept{
        glDeleteProgram(programID);
        programID = shaderProgram.programID;
        isCompiled = shaderProgram.getCompiledStatus();

        shaderProgram.programID = 0;
        shaderProgram.isCompiled = false;
    }

    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept{
        programID = shaderProgram.programID;
        isCompiled = shaderProgram.getCompiledStatus();

        shaderProgram.programID = 0;
        shaderProgram.isCompiled = false;
        return *this;
    }
}