#include <Renderer/rectangle.h>
#include <iostream>
#include <Renderer/renderer.h>

#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

#include "gl_utils.h"
#include "gl_core.h"

using namespace std;
Rectangle::Rectangle(int width, int height) {
    this->scale.x = width;
    this->scale.y = height;
    mInit = false;
}

void Rectangle::render(glm::mat4 mat) {
    if(!mInit) {
        init();
    }

    glm::mat4 P = mat;

    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
    model = glm::rotate(model, rotation, glm::vec3(0.0, 0.0, 1.0));
    model = glm::scale(model, glm::vec3(scale.x, scale.y, 0.0));
    model = P * model;

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));

    unsigned int uv_transformLoc = glGetUniformLocation(shaderProgram, "uv_transform");
    glUniformMatrix4fv(uv_transformLoc, 1, GL_FALSE, glm::value_ptr(UVTransform));

    unsigned int colorLoc = glGetUniformLocation(shaderProgram, "color");
    glUniform4f(colorLoc, color.r, color.g, color.b, color.a);
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(shaderProgram, "image"), 0);
    glBindTexture(GL_TEXTURE_2D, texture);

    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Rectangle::init() {
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec2 aPos;\n"
        "layout (location = 1) in vec2 aUv;\n"
        "uniform mat4 transform;"
        "uniform mat4 uv_transform;"
        "out vec2 vUv;"
        "void main()\n"
        "{\n"
        "   gl_Position = transform * vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
        "   vUv = (uv_transform * vec4(aUv, 0.0, 1.0)).xy;\n"
        "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec2 vUv;\n"
        "uniform vec4 color;"
        "uniform sampler2D image;\n"

        "void main()\n"
        "{\n"
        //"   FragColor =  vec4(vUv, 0.0, 1.0);\n"
        "   FragColor = texture(image, vUv) + color;\n"
        "}\n\0";

    unsigned int VBO_VERTICES;
    unsigned int VBO_UVS;
    unsigned int EBO;

    float vertices[] = {
        0.5f,  0.5f,  // top right
        0.5f, -0.5f,  // bottom right
        -0.5f, -0.5f,  // bottom left
        -0.5f,  0.5f   // top left
    };
    float uvs[] = {
        1.0,  1.0f,  // top right
        1.0f, 0.0f,  // bottom right
        0.0f, 0.0f,  // bottom left
        0.0f, 1.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    shaderProgram = buildShaderProgram(vertexShaderSource, fragmentShaderSource);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO_VERTICES);
    glGenBuffers(1, &VBO_UVS);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_VERTICES);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_UVS);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    mInit = true;


}
