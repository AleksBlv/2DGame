#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "texture.h"
#include "modelInterface.h"

namespace Renderer{
    const double EPSILON = 1e-10;

    struct Material {
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float shininess;
    };

class ShaderProgram;
class BaseModel : public ModelInterface{
    public:
        BaseModel(const std::string& id);
        ~BaseModel() = default;

        void init(const std::vector<float>& data, int size) override;
        void setTexture(Texture* t) override;
        void setColor(glm::vec3 val) override;
        void setColor(float r, float g, float b) override;


        unsigned int getTexture() override;
        void prepare(ShaderProgram* shaderProgram) override;
        void draw(ShaderProgram* shaderProgram) override;
        void unbind();

        glm::vec3 getColor() override;

        void setPosition(float x, float y, float z) override;
        void setRotation(float x, float y, float z) override;
        void setScale(float x, float y, float z) override;

        glm::vec3 getScale() override;
        glm::vec3 getRotation() override;
        glm::vec3 getPosition() override;
        
        std::string getID() override {return ID;}

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
        Material material;
};


}