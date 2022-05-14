#include "window.h"
#include "camera.h"
#include "utils/log.h"

namespace Renderer{

    Window::Window(int width, int heigth, const char* title){
        mWidth = width;
        mHeight = heigth;
        mTitle = title;
        mLastMouseXPos = mWidth / 2.f;
        mLastMouseYPos = mHeight / 2.f;
    }

    bool Window::init(){
        if (!glfwInit()){
            LOG_ERROR("Couldn't init glfw!");
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        pWindow = glfwCreateWindow(mWidth, mHeight, mTitle, nullptr, nullptr);

        if (!pWindow){
            LOG_ERROR("Couldn't create window!");
            glfwTerminate();
            return -1;
        }
        glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        cursorEnabled = false;

        glfwSetWindowUserPointer(pWindow, this);

        setSizeCallback();
        setKeyCallback();

        glfwMakeContextCurrent(pWindow);
        if(!gladLoadGL()){
            LOG_ERROR("Unable to initialize glad");
            return -1;
        }
    
        LOG_INFO("OpenGL version: {0:d}.{1:d}", GLVersion.major, GLVersion.minor);
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
            if(key == GLFW_KEY_Q && action == GLFW_PRESS){
                if(auto self = static_cast<Window*>(glfwGetWindowUserPointer(pWindow))){
                    self->toggleCursor();
                }
            }
        });
    }

    void Window::setMouseCallback(){
        glfwSetCursorPosCallback(pWindow, [](GLFWwindow* window, double xPos, double yPos){
            if(auto self = static_cast<Window*>(glfwGetWindowUserPointer(window))){
                if(self->isCursorEnabled())return;

                float xOffset = xPos - self->getLastMouseXPosition();
                float yOffset = yPos - self->getLastMouseYPosition();
                self->setLastMouseXPosition(xPos);
                self->setLastMouseYPosition(yPos);

                float sensivity = 0.1f;
                xOffset *= sensivity;
                yOffset *= sensivity * -1.f;

                auto cam = self->getCamera();
                if (!cam) {
                    LOG_ERROR("Couldn't get camera");
                    return;
                }
                cam->setYaw(cam->getYaw() + xOffset);
                cam->setPitch(cam->getPitch() + yOffset);
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

    void Window::setCamera(Camera* camera){
        pCamera = camera;
        setMouseCallback();
    }

    void Window::toggleCursor(){
        if(cursorEnabled){
            glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            cursorEnabled = false;
        } else {
            glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            cursorEnabled = true;
        }
    }
}