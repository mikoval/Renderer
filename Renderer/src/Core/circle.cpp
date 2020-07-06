#include <Renderer/circle.h>
#include <iostream>

#include "gl_utils.h"
#include "gl_core.h"

using namespace std;
Circle::Circle(float radius) {
}

void Circle::render() {
    if(!mInit) {
        init();
    }

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Circle::init() {
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

    unsigned int VBO;
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
        0.5f, -0.5f, 0.0f, // right 
        0.0f,  0.5f, 0.0f  // top   
    }; 

    shaderProgram = buildShaderProgram(vertexShaderSource, fragmentShaderSource);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    mInit = true;

}
