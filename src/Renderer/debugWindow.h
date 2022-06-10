#pragma once
#include <vector>

namespace Renderer{
    class Window;
    class BaseModel;
    class Light;
    class debugWindow{
        public:
            debugWindow(Window* pWindow);
            ~debugWindow();

            void update();
            void testWindow();
            void setModelsVector(std::vector<Renderer::BaseModel*>& data);
            void setLight(Light* l){light = l;};

        private:
            Window* appWindow = nullptr;
            Light* light = nullptr;
            std::vector<Renderer::BaseModel*> models;
            int selectedModel = 0;

    };
}