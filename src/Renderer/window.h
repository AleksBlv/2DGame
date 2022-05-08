#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Renderer{
    class Camera;
    class Window{
        
        public:
            Window(int width, int heigth, const char* title);
            
            bool init();

            bool shouldClose();
            void terminate();
            GLFWwindow* get();
            inline int getWidth(){return mWidth;}
            inline void setWidth(int width){mWidth = width;}
            inline int getHeight(){return mHeight;}
            inline void setHeight(int height){mHeight = height;}
            inline float getLastMouseXPosition(){return mLastMouseXPos;}
            inline void setLastMouseXPosition(float xPos){mLastMouseXPos = xPos;}
            inline float getLastMouseYPosition(){return mLastMouseYPos;}
            inline void setLastMouseYPosition(float yPos){mLastMouseYPos = yPos;}
            void setCamera(Renderer::Camera* camera);
            Camera* getCamera(){return pCamera;};
        private:
            int mWidth = 0;
            int mHeight = 0;
            float mLastMouseXPos = 0.0;
            float mLastMouseYPos = 0.0;
            const char* mTitle;
            Camera* pCamera = nullptr;
            GLFWwindow* pWindow = nullptr;
            void setKeyCallback();
            void setMouseCallback();
            void setSizeCallback();

    };
}