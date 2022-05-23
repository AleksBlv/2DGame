#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "texture.h"

namespace Renderer {
    class ShaderProgram;
    class ModelInterface{
        public:
            virtual ~ModelInterface() {};
            virtual void init(const std::vector<float>& data, int size) = 0;
            virtual void setTexture(Texture* t) = 0;
            virtual void setColor(glm::vec3 val) = 0;
            virtual void setColor(float r, float g, float b) = 0;
            virtual void prepare(ShaderProgram* shaderProgram) =0;
            virtual void draw(ShaderProgram* shaderProgram) =0;
            virtual void setPosition(float x, float y, float z) =0;
            virtual void setRotation(float x, float y, float z) =0;
            virtual void setScale(float x, float y, float z) =0;

            virtual glm::vec3 getScale() =0;
            virtual glm::vec3 getRotation() =0;
            virtual glm::vec3 getPosition()=0;
            virtual unsigned int getTexture() =0;
            virtual glm::vec3 getColor() =0;
            virtual std::string getID() =0;
    };
}