#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Renderer{
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
        private:
            int mWidth = 0;
            int mHeight = 0;
            const char* mTitle;
            GLFWwindow* pWindow = nullptr;
            void setKeyCallback();
            void setSizeCallback();

    };
}