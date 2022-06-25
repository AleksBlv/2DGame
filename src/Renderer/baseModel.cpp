#include "baseModel.h"
#include <glad/glad.h>
#include "../external/glm/gtc/matrix_transform.hpp"
#include "../external/glm/gtc/type_ptr.hpp"
#include "../external/glm/gtx/matrix_decompose.hpp"
#include "Renderer/shaderProgram.h"

namespace Renderer{

BaseModel::BaseModel(const std::string& id): ID(id){
    color = glm::vec3(0.0f, 0.0f, 1.0f);
    setPosition(0.f, 0.f, 0.f);
    setRotation(0.f, 0.f, 0.f);
    setScale(1.f, 1.f, 1.f);

    //material = materialMap["silver"];
    material.diffuse = 0u;
    material.specular = glm::vec3(0.5f, 0.5f, 0.5f);
    material.shininess = 32.f;
}

void BaseModel::init(const std::vector<float>& data, int size){
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
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void BaseModel::setTexture(Texture* t){
    texture = t;
}

void BaseModel::prepare(ShaderProgram* shaderProgram){
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
    auto transformMatrix = getTransformMatrix();
    shaderProgram->setUniformLocationMat4fv(transformMatrix, "model");

    shaderProgram->setUniformLocationInt(material.diffuse, "material.duffuse");
    shaderProgram->setUniformLocation3f(material.specular, "material.specular");
    shaderProgram->setUniformLocation1f(material.shininess, "material.shininess");

}

void BaseModel::draw(ShaderProgram* shaderProgram){
    prepare(shaderProgram);
    glDrawArrays(GL_TRIANGLES, 0, vertCount);
    unbind();
}

void BaseModel::unbind(){
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    texture->unbindTexture();
    glUseProgram(0);
}

void BaseModel::setPosition(float x, float y, float z){
    positions.x = x;
    positions.y = y;
    positions.z = z;
}

glm::vec3 BaseModel::getPosition(){
    return positions;
}

glm::vec3 BaseModel::getRotation(){
    return rotation;
}

void BaseModel::setRotation(float x, float y, float z){
    rotation.x = x;
    rotation.y = y;
    rotation.z = z;
}

void BaseModel::setScale(float x, float y, float z){
    scales.x = x;
    scales.y = y;
    scales.z = z;
}

glm::vec3 BaseModel::getScale(){
    return scales;
}

void BaseModel::setColor(float r, float g, float b){
    color = glm::vec3(r/255.f, g/255.f, b/255.f);
}

void BaseModel::setColor(glm::vec3 val){
    color = val;
}

float BaseModel::normalizeGrad(float grad){
    float f;
    return std::modf(grad / 360.f, &f) * 360.f;
}

glm::mat4 BaseModel::getTransformMatrix(){
    glm::mat4 transformMatrix(1.f);
    transformMatrix = glm::translate(transformMatrix, positions);
    transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
    transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
    transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
    transformMatrix = glm::scale(transformMatrix, scales);

    return transformMatrix;
}

glm::vec3 BaseModel::getColor(){
    return color;
}

unsigned int BaseModel::getTexture(){
    if(texture)
        return texture->getTextureID();
    return 0u;
}

void BaseModel::setMaterial(Material m, const std::string& name){
    material = m;
    materialName = name;
}

}