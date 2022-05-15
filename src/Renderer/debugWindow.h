#pragma once
#include <vector>

namespace Renderer{
    class Window;
    class Model;
    class debugWindow{
        public:
            debugWindow(Window* pWindow);
            ~debugWindow();

            void update();
            void testWindow();
            void setModelsVector(std::vector<Renderer::Model*>& data);

        private:
            Window* appWindow = nullptr;
            std::vector<Renderer::Model*> models;
            int selectedModel = 0;
    };
}