#pragma once
#include "glm/glm.hpp"
#include <map>
#include <string>

namespace Renderer{

    struct Material {
        Material(){};
        Material(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float sh){
            ambient = amb;
            diffuse = diff;
            specular = spec;
            shininess = sh;
        }
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float shininess;
    };

    static std::map<std::string, Material> materialMap = {
        {"emerald", Material(glm::vec3(0.0215f, 0.1745f, 0.0215f), glm::vec3(0.07568f, 0.61424f, 0.07568f), glm::vec3(0.633f, 0.727811f, 0.633f), 0.6f * 128.f)},
        {"jade", Material(glm::vec3(0.135f, 0.2225f, 0.1575f), glm::vec3(0.54f, 0.89f, 0.63f), glm::vec3(0.316228f, 0.316228f, 0.316228f), 0.1f* 128.f)},
        {"obsidian", Material(glm::vec3(0.05375f, 0.05f, 0.06625f), glm::vec3(0.18275f, 0.17f, 0.22525f), glm::vec3(0.332741f, 0.328634f, 0.346435f), 0.3f* 128.f)},
        {"pearl", Material(glm::vec3(0.25, 0.20725f, 0.20725f), glm::vec3(1.f, 0.829f, 0.829f), glm::vec3(0.296648, 0.296648f, 0.296648f), 0.088f* 128.f)},
        {"rubi", Material(glm::vec3(0.1745, 0.01175f, 0.01175f), glm::vec3(0.61424f, 0.04136f, 0.04136f), glm::vec3(0.727811f, 0.626959f, 0.626959f), 0.6f* 128.f)},
        {"turquoise", Material(glm::vec3(0.1f, 0.18725f, 0.1745f), glm::vec3(0.396f, 0.74151f, 0.69102f), glm::vec3(0.297254f, 0.30829f, 0.306678f), 0.1f* 128.f)},
        {"brass", Material(glm::vec3(0.329412f, 0.223529f, 0.027451f), glm::vec3(0.780392f, 0.568627f, 0.113725), glm::vec3(0.992157f, 0.941176f, 0.807843f), 0.21794872f* 128.f)},
        {"bronze", Material(glm::vec3(0.2125f, 0.1275f, 0.054f), glm::vec3(0.714f, 0.4284f, 0.18144f), glm::vec3(0.393548, 0.271906f, 0.166721f), 0.2f* 128.f)},
        {"chrome", Material(glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.774597f, 0.774597f, 0.774597f), 0.6f* 128.f)},
        {"copper", Material(glm::vec3(0.19125, 0.0735, 0.0225), glm::vec3(0.7038, 0.27048, 0.0828), glm::vec3(0.256777, 0.137622, 0.086014), 0.1f* 128.f)},
        {"gold", Material(glm::vec3(0.24725, 0.1995, 0.0745), glm::vec3(0.75164, 0.60648, 0.22648), glm::vec3(0.628281, 0.555802, 0.366065), 0.4f* 128.f)},
        {"silver", Material(glm::vec3(0.19225, 0.19225, 0.19225), glm::vec3(0.50754, 0.50754, 0.50754), glm::vec3(0.508273, 0.508273, 0.508273), 0.4f* 128.f)},
    };

}