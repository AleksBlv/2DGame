#include <iostream>
#include "window.h"

namespace Renderer{

    Window::Window(int width, int heigth, const char* title){
        mWidth = width;
        mHeight = heigth;
        mTitle = title;
    }

    bool Window::init(){
        if (!glfwInit()){
            std::cerr << "Couldn't init glfw!" <<std::endl;
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        pWindow = glfwCreateWindow(mWidth, mHeight, mTitle, nullptr, nullptr);

        if (!pWindow){
            std::cerr << "Couldn't create window!" <<std::endl;
            glfwTerminate();
            return -1;
        }

        glfwSetWindowUserPointer(pWindow, this);

        setSizeCallback();
        setKeyCallback();

        glfwMakeContextCurrent(pWindow);
        if(!gladLoadGL()){
            std::cerr << "Unable to initialize glad"<<std::endl;
            return -1;
        }
    
    std::cout << "OpenGL version: " << GLVersion.major <<"."<<GLVersion.minor<<std::endl;

        return true;
    }

    bool Window::shouldClose(){
        if(glfwWindowShouldClose(pWindow)){
            return true;
        }
        return false;
    }
    void Window::terminate(){
        glfwTerminate();
    }

    GLFWwindow* Window::get(){
        return pWindow;
    }

    void Window::setKeyCallback(){
        glfwSetKeyCallback(pWindow, [](GLFWwindow* pWindow, int key, int scancode, int action, int mode){
            if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
                glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
            }
        });
    }
    void Window::setSizeCallback(){
        glfwSetWindowSizeCallback(pWindow, [](GLFWwindow* window, int width, int height){
            auto& self = *static_cast<Window*>(glfwGetWindowUserPointer(window));
            self.setWidth(width);
            self.setHeight(height);
            glViewport(0, 0, self.getWidth(), self.getHeight());
        });
    }
}