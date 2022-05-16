#include "debugWindow.h"
#include "window.h"
#include "model.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "utils/log.h"

using namespace Renderer;

debugWindow::debugWindow(Window* pWindow){
    if(!pWindow){
        LOG_ERROR("Window pointer isn't valid!");
        return;
    }
    appWindow = pWindow;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(appWindow->get(), true);
    ImGui_ImplOpenGL3_Init();
}

void debugWindow::update(){
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize.x = appWindow->getWidth();
    io.DisplaySize.y = appWindow->getHeight();
    io.DisplayFramebufferScale.x = 2;
    io.DisplayFramebufferScale.y = 2;
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
    
    //Draw context here
    testWindow();

    //ImGui::ShowDemoWindow();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

debugWindow::~debugWindow(){
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

bool namesGetter(void *vec, int idx, const char** outText){
    const auto* data = (std::vector<Renderer::Model*>*)vec;
    *outText = data->at(idx)->getID().c_str();
    return true;
}

void debugWindow::testWindow(){
    ImGui::Begin("Test Window");
    const char* names[models.size()];
    for(int i = 0; i < models.size(); i++){
        names[i] = models[i]->getID().c_str();
    }
    const char** out;
    //ImGui::ListBox("Models", &selectedModel, namesGetter((void*)&models, (int)models.size(), out));
    ImGui::BeginListBox("ListBox");
    static int selected = 0;
    for(int i = 0; i<models.size(); i++){
        
        ImGui::Selectable(models[i]->getID().c_str(), i==selected);
        if(ImGui::IsItemClicked()){
            selected = i;
        }

    }

    if(models.size()){
        ImGui::Text(models[selected]->getID().c_str());
        auto position = models[selected]->getPosition();
        float pos[] = {position.x, position.y, position.z, 1.0};
        
        ImGui::DragFloat3("Position", pos ,0.01f, -100.f, 100.f, "%.2f");
        models[selected]->setPosition(pos[0], pos[1], pos[2]);

    }

    ImGui::EndListBox();
    ImGui::End();
}

void debugWindow::setModelsVector(std::vector<Renderer::Model*>& data){
    models = data;
}