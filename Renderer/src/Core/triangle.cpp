#include <Renderer/triangle.h>
#include <iostream>
#include <Renderer/renderer.h>

#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

#include "gl_utils.h"

using namespace std;
Triangle::Triangle(glm::vec2 a, glm::vec2 b, glm::vec2 c) {
    this->a = a;
    this->b = b;
    this->c = c;
    mInit = false;
}

void Triangle::render() {
    if(!mInit) {
        init();
    }

    glm::mat4 P = glm::ortho(-600.0f, 600.0f,400.0f,-400.0f, -1.0f, 100.0f);

    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
    model = glm::rotate(model, rotation, glm::vec3(0.0, 0.0, 1.0));
    model = glm::scale(model, glm::vec3(scale, scale, 0.0));
    model = P * model;

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Triangle::init() {
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec2 aPos;\n"
        "uniform mat4 transform;"
        "void main()\n"
        "{\n"
        "   gl_Position = transform * vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
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
