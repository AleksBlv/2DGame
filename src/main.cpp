#include "Renderer/window.h"
#include <iostream>
#include "Renderer/shaderProgram.h"
#include "Renderer/texture.h"

#include "../external/glm/glm.hpp"
#include "../external/glm/gtc/matrix_transform.hpp"
#include "../external/glm/gtc/type_ptr.hpp"

//TODO: copy assets folder into the build folder

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


int main(void)
{
    Renderer::Window window(800, 600, "Triangle");
    if(!window.init()){
        std::cerr << "failed to create window" <<std::endl;
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
        std::cerr << "Can't create shader program" <<std::endl;
        return -1;
    }

    GLuint pointsVBO = 0;
    glGenBuffers(1, &pointsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint colorsVBO = 0;
    glGenBuffers(1, &colorsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint texturesVBO = 0;
    glGenBuffers(1, &texturesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, texturesVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textures), textures, GL_STATIC_DRAW);


    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, texturesVBO);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    
    

    GLuint ibo = 0;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0);
    glm::mat4 model = glm::mat4(1.0f);

    //model = glm::rotate(model, glm::radians(0.f), glm::vec3(1.f, 0.f, 0.f));
    //trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
    //trans = glm::translate(trans, glm::vec3(-0.5f, -0.5f, 0.0f));

    glm::mat4 view = glm::mat4(1.f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.f), (float)(window.getWidth()/window.getHeight()), 0.1f, 100.f);
    glEnable(GL_DEPTH_TEST);
    /* Loop until the user closes the window */
    while (!window.shouldClose())
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shaderProgram.use();

        
        model = glm::rotate(model, 0.01f, glm::vec3(1.0f, 1.0f, 0.0f));

        GLuint modelLoc = glGetUniformLocation(shaderProgram.getProgramID(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        GLuint viewLoc = glGetUniformLocation(shaderProgram.getProgramID(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        GLuint projectionLoc = glGetUniformLocation(shaderProgram.getProgramID(), "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


        myTexture.bindTexture(0);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
        //6 is a number of indicies we draw
        //glDrawArrays(GL_TRIANGLES, 0, 6);

        /* Swap front and back buffers */
        glfwSwapBuffers(window.get());

        /* Poll for and process events */
        glfwPollEvents();
    }

    window.terminate();
    return 0;
}
