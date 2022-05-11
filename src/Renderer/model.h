#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "texture.h"

namespace Renderer{
class ShaderProgram;
class Model{
    public:
        Model();
        ~Model() = default;

        void init(const std::vector<float>& data, int size);
        void setTexture(Texture* t);
        void setColor(glm::vec3 color);

        unsigned int getTexture();
        void prepare(ShaderProgram* shaderProgram);
        void draw(ShaderProgram* shaderProgram);
        void unbind();
        void rotate(float x, float y, float z, float grad);
        void move(float x, float y, float z);
        void scale(float x, float y, float z);

        glm::vec3 getPosition();

    private:
        void genBuffers();

        Texture* texture = nullptr;
        glm::vec3 color;
        std::vector<float> verticies;
        int vertCount = 0;
        unsigned int vao=0, vbo=0;
        glm::mat4 transformMatrix;
};


}