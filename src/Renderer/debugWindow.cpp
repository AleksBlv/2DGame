#include "debugWindow.h"
#include "window.h"
#include "baseModel.h"
#include "light.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "utils/log.h"
#include "../external/glm/gtc/type_ptr.hpp"

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
    const auto* data = (std::vector<Renderer::BaseModel*>*)vec;
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
    ImGui::EndListBox();
    

    if(models.size()){
        ImGui::Text(models[selected]->getID().c_str());
        bool valueChanged = false;
        auto scale = models[selected]->getScale();
        float sc[] = {scale.x, scale.y, scale.z, 1.0};
        valueChanged |= ImGui::DragFloat3("Scale", sc, 0.1f, -100.f, 100.f, "%.1f");
        

        auto rotation = models[selected]->getRotation();
        float rot[] = {rotation.x, rotation.y, rotation.z};
        valueChanged |= ImGui::DragFloat3("Rotation", rot , 1.f, -180.f, 180.f, "%.1f");


        auto position = models[selected]->getPosition();
        float pos[] = {position.x, position.y, position.z};
        valueChanged |= ImGui::DragFloat3("Position", pos ,0.01f, -100.f, 100.f, "%.2f");

        auto color = models[selected]->getColor();
        float col[] = {color.x , color.y, color.z};
        ImGui::ColorEdit3("Model color", col);
    
        if(valueChanged){
            models[selected]->setScale(sc[0], sc[1], sc[2]);
            models[selected]->setRotation(rot[0], rot[1], rot[2]);
            models[selected]->setPosition(pos[0], pos[1], pos[2]);
        }
        models[selected]->setColor(glm::vec3(col[0], col[1], col[2]));

        

        ImGui::Text("Material properties");
        valueChanged = false;
        auto material = models[selected]->getmaterial();

        auto ambient = material.ambient;
        auto diffuse = material.diffuse;
        auto specular = material.specular;
        auto shininess = material.shininess;
        
        float amb[] = {ambient.x, ambient.y, ambient.z};
        float diff[] = {diffuse.x, diffuse.y, diffuse.z};
        float spec[] = {specular.x, specular.y, specular.z};

        valueChanged |= ImGui::DragFloat3("Ambient", amb ,0.01f, 0.f, 1.f, "%.2f");
        valueChanged |= ImGui::DragFloat3("Diffuse", diff ,0.01f, 0.f, 1.f, "%.2f");
        valueChanged |= ImGui::DragFloat3("Specular", spec ,0.01f, 0.f, 1.f, "%.2f");
        valueChanged |= ImGui::DragFloat("Shininess", &shininess, 1.f, 0.f, 256.f, "%.0f");

        if(valueChanged){
            Material newMaterial(glm::vec3(amb[0], amb[1], amb[2]),
                                glm::vec3(diff[0], diff[1], diff[2]),
                                glm::vec3(spec[0], spec[1], spec[2]),
                                shininess);
            models[selected]->setMaterial(newMaterial);
        }

        valueChanged = false;
        std::vector<const char*> materialNames;
        int index = 0;
        int itemCurrent = 0;
        auto currentMaterial = models[selected]->getMaterialName();
        for(const auto& [key, val]: materialMap){
            materialNames.push_back(key.c_str());
            if(currentMaterial == key){
                itemCurrent = index;
            }
            index++;
        }
        
        valueChanged = ImGui::Combo("Combo", &itemCurrent, materialNames.data(), materialNames.size());
        if(valueChanged){
            models[selected]->setMaterial(materialMap[materialNames[itemCurrent]]);
            models[selected]->setMaterialName(materialNames[itemCurrent]);
        }
    }

    if(light){
        bool valueChanged = false;
        ImGui::Text("Light properties");
        auto ambient = light->getAmbient();
        auto diffuse = light->getDiffuse();
        auto specular = light->getSpecular();
        
        float amb[] = {ambient.x, ambient.y, ambient.z};
        float diff[] = {diffuse.x, diffuse.y, diffuse.z};
        float spec[] = {specular.x, specular.y, specular.z};

        valueChanged |= ImGui::DragFloat3("LAmbient", amb ,0.01f, 0.f, 1.f, "%.2f");
        valueChanged |= ImGui::DragFloat3("LDiffuse", diff ,0.01f, 0.f, 1.f, "%.2f");
        valueChanged |= ImGui::DragFloat3("LSpecular", spec ,0.01f, 0.f, 1.f, "%.2f");

        if(valueChanged){
            light->setLight(glm::vec3(amb[0], amb[1], amb[2]),
                            glm::vec3(diff[0], diff[1], diff[2]),
                            glm::vec3(spec[0], spec[1], spec[2]));
        }
    }


    ImGui::End();

}

void debugWindow::setModelsVector(std::vector<Renderer::BaseModel*>& data){
    models = data;
}