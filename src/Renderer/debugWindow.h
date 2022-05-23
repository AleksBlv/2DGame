#pragma once
#include <vector>

namespace Renderer{
    class Window;
    class BaseModel;
    class debugWindow{
        public:
            debugWindow(Window* pWindow);
            ~debugWindow();

            void update();
            void testWindow();
            void setModelsVector(std::vector<Renderer::BaseModel*>& data);

        private:
            Window* appWindow = nullptr;
            std::vector<Renderer::BaseModel*> models;
            int selectedModel = 0;
    };
}