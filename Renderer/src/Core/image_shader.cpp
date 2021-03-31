#include <Renderer/image_shader.h>
#include <Renderer/file.h>
#include <Renderer/ImageLoader.h>
#include <iostream>
#include <Renderer/renderer.h>
#include "stb_image.h"

#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

#include "gl_utils.h"
#include "gl_core.h"
#include <map>


using namespace std;

static std::map<std::string, int> texture_map;

ImageShader::ImageShader(std::string path) {
    this->texture = loadImage(path);
}

void ImageShader::activate() {
    if(!mInit) {
        init();
    } 

    glUseProgram(shaderProgram);

    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(shaderProgram, "image"), 0);
    glBindTexture(GL_TEXTURE_2D, texture);

}

void ImageShader::init(){
    mInit = true;
    const char *vertexShaderSource = ReadFile((char *)"assets/shaders/ImageShader/shader.vert");
    const char *fragmentShaderSource = ReadFile((char *)"assets/shaders/ImageShader/shader.frag");

    shaderProgram = buildShaderProgram(vertexShaderSource, fragmentShaderSource);
}
