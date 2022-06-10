#pragma once
#include "baseModel.h"
#include "glm/glm.hpp"

namespace Renderer {
    class Light : public BaseModel {
        public:
            Light(const std::string& id);
            ~Light() = default;

            void setLight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec);
            glm::vec3 getAmbient();
            glm::vec3 getDiffuse();
            glm::vec3 getSpecular();

        private:
            glm::vec3 ambient;
            glm::vec3 diffuse;
            glm::vec3 specular;

    };
}