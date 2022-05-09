#include "shaderProgram.h"
#include "utils/log.h"
#include <fstream>
#include <sstream>

namespace Renderer{
    ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader){
        GLuint vertexShaderID;
        std::string vertexShaderCode = loadShader(vertexShader.c_str());
        if(!createShader(GL_VERTEX_SHADER, vertexShaderCode, vertexShaderID)){
            LOG_ERROR("Vertex shader compile error");
            glDeleteShader(vertexShaderID);
            return;
        }
        GLuint fragmentShaderID;
        std::string fragmentShaderCode = loadShader(fragmentShader.c_str());
        if(!createShader(GL_FRAGMENT_SHADER, fragmentShaderCode, fragmentShaderID)){
            LOG_ERROR("Fragment shader compile error");
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
            LOG_ERROR("ERROR::SHADER: Link time error\n{0}", infolog );
            return;
        }else{
            isCompiled = true;
        }

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }

    std::string ShaderProgram::loadShader(const GLchar* path){
        std::string shaderCode;
        std::ifstream shaderFile;

        shaderFile.exceptions(std::ifstream::badbit);
        try{
            shaderFile.open(path);
            std::stringstream shaderStream;
            shaderStream << shaderFile.rdbuf();
            shaderFile.close();
            shaderCode = shaderStream.str();
        } catch (std::ifstream::failure e){
            LOG_ERROR("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
        }
        return shaderCode;
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
            LOG_ERROR("ERROR::SHADER: Compile time error\n{0}", infolog);
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