#include "model.h"
#include <glad/glad.h>
#include "../external/glm/gtc/matrix_transform.hpp"
#include "../external/glm/gtc/type_ptr.hpp"
#include "../external/glm/gtx/matrix_decompose.hpp"
#include "Renderer/shaderProgram.h"

namespace Renderer{

Model::Model(){
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
}

void Model::unbind(){
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    texture->unbindTexture();
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

glm::vec3 Model::getPosition(){
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(transformMatrix, scale, rotation, translation, skew,perspective);
    return translation;
}

void Model::setColor(float r, float g, float b){
    color = glm::vec3(r/255.f, g/255.f, b/255.f);
}

void Model::setColor(glm::vec3 val){
    color = val;
}

}