#include <Renderer/color_shader.h>
#include <Renderer/file.h>
#include <iostream>
#include <Renderer/renderer.h>

#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

#include "gl_utils.h"
#include "gl_core.h"

using namespace std;
ColorShader::ColorShader() {
}

ColorShader::ColorShader(float r, float g, float b, float a) {
    this->setColor(r, g, b, a);
}
ColorShader::ColorShader(Color color) {
    this->setColor(color);
}

void ColorShader::setColor(float r, float g, float b, float a) {
    this->color.r = r;
    this->color.g = g;
    this->color.b = b;
    this->color.a = a;
}

void ColorShader::setColor(Color color) {
    this->color = color;
}

void ColorShader::activate() {
    if(!mInit) {
        init();
    } 

    glUseProgram(shaderProgram);

    unsigned int colorLoc = glGetUniformLocation(shaderProgram, "color");
    glUniform4f(colorLoc, color.r, color.g, color.b, color.a);
}

void ColorShader::init(){
    mInit = true;
    const char *vertexShaderSource =  ReadFile((char *)"assets/shaders/ColorShader/shader.vert");
    const char *fragmentShaderSource =  ReadFile((char *)"assets/shaders/ColorShader/shader.frag");
    shaderProgram = buildShaderProgram(vertexShaderSource, fragmentShaderSource);
}
