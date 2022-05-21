#include "model.h"
#include <glad/glad.h>
#include "../external/glm/gtc/matrix_transform.hpp"
#include "../external/glm/gtc/type_ptr.hpp"
#include "../external/glm/gtx/matrix_decompose.hpp"
#include "Renderer/shaderProgram.h"

namespace Renderer{

Model::Model(const std::string& id): ID(id){
    color = glm::vec3(0.0f, 0.0f, 1.0f);
}

void Model::init(const std::vector<float>& data, int size){
    verticies = data;
    vertCount = size;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticies.size(), verticies.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    transformMatrix = glm::mat4(1.0f);
}

void Model::setTexture(Texture* t){
    texture = t;
}

void Model::prepare(ShaderProgram* shaderProgram){
    glUseProgram(shaderProgram->getProgramID());
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    GLuint applyTextureLocation = glGetUniformLocation(shaderProgram->getProgramID(), "applyTexture");
    if(texture){
        texture->bindTexture(0);
        glUniform1f(applyTextureLocation, 1.0f);
    } else {
        glUniform1f(applyTextureLocation, 0.0f);
    }

    shaderProgram->setUniformLocation3f(color, "objectColor");
    shaderProgram->setUniformLocationMat4fv(transformMatrix, "model");
}

void Model::draw(ShaderProgram* shaderProgram){
    prepare(shaderProgram);
    glDrawArrays(GL_TRIANGLES, 0, vertCount);
    unbind();
}

void Model::unbind(){
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    texture->unbindTexture();
    glUseProgram(0);
}

void Model::rotate(float x, float y, float z, float grad){
    transformMatrix = glm::rotate(transformMatrix, glm::radians(grad), glm::vec3(x, y, z));
}

void Model::move(float x, float y, float z){
    transformMatrix = glm::translate(transformMatrix, glm::vec3(x, y, z));
}

void Model::scale(float x, float y, float z){
    transformMatrix = glm::scale(transformMatrix, glm::vec3(x, y, z));
}

void Model::setPosition(float x, float y, float z){
    transformMatrix[3][0] = x;
    transformMatrix[3][1] = y;
    transformMatrix[3][2] = z;
}

glm::vec3 Model::getPosition(){
    return glm::vec3(transformMatrix[3]);
}

Rotation Model::getRotation(){
    return rotation;
}

void Model::setRotationX(float grad){
    if (grad > 360.f){
        grad = normalizeGrad(grad);
    }
    transformMatrix = glm::rotate(transformMatrix, glm::radians(grad), glm::vec3(1.f, 0.f, 0.f));
    rotation.angelX = grad;
}

void Model::setRotationY(float grad){
    if (grad > 360.f){
        grad = normalizeGrad(grad);
    }
    transformMatrix = glm::rotate(transformMatrix, glm::radians(grad), glm::vec3(0.f, 1.f, 0.f));
    rotation.angelY = grad;
}

void Model::setRotationZ(float grad){
    if (grad > 360.f){
        grad = normalizeGrad(grad);
    }
    transformMatrix = glm::rotate(transformMatrix, glm::radians(grad), glm::vec3(0.f, 0.f, 1.f));
    rotation.angelZ = grad;
}

void Model::setRotation(float x, float y, float z){
    resetRotation();
    setRotationX(x);
    setRotationY(y);
    setRotationZ(z);
}

void Model::resetRotation(){
    setRotationZ(-rotation.angelZ);
    setRotationY(-rotation.angelY);
    setRotationX(-rotation.angelX);
}

void Model::setColor(float r, float g, float b){
    color = glm::vec3(r/255.f, g/255.f, b/255.f);
}

void Model::setColor(glm::vec3 val){
    color = val;
}

float Model::normalizeGrad(float grad){
    float f;
    return std::modf(grad / 360.f, &f) * 360.f;
}

}