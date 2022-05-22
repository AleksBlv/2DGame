#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "texture.h"

namespace Renderer{
    const double EPSILON = 1e-10;

class ShaderProgram;
class Model{
    public:
        Model(const std::string& id);
        ~Model() = default;

        void init(const std::vector<float>& data, int size);
        void setTexture(Texture* t);
        void setColor(glm::vec3 val);
        void setColor(float r, float g, float b);


        unsigned int getTexture();
        void prepare(ShaderProgram* shaderProgram);
        void draw(ShaderProgram* shaderProgram);
        void unbind();

        glm::vec3 getColor();

        void setPosition(float x, float y, float z);
        void setRotation(float x, float y, float z);
        void setScale(float x, float y, float z);

        glm::vec3 getScale();
        glm::vec3 getRotation();
        glm::vec3 getPosition();
        
        std::string getID(){return ID;}

        glm::mat4 getTransformMatrix();

    private:
        void genBuffers();
        float normalizeGrad(float grad);
        
        std::string ID = "";
        Texture* texture = nullptr;
        glm::vec3 color;
        std::vector<float> verticies;
        int vertCount = 0;
        unsigned int vao=0, vbo=0;

        glm::vec3 rotation;
        glm::vec3 positions;
        glm::vec3 scales;
};


}