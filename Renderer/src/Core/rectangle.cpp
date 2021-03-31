#include <Renderer/rectangle.h>
#include <iostream>
#include <Renderer/renderer.h>

#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include <glm/gtx/quaternion.hpp>


#include "gl_utils.h"
#include "gl_core.h"

using namespace std;
Rectangle::Rectangle(int width, int height) {
    this->scale.x = width;
    this->scale.y = height;
    mInit = false;
}

void Rectangle::render(Camera *camera) {
    if(!mInit) {
        init();
    }

    glBindVertexArray(VAO);

    setTransforms(camera);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Rectangle::init() {
    unsigned int VBO_VERTICES;
    unsigned int VBO_UVS;
    unsigned int EBO;

    float vertices[] = {
        0.5f,  0.5f, 0,  // top right
        0.5f, -0.5f, 0, // bottom right
        -0.5f, -0.5f,0,  // bottom left
        -0.5f,  0.5f,0,  // top left
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

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO_VERTICES);
    glGenBuffers(1, &VBO_UVS);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_VERTICES);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_UVS);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    mInit = true;


}
