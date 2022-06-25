#include "Renderer/window.h"
#include <iostream>
#include "Renderer/shaderProgram.h"
#include "Renderer/texture.h"
#include "Renderer/baseModel.h"
#include "Renderer/light.h"
#include "Renderer/camera.h"
#include "Renderer/debugWindow.h"
#include "utils/log.h"

#include "../external/glm/glm.hpp"
#include "../external/glm/gtc/matrix_transform.hpp"
#include "../external/glm/gtc/type_ptr.hpp"



/*float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};*/

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f

};

GLfloat points[] = {
    -0.5, 0.5, 0.5,
    -0.5, -0.5, 0.5,
    0.5, -0.5, 0.5,
    0.5, 0.5, 0.5,
    -0.5, 0.5, -0.5,
    -0.5, -0.5, -0.5,
    0.5, -0.5, -0.5,
    0.5, 0.5, -0.5
};

GLfloat colors[] = {
    0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f
};

GLfloat textures[] = {
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,

    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.1f,
    1.f, 0.0f

};

GLuint indicies[] = {
    0, 1, 2,
    0, 2, 3,

    4, 5, 6,
    4, 6, 7,

    0, 4, 1,
    4, 1, 5,

    2, 3, 7,
    2, 7, 6,

    0, 4, 3,
    4, 3, 7,

    1, 5, 2,
    5, 2, 6
};

glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};


int main(void)
{
    Renderer::Window window(1280, 720, "Triangle");
    if(!window.init()){
        LOG_ERROR("failed to create window");
        return -1;
    }
    std::vector<std::shared_ptr<Renderer::BaseModel>> modelVector;
    Renderer::Texture myTexture("assets/boxTexture.png");
    Renderer::Texture groundTexture("assets/ground.jpeg");
    
    glClearColor(68.f/255.f, 120.f/255.f, 199.f/255.f, 0);

    //std::string vertexShader(vertex_Shader);
    //std::string fragmentShader(fragment_Shader);
    std::string vertPath = "assets/vert.glsl";
    std::string fragPath = "assets/frag.glsl";
    Renderer::ShaderProgram shaderProgram(vertPath, fragPath);
    if(!shaderProgram.getCompiledStatus()){
        LOG_ERROR("Can't create shader program");
        return -1;
    }

    std::string lightVertPath = "assets/lightVert.glsl";
    std::string lightFragPath = "assets/lightFrag.glsl";
    Renderer::ShaderProgram lightShaderProgram(lightVertPath, lightFragPath);
    if(!lightShaderProgram.getCompiledStatus()){
        LOG_ERROR("Can't create shader program");
        return -1;
    }

    std::vector<float> d;
    for(auto x: vertices){
        d.push_back(x);
    }

    auto plate = std::make_shared<Renderer::BaseModel>("plate");
    plate->init(d, 36);
    plate->setColor(17.f, 122.f, 133.f);
    plate->setScale(100.f, 0.1f, 100.f);
    plate->setPosition(0.f, -5.f, 0.f);
    plate->setTexture(&groundTexture);
    modelVector.push_back(plate);

    
    auto cube = std::make_shared<Renderer::BaseModel>("cube");
    cube->init(d, 36);
    cube->setTexture(&myTexture);
    auto material = Renderer::Material(0, glm::vec3(0.5f, 0.5f, 0.5f), 64.f);
    cube->setMaterial(material);
    modelVector.push_back(cube);
    
    

    //Renderer::Light lightCube("lightSrc");
    auto lightCube = std::make_shared<Renderer::Light>("light");
    lightCube->init(d, 36);
    lightCube->setLight(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.f, 1.f, 1.f));
    lightCube->setPosition(-1.7f,  3.0f, -7.5f);
    lightCube->setScale(0.2f, 0.2f, 0.2f);
    modelVector.push_back(lightCube);


    glm::mat4 view = glm::mat4(1.f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.f), (float)(window.getWidth())/(float)(window.getHeight()), 0.1f, 100.f);
    glEnable(GL_DEPTH_TEST);

    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    Renderer::Camera camera(cameraPos, cameraFront, cameraUp, &window);
   
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    /* Loop until the user closes the window */
    int fpsCap = 60;
    float fpsDelay = (1000.f / fpsCap) / 1000.f;

    Renderer::debugWindow dbWin(&window);
    dbWin.setModelsVector(modelVector);
    dbWin.setLight(lightCube.get());

    while (!window.shouldClose())
    {
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;
        if(deltaTime < fpsDelay){
            continue;
        }
        
        lastFrame = currentTime;
        camera.move(deltaTime);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shaderProgram.use(); 

        glm::vec3 lightColor(1.f, 1.0f, 1.0f);

        shaderProgram.setUniformLocation3f(lightColor, "lightColor");
        auto view = camera.getCameraMatrix();
        shaderProgram.setUniformLocationMat4fv(view, "view");
        shaderProgram.setUniformLocationMat4fv(projection, "projection");
        shaderProgram.setUniformLocation3f(static_cast<Renderer::Light*>(lightCube.get())->getPosition(), "light.position");
        shaderProgram.setUniformLocation3f(static_cast<Renderer::Light*>(lightCube.get())->getAmbient(), "light.ambient");
        shaderProgram.setUniformLocation3f(static_cast<Renderer::Light*>(lightCube.get())->getDiffuse(), "light.diffuse");
        shaderProgram.setUniformLocation3f(static_cast<Renderer::Light*>(lightCube.get())->getSpecular(), "light.specular");

        shaderProgram.setUniformLocation3f(camera.getCameraPosition(), "cameraPos");
        
        for(auto m: modelVector){
            auto l = dynamic_cast<Renderer::Light*>(m.get());
            if(l == nullptr){
                m->draw(&shaderProgram);
            }
        }

        lightShaderProgram.use();
        
        lightShaderProgram.setUniformLocationMat4fv(view, "view");
        lightShaderProgram.setUniformLocationMat4fv(projection, "projection");
        lightCube->draw(&lightShaderProgram);

        dbWin.update();
        /* Swap front and back buffers */
        
        glfwSwapBuffers(window.get());

        /* Poll for and process events */
        glfwPollEvents();
    }

    window.terminate();
    return 0;
}