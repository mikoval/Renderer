#include <Renderer/triangle.h>
#include <iostream>
#include <Renderer/renderer.h>

#include "gl_utils.h"

using namespace std;
Triangle::Triangle(glm::vec2 a, glm::vec2 b, glm::vec2 c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

void Triangle::render() {
    if(!mInit) {
        init();
    }

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Triangle::init() {
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec2 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
        "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

    unsigned int VBO;
    float vertices[] = {
        0.0f, 0.0f, 
        0.0f, 0.0f,
        0.0f, 0.0f, 
    }; 
    vertices[0] = a.x; vertices[1] = a.y;
    vertices[2] = b.x; vertices[3] = b.y;
    vertices[4] = c.x; vertices[5] = c.y;

    shaderProgram = buildShaderProgram(vertexShaderSource, fragmentShaderSource);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    mInit = true;

}
