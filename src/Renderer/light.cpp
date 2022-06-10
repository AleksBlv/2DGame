#include "light.h"

using namespace Renderer;

Light::Light(const std::string& id) : BaseModel(id), 
                                    ambient(glm::vec3(1.f)), 
                                    diffuse(glm::vec3(1.f)), 
                                    specular(glm::vec3(1.f)) {
    
}

void Light::setLight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec){
    ambient = amb;
    diffuse = diff;
    specular = spec;
}

glm::vec3 Light::getAmbient(){
    return ambient;
}
glm::vec3 Light::getDiffuse(){
    return diffuse;
}
glm::vec3 Light::getSpecular(){
    return specular;
}
