#include "camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>

float DEFAUL_SPEED = 2.f;

namespace Renderer{

Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up, Window* w):cameraPos(pos),
                                                            cameraFront(front),
                                                            cameraUp(up),
                                                            window(w){
    cameraSpeed = DEFAUL_SPEED;
    window->setCamera(this);
}

Camera::Camera(Window* w){
    window = w;
    cameraPos = glm::vec3(0.f);
    cameraFront = glm::vec3(0.f);
    cameraUp = glm::vec3(0.f);
    cameraSpeed = DEFAUL_SPEED;
    window->setCamera(this);
}

void Camera::setCameraSpeed(float val){
    cameraSpeed = val;
}
void Camera::setCameraPos(glm::vec3 pos){
    cameraPos = pos;
}
void Camera::setCameraFront(glm::vec3 front){
    cameraFront = front;
}
void Camera::setCameraUp(glm::vec3 up){
    cameraUp = up;
}

glm::mat4 Camera::getCameraMatrix(){
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::move(float deltaTime){
    auto speed = cameraSpeed * deltaTime;
    if(glfwGetKey(window->get(), GLFW_KEY_W) == GLFW_PRESS){
        cameraPos += speed * cameraFront;
    }
    if(glfwGetKey(window->get(), GLFW_KEY_S) == GLFW_PRESS){
        cameraPos -= speed * cameraFront;
    }
    if(glfwGetKey(window->get(), GLFW_KEY_A) == GLFW_PRESS){
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
    }
    if(glfwGetKey(window->get(), GLFW_KEY_D) == GLFW_PRESS){
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
    }
    if(glfwGetKey(window->get(), GLFW_KEY_R) == GLFW_PRESS){
        cameraPos += speed * cameraUp;
    }
    if(glfwGetKey(window->get(), GLFW_KEY_F) == GLFW_PRESS){
        cameraPos -= speed * cameraUp;
    }
}

float Camera::getYaw(){
    return yaw;
}
void Camera::setYaw(float val){
    
    yaw = val;
}
float Camera::getPitch(){
    return pitch;
}
void Camera::setPitch(float val){
    pitch = val;
    if (pitch > 89.f) pitch = 89.f;
    if (pitch < -89.f) pitch = -89.f;
}


}