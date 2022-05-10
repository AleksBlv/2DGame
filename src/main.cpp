#include "Renderer/window.h"
#include <iostream>
#include "Renderer/shaderProgram.h"
#include "Renderer/texture.h"
#include "Renderer/model.h"
#include "Renderer/camera.h"
#include "utils/log.h"

#include "../external/glm/glm.hpp"
#include "../external/glm/gtc/matrix_transform.hpp"
#include "../external/glm/gtc/type_ptr.hpp"

//TODO: copy assets folder into the build folder

float vertices[] = {
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
    Renderer::Window window(800, 600, "Triangle");
    if(!window.init()){
        LOG_ERROR("failed to create window");
        return -1;
    }

    Renderer::Texture myTexture("assets/web_cat.jpeg");
    
    glClearColor(0.5, 0.5, 0.5, 0);

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

    std::vector<std::shared_ptr<Renderer::Model>> models;
    for (int i=0; i<10; i++){
        auto obj = std::make_shared<Renderer::Model>();
        obj->init(d, 36);
        obj->setTexture(&myTexture);
        obj->move(cubePositions[i].x, cubePositions[i].y, cubePositions[i].z);
        models.push_back(obj);
    }

    Renderer::Model cube;
    cube.init(d, 36);

    Renderer::Model lightCube;
    lightCube.init(d, 36);
    lightCube.move(-1.7f,  3.0f, -7.5f);



    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0);
    //glm::mat4 model = glm::mat4(1.0f);

    //model = glm::rotate(model, glm::radians(0.f), glm::vec3(1.f, 0.f, 0.f));
    //trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
    //trans = glm::translate(trans, glm::vec3(-0.5f, -0.5f, 0.0f));

    glm::mat4 view = glm::mat4(1.f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.f), (float)(window.getWidth()/window.getHeight()), 0.1f, 100.f);
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

        glm::vec3 lightColor(1.f, 0.2f, 0.2f);
        GLuint lightColorLoc = glGetUniformLocation(shaderProgram.getProgramID(), "lightColor");
        glUniform3f(lightColorLoc, lightColor.x, lightColor.y, lightColor.z);

        auto view = camera.getCameraMatrix();
        GLuint viewLoc = glGetUniformLocation(shaderProgram.getProgramID(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        GLuint projectionLoc = glGetUniformLocation(shaderProgram.getProgramID(), "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        cube.draw(shaderProgram.getProgramID());

        lightShaderProgram.use();
        


        GLuint viewLocLight = glGetUniformLocation(lightShaderProgram.getProgramID(), "view");
        glUniformMatrix4fv(viewLocLight, 1, GL_FALSE, glm::value_ptr(view));

        GLuint projectionLocLight = glGetUniformLocation(lightShaderProgram.getProgramID(), "projection");
        glUniformMatrix4fv(projectionLocLight, 1, GL_FALSE, glm::value_ptr(projection));

        lightCube.draw(lightShaderProgram.getProgramID());

        // for(auto& model: models){
        //     model->rotate(1.f, 1.f, 1.f, 1.f);
        //     model->draw(shaderProgram.getProgramID());
        // }

        /* Swap front and back buffers */
        glfwSwapBuffers(window.get());

        /* Poll for and process events */
        glfwPollEvents();
    }

    window.terminate();
    return 0;
}
