#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "texture.h"

namespace Renderer{
    const double epsilon = 1e-10;
struct Rotation{
    float angelX = 0.f;
    float angelY = 0.f;
    float angelZ = 0.f;
};
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
        void rotate(float x, float y, float z, float grad);
        void move(float x, float y, float z);
        void scale(float x, float y, float z);
        void setPosition(float x, float y, float z);

        void setRotationX(float grad);
        void setRotationY(float grad);
        void setRotationZ(float grad);

        void setRotation(float x, float y, float z);
        void resetRotation();

        Rotation getRotation();
        glm::vec3 getPosition();
        
        std::string getID(){return ID;}

    private:
        void genBuffers();
        float normalizeGrad(float grad);
        std::string ID = "";
        Texture* texture = nullptr;
        glm::vec3 color;
        std::vector<float> verticies;
        int vertCount = 0;
        unsigned int vao=0, vbo=0;
        glm::mat4 transformMatrix;
        Rotation rotation;
};


}