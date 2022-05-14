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
        float getYaw() const;
        void setYaw(float val);
        float getPitch() const;
        void setPitch(float val);

        void initMouseMoveCallback();

        glm::mat4 getCameraMatrix();
        glm::vec3 getCameraPosition() const;
        
    private:
        Window* window = nullptr;
        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;
        float cameraSpeed;
        float yaw = -89.0f;
        float pitch = 0.f;

        void mouseMove(GLFWwindow* window, double xPos, double yPos);
};


}