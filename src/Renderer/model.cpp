#include "model.h"
#include <glad/glad.h>
#include "../external/glm/gtc/matrix_transform.hpp"
#include "../external/glm/gtc/type_ptr.hpp"

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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    transformMatrix = glm::mat4(1.0f);
}

void Model::setTexture(Texture* t){
    texture = t;
}

void Model::prepare(unsigned int shaderId){
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    GLuint applyTextureLocation = glGetUniformLocation(shaderId, "applyTexture");
    if(texture){
        texture->bindTexture(0);
        glUniform1f(applyTextureLocation, 1.0f);
    } else {
        glUniform1f(applyTextureLocation, 0.0f);
    }

    GLuint objectColorLocation = glGetUniformLocation(shaderId, "objectColor");
    glUniform3f(objectColorLocation, color.x, color.y, color.z);

    GLuint modelLoc = glGetUniformLocation(shaderId, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transformMatrix));
}

void Model::draw(unsigned int  shaderId){
    prepare(shaderId);
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

}