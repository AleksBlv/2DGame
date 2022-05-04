#pragma once
#include "glm/glm.hpp"
#include "window.h"

namespace Renderer{

class Camera{
    public:
        Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up, Window* w);
        Camera(Window* w);
        ~Camera() = default;

        void move(float deltaTime);

        void setCameraSpeed(float val);
        void setCameraPos(glm::vec3 pos);
        void setCameraFront(glm::vec3 front);
        void setCameraUp(glm::vec3 up);

        glm::mat4 getCameraMatrix();
        
    private:
        Window* window = nullptr;
        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;
        float cameraSpeed;
};


}