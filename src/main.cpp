#include "Renderer/window.h"
#include <iostream>
#include "Renderer/shaderProgram.h"

GLfloat points[] = {
    -0.5, -0.5, 0.0,
    -0.5, 0.5, 0.0,
    0.5, 0.5, 0.0,
    0.5, -0.5, 0.0
};

GLfloat colors[] = {
    0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f
};

GLuint indicies[] = {
    0, 1, 2,
    0, 2, 3
};

const char* vertex_Shader = 
"#version 410\n"
"layout(location = 0) in vec3 vertexPosition;\n"
"layout(location = 1) in vec3 vertexColor;\n"
"out vec3 color;"
"void main(){"
"   color = vertexColor;"
"   gl_Position = vec4(vertexPosition, 1.0);"
"}";

const char* fragment_Shader = 
"#version 410\n"
"in vec3 color;"
"out vec4 fragColor;"
"void main(){"
"   fragColor = vec4(color, 1.0);"
"}";

int main(void)
{
    Renderer::Window window(800, 600, "Triangle");
    if(!window.init()){
        std::cerr << "failed to create window" <<std::endl;
        return -1;
    }

    
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


    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    GLuint ibo = 0;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);


    /* Loop until the user closes the window */
    while (!window.shouldClose())
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
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
