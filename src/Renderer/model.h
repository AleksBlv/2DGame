#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "texture.h"

namespace Renderer{

class Model{
    public:
        Model();
        ~Model() = default;

        void init(const std::vector<float>& data, int size);
        void setTexture(Texture* t);

        unsigned int getTexture();
        void prepare(unsigned int shaderId);
        void draw(unsigned int shaderId);
        void unbind();
        void rotate(float x, float y, float z, float grad);
        void move(float x, float y, float z);

    private:
        void genBuffers();

        Texture* texture = nullptr;
        std::vector<float> verticies;
        int vertCount = 0;
        unsigned int vao=0, vbo=0;
        glm::mat4 transformMatrix;
};


}