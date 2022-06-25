#pragma once
#include "glm/glm.hpp"
#include <map>
#include <string>
#include <glad/glad.h>

namespace Renderer{

    struct Material {
        Material(){};
        Material(GLuint64 textureID, glm::vec3 spec, float sh){
            diffuse = textureID;
            specular = spec;
            shininess = sh;
        }
        GLuint64 diffuse;
        glm::vec3 specular;
        float shininess;
    };

}